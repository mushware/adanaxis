#!/usr/bin/perl -w

#
# $Id$
# $Log$
#

use DirHandle;

my @standardHeader=(
"/*****************************************************************************",
" *",
" * (Mushware file header version 1.0)",
" *",
" * This file contains original work by Andy Southgate.  Contact details can be",
" * found at http://www.mushware.co.uk.  This file was placed in the Public",
" * Domain by Andy Southgate and Mushware Limited in 2002.",
" *",
" * This software carries NO WARRANTY of any kind.",
" *",
" ****************************************************************************/",
""
);

my $headerMarker="Mushware file header version";
my $real=1;

ProcessDirectory(".");
print "Done.\n";

sub ProcessDirectory
{
    my $prefix=shift;
    print "Entering directory $prefix\n";
    
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
                print "Ignoring file $filename\n";
            }
        }
    }
    print "Leaving directory $prefix\n";
}

sub ProcessCPPFile
{
    my $filename=shift;
    print "Processing CPP file $filename\n";
    open(FILE, $filename) or die "File open for read failed for $filename: $!";
    my @contents=();
    while (<FILE>)
    {
        s/\012//g;
        s/\015//g;        
        push(@contents, $_);
    }
    close FILE;
    CheckHeader(\@contents);
    
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

sub ProcessHFile
{
    my $filename=shift;
    print "Processing H file $filename\n";
        open(FILE, $filename) or die "File open for read failed for $filename: $!";
    my @contents=();
    while (<FILE>)
    {
        s/\012//g;
        s/\015//g;        
        push(@contents, $_);
    }
    close FILE;
    CheckHeader(\@contents);
    CheckIncludeGuards(\@contents, $filename);
    
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
            unless (/^ \*/)
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
    print "Adding header replacing lines $headerStart to $headerEnd\n";
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
    print "Adding include guard replaing line $guardStart to $guardEnd using #ifdef $defName\n";
    splice @$arrayref, $guardStart-1, $guardEnd-$guardStart, ("#ifndef $defName", "#define $defName");
    unless ($guardPresent)
    {
        push @$arrayref, "#endif";
    }
}
