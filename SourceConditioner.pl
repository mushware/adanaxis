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

# $Id: SourceConditioner.pl,v 1.14 2003/10/01 23:18:24 southa Exp $
# $Log: SourceConditioner.pl,v $
# Revision 1.14  2003/10/01 23:18:24  southa
# XML object handling
#
# Revision 1.13  2003/09/30 22:11:26  southa
# XML objects within objects
#
# Revision 1.12  2003/09/29 21:48:33  southa
# XML work
#
# Revision 1.11  2003/09/27 17:50:46  southa
# XML null pointer handling
#
# Revision 1.10  2003/09/26 19:18:06  southa
# XML null pointer handling
#
# Revision 1.9  2003/09/25 20:02:22  southa
# XML pointer work
#
# Revision 1.8  2003/09/24 19:03:19  southa
# XML map IO
#
# Revision 1.7  2003/09/23 22:57:54  southa
# XML vector handling
#
# Revision 1.6  2003/09/22 19:40:33  southa
# XML I/O work
#
# Revision 1.5  2003/09/21 23:15:06  southa
# XML input stream improvements
#
# Revision 1.4  2003/09/21 11:45:46  southa
# XML input stream
#
# Revision 1.3  2003/09/21 09:50:50  southa
# Stream autogenerators
#
# Revision 1.2  2003/09/17 19:40:26  southa
# Source conditioning upgrades
#
# Revision 1.1  2003/09/17 19:12:13  southa
# Created
#

use SourceProcess;

use strict;

my $gExprScopedType = '[A-Za-z0-9_:]+'; # typename with optional ::
my $gExprVariableName = '[A-Za-z0-9_]+'; # Variable name
my $gExprVariableExpr = '\**[A-Za-z0-9_[\]]+'; # variable expression, e.g. *x
my $gExprTemplateSuffix = '<.+>'; # template suffix, e.g. <std::string>
my $gVerbose = 0;

my %gConfig = (
AUTO_PREFIX => 'Auto',
INDENT => '    ',
NAMESPACE => 'Mushcore'
);

use constant HS_SCAN_FOR_CLASS => 0;
use constant HS_SCAN_FOR_MEMBERS => 1;
use constant HS_DONE => 10;

my @gCHeaders = (
'^Mustl' => [
'/*****************************************************************************',
' *',
' * File: @FILENAME@',
' *',
' * Copyright Andy Southgate 2002-2003',
' *',
' * This file may be redistributed and/or modified under the terms of the',
' * Mushware licence which you should have received with this file.  For',
' * information, please contact the author via http://www.mushware.com/.',
' *',
' * This software carries NO WARRANTY of any kind.',
' *',
' ****************************************************************************/'
],
'.*' =>
[
'/*****************************************************************************',
' *',
' * File: @FILENAME@',
' *',
' * This file contains original work by Andy Southgate.  Contact details can be',
' * found at http://www.mushware.com/.  This file was placed in the Public',
' * Domain by Andy Southgate and Mushware Limited in 2002-2003.',
' *',
' * This software carries NO WARRANTY of any kind.',
' *',
' ****************************************************************************/'
]
);

my $headerMarker='Mushware file header version';

# main
SourceProcess::AddArrayProcessor('\.h$', \&OldBlocksStrip);
SourceProcess::AddArrayProcessor('\.h$', \&ProcessFileHeader);
SourceProcess::AddArrayProcessor('\.cpp$', \&ProcessFileHeader);
SourceProcess::AddArrayProcessor('\.h$', \&ProcessHeader);
SourceProcess::AddArrayProcessor('\.cpp$', \&ProcessCPP);
SourceProcess::AddArrayProcessor('\.h$', \&ProcessIncludeGuard);

SourceProcess::Process('src');


sub HeaderInfoCreate($$)
{
    my ($infoRef, $contentRef) = @_;
    
    my $state = HS_SCAN_FOR_CLASS;
    my $lineNum = 0;
    
    foreach my $lineRef (@$contentRef)
    {
        my $line = "$lineRef";
        # remove comments
        my $comments = "";
        if ($line =~ s#//(.*)##)
        {
            $comments .= $1;
        }
        if ($line =~ s#/\*(.*)\*/##)
        {
            $comments .= $1;
        }
                
        if ($state == HS_SCAN_FOR_CLASS)
        {
            if ($line =~ /^class/)
            {
                # Class definition or declaration line
                if ($line =~ /;\s*$/)
                {
                    # Declaration only - ignore
                }
                else
                {
                    ClassLineRead($infoRef, $line);
                    $state = HS_SCAN_FOR_MEMBERS;
                }
            }
            if ($comments =~ /^\s*:(.*)$/)
            {
                CommandsAdd($infoRef, $1);
            }
        }
        elsif ($state == HS_SCAN_FOR_MEMBERS)
        {
            if ($line =~ /^\s*}\s*;\s*$/)
            {
                $$infoRef{CLOSING_LINE} = $lineNum;
                $state = HS_DONE;
            }
        
            if ($line =~ /^\s+($gExprScopedType)\s*($gExprTemplateSuffix)?\s+($gExprVariableExpr)\s*;/)
            {
                my $template = $2;
                $template = "" unless defined($template);
                AttributeAdd($infoRef, $1.$template, $3, $comments);
            }
        }
        
        if ($line =~ /^\s*}\s*;?\s*$/)
        {
            # line closing the last function or the class definition.
            # +1 -> choose the next one.
            $$infoRef{LAST_LINE} = $lineNum+1;
        }            
        ++$lineNum;
    }
    $$infoRef{EOF_LINE} = $lineNum;
    $$infoRef{ARRAY_ELEMENTS} = scalar @$contentRef;
}

sub ClassLineRead($$)
{
    my ($infoRef, $line) = @_;
    
    unless ($line =~ /class\s+(\S+)\s*/)
    {
        die "Couldn't detect class name from $line";
    }
    
    $$infoRef{CLASSNAME} = $1;
    
    if ($line =~ /class\s+\S+\s*:\s*(\S.+)/)
    {
        $$infoRef{BASES} = $1;
    }
    else
    {
        $$infoRef{BASES} = "";
    }
}

sub CommandsAdd($$)
{
    my ($infoRef, $command) = @_;

    $$infoRef{COMMANDS} = [] unless defined ($$infoRef{COMMANDS});
    
    my $commandsRef = $$infoRef{COMMANDS};
    
    push @$commandsRef, $command;
}

sub AttributeAdd($$$$)
{
    my ($infoRef, $type, $name, $commands) = @_;
    
    $$infoRef{ATTRIBUTES} = [] unless defined ($$infoRef{ATTRIBUTES});
    
    my $attributesRef = $$infoRef{ATTRIBUTES};
    
    push @$attributesRef, $type;
    push @$attributesRef, $name;
    push @$attributesRef, $commands;
}

sub HeaderInfoPrint($)
{
    my ($infoRef) = @_;
    
    my $className = $$infoRef{CLASSNAME};
    print "Class: $className\n" if defined($className);

    foreach ('CLOSING_LINE', 'LAST_LINE', 'EOF_LINE', 'ARRAY_ELEMENTS', 'BASES')
    {
        my $value = $$infoRef{$_};
        print "$_: $value\n" if defined($value);
    }
    
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            print "Attribute: $$attributesRef[$i] $$attributesRef[$i+1] $$attributesRef[$i+2]\n"
        }
    }
    my $commandsRef = $$infoRef{COMMANDS};
    if (defined($commandsRef))
    {
        for (my $i=0; $i < @$commandsRef; $i += 1)
        {
            print "Commands: $$commandsRef[$i]\n"
        }
    }
}

sub TypeSpecial($$)
{
    my ($type, $attr) = @_;

    if ($type =~ /^(.*::)U8$/)
    {
        return "static_cast<${1}U32>($attr)";
    }
    elsif  ($type =~ /^(.*::)S8$/)
    {
        return "static_cast<${1}S32>($attr)";
    }
    else
    {
        return $attr;
    }
}

sub IndirectionGet($)
{
    my ($name) = @_;
    if ($name =~ /^\*{3}/)
    {
        die "Too much indirection in $name";
    }
    if ($name =~ /^\*{2}/)
    {
        return 2;
    }
    if ($name =~ /^\*/)
    {
        return 1;
    }
}


sub VarNameTrim($)
{
    my ($name) = @_;
    $name =~ s/^\*//;
    $name =~ s/^m_//;
    return $name;
}

sub VarBaseNameGet($)
{
    my ($name) = @_;
    $name =~ s/^\*+//;
    return $name;
}

##########################################################
#
#    Standard functions
#
##########################################################

sub StandardPrototypeGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for standard functions" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}virtual const char *$gConfig{AUTO_PREFIX}NameGet(void) const;"; 
    push @$outputRef, "$gConfig{INDENT}virtual $className *$gConfig{AUTO_PREFIX}Clone(void) const;"; 
    push @$outputRef, "$gConfig{INDENT}virtual $className *$gConfig{AUTO_PREFIX}Create(void) const;"; 
    push @$outputRef, "$gConfig{INDENT}static MushcoreVirtualObject *$gConfig{AUTO_PREFIX}VirtualFactory(void);"; 
}

sub StandardFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for standard functions" unless defined ($className);
    
    push @$outputRef,
"const char *".
"${className}::$gConfig{AUTO_PREFIX}NameGet(void) const",
"{",
"    return \"$className\";",
"}",
"$className *".
"${className}::$gConfig{AUTO_PREFIX}Clone(void) const",
"{",
"    return new $className(*this);",
"}",
"$className *".
"${className}::$gConfig{AUTO_PREFIX}Create(void) const",
"{",
"    return new $className;",
"}",
"MushcoreVirtualObject *".
"${className}::$gConfig{AUTO_PREFIX}VirtualFactory(void)",
"{",
"    return new $className;",
"}",
"namespace",
"{",
"void Install(void)",
"{",
"    MushcoreFactory::Sgl().FactoryAdd(\"${className}\", ${className}::$gConfig{AUTO_PREFIX}VirtualFactory);",
"}",
"MushcoreInstaller Installer(Install);",
"} // end anonymous namespace";
}

##########################################################
#
#    std::ostream output
#
##########################################################

sub OstreamWritePrototypeGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for ostream writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}void $gConfig{AUTO_PREFIX}Print(std::ostream& ioOut) const;"; 
}

sub OstreamWriteFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for ostream writer" unless defined ($className);
    
    push @$outputRef, "void";
    push @$outputRef, "${className}::$gConfig{AUTO_PREFIX}Print(std::ostream& ioOut) const";
    push @$outputRef, "{";
    push @$outputRef, "    ioOut << \"[\";";
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $trimmedAttr = VarNameTrim($attr);
            my $indirection = IndirectionGet($attr);
            my $comma = "";
            $comma = " << \", \"" unless ($i+3 == @$attributesRef);
           
            my $line = "    ioOut << \"$trimmedAttr=\" << ".TypeSpecial($type, $attr);
            
            $line .= "$comma;";
            
            if ($indirection > 0)
            {
                push @$outputRef,
"    if (".VarBaseNameGet($attr)." == NULL)",
"    {",
"        ioOut << \"$trimmedAttr=NULL\" $comma;",
"    }",
"    else",
"    {",
"    ".$line,
"    }";
            }
            else
            {
                push @$outputRef, $line;
            }
        }
    }
    push @$outputRef, "    ioOut << \"]\";";
    push @$outputRef, "}";  
}

sub OstreamOperatorGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for ostream operator" unless defined ($className);
    
    push @$outputRef, "inline std::ostream&";
    push @$outputRef, "operator<<(std::ostream& ioOut, const $className& inObj)";
    push @$outputRef,
"{",
"    inObj.$gConfig{AUTO_PREFIX}Print(ioOut);",
"    return ioOut;",
"}";
}

##########################################################
#
#    Basic operators
#
##########################################################
sub BasicOperatorsPrototypeGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for BasicOperators writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}bool $gConfig{AUTO_PREFIX}Equals(const $className& inObj) const;"; 
}

sub BasicOperatorsFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for BasicOperators writer" unless defined ($className);
    
    push @$outputRef,
"bool",
"${className}::$gConfig{AUTO_PREFIX}Equals(const $className& inObj) const",
"{",
"    return 1";
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $comment = $$attributesRef[$i+2];
            next if ($comment =~ /nobasic/);
            my $attr = $$attributesRef[$i+1];
            my $indirection = IndirectionGet($attr);
            my $line = "        && ";

            if ($indirection > 0)
            {
                my $baseName = VarBaseNameGet($attr);
                $line .= "($baseName == inObj.$baseName || ($baseName != NULL && inObj.$baseName != NULL && *$baseName == *inObj.$baseName))";
            }
            else
            {
                $line .= "($attr == inObj.$attr)";
            }
            push @$outputRef, $line;
        }
    }
    push @$outputRef,
"    ;",
"}";
}

sub BasicOperatorsInlineGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for BasicOperators writer" unless defined ($className);

    push @$outputRef,
"inline bool",
"operator==(const $className& inA, const $className& inB)",
"{",
"    return inA.$gConfig{AUTO_PREFIX}Equals(inB);",
"}",
}

##########################################################
#
#    XML input
#
##########################################################

sub XMLIStreamWritePrototypeGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for XMLIStream writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}void $gConfig{AUTO_PREFIX}XMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);"; 
}

sub XMLIStreamWriteFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for XMLIStream writer" unless defined ($className);
    
    push @$outputRef,
"void",
"${className}::$gConfig{AUTO_PREFIX}XMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)",
"{",
"    if (inTagStr == \"obj\")",
"    {",
"        ioIn >> *this;",
"    }";
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $baseAttr = VarBaseNameGet($attr);
            my $trimmedAttr = VarNameTrim($attr);
            push @$outputRef,
"    else if (inTagStr == \"$trimmedAttr\")",
"    {",
"        ioIn >> $baseAttr;",
"    }";

        }
    }
    push @$outputRef,
"    else",
"    {",
"        ioIn.Throw(\"Unrecognised tag '\"+inTagStr+\"'\");",
"    }",
"}";
}

sub XMLIStreamOperatorGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for XMLIStream operator" unless defined ($className);
    
}

##########################################################
#
#    XML output
#
##########################################################

sub XMLOStreamWritePrototypeGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for XMLOStream writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}void $gConfig{AUTO_PREFIX}XMLPrint(MushcoreXMLOStream& ioOut) const;"; 
}

sub XMLOStreamWriteFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};

    die "No class found for XMLOStream writer" unless defined ($className);
    
    push @$outputRef, "void";
    push @$outputRef, "${className}::$gConfig{AUTO_PREFIX}XMLPrint(MushcoreXMLOStream& ioOut) const";
    push @$outputRef,
"{";
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $trimmedAttr = VarNameTrim($attr);
            my $indirection = IndirectionGet($attr);
            
            push @$outputRef,
"    ioOut.TagSet(\"$trimmedAttr\");";
           
            if ($indirection > 0)
            {
                push @$outputRef,
"    ioOut << ".VarBaseNameGet($attr)." << \"\\n\";";
            }
            else
            {
                push @$outputRef,
"    ioOut << ".$attr." << \"\\n\";";
            }
        }
    }
    push @$outputRef, "}";  
}

sub OldBlocksStrip($$)
{
    my ($contentRef, $filename) = @_;

    SourceProcess::BlockReplace(\@$contentRef, [], 'IncGuard1', 0);
}

sub OldHeaderStrip($)
{
    my ($arrayRef) = @_;
    my $lineNum = 0;
    my $headerStart=0;
    my $headerEnd=0;
    my $headerPresent=0;
    my $started = 0;
    my $ended = 0;
    
    foreach (@$arrayRef)
    {
        unless ($started)
        {
            unless (/^\s*\#/ || /^\s*$/ || /^\s*\/\//)
            {
                # Not a # directive or blank line
                $headerStart=$lineNum;
                $started = 1;
            }
        }
        elsif (!$ended)
        {
            unless (/^ \*/ || /^$/)
            {
                $headerEnd=$lineNum;
                $ended = 1;
            }
        }
        if (/$headerMarker/)
        {
            $headerPresent=1;
        }
        ++$lineNum;
    }
    
    if ($headerPresent && $started && $ended)
    {
        splice @$arrayRef, $headerStart, $headerEnd-$headerStart;
    }
}

sub HeaderGenerate($$$)
{
    my ($arrayRef, $filename, $headersRef) = @_;

    my $line=0;
    my $leafname="";    

    if ($filename =~ /\/([^\/]+)$/)
    {
        $leafname = $1;
    }
        
    my $userFilename = $filename;
    
    $userFilename =~ s/^\.\///;
    
    # find appropriate header
    for (my $i=0; $i < @$headersRef; $i += 2)
    {
        if ($leafname =~ /$$headersRef[$i]/)
        {
            my $chosenRef = @$headersRef[$i+1];         
            my @headerStore;
            foreach my $lineRef (@$chosenRef)
            {
                my $line = "$lineRef";
                $line =~ s/\@FILENAME\@/$userFilename/;
                push @headerStore, $line;
            }
            SourceProcess::BlockReplace(\@$arrayRef, \@headerStore, 'Header', 0);
            last;
        }
    }
}

sub ProcessFileHeader($$)
{
    my ($contentRef, $filename) = @_;

    OldHeaderStrip(\@$contentRef);
    HeaderGenerate(\@$contentRef, $filename, \@gCHeaders);
}

sub OldIncludeGuardStrip($$)
{
    my ($arrayRef, $filename) = @_;
    my $guardStart=0;
    my $guardEnd=0;
    my $guardPresent=0;
    my $defName=$1;
    $defName = uc $defName;
    $defName =~ s/[-\.]/_/g;
    my $line=0;
    my $endifLine=0;
    
    SourceProcess::BlockReplace(\@$arrayRef, [], 'includeGuardStart', 0);
    SourceProcess::BlockReplace(\@$arrayRef, [], 'includeGuardEnd', scalar @$arrayRef);
        
    foreach (@$arrayRef)
    {
        if (/\#ifndef\s+$defName/)
        {
            $guardStart=$line;
            $guardEnd=$line+2;
            $guardPresent=1;
        }
        if (/\#endif/)
        {
            $endifLine = $line;
        }
        $line++;
    }
    if ($guardPresent)
    {
        if ($endifLine != 0)
        {
            splice @$arrayRef, $endifLine, 1;
        }
        splice @$arrayRef, $guardStart, $guardEnd-$guardStart;
    }
}

sub IncludeGuardGenerate
{
    my ($arrayRef, $filename) = @_;

    $filename =~ /\/([^\/]+)$/;
    my $defName=$1;
    $defName = uc $defName;
    $defName =~ s/[-\.]/_/g;
    
    print "Adding include guards #ifdef $defName\n" if ($gVerbose);
    
    SourceProcess::BlockReplace(\@$arrayRef, ["#ifndef $defName", "#define $defName"], 'includeGuardStart', 0);
    SourceProcess::BlockReplace(\@$arrayRef, ["#endif"], 'includeGuardEnd', scalar @$arrayRef);
}

sub ProcessIncludeGuard($$)
{
    my ($contentRef, $filename) = @_;

    OldIncludeGuardStrip(\@$contentRef, $filename);
    IncludeGuardGenerate(\@$contentRef, $filename);
}

sub ProcessHeader($$)
{
    my ($contentRef, $filename) = @_;
    my %headerInfo;
    
    HeaderInfoCreate(\%headerInfo, \@$contentRef);
    HeaderInfoPrint(\%headerInfo) if $gVerbose;
    
    my @classPrototypes;
    my @inlineHeader;
    my @inlineNamespaced;
    
    my $commandsRef = $headerInfo{COMMANDS};

    if (defined($commandsRef))
    {
        push @ classPrototypes, "public:";
        
        for (my $i=0; $i < @$commandsRef; $i += 1)
        {
            # Standard functions
            if ($$commandsRef[$i] =~ /generate.*\bstandard\b/)
            {            
                StandardPrototypeGenerate(\@classPrototypes, \%headerInfo);
            }
            # BasicOperators
            if ($$commandsRef[$i] =~ /generate.*\bbasic(.*)\b/)
            {            
                BasicOperatorsPrototypeGenerate(\@classPrototypes, \%headerInfo);
                BasicOperatorsInlineGenerate(\@inlineHeader, \%headerInfo);
            }
            # std::ostream
            if ($$commandsRef[$i] =~ /generate.*\bostream\b/)
            {
                OstreamWritePrototypeGenerate(\@classPrototypes, \%headerInfo);
                OstreamOperatorGenerate(\@inlineHeader, \%headerInfo);
            }
 
            # MushcoreXMLOstream
            if ($$commandsRef[$i] =~ /generate.*\bxml1(.*)\b/)
            {
                XMLIStreamWritePrototypeGenerate(\@classPrototypes, \%headerInfo);
                # XMLIStreamOperatorGenerate(\@inlineNamespaced, \%headerInfo);
                XMLOStreamWritePrototypeGenerate(\@classPrototypes, \%headerInfo);
                # XMLOStreamOperatorGenerate(\@inlineheader, \%headerInfo);
            }
            

        }
    }
    
    if (scalar @inlineNamespaced > 0)
    {
        # Add the namesapce shell
        splice @inlineNamespaced, 0, 0, ("namespace $gConfig{NAMESPACE}", "{", ""); 
        push @inlineNamespaced, "", "} // end namespace $gConfig{NAMESPACE}";
    }
    
    # Replacements should be from the bottom up so that the
    # line numbers remain valid
    my $lastLine = $headerInfo{LAST_LINE};
    SourceProcess::BlockReplace(\@$contentRef, \@inlineHeader, 'inlineHeader', $lastLine);

    SourceProcess::BlockReplace(\@$contentRef, \@inlineNamespaced, 'inlineNamespaced', $lastLine);
    
    my $closingLine = $headerInfo{CLOSING_LINE};
    SourceProcess::BlockReplace(\@$contentRef, \@classPrototypes, 'classPrototypes', $closingLine);

}

sub ProcessCPP($$)
{
    my ($contentRef, $filename) = @_;

    my $headerFilename = $filename;
    
    unless ($headerFilename =~ s/\.[^.]+$/.h/)
    {
        print "Cannot translate '$filename' to header filename\n" if $gVerbose;
        return;
    }
    
    unless ( -f $headerFilename )
    {
        print "Header for $filename ($headerFilename) not present\n" if $gVerbose;
        return;
    }

    my %headerInfo;

    {
        my @headerContents;
        SourceProcess::ReadFile(\@headerContents, $headerFilename);
        HeaderInfoCreate(\%headerInfo, \@headerContents);
    }
    
    my @outOfLineCode;
    my $commandsRef = $headerInfo{COMMANDS};
    
    if (defined($commandsRef))
    {
        for (my $i=0; $i < @$commandsRef; $i += 1)
        {
            # Standard
            if ($$commandsRef[$i] =~ /generate.*\bstandard\b/)
            {            
                StandardFunctionGenerate(\@outOfLineCode, \%headerInfo);
            }
            # BasicOperators
            if ($$commandsRef[$i] =~ /generate.*\bbasic(.*)\b/)
            {            
                BasicOperatorsFunctionGenerate(\@outOfLineCode, \%headerInfo);
            }
            # std::ostream
            if ($$commandsRef[$i] =~ /generate.*\bostream\b/)
            {
                OstreamWriteFunctionGenerate(\@outOfLineCode, \%headerInfo);
            }
            # MushcoreXMLOstream
            if ($$commandsRef[$i] =~ /generate.*\bxml1(.*)\b/)
            {
                XMLIStreamWriteFunctionGenerate(\@outOfLineCode, \%headerInfo);
                XMLOStreamWriteFunctionGenerate(\@outOfLineCode, \%headerInfo);
            }
        }
    }
    SourceProcess::BlockReplace(\@$contentRef, \@outOfLineCode, 'outOfLineFunctions', @$contentRef);
}
