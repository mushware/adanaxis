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
# $Id$
# $Log$

use DirHandle;
use Getopt::Long;
use Cwd;

use strict;

use constant TARGETTYPE_NONE => 1;
use constant TARGETTYPE_PROGRAM => 2;
use constant TARGETTYPE_LIBRARY => 3;

my $gVerbose=1;
my $gTargetDirectory='targets';
my $gTarget;
my $gTargetType = TARGETTYPE_NONE;

my %gConfig;
my %gContext;

%gConfig =
(
    'SRC' => 'src'
);

sub ProcessDirectory($);

sub FilenamesGet($$$)
{
    my ($outputRef, $prefix, $regExp) = @_;
    print "Entering directory $prefix\n" if ($gVerbose);
    
    my $handle = new DirHandle;
    
    $handle->open($prefix) or die "Couldn't open $prefix: $!";
    
    while (defined(my $suffix = $handle->read()))
    {
        %gContext = ();
        $gContext{FILE} = $suffix;
        $gContext{PATH} = $prefix;
        
        my $filename="$prefix/$suffix";
        if ( -d $filename )
        {
            if (substr($suffix,0,1) ne "." && $suffix ne "CVS")
            {
                ProcessDirectory($filename);
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
    print "Leaving directory $prefix\n" if ($gVerbose);
}

sub Use($$)
{
    my ($source, $target) = @_;
    print "Using $source as $target\n" if ($gVerbose);
    system("cp -f $source $target");
}

sub Modules($$)
{
    my ($outputRef, $modules) = @_;

    my $entryDir = getcwd();
    chdir $gConfig{'SRC'};
    
    my @sourceFiles;
    my @headerFiles;
    
    foreach my $moduleName (split(' ', $modules))
    {
        unless( $moduleName =~ /^\s*$/) # Ignore whitespace-only
        {
            print "Adding module '$moduleName'\n" if ($gVerbose);
            unless ( -d $moduleName )
            {
                die "No module named '$moduleName' (no directory '$gConfig{'SRC'}/$moduleName')";
            }
            
            FilenamesGet(\@sourceFiles, $moduleName, '/.*\.cpp');
            FilenamesGet(\@headerFiles, $moduleName, '/.*\.h');
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
            "lib$gConfig{'LIBRARY'}_la_SOURCES=".join(' ', @sourceFiles).join(' ', @headerFiles),
            'library_includedir=$(includedir)/'."$gConfig{'NAME'}",
            'library_include_HEADERS='.join(' ', @headerFiles);
    }
    elsif ($gTargetType == TARGETTYPE_PROGRAM)
    {
        push @$outputRef,
        "bin_PROGRAMS=$gConfig{'PROGRAM'}",
        "$gConfig{'PROGRAM'}_SOURCES=".join(' ', @sourceFiles).join(' ', @headerFiles);        
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
    
    print "Writing modified file $filename\n" if $gVerbose;
        
    open(FILE, ">$filename") or die "File open for write failed for $filename: $!";
    
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
    my $outputFilename;
    
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
        elsif ($command =~ /Create:/)
        {
            if ($command =~ /Create:\s*(\S+)\s*$/)
            {
                $outputFilename = $1;
            }
            else
            {
                die "Malformed command '$command'";
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
    print "Done...\n";
}

Main();
