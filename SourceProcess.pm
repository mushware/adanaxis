#!/usr/bin/perl -w

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2002.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

#
# $Id: SourceProcess.pm,v 1.1 2003/09/17 19:12:13 southa Exp $
# $Log: SourceProcess.pm,v $
# Revision 1.1  2003/09/17 19:12:13  southa
# Created
#
# Revision 1.7  2003/08/21 23:08:16  southa
# Fixed file headers
#
# Revision 1.6  2002/12/29 20:59:49  southa
# More build fixes
#
# Revision 1.4  2002/12/20 13:17:30  southa
# Namespace changes, licence changes and source conditioning
#
# Revision 1.3  2002/10/20 17:57:43  southa
# Preparation for 0.1.0
#
# Revision 1.2  2002/06/27 12:36:01  southa
# Build process fixes
#
# Revision 1.1  2002/06/27 09:41:40  southa
# Created
#
#

package SourceProcess;

use DirHandle;
use Digest::MD5;
use Getopt::Long;

use strict;

my %gConfig = (
'ENTRIES_FILENAME' => 'Entries.txt',
'COMMENT_START' => '//',
'AUTO_PREFIX' => '%',
'START_SUFFIX' => ' {',
'END_SUFFIX' => ' }',
'DIGEST_SEED' => '&3jdYHkjd02aP{iuI'
);

my %gContext;

my @gProcessors = (
#    '.cpp$', \&ProcessCPPFile,
#    '.h$', \&ProcessHFile
);

my $gReal=1;
my $gVerbose=0;
my %gEntries = ();

GetOptions(
'real=i' => \$gReal,
'verbose' => \$gVerbose
);

sub AddArrayProcessor($$)
{
    my ($expression, $processor) = @_;
    push @gProcessors, $expression, $processor;
}

sub GetContext()
{
    my $context = '';
    $context .= $gContext{PATH}.'/' if defined($gContext{PATH});
    
    if (defined($gContext{FILE}))
    {
        $context .= "$gContext{FILE} ";
    }
    $context .= "#$gContext{LINE} " if defined($gContext{LINE});    
    $context .= 'modified '.localtime($gContext{TIMESTAMP}).' ' if defined($gContext{TIMESTAMP});
    $context;
}

sub ProcessDirectory($)
{
    my $prefix=shift;
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
                ProcessDirectory("$filename");
            }
        }
        elsif ( -f $filename )
        {
            my $timestamp = FileTimestampGet($filename);

            $gContext{TIMESTAMP} = $timestamp;

            my $storedTimestamp = FileEntryGet($filename);
            
            if (defined($storedTimestamp) &&
                $storedTimestamp == $timestamp)
            {
                print "File $filename up to date\n" if ($gVerbose);
            }
            else
            {
                my $processed = 0;
                my @contents;
                my @origContents;
                       
                for (my $i=0; $i < @gProcessors; $i += 2)
                {
                    if ($filename =~ /$gProcessors[$i]/)
                    {
                        unless ($processed)
                        {
                            ReadFile(\@contents, $filename);
                            foreach (@contents)
                            {
                                push @origContents, $_;
                                s/\012//g;
                                s/\015//g;        
                            }
                        }
                        $gProcessors[$i+1](\@contents, $filename);
                        $processed = 1;
                    }
                }
                if ($processed)
                {
                    unless (CompareArrays(\@contents, \@origContents))
                    {
                        WriteFile(\@contents, $filename);
                    }
                    else
                    {
                        print "No modifications to $filename\n" if $gVerbose;
                    }
                    $timestamp = FileTimestampGet($filename);
                    FileEntrySet($filename, $timestamp);
                }
                else
                {
                    print "Ignoring file $filename\n" if ($gVerbose);
                }
            }
        }
    }
    print "Leaving directory $prefix\n" if ($gVerbose);
}

sub Process($)
{
    my ($dirname) = @_;
    FileEntriesLoad($gConfig{ENTRIES_FILENAME});
    ProcessDirectory($dirname);
    FileEntriesSave($gConfig{ENTRIES_FILENAME});
    print "Done.\n";
}

sub CompareArrays($$)
{
    my ($array1Ref, $array2Ref) = @_;
    
    if (@$array1Ref != @$array2Ref)
    {
        return 0;    
    }
    for (my $i=0; $i < scalar @$array1Ref; ++$i)
    {
        if ($$array1Ref[$i] ne $$array2Ref[$i])
        {
            return 0;
        }
    }
    return 1;
}

sub ReadFile($$)
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

sub WriteFile($$)
{
    my ($contentRef, $filename) = @_;

    print "Writing modified file $filename\n" if $gVerbose;

    if ($gReal)
    {
        open(FILE, ">$filename") or die "File open for write failed for $filename: $!";
        foreach (@$contentRef)
        {
            print FILE "$_\n";
        }
        close FILE;
    }
    else
    {    
        foreach (@$contentRef)
        {
            print "$_\n";
        }
    }
}

sub ProcessCPPFile($$)
{
    my ($contentRef, $filename) = @_;

    my @origcontents=();

    print "Processing CPP file $filename\n" if ($gVerbose);

    # CheckHeader(\@$contentRef, $filename, \@gCHeaders);
    ReorderIncludeFiles(\@$contentRef, $filename);
    AddUsingNamespace(\@$contentRef, $filename);

    if (!CompareArrays(\@$contentRef, \@origcontents))
    {
        print "Writing modified file $filename\n";
        WriteFile(\@$contentRef, $filename);
    }
}
    
sub ProcessHFile($$)
{
    my ($contentRef, $filename) = @_;
    print "Processing H file $filename\n" if ($gVerbose);
    open(FILE, $filename) or die "File open for read failed for $filename: $!";

    my @origcontents=();

    foreach (@$contentRef)
    {
        push @origcontents, $_;
    }
    
    # CheckHeader(\@$contentRef, $filename, \@gCHeaders);
    # CheckIncludeGuards(\@$contentRef, $filename);
    ReorderIncludeFiles(\@$contentRef, $filename);
    AddHeaderNamespace(\@$contentRef);
    
    if (!CompareArrays(\@$contentRef, \@origcontents))
    {
        print "Writing modified file $filename\n";
        WriteFile(\@$contentRef, $filename);
    }
}


sub ReorderIncludeFiles
{
    # Reorder each contiguous block of #includes in alphabetical order
    my $arrayRef=shift;
    my $filename=shift;
    my $cppCounterpart = $filename;
    $cppCounterpart =~ /\/([^\/]+)$/;
    $cppCounterpart = $1;
    $cppCounterpart =~ s/\.cpp$/\.h/;
    my %includeHash;
    my $line=0;
    my $includeLine = $line;
    foreach (@$arrayRef)
    {
        $line++;
        if (/^\s*\#include\s+"([^"]+)"/)
        {
            $includeHash{$1} = $_;
        }
        else
        {
            if (scalar keys %includeHash > 0)
            {
                if (defined($includeHash{$cppCounterpart}))
                {
                    splice @$arrayRef, $includeLine, 1, $includeHash{$cppCounterpart};
                    $includeLine++;
                    delete $includeHash{$cppCounterpart};
                }
                foreach my $include (sort keys %includeHash)
                {
                    splice @$arrayRef, $includeLine, 1, $includeHash{$include};
                    $includeLine++;
                }
                %includeHash = ();
            }
            $includeLine=$line;
        }
    }
    print "Reordered include blocks\n" if ($gVerbose);
}

sub AddHeaderNamespace
{
    my $arrayRef=shift;
    my @stdnames = ("ostream", "istream", "vector", "list", "map", "string", "auto_ptr", "stack");
    my @mushnames = ("U32", "S32", "U16", "S16", "U8", "S8", "tVal", "u8istream");
    foreach my $line (@$arrayRef)
    {
        foreach (@stdnames)
        {
            $line =~ s/([^:\w<])$_([^\w>;])/$1std::$_$2/g;
        }
        foreach (@mushnames)
        {
            $line =~ s/([^:\w<])$_([^\w>;])/$1Mushware::$_$2/g;
        }
        $line =~ s/([^:\w<])tSize([^\w>;])/$1Mushware::U32$2/g;        
    }
    print "Added scope resolution to headers\n" if ($gVerbose);
}

sub AddUsingNamespace
{
    my $arrayRef=shift;
    my $filename=shift;
    
    my $line=0;
    my $usingMushLine = 0;
    my $usingStdLine = 0;
    my $lastIncludeLine = 0;

    foreach (@$arrayRef)
    {
        $line++;
        if (/^\s*\#include/)
        {
            $lastIncludeLine = $line;
        }
        if (/^\s*using\s+namespace\s+(Mushware|Mustl)/)
        {
            $usingMushLine = $line;
        }
        if (/^\s*using\s+namespace\s+std/)
        {
            $usingStdLine = $line;
        }
    }
    if ($lastIncludeLine != 0)
    {
        if ($usingStdLine == 0)
        {
            if ($usingMushLine == 0)
            {
                splice @$arrayRef, $lastIncludeLine, 0, ("using namespace std;");
            }
            else
            {
                splice @$arrayRef, $usingMushLine, 0, ("using namespace std;");
            }            
        }
        if ($usingMushLine == 0)
        {
            splice @$arrayRef, $lastIncludeLine, 0, ("", "using namespace Mushware;");
        }
        print "Added using namespace lines\n" if ($gVerbose);
    }
}

sub FileEntriesLoad
{
    my $filename = shift;
    print "Reading entries from $filename\n" if $gVerbose;
    if (open(FILE, $filename))
    {
        while (<FILE>)
        {
            unless (/^"([^"]+)"\s+"([^"]+)"$/)
            {
                die "Corrupt $filename : '$_'";
            }
            $gEntries{$1} = $2;
        }
        close FILE;
    }
    else
    {
        print "File open for read failed for $filename: $!\n" if $gVerbose;
    }
}

sub FileEntriesSave
{
    my $filename = shift;
    print "Writing entries to $filename\n" if $gVerbose;
    open(FILE, ">$filename") or die "File open for write failed for $filename: $!";
    foreach (sort keys %gEntries)
    {
        print FILE '"',$_,'" "',$gEntries{$_},'"',"\n";
    }
    close FILE;
}

sub FileEntrySet
{
    my $filename = shift;
    my $timestamp = shift;
    $gEntries{$filename} = $timestamp;
}

sub FileEntryGet
{
    my $filename = shift;
    $gEntries{$filename};
}

sub FileTimestampGet()
{
    my $filename = shift;
    my $timestamp;
    
    if ( -f $filename )
    {
        $timestamp = (stat($filename))[9];
    }
    $timestamp;
}

sub BlockIdMake
{
    my ($type) = @_;
    $gConfig{AUTO_PREFIX}.$type;
}

sub BlockStartMake($)
{
    my ($blockId) = @_;
    "$gConfig{'COMMENT_START'}".$blockId."$gConfig{'START_SUFFIX'}";
}

sub BlockEndMake($)
{
    my ($blockId) = @_;
    "$gConfig{'COMMENT_START'}".$blockId."$gConfig{'END_SUFFIX'}";
}

sub BlockReplace($$$$)
{
    my ($arrayRef, $contentRef, $blockName, $suggestedLine) = @_;
    my $lineNum = 0;
    my $startLine = $suggestedLine;
    my $endLine = 0;
    my $started = 0;
    my $ended = 0;
    my $digest = new Digest::MD5;
    my $checksum = "";
    my $blockId = BlockIdMake($blockName);

    # Match base64 checksum
    my $startExpression = '^\s*'.quotemeta(BlockStartMake($blockId));
    my $endExpression = '^\s*'.quotemeta(BlockEndMake($blockId)).'\s*([0-9a-zA-Z+/]*)';

    $digest->add($gConfig{DIGEST_SEED});

    foreach my $line (@$arrayRef)
    {
        chomp $line;
        if ($line =~ /$endExpression/)
        {
            $checksum = $1;
            $endLine = $lineNum;
            $ended = 1;
        }
        
        if ($started && !$ended)
        {
            $digest->add($line);
        }
        
        if ($line =~ /$startExpression/)
        {
            $startLine = $lineNum;
            $started = 1;
        }

        ++$lineNum;
    }
    
    $gContext{LINE} = $startLine;
    
    my $blockMD5 = $digest->b64digest();
    my $replace = 1;
    
    if ($checksum ne "" && $checksum ne $blockMD5)
    {
        $replace = QueryReplace($blockId);
    }

    if ($replace)
    {
        $digest->reset();
        $digest->add($gConfig{DIGEST_SEED});
        foreach (@$contentRef)
        {
            $digest->add($_);
        }
        
        my $newMD5 = $digest->b64digest();
    
        if ($started && $ended)
        {
            # Remove previous block
            print "Removed block $startLine to $endLine\n" if $gVerbose;
            splice @$arrayRef, $startLine, $endLine - $startLine + 1;
        }
        if (scalar @$contentRef > 0)
        {
            splice @$arrayRef, $startLine, 0, (BlockStartMake($blockId), @$contentRef, BlockEndMake($blockId)." $newMD5");
        }
    }
}

sub QueryReplace($)
{
    print "At ", GetContext(), ":\nBlock ", shift, " has been altered.  Not replacing\n";
    0;
}


1;
