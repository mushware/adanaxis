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
# $Id$
# $Log$

use strict;

my $gVerbose = 1;

my %gChunkList =
(
    "BOLX"     => "ChunkBOLX"
);

sub COBChunkFile($$)
{
    my ($chunksRef, $filename) = @_;
    print "Reading $filename\n" if $gVerbose;
        
    my $state = 0;
    
    open INFILE, $filename or die "Couldn't open $filename : $!";
    
    my $line;
    
    while ($line = <INFILE>)
    {
        if ($state == 0)
        {
            die "Bad first line $line" unless $line =~ /^Caligari V00\.01ALH/;
            $state = 1;
        }
        elsif ($state == 1)
        {
            # Unit V0.01 Id 83736949 Parent 83736948 Size 00000009
            # Units 2
            
            last if $line =~ /^END\s/;
            
            die "No chunk ID in '$line'" unless
                $line =~ /^(\w{4})\s/;
            
            die "Cannot parse chunk header" unless
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
                warn "Chunk size mismatch $size != $$chunkRef{'size'}";
            }
                        
            if ($gVerbose, 0)
            {
                foreach (sort keys %$chunkRef) { print "$_: $$chunkRef{$_}\n"; }
            };
        }
    }
    close INFILE;
}

sub COBDumpChunk($)
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

sub COBDumpChunks($)
{
    my ($chunksRef) = @_;
    
    foreach my $chunkRef (@$chunksRef)
    {
        COBDumpChunk($chunkRef);
        print "\n";
    }
}

sub main()
{
    my @chunks;
    COBChunkFile(\@chunks, "Cube0.cob");
    COBDumpChunks(\@chunks);
}

main();
