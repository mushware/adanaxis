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
# $Id: autogen.pl,v 1.2 2004/01/06 20:46:48 southa Exp $
# $Log: autogen.pl,v $
# Revision 1.2  2004/01/06 20:46:48  southa
# Build fixes
#
# Revision 1.1  2003/12/31 15:46:55  southa
# Created
#

use DirHandle;
use Getopt::Long;
use Cwd;

use strict;

use constant TARGETTYPE_NONE => 1;
use constant TARGETTYPE_PROGRAM => 2;
use constant TARGETTYPE_LIBRARY => 3;
use constant TARGETTYPE_EXTRADIST => 4;

my $gVerbose=0;
my $gTargetDirectory='targets';
my $gTarget;
my $gTargetType = TARGETTYPE_NONE;

my %gConfig;
my %gContext;

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
            if ($filename =~ $regExp)
            {
                push @$outputRef, $filename;
            }
        }
    }
    print "Leaving directory $dir\n" if ($gVerbose);
}

sub Use($$)
{
    my ($source, $target) = @_;
    print "Using $source as $target\n" if ($gVerbose);
    if (system("cp -f $source $target") != 0)
    {
        die "File copy '$source'->'$target' failed";
    }
}

sub Modules($$)
{
    my ($outputRef, $modules) = @_;

    my $entryDir = getcwd();
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
            
            if ($moduleExp =~ /\*/)
            {
                # Modulename has wildcards
                $searchExp = $moduleExp;
            }
            elsif ($modulePath eq "" && -f $moduleName )
            {
                # Module is a single file
                $searchExp = quotemeta $moduleExp;
            }
            elsif ( -f "$modulePath/$moduleName" )
            {
                # Module is a single file
                $searchExp = quotemeta $moduleExp;
            }
            # print "modulePath=$modulePath, moduleExp=$moduleExp, searchExp=$searchExp\n";
            unless ( $modulePath eq "" || -d $modulePath )
            {
                die "No module named '$moduleName' (no directory '$gConfig{'PATH'}/$modulePath')";
            }
            
            if ($searchExp ne "")
            {
                FilenamesGet(\@sourceFiles, $modulePath, "$searchExp", $recurse);
            }
            else
            {
                FilenamesGet(\@sourceFiles, $modulePath, '/.*\.cpp', $recurse);
                FilenamesGet(\@headerFiles, $modulePath, '/.*\.h', $recurse);
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
        "EXTRA_DIST=".join(' ', @sourceFiles).' '.join(' ', @headerFiles);        
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
            if ($command =~ /Name:\s*(\S+)\s*$/)
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
    print "Configuring for target '$gTarget'\n";
    
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
    print "Done.\n";
}

Main();
