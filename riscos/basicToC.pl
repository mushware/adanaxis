#!/usr/bin/perl
#
# $Id¢
# $Log$

use strict;

my $inputFilename=$ARGV[0];
$inputFilename="BasText.txt" unless (defined($inputFilename));
my $outputFilename=$ARGV[1];
$outputFilename="asylum.c" unless (defined($outputFilename));

print "Processing $inputFilename to $outputFilename\n";

my @input=();
my @output=();

open(INFILE, $inputFilename) or die "Could not open $inputFilename:$!";
while(<INFILE>)
{
    push @input, $_;
}
close INFILE;

foreach my $line(@input)
{
    push @output,ProcessLine($line);
}

open(OUTFILE, ">$outputFilename") or die "Could not open $outputFilename:$!";
foreach (@output)
{
    print OUTFILE;
}
close OUTFILE;
print "Done\n";

sub ProcessLine
{
    my $line=shift;
    chomp($line);
    my $orig=$line;
    my $append="";
    my $prepend="";
    my $condition="";
    my $cond="EQ|NE|CC|CS|VS|VC|GE|GT|LT|LE|PL|MI|";
    my $arith="ADD|SUB|RSB|BIC|AND|ORR|MUL";
    my $num="[ a-zA-z0-9&+*/<>-]";
    my $numB="([ a-zA-z0-9&+*/<>-]+)";
    my $reg="R[0-9][0-9]?";
    my $regB="($reg)";
    my $regnumB="#?([ a-zA-z0-9&+*/<>-]+)";
    if ($line =~ s/:\s*REM(.*)$//)
    {
        $append = " // $1";
    }
    elsif ($line =~ s/;(.*)$//)
    {
        $append = " //$1";
    }
    while ($line =~ s/\s+$//) # remove trailing whitespace
        {}
    $line =~ s/&([a-fA-F0-9])/0x$1/g;

    if ($line =~ m@^\s*$@) # Empty line
    {
        $line="";
    }
    elsif ($line =~ s@^REM@// @) # REM
    {
    }
    elsif ($line =~ s@^(\w+=$num+)$@const U32 $1;@) # strengthmax=108<<8
    {
        $line =~ s/&/0x/g;
    }
    elsif ($line =~ s@^\.(\w+)@$1:@) # .init
    {
    }
    elsif ($line =~ s@^MOV($cond)\s+$regB,$regnumB$@$2=$3; // $orig@) # MOV R12,R0
    {
        $condition=$1;
    }
    elsif ($line =~ s@^MVN($cond)\s+$regB,$regnumB$@$2=-$3; // $orig@) # MVN R12,R0
    {
        $condition=$1;
    }
    elsif ($line =~ s@^STM($cond)FD\s+$regB!,{([R0-9,]+)}$@@) # STMFD R13!,{R14}
    {
        $line .= "{";
        foreach (split ",", $3)
        {
            $line .= "*--$2=$_;";
        }
        $line .= "} // $orig";
    }
    elsif ($line =~ s@^(STM|LDM)($cond)IA\s+$regB(!?),{([R0-9-]+)}$@@) # STMIA R13!,{R14}
    {
        $line .= "{";
        my $opcode=$1;
        $condition=$2;
        my $targreg=$3;
        my $excl=$4;
        my $reglist=$5;
        $reglist =~ m/R(\d+)-R(\d+)/;

        for (my $i=$1; $i<$2; ++$i)
        {
            $line .= "((U32*)$targreg)[".($i-$1)."]=R$i;" if ($opcode eq "STM");
            $line .= "R$i=((U32*)$targreg)[".($i-$1)."];" if ($opcode eq "LDM");
        }
        $line .= "$targreg+=".(4*($2-$1)).";" if ($excl eq "!");
        $line .= "} // $orig";
    }
    elsif ($line =~ s@^LDM($cond)FD\s+$regB!,{([R0-9,]+)}$@@) # LDMFD R13!,{R14}
    {
        $line .= "{";
        foreach (split ",", $3)
        {
            $line .= "$_=*$2++;";
        }
        $line .= "} // $orig";
    }
    elsif ($line =~ s@^(STR|LDR)($cond)(B?)\s+$regB,\[$regB,$regnumB]$@$1$3_preinc($4,$5,$6); // $orig@) # STRB R1,[R12,#storage]
    {
        $condition=$2;
    }
    elsif ($line =~ s@^(STR|LDR)($cond)(B?)\s+$regB,\[$regB]$@$1$3_preinc($4,$5,0); // $orig@) # STRB R1,[R12]
    {
        $condition=$2;
    }
    elsif ($line =~ s@^(STR|LDR)($cond)(B?)\s+$regB,\[$regB,$regnumB]!$@$1$3_preincWriteback($4,$5,$6); // $orig@) # STRB R1,[R12,#storage]
    {
        $condition=$2;
    }
    elsif ($line =~ s@^(STR|LDR)($cond)(B?)\s+$regB,\[$regB],$regnumB$@$1$3_postinc($4,$5,$6); // $orig@) # STRB R1,[R12]
    {
        $condition=$2;
    }
    elsif ($line =~ s@^STR($cond)(B?)\s+$regB,$regnumB$@*(U32 *)$3=$4; // $orig@) # STR R12,varstr
    {
        $condition=$2;
    }
    elsif ($line =~ s@^($arith)(S?)($cond)\s+$regB,$regB,$regnumB$@$1_arith$2($4,$5,$6); // $orig@) # ADD R2,R2,R1
    {
        $condition=$3;
    }
    elsif ($line =~ s@^(CMP|TST)($cond)\s+$regB,$regnumB$@$1_plain($3,$4); // $orig@) # CMP
    {
        $condition=$2;
    }
    elsif ($line =~ s@^BL($cond)\s+(\w+)$@$2(); // $orig@) # BL gethandlers
    {
        $condition=$1;
    }
    elsif ($line =~ s@^B($cond)\s+(\w+)$@goto $2; // $orig@) # BVS abort
    {
        $condition=$1;
    }
    elsif ($line =~ s@^SWI($cond)\s+"(\w+)"$@$2(); // $orig@) # SWI "FastSpr_GetAddress"
    {
        $condition=$1;
    }
    else
    {
        $line = "// " . $line . " // Manual"
    }
    
    if ($condition ne "")
    {
        $prepend="if (cond_$condition()) ";
    }
    return $prepend.$line.$append."\n";
}
