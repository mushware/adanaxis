#!/usr/bin/perl
#
# $Id¢
# $Log: basicToC.pl,v $
# Revision 1.1  2002/02/26 23:27:16  southa
# Added riscos files
#

use strict;

my $funcState=1;
my $lastFuncLabel="main";
my $lastLabel="unknown";

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
    my $cond="EQ|NE|CC|CS|VS|VC|GE|GT|LT|LE|PL|MI|HI|LS|";
    my $arith="ADD|SUB|RSB|BIC|AND|ORR|MUL|EOR";
    my $shiftB="(ASL|ASR|LSL|LSR|ROR)";
    my $num="[ a-zA-z0-9&+*/<>-]";
    my $numB="([ a-zA-z0-9&+*/<>-]+)";
    my $reg="[RP][0-9C][0-9]?";
    my $regB="($reg)";
    my $regnumB="#?([ a-zA-Z0-9()&+*/<>,_-]+)";
    my $pcTarget=0;
    my $wasSTMFD=0;

    if ($line =~ s/:\s*REM(.*)$//) # remove and store REM comments
    {
        $append = " //$1";
    }
    elsif ($line =~ s/;(.*)$//) # remove and store ; comments
    {
        $append = " //$1";
    }
    while ($line =~ s/\s+$//) # remove trailing whitespace
        {}
    $line =~ s/&([a-fA-F0-9])/0x$1/g; # Convert hex numbers to C style

    if ($line =~ s@$regB,\s*$shiftB\s+$regnumB@$2_shift($1,$3)@) # handle shifts
    {
        # print "$line\n";
    }
        
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
        $lastLabel=$1;
        if ($funcState==1)
        {
            $line="// $line";
        }
    }
    elsif ($line =~ s@^MOV($cond)\s+$regB,$regnumB$@$2=$3; // $orig@) # MOV R12,R0
    {
        $condition=$1;
        $pcTarget=($2 eq "PC") if ($condition eq "");
    }
    elsif ($line =~ s@^MVN($cond)\s+$regB,$regnumB$@$2=-$3; // $orig@) # MVN R12,R0
    {
        $condition=$1;
    }
    elsif ($line =~ s@^STM($cond)FD\s+$regB!,{([PCR0-9,-]+)}$@@) # STMFD R13!,{R14}
    {
        $wasSTMFD=1;
        $line .= "{";
        foreach (split ",", $3)
        {
            $line .= "*--$2=$_;";
        }
        $line .= "} // $orig";
    }
    elsif ($line =~ s@^(STM|LDM)($cond)IA\s+$regB(!?),{([PCR0-9-]+)}$@@) # STMIA R13!,{R14}
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
    elsif ($line =~ s@^LDM($cond)FD\s+$regB!,{([PCR0-9,-]+)}$@@) # LDMFD R13!,{R14}
    {
        $condition=$1;
        my $target=$2;
        my $regList=$3;
        $pcTarget=($3 =~ /PC/) if ($condition eq "");
        $line .= "{";
        foreach (split ",", $regList)
        {
            $line .= "$_=*$target++;";
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
    elsif ($line =~ s@^($arith)(S?)($cond)\s+$regB,$regB,$regnumB$@$1$2_arith($4,$5,$6); // $orig@) # ADD R2,R2,R1
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
    elsif ($line =~ s@^B($cond)\s+(\w+)$@goto $2; // $orig@) # B abort
    {
        $condition=$1;
    }
    elsif ($line =~ s@^SWI($cond)\s+"(\w+)"$@$2(); // $orig@) # SWI "FastSpr_GetAddress"
    {
        $condition=$1;
    }
    else
    {
        $line = "// " . $line . " // $orig Manual"
    }
    
    if ($line =~ /^\s*$/)
    {
    }
    elsif ($funcState == 1)
    {
        $line = "void $lastLabel(void)\n{\n    $line";
        $funcState=2;
    }
    elsif ($funcState == 2)
    {
        $prepend.="    ";
        if ($pcTarget)
        {
            $line="$line\n} // $lastFuncLabel()";
            $funcState=1;
            $lastLabel="unknown";
        }
    }

    if ($condition ne "")
    {
        $prepend.="if (cond_$condition()) ";
    }

    return $prepend.$line.$append."\n";
}
