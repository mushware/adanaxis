#!/usr/bin/perl -w

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2004.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
# $Id: COBTranslate.pl,v 1.1 2004/06/12 14:30:35 southa Exp $
# $Log: COBTranslate.pl,v $
# Revision 1.1  2004/06/12 14:30:35  southa
# Created
#

package COBHandler;

use Carp;
use Data::Dumper;

use strict;

my $gVerbose = 1;


sub ChunkDump($)
{
    my ($chunkRef) = @_;
    print "Chunk named $$chunkRef{'name'}\n";
    foreach my $key (sort keys %$chunkRef)
    {
        if ($key eq 'data')
        {
            print "  $key:\n    ";
            my $dataRef = $$chunkRef{$key};
            print join "    ", @$dataRef;
        }
        else
        {
            print "  $key: $$chunkRef{$key}\n";
        }
    }
}

sub ChunkDumps($)
{
    my ($chunksRef) = @_;
    
    foreach my $chunkRef (@$chunksRef)
    {
        ChunkDump($chunkRef);
        print "\n";
    }
}

sub FileProcess($$)
{
    my ($chunksRef, $filename) = @_;
    print "Reading $filename\n" if $gVerbose;
        
    my $state = 0;
    
    open INFILE, $filename or croak "Couldn't open $filename : $!";
    
    my $line;
    
    while ($line = <INFILE>)
    {
        if ($state == 0)
        {
            croak "Bad first line $line" unless $line =~ /^Caligari V00\.01ALH/;
            $state = 1;
        }
        elsif ($state == 1)
        {
            # Unit V0.01 Id 83736949 Parent 83736948 Size 00000009
            # Units 2
            
            last if $line =~ /^END\s/;
            
            croak "No chunk ID in '$line'" unless
                $line =~ /^(\w{4})\s/;
            
            croak "Cannot parse chunk header" unless
                $line =~ /^(\w+)\s+V(\d+\.\d+)\s+Id\s+(\w+)\s+Parent\s+(\w+)\s+Size\s+(\w+)/;
            
            push @$chunksRef, {}; # Anonymous hash to store our data
            my $chunkRef = @$chunksRef[-1]; # reference to that new hash
            
            ($$chunkRef{'name'}, $$chunkRef{'version'}, $$chunkRef{'id'}, $$chunkRef{'parent'}, $$chunkRef{'size'}) =
                ($1, $2, $3, $4, int($5));
            
            my $size = 1;
            
            $$chunkRef{'data'} = []; # Anonymous array for data
            my $dataRef = $$chunkRef{'data'}; # Reference to that array
            
            while ($size < $$chunkRef{'size'} && ($line = <INFILE>))
            {
                # print "'$line' length=", length($line), "\n";
                push @$dataRef, $line;
                $size += length($line);
            }
            if ($size != $$chunkRef{'size'})
            {
                carp "Chunk size mismatch $size != $$chunkRef{'size'}";
            }
        }
    }
    close INFILE;
}

sub PolHProcess($$)
{
    my ($dataRef, $chunkRef) = @_;
    
    push @{$dataRef->{'polh'}}, {};
    my $polhRef = $dataRef->{'polh'}[-1];
    
    $polhRef->{'id'} = $chunkRef->{'id'};
    
    my $state = 0;
    my $lineCount;
    my $F = '[-+.\d]+'; # regexp filler for floating point number
    my $I = '[-+\d]+';  # regexp filler for integer
    foreach my $line (@{$chunkRef->{'data'}})
    {
        if ($state == 0) # Name search
        {
            croak "Missing name in PolH" unless ($line =~ /^Name\s+(.+)$/);
            print "Name '$1'\n";
            $polhRef->{'name'} = $1;
            $state = 1;
        }
        elsif ($state == 1) # Block search state
        {
            if ($line =~ /^\s*World\s+Vertices\s+($I)/)
            {
                $polhRef->{'numWorldVertices'} = $1;
                $lineCount = 0;
                $state = 2;
            }
            elsif ($line =~ /^\s*Texture\s+Vertices\s+($I)/)
        {
                $polhRef->{'numTextureVertices'} = $1;
                $lineCount = 0;
                $state = 3;
        }
            elsif ($line =~ /^\s*Faces\s+($I)/)
        {
                $polhRef->{'numFaces'} = $1;
                $lineCount = 0;
                $state = 4;
        }
        }
        elsif ($state == 2)
        {
                croak "Badly formed world vertex" unless $line =~ /\s*($F)\s+($F)\s+($F)/;
                push @{$polhRef->{'worldVertices'}}, [$1, $2, $3];
                ++$lineCount;
                $state = 1 if ($lineCount >= $polhRef->{'numWorldVertices'});
        }
        elsif ($state == 3)
        {
                croak "Badly formed texture vertex" unless $line =~ /\s*($F)\s+($F)/;
                push @{$polhRef->{'textureVertices'}}, [$1, $2];
                ++$lineCount;
                $state = 1 if ($lineCount >= $polhRef->{'numTextureVertices'});
        }
        elsif ($state == 4)
        {
            push @{$polhRef->{'faces'}}, {};
            my $faceRef = $polhRef->{'faces'}[-1];
            
            croak "Badly formed face '$line'" unless $line =~ /\s*Face\s+verts\s+($I)\s+flags\s+($I)\s+mat\s+($I)/;
            $faceRef->{'verts'} = $1;
            $faceRef->{'flags'} = $2;
            $faceRef->{'mat'} = $3;
        
            ++$lineCount;
            $state = 5;
        }
        elsif ($state == 5)
        {
            ++$lineCount;
            $state = 4;
            $state = 1 if ($lineCount >= 2*$polhRef->{'numFaces'});
        }
    }
}

sub ChunksProcess($$)
{
    my ($dataRef, $chunksRef) = @_;
    
    my %chunkList =
        (   
            "PolH" => \&PolHProcess
        );
    
    foreach my $chunkRef (@$chunksRef)
    {
        my $chunkName = $$chunkRef{'name'};
        if (defined($chunkList{$chunkName}))
        {
            $chunkList{$chunkName}($dataRef, $chunkRef);
        }
    }
}

sub Translate($$)
{
    my ($inFile, $outFile) = @_;
    
    my @chunks;
    FileProcess(\@chunks, $inFile);
    
    my %data;

    ChunksProcess(\%data, \@chunks);
    
    print Dumper(\%data);
    
# ChunkDumps(\@chunks);
}

1;
