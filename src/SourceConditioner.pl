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
# $Id: SourceConditioner.pl,v 1.3 2002/10/20 17:57:43 southa Exp $
# $Log: SourceConditioner.pl,v $
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

use DirHandle;

use strict;

my @standardHeader=(
"/*****************************************************************************",
" *",
" * (Mushware file header version 1.2)",
" *",
" * This file contains original work by Andy Southgate.",
" * Copyright Andy Southgate 2002.  All rights reserved.",
" * Contact details can be found at http://www.mushware.com/",
" *",
" ****************************************************************************/",
""
);

my $headerMarker="Mushware file header version";
my $real=1;
my $verbose=0;

ProcessDirectory(".");
print "Done.\n";

sub ProcessDirectory
{
    my $prefix=shift;
    print "Entering directory $prefix\n" if ($verbose);
    
    my $handle = new DirHandle;
    
    $handle->open($prefix) or die "Couldn't open $prefix: $!";
    
    while (defined(my $suffix = $handle->read()))
    {
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
            if ($filename =~ /\.cpp$/)
            {	
                ProcessCPPFile($filename);
            }
            elsif ($filename =~ /\.h$/)
            {
                ProcessHFile($filename);
            }
            else
            {
                print "Ignoring file $filename\n" if ($verbose);
            }
        }
    }
    print "Leaving directory $prefix\n" if ($verbose);
}

sub CompareArrays
{
    my $array1ref=shift;
    my $array2ref=shift;
    
    if (@$array1ref != @$array2ref)
    {
        return 0;    
    }
    for (my $i=0; $i < scalar @$array1ref; ++$i)
    {
        if ($$array1ref[$i] ne $$array2ref[$i])
        {
            return 0;
        }
    }
    return 1;
}

sub ProcessCPPFile
{
    my $filename=shift;
    print "Processing CPP file $filename\n" if ($verbose);
    open(FILE, $filename) or die "File open for read failed for $filename: $!";
    my @contents=();
    my @origcontents=();
    while (<FILE>)
    {
        s/\012//g;
        s/\015//g;        
        push(@contents, $_);
        push(@origcontents, $_);
    }
    close FILE;
    CheckHeader(\@contents);
    ReorderIncludeFiles(\@contents, $filename);
    AddUsingNamespace(\@contents, $filename);

    if (!CompareArrays(\@contents, \@origcontents))
    {
        print "Writing modified file $filename\n";
        if ($real)
        {
            open(FILE, ">$filename") or die "File open for write failed for $filename: $!";
            foreach (@contents)
            {
                print FILE "$_\n";
            }
            close FILE;
        }
        else
        {    
            foreach (@contents)
            {
                print "$_\n";
            }
        }
    }
}
    
sub ProcessHFile
{
    my $filename=shift;
    print "Processing H file $filename\n" if ($verbose);
    open(FILE, $filename) or die "File open for read failed for $filename: $!";
    my @contents=();
    my @origcontents=();
    while (<FILE>)
    {
        s/\012//g;
        s/\015//g;        
        push(@contents, $_);
        push(@origcontents, $_);
    }
    close FILE;
    CheckHeader(\@contents);
    CheckIncludeGuards(\@contents, $filename);
    ReorderIncludeFiles(\@contents, $filename);
    AddHeaderNamespace(\@contents);
    
    if (!CompareArrays(\@contents, \@origcontents))
    {
        print "Writing modified file $filename\n";
        if ($real)
        {
            open(FILE, ">$filename") or die "File open for write failed for $filename: $!";
            foreach (@contents)
            {
                print FILE "$_\n";
            }
            close FILE;
        }
        else
        {    
            foreach (@contents)
            {
                print "$_\n";
            }
        }
    }
}

sub CheckHeader
{
    my $arrayref=shift;
    my $headerStart=0;
    my $headerEnd=0;
    my $headerPresent=0;
    my $line=0;
    foreach (@$arrayref)
    {
        $line++;
        if ($headerStart == 0)
        {
            unless (/^\s*\#/ || /^\s*$/)
            {
                # Not a # directive or blank line
                $headerStart=$line;
            }
        }
        elsif ($headerEnd == 0)
        {
            unless (/^ \*/ || /^$/)
            {
                $headerEnd=$line;
            }
        }
        if (/$headerMarker/)
        {
            $headerPresent=1;
        }
    }
    $headerStart=1 if ($headerStart < 1);
    
    $headerEnd=$headerStart if ($headerEnd < $headerStart || !$headerPresent);
    print "Adding header replacing lines $headerStart to $headerEnd\n" if ($verbose);
    splice @$arrayref, $headerStart-1, $headerEnd-$headerStart, @standardHeader;
}

sub CheckIncludeGuards
{
    my $arrayref=shift;
    my $filename=shift;
    my $guardStart=1;
    my $guardEnd=1;
    my $guardPresent=0;
    $filename =~ /\/([^\/]+)$/;
    my $defName=$1;
    $defName = uc $defName;
    $defName =~ s/[-\.]/_/g;
    
    my $line=0;
    foreach (@$arrayref)
    {
        $line++;
        if (/\#ifndef\s+$defName/)
        {
            $guardStart=$line;
            $guardEnd=$line+2;
            $guardPresent=1;
        }
    }
    print "Adding include guard replaing line $guardStart to $guardEnd using #ifdef $defName\n" if ($verbose);
    splice @$arrayref, $guardStart-1, $guardEnd-$guardStart, ("#ifndef $defName", "#define $defName");
    unless ($guardPresent)
    {
        push @$arrayref, "#endif";
    }
}

sub ReorderIncludeFiles
{
    # Reorder each contiguous block of #includes in alphabetical order
    my $arrayref=shift;
    my $filename=shift;
    my $cppCounterpart = $filename;
    $cppCounterpart =~ /\/([^\/]+)$/;
    $cppCounterpart = $1;
    $cppCounterpart =~ s/\.cpp$/\.h/;
    my %includeHash;
    my $line=0;
    my $includeLine = $line;
    foreach (@$arrayref)
    {
        $line++;
        if (/^\s*\#include\s+["<]([^">]+)[">]/)
        {
            $includeHash{$1} = $_;
        }
        else
        {
            if (scalar keys %includeHash > 0)
            {
                if (defined($includeHash{$cppCounterpart}))
                {
                    splice @$arrayref, $includeLine, 1, $includeHash{$cppCounterpart};
                    $includeLine++;
                    delete $includeHash{$cppCounterpart};
                }
                foreach my $include (sort keys %includeHash)
                {
                    splice @$arrayref, $includeLine, 1, $includeHash{$include};
                    $includeLine++;
                }
                %includeHash = ();
            }
            $includeLine=$line;
        }
    }
    print "Reordered include blocks\n" if ($verbose);
}

sub AddHeaderNamespace
{
    my $arrayref=shift;
    my @stdnames = ("ostream", "vector", "list", "map");
    my @mushnames = ("U32", "S32", "U16", "S16", "U8", "S8", "tVal", "u8istream");
    foreach my $line (@$arrayref)
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
    print "Added scope resolution to headers\n" if ($verbose);
}

sub AddUsingNamespace
{
    my $arrayref=shift;
    my $filename=shift;
    
    my $line=0;
    my $usingLine = 0;
    my $lastIncludeLine = 0;

    foreach (@$arrayref)
    {
        $line++;
        if (/^\s*\#include/)
        {
            $lastIncludeLine = $line;
        }
        if (/^\s*using\s+namespace/)
        {
            $usingLine = $line;
        }
    }
    if ($usingLine == 0 && $lastIncludeLine != 0)
    {
        splice @$arrayref, $lastIncludeLine, 0, ("", "using namespace Mushware;");
 
        print "Added using namespace Mushware\n" if ($verbose);
    }
}
