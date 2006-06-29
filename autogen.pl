#!/usr/bin/perl -w
##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2002-2003.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
# $Id: autogen.pl,v 1.11 2006/06/22 19:07:24 southa Exp $
# $Log: autogen.pl,v $
# Revision 1.11  2006/06/22 19:07:24  southa
# Build fixes
#
# Revision 1.10  2005/06/08 20:59:50  southa
# X11 release
#
# Revision 1.9  2005/06/04 13:45:11  southa
# Release 0.1.2 tweaks
#
# Revision 1.8  2005/05/27 19:25:23  southa
# win32 build fixes
#
# Revision 1.7  2005/05/26 16:05:28  southa
# win32 support
#
# Revision 1.6  2005/05/19 13:01:55  southa
# Mac release work
#
# Revision 1.5  2005/03/13 00:34:44  southa
# Build fixes, key support and stereo
#
# Revision 1.4  2004/01/07 13:22:47  southa
# Snapshot fixes
#
# Revision 1.3  2004/01/07 11:14:15  southa
# Snapshot fixes
#
# Revision 1.2  2004/01/06 20:46:48  southa
# Build fixes
#
# Revision 1.1  2003/12/31 15:46:55  southa
# Created
#

use DirHandle;
use Getopt::Long;
require Cwd;

use strict;

use constant TARGETTYPE_NONE => 1;
use constant TARGETTYPE_PROGRAM => 2;
use constant TARGETTYPE_LIBRARY => 3;
use constant TARGETTYPE_EXTRADIST => 4;
use constant TARGETTYPE_PKGDATA => 5;
use constant TARGETTYPE_MANUAL => 6;

my $gVerbose=0;
my $gTargetDirectory='targets';
my $gTarget;
my $gTargetType = TARGETTYPE_NONE;

my %gConfig;
my %gContext;
my %gVars;

%gConfig =
(
);

sub FilenamesGet($$$$);
sub FilenamesGet($$$$)
{
    my ($outputRef, $prefix, $regExp, $recurse) = @_;
    
    my $handle = new DirHandle;
    
    my $dir = $prefix;
    $dir = "." if $dir eq "";

    print "Entering directory $dir\n" if ($gVerbose);
    
    $handle->open($dir) or die "Couldn't open $prefix: $!";
    
    while (defined(my $suffix = $handle->read()))
    {
        %gContext = ();
        $gContext{FILE} = $suffix;
        $gContext{PATH} = $prefix;
        
        my $filename="$prefix/$suffix";
        $filename = $suffix if $prefix eq "";
        
        if ( -d $filename )
        {
            if (substr($suffix,0,1) ne "." && $suffix ne "CVS")
            {
                FilenamesGet($outputRef, $filename, $regExp, $recurse) if $recurse;
            }
        }
        elsif ( -f $filename )
        {
            if ($filename =~ /~$/ || $suffix =~ /^\./)
            {
                # Discard
            }
            elsif ($filename =~ $regExp)
            {
                push @$outputRef, $filename;
            }
        }
    }
    print "Leaving directory $dir\n" if ($gVerbose);
}

sub Substitute($)
{
    my ($line) = @_;
    foreach my $varExp (keys %gVars)
    {
        $line =~ s/$varExp/$gVars{$varExp}/g;
    }
    return $line;
}

sub Use($$)
{
    my ($source, $target) = @_;
    print "Using $source as $target\n" if ($gVerbose);
    open INUSE, $source or die "Couldn't open '$source': $!";
    open OUTUSE, ">$target" or die "Couldn't open '$target': $!";
    
    while (<INUSE>)
    {
        print OUTUSE Substitute($_);
    }
}

sub Modules($$)
{
    my ($outputRef, $modules) = @_;

    my $entryDir = Cwd::getcwd();
    chdir $gConfig{'PATH'};
    
    my @sourceFiles;
    my @headerFiles;
    
    foreach my $moduleName (split(' ', $modules))
    {
        unless ($moduleName =~ /^\s*$/) # Ignore whitespace-only
        {
            print "Adding module '$moduleName'\n" if ($gVerbose);
            
            my $recurse = 0;
            if ($moduleName =~ s/^\+//)
            {
                $recurse = 1;
            }

            my $modulePath = $moduleName;
            my $moduleExp = $moduleName;
            
            if ( -d $modulePath )
            {
                # Module is directory
                $moduleExp = "";
            }
            elsif ($modulePath =~ /\//)
            {
                # Slash(es) present so split the path
                $modulePath =~ s/\/([^\/]+)$//;
                $moduleExp = $1;
            }
            else
            {
                # No slashes so use current directory
                $modulePath = "";
                # Leave $moduleExp as is
            }

            my $searchExp = "";
            
            if ($moduleExp =~ /[*+?|]/)
            {
                # Modulename has wildcards
                $searchExp = $moduleExp;
	        print "Wildcarded expression\n" if ($gVerbose);
            }
            elsif ($modulePath eq "" && -f $moduleExp )
            {
                # Module is a single file
                $searchExp = quotemeta $moduleExp;
	            print "Single file without path\n" if ($gVerbose);
            }
            elsif ( -f "$modulePath/$moduleExp" )
            {
                # Module is a single file
                $searchExp = quotemeta $moduleExp;
                print "Single file with path '$modulePath'\n" if ($gVerbose);
            }
            else
            {
                print "Directory '$modulePath'\n" if ($gVerbose);
                if ($moduleExp ne "")
                {
                    die "No file named '$moduleName'";
                }
            }
            # print "modulePath=$modulePath, moduleExp=$moduleExp, searchExp=$searchExp\n";
            unless ( $modulePath eq "" || -d $modulePath )
            {
                die "No module named '$moduleName' (no directory '$gConfig{'PATH'}/$modulePath')";
            }
            
            if ($searchExp ne "")
            {
	            print "Searching in '$modulePath' using expression '$searchExp'\n" if ($gVerbose);

                FilenamesGet(\@sourceFiles, $modulePath, "$searchExp", $recurse);
            }
            else
            {
                if ($gTargetType == TARGETTYPE_LIBRARY ||
                $gTargetType == TARGETTYPE_PROGRAM)
				{
						print "Source searching in '$modulePath'\n" if ($gVerbose);
						FilenamesGet(\@sourceFiles, $modulePath, '/.*\.cpp\b', $recurse);
						FilenamesGet(\@sourceFiles, $modulePath, '/.*\.c\b', $recurse);
							FilenamesGet(\@headerFiles, $modulePath, '/.*\.h\b', $recurse);
				}
				else
				{
						print "Wide searching in '$modulePath'\n" if ($gVerbose);
					FilenamesGet(\@sourceFiles, $modulePath, '/.*', $recurse);
				}
            }
            if ($gVerbose)
            {
                print "Source files: ", join(' ', @sourceFiles), "\n";
                print "Header files: ", join(' ', @headerFiles), "\n";
            }
            warn "Empty module '$moduleName'" if (@sourceFiles == 0 && @headerFiles == 0);
        }
    }
    chdir $entryDir;
    
# Now have filelists
    if ($gTargetType == TARGETTYPE_LIBRARY)
    {
        push @$outputRef,
            "lib_LTLIBRARIES=lib$gConfig{'LIBRARY'}.la",
            "lib$gConfig{'LIBRARY'}_la_SOURCES=".join(' ', @sourceFiles).' '.join(' ', @headerFiles),
            'library_includedir=$(includedir)/'."$gConfig{'NAME'}",
            'library_include_HEADERS='.join(' ', @headerFiles);
    }
    elsif ($gTargetType == TARGETTYPE_PROGRAM)
    {
        push @$outputRef,
        "bin_PROGRAMS=$gConfig{'PROGRAM'}",
        "$gConfig{'PROGRAM'}_SOURCES=".join(' ', @sourceFiles).' '.join(' ', @headerFiles);        
    }
    elsif ($gTargetType == TARGETTYPE_EXTRADIST)
    {
        push @$outputRef,
        "EXTRA_DIST=".join(" ", @sourceFiles)." ".join(" ", @headerFiles);        
    }
    elsif ($gTargetType == TARGETTYPE_PKGDATA)
    {
        push @$outputRef,
        "nobase_dist_pkgdata_DATA=".join(" ", @sourceFiles)." ".join(" ", @headerFiles);
    }
    elsif ($gTargetType == TARGETTYPE_MANUAL)
    {
        push @$outputRef,
        "dist_man_MANS=".join(" ", @sourceFiles)." ".join(" ", @headerFiles);
    }
    else
    {
        die "No target specified (Program: or Library:) when Modules: command issued";
    }
}    

sub FileRead($$)
{
    my ($contentRef, $filename) = @_;
    
    print "Reading file $filename\n" if $gVerbose;
        
        open(FILE, $filename) or die "File open for read failed for $filename: $!";
    
    while (<FILE>)
    {
        push(@$contentRef, $_);
    }
    close FILE;
}

sub FileWrite($$)
{
    my ($contentRef, $filename) = @_;
    
    print "Writing file $filename\n" if $gVerbose;
        
    open(FILE, ">>$filename") or die "File open for write failed for $filename: $!";
    
    foreach (@$contentRef)
    {
        print FILE $_, "\n";
    }
    close FILE;
}

sub Process($)
{
    my ($contentRef) = @_;

    my @output;
    my $outputFilename="";
    
    foreach my $command (@$contentRef)
    {
        chomp $command;
        $command =~ s/#.*//; # Remove comments
            
        if ($command =~ /^\s*$/)
        {
            # skip blank line   
        }
        elsif ($command =~ /Use:/)
        {
            if ($command =~ /Use:\s*(\S+)\s+as\s+(\S+)\s*$/)
            {
                Use($1, $2);
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Name:/)
        {
            if ($command =~ /Name:\s*'([^']+)'\s*$/)
            {
                $gConfig{'NAME'} = $1;
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /(Create|Append):/)
        {
            if ($outputFilename ne "")
            {
                FileWrite(\@output, $outputFilename);
                @output=();
            }
            if ($command =~ /(Create|Append):\s*(\S+)\s*$/)
            {
                $outputFilename = $2;
                $gConfig{'PATH'} = $outputFilename;
                unless ($gConfig{'PATH'} =~ s/\/.*$//)
                {
                    $gConfig{'PATH'} = ".";
                }
            }
            else
            {
                die "Malformed command '$command'";
            }
            if ($command =~ /Create:/)
            {
                unlink $outputFilename;
            }
        }
        elsif ($command =~ /Library:/)
        {
            if ($command =~ /Library:\s*(\S+)\s*$/)
            {
                $gTargetType = TARGETTYPE_LIBRARY;
                $gConfig{'LIBRARY'} = $1;
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Program:/)
        {
            if ($command =~ /Program:\s*(\S+)\s*$/)
            {
                $gTargetType = TARGETTYPE_PROGRAM;
                $gConfig{'PROGRAM'} = $1;   
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /ExtraDist:/)
        {
            if ($command =~ /ExtraDist:\s*$/)
            {
                $gTargetType = TARGETTYPE_EXTRADIST;   
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /PkgData:/)
        {
            if ($command =~ /PkgData:\s*$/)
            {
                $gTargetType = TARGETTYPE_PKGDATA;   
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Manual:/)
        {
            if ($command =~ /Manual:\s*$/)
            {
                $gTargetType = TARGETTYPE_MANUAL;   
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Modules:/)
        {
            if ($command =~ /Modules:\s*(.*)$/)
            {   
                Modules(\@output, $1);
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Output:/)
        {
            if ($command =~ /Output:\s*(.*)$/)
            {   
                push @output, $1;
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Test:/)
        {
            if ($command =~ /Test:\s*$/)
            {   
                push @output,
                '',
                'test: test_@PACKAGE@',
                '	@echo',
                '	@echo Launching test application...',
                '	@echo',
                '	./test_@PACKAGE@';
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        elsif ($command =~ /Subst:/)
        {
            if ($command =~ /Subst:\s*(\w+)\s+'([^']*)'$/)
            {   
                $gVars{$1} = Substitute($2);
                print "Subst varaible $1 = $gVars{$1}\n" if $gVerbose;
            }
            else
            {
                die "Malformed command '$command'";
            }
        }
        else
        {
            die "Unknown command '$command'";
        }
    }
    
    if ($outputFilename ne "")
    {
        FileWrite(\@output, $outputFilename);
    }
}

sub UsagePrint()
{
    print <<EOT;
Usage: $0 [options] <target name>
    
Autogenerates configuration files for the specified target
    
--help                  Print this text
--verbose               Verbose
--targetdir=<directory> Search that directory for targets 

List of available targets:
EOT
    system("ls -1 $gTargetDirectory/*.def");
}

sub Main()
{
    my $help;
    GetOptions(
               'help' => \$help,
               'verbose' => \$gVerbose,
               'targetdir=s' => \$gTargetDirectory
               );

    if ($help || @ARGV != 1)
    {
        UsagePrint();
        return 1;
    }
    $gTarget=$ARGV[0];
    
    die "Try without the '.def'" if ($gTarget =~ /\.def$/);
    
    my $targetFilename = "$gTargetDirectory/$gTarget.def";
    unless ( -f $targetFilename )
    {
        die "No target named $gTarget (No file named '$targetFilename')";
    }
    print "Configuring for target '$gTarget'...\n";
    
    my @configFile;
    
    FileRead(\@configFile, $targetFilename);
    Process(\@configFile);
    foreach my $command('aclocal', 'autoheader', 'automake', 'autoconf')
    {
        print "Running $command...\n" if ($gVerbose);
        if (system($command) != 0)
        {
            die "Command '$command' failed";
        }
    }

    foreach my $command('chmod +x install-sh')
    {
        print "Running $command...\n" if ($gVerbose);
        if (system($command) != 0)
        {
            warn "Command '$command' failed";
        }
    }

    print "Done.\n";
}

Main();
