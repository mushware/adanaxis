#!/usr/bin/perl -w

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2002-2005.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

# $Id: SourceConditioner.pl,v 1.37 2005/06/20 14:30:31 southa Exp $
# $Log: SourceConditioner.pl,v $
# Revision 1.37  2005/06/20 14:30:31  southa
# Adanaxis work
#
# Revision 1.36  2005/06/14 13:25:30  southa
# Adanaxis work
#
# Revision 1.35  2005/05/20 10:26:23  southa
# Release work
#
# Revision 1.34  2005/05/19 13:01:55  southa
# Mac release work
#
# Revision 1.33  2005/04/19 19:23:10  southa
# Save and load config
#
# Revision 1.32  2005/03/25 19:13:46  southa
# GameDialogue work
#
# Revision 1.31  2005/02/10 12:33:52  southa
# Template fixes
#
# Revision 1.30  2005/02/03 21:02:47  southa
# Build fixes
#
# Revision 1.29  2005/01/29 18:27:30  southa
# Vertex buffer stuff
#
# Revision 1.28  2005/01/29 14:06:11  southa
# OpenGL buffers and extensions
#
# Revision 1.27  2004/09/27 22:42:08  southa
# MSVC compilation fixes
#
# Revision 1.26  2004/01/10 20:29:33  southa
# Form and rendering work
#
# Revision 1.25  2004/01/08 22:41:09  southa
# MushModel commands
#
# Revision 1.24  2004/01/06 00:34:56  southa
# MushPie testing
#
# Revision 1.23  2004/01/04 14:36:37  southa
# Handle 'inline' in source conditioner
#
# Revision 1.22  2004/01/02 21:13:04  southa
# Source conditioning
#
# Revision 1.21  2004/01/02 11:56:58  southa
# MushPie created
#
# Revision 1.20  2004/01/01 23:03:58  southa
# XCode fixes
#
# Revision 1.19  2003/10/17 12:27:17  southa
# Line end fixes and more mesh work
#
# Revision 1.18  2003/10/14 10:46:04  southa
# MeshMover creation
#
# Revision 1.17  2003/10/06 22:53:03  southa
# Removed old strip processing
#
# Revision 1.16  2003/10/03 23:39:31  southa
# XML polymorphs
#
# Revision 1.15  2003/10/02 23:33:35  southa
# XML polymorphic objects
#
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
'^CodeGen' => [
'/*****************************************************************************',
' *',
' * File: @FILENAME@',
' *',
' * Copyright: Andy Southgate 2002-2005',
' *',
' * All rights reserved.  Distribution prohibited.  For information, please',
' * contact the author via http://www.mushware.com/.',
' *',
' * This software carries NO WARRANTY of any kind.',
' *',
' ****************************************************************************/'
],
'^Adanaxis' => [
'/*****************************************************************************',
' *',
' * File: @FILENAME@',
' *',
' * Copyright: Andy Southgate 2005',
' *',
' * This file may be used and distributed under the terms of the Mushware',
' * software licence version 1.0, under the terms for \'Proprietary original',
' * source files\'.  If not supplied with this software, a copy of the licence',
' * can be obtained from Mushware Limited via http://www.mushware.com/.',
' * One of your options under that licence is to use and distribute this file',
' * under the terms of the GNU General Public Licence version 2.',
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
' * Author: Andy Southgate 2002-2005',
' *',
' * This file contains original work by Andy Southgate.  The author and his',
' * employer (Mushware Limited) irrevocably waive all of their copyright rights',
' * vested in this particular version of this file to the furthest extent',
' * permitted.  The author and Mushware Limited also irrevocably waive any and',
' * all of their intellectual property rights arising from said file and its',
' * creation that would otherwise restrict the rights of any party to use and/or',
' * distribute the use of, the techniques and methods used herein.  A written',
' * waiver can be obtained via http://www.mushware.com/.',
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
SourceProcess::AddArrayProcessor('\.h$', \&ProcessTouchCFile);

SourceProcess::Process('src');

sub XMLBaseGenerate($)
{
    my ($infoRef) = @_;
    $$infoRef{XML_BASES} = [];
    
    my $commandsRef = $$infoRef{COMMANDS};
    my $xmlBasesRef = $$infoRef{XML_BASES};
    foreach my $command (@$commandsRef)
    {
        if ($command =~ /^xml1base\s+(.*)$/)
        {
            foreach my $class (split(',', $1))
            {
                $class =~ s/\s//g; # remove whitespace
                push @$xmlBasesRef, $class;
            }
        }
    }
}

sub TemplateDataGenerate($$)
{
    my ($infoRef, $templateLine) = @_;
    
    if ($templateLine eq "")
    {
        $infoRef->{OUTER_CLASSNAME} = $infoRef->{CLASSNAME};
        $infoRef->{TEMPLATE_PREFIX} = "";
    }
    else
    {
        $infoRef->{TEMPLATE_PREFIX} = $templateLine;
        
        die "Malformed template directive" unless ($templateLine =~ /<(.*)>/);

        my $typedSuffix = $1;
        my $untypedSuffix = "<";
        
        while ($typedSuffix =~ s/,?\s*\w+\s+(\w+)//)
        {
            if ($untypedSuffix ne "<")
            {
                $untypedSuffix .= ", ";
            }
            $untypedSuffix .= $1;
        }
        $untypedSuffix .= ">";
        
        if ($untypedSuffix eq "<>")
        {
            die "Cannot decode template directive '$typedSuffix'";
        }
        
        $infoRef->{TEMPLATE_SUFFIX} = $untypedSuffix;  
        $infoRef->{OUTER_CLASSNAME} = $infoRef->{CLASSNAME}.$infoRef->{TEMPLATE_SUFFIX};
        $infoRef->{INLINE} = 1;
    }
}

sub HeaderInfoCreate($$)
{
    my ($infoRef, $contentRef) = @_;
    
    my $state = HS_SCAN_FOR_CLASS;
    my $lineNum = 0;
    
    foreach my $lineRef (@$contentRef)
    {
        my $line = "$lineRef";
        chomp $line;
        
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
            if ($line =~ /^template/)
            {
# Class definition or declaration line
                if ($line =~ /;\s*$/)
                {
# Declaration only - ignore
                }
                else
                {
                    $$infoRef{CLASS_TEMPLATE} = $line;
                }
            }
            elsif ($line =~ /^class/)
            {
                # Class definition or declaration line
                if ($line =~ /;\s*$/)
                {
                    # Declaration only - ignore
                    $$infoRef{CLASS_TEMPLATE} = "";
                }
                else
                {
                    ClassLineRead($infoRef, $line);
                    $state = HS_SCAN_FOR_MEMBERS;
                }
            }
            else
            {
                # Ignore template lines unless they're directly above the class line
                $$infoRef{CLASS_TEMPLATE} = "";
            }

            if ($comments =~ /^\s*:(.*)$/)
            {
                CommandsAdd($infoRef, $1);
            }
        }
        elsif ($state == HS_SCAN_FOR_MEMBERS)
        {
            if ($line =~ /^}\s*;\s*$/)
            {
                $$infoRef{CLOSING_LINE} = $lineNum;
                $state = HS_DONE;
            }
        
            if ($line =~ /^\s+(mutable\s+|const\s+)($gExprScopedType)\s*($gExprTemplateSuffix)?\s+($gExprVariableExpr)\s*;/)
            {
                my $template = $3;
                $template = "" unless defined($template);
                AttributeAdd($infoRef, $2.$template, $4, $comments);
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

    XMLBaseGenerate($infoRef);
    TemplateDataGenerate($infoRef, $$infoRef{CLASS_TEMPLATE});
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
    $name =~ s/\[.*\]//;
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
#    Access functions
#
##########################################################

sub AccessPrototypeGenerate($$)
{
    my ($outputRef, $infoRef) = @_;
    
    my $className = $$infoRef{CLASSNAME};
    
    die "No class found for standard functions" unless defined ($className);
    
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $comment = $$attributesRef[$i+2];
            my $trimmedAttr = VarNameTrim($attr);
            my $capitalisedAttr = uc(substr($trimmedAttr,0,1)).substr($trimmedAttr,1);
            
            if ($comment =~ /(:read\b|:readwrite)\b/)
            {
                push @$outputRef, "$gConfig{INDENT}const $type& ${capitalisedAttr}(void) const { return $attr; }";
            }
            if ($comment =~ /(:write\b|:readwrite)\b/)
            {
                push @$outputRef, "$gConfig{INDENT}void ${capitalisedAttr}Set(const $type& inValue) { $attr=inValue; }";
            }
            if ($comment =~ /:wref\b/)
            {
                push @$outputRef, "$gConfig{INDENT}// Writable reference for $attr";
                push @$outputRef, "$gConfig{INDENT}$type& ${capitalisedAttr}WRef(void) { return $attr; }";
            }
            if ($comment =~ /:toggle\b/)
            {
                push @$outputRef, "$gConfig{INDENT}void ${capitalisedAttr}Toggle(void) { $attr=!($attr); }";
            }                
        }
    }
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
    my $virtual = $$infoRef{VIRTUAL};

    die "No class found for standard functions" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}${virtual}const char *$gConfig{AUTO_PREFIX}Name(void) const;"; 
    push @$outputRef, "$gConfig{INDENT}${virtual}MushcoreVirtualObject *$gConfig{AUTO_PREFIX}Clone(void) const;"; 
    push @$outputRef, "$gConfig{INDENT}${virtual}MushcoreVirtualObject *$gConfig{AUTO_PREFIX}Create(void) const;"; 
    push @$outputRef, "$gConfig{INDENT}static MushcoreVirtualObject *$gConfig{AUTO_PREFIX}VirtualFactory(void);"; 
}

sub StandardFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for standard functions" unless defined ($className);
    
    die "Cannot generate 'standard' inline " if $$infoRef{INLINE};
    
    push @$outputRef,
$templatePrefix,
"const char *".
"${outerClassName}::$gConfig{AUTO_PREFIX}Name(void) const",
"{",
"    return \"$className\";",
"}",
$templatePrefix,
"MushcoreVirtualObject *".
"${outerClassName}::$gConfig{AUTO_PREFIX}Clone(void) const",
"{",
"    return new $className(*this);",
"}",
$templatePrefix,
"MushcoreVirtualObject *".
"${outerClassName}::$gConfig{AUTO_PREFIX}Create(void) const",
"{",
"    return new $className;",
"}",
$templatePrefix,
"MushcoreVirtualObject *".
"${outerClassName}::$gConfig{AUTO_PREFIX}VirtualFactory(void)",
"{",
"    return new $className;",
"}",
"namespace",
"{",
"void $gConfig{AUTO_PREFIX}Install(void)",
"{",
"    MushcoreFactory::Sgl().FactoryAdd(\"${outerClassName}\", ${className}::$gConfig{AUTO_PREFIX}VirtualFactory);",
"}",
"MushcoreInstaller $gConfig{AUTO_PREFIX}Installer($gConfig{AUTO_PREFIX}Install);",
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
    my $virtual = $$infoRef{VIRTUAL};

    die "No class found for ostream writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}${virtual}void $gConfig{AUTO_PREFIX}Print(std::ostream& ioOut) const;"; 
}

sub OstreamWriteFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for ostream writer" unless defined ($className);

    if ($templatePrefix ne "")
    {
        push @$outputRef, $templatePrefix;
    }
    my $decPrefix = $$infoRef{INLINE}?"inline ":"";

    push @$outputRef, "${decPrefix}void";
    push @$outputRef, "${outerClassName}::$gConfig{AUTO_PREFIX}Print(std::ostream& ioOut) const";
    push @$outputRef, "{";
    push @$outputRef, "    ioOut << \"[\";";
    my $xmlBases = $$infoRef{XML_BASES};
    if (defined($xmlBases))
    {
        foreach my $base (@$xmlBases)
        {
            push @$outputRef, "    ${base}::$gConfig{AUTO_PREFIX}Print(ioOut);";
        }
    }
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $comment = $$attributesRef[$i+2];
            next if ($comment =~ /:ignore\b/);
            my $trimmedAttr = VarNameTrim($attr);
            my $indirection = IndirectionGet($attr);
            my $comma = "";
            $comma = " << \", \"" unless ($i+3 == @$attributesRef);
           
            my $line = "    ioOut << \"$trimmedAttr=\" << ";
            if ($comment =~ /:fnpointer\b/)
            {
                $line .= '(void *)';   
            }
            $line .= TypeSpecial($type, $attr);
            
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
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for ostream operator" unless defined ($className);
    
    if ($templatePrefix ne "")
    {
        push @$outputRef, $templatePrefix;
    }
    push @$outputRef, "inline std::ostream&";
    push @$outputRef, "operator<<(std::ostream& ioOut, const $outerClassName& inObj)";
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
    my $virtual = $$infoRef{VIRTUAL};

    die "No class found for BasicOperators writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}${virtual}bool $gConfig{AUTO_PREFIX}Equals(const $className& inObj) const;"; 
}

sub BasicOperatorsFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for BasicOperators writer" unless defined ($className);

    if ($templatePrefix ne "")
    {
        push @$outputRef, $templatePrefix;
    }
    my $decPrefix = $$infoRef{INLINE}?"inline ":"";
        
    push @$outputRef,
"${decPrefix}bool",
"${outerClassName}::$gConfig{AUTO_PREFIX}Equals(const $className& inObj) const",
"{",
"    return 1";
    
    my $xmlBases = $$infoRef{XML_BASES};
    if (defined($xmlBases))
    {
        foreach my $base (@$xmlBases)
        {
            push @$outputRef, "        && ${base}::$gConfig{AUTO_PREFIX}Equals(inObj)";
        }
    }
    
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $comment = $$attributesRef[$i+2];
            next if ($comment =~ /:ignore\b/);
            next if ($comment =~ /\bnobasic\b/);
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
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for BasicOperators writer" unless defined ($className);

    push @$outputRef,
$templatePrefix,
"inline bool",
"operator==(const $outerClassName& inA, const $outerClassName& inB)",
"{",
"    return inA.$gConfig{AUTO_PREFIX}Equals(inB);",
"}",
$templatePrefix,
"inline bool",
"operator!=(const $outerClassName& inA, const $outerClassName& inB)",
"{",
"    return !inA.$gConfig{AUTO_PREFIX}Equals(inB);",
"}";
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
    my $virtual = $$infoRef{VIRTUAL};

    die "No class found for XMLIStream writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}${virtual}bool $gConfig{AUTO_PREFIX}XMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);"; 
}

sub XMLIStreamWriteFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for XMLIStream writer" unless defined ($className);
    
    if ($templatePrefix ne "")
    {
        push @$outputRef, $templatePrefix;
    }
    my $decPrefix = $$infoRef{INLINE}?"inline ":"";
   
    push @$outputRef,
"${decPrefix}bool",
"${outerClassName}::$gConfig{AUTO_PREFIX}XMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)",
"{",
"    if (inTagStr == \"obj\")",
"    {",
"        AutoInputPrologue(ioIn);",        
"        ioIn >> *this;",
"        AutoInputEpilogue(ioIn);",        
"    }";

    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $comment = $$attributesRef[$i+2];
            next if ($comment =~ /:ignore\b/);
            my $baseAttr = VarBaseNameGet($attr);
            my $trimmedAttr = VarNameTrim($attr);
            push @$outputRef,
"    else if (inTagStr == \"$trimmedAttr\")",
"    {",
"        ioIn >> $baseAttr;",
"    }";

        }
    }
    my $xmlBases = $$infoRef{XML_BASES};
    if (defined($xmlBases))
    {
        foreach my $base (@$xmlBases)
        {
            push @$outputRef,
"    else if (${base}::$gConfig{AUTO_PREFIX}XMLDataProcess(ioIn, inTagStr))",
"    {",
"        // Tag consumed by base class",
"    }";
        }
    }
    push @$outputRef,
"    else",
"    {",
"        return false;",
"    }",
"    return true;",        
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
    my $virtual = $$infoRef{VIRTUAL};

    die "No class found for XMLOStream writer" unless defined ($className);
    
    push @$outputRef, "$gConfig{INDENT}${virtual}void $gConfig{AUTO_PREFIX}XMLPrint(MushcoreXMLOStream& ioOut) const;"; 
}

sub XMLOStreamWriteFunctionGenerate($$)
{
    my ($outputRef, $infoRef) = @_;

    my $className = $$infoRef{CLASSNAME};
    my $outerClassName = $$infoRef{OUTER_CLASSNAME};
    my $templatePrefix = $$infoRef{TEMPLATE_PREFIX};

    die "No class found for XMLOStream writer" unless defined ($className);
    
    if ($templatePrefix ne "")
    {
        push @$outputRef, $templatePrefix;
    }
    
    my $decPrefix = $$infoRef{INLINE}?"inline ":"";
    
    push @$outputRef, "${decPrefix}void";
    push @$outputRef, "${outerClassName}::$gConfig{AUTO_PREFIX}XMLPrint(MushcoreXMLOStream& ioOut) const";
    push @$outputRef,
"{";
    my $xmlBases = $$infoRef{XML_BASES};
    if (defined($xmlBases))
    {
        foreach my $base (@$xmlBases)
        {
            push @$outputRef, "    ${base}::$gConfig{AUTO_PREFIX}XMLPrint(ioOut);";
        }
    }
    
    my $attributesRef = $$infoRef{ATTRIBUTES};
    if (defined($attributesRef))
    {
        for (my $i=0; $i < @$attributesRef; $i += 3)
        {
            my $type = $$attributesRef[$i];
            my $attr = $$attributesRef[$i+1];
            my $comment = $$attributesRef[$i+2];
            next if ($comment =~ /:(xml|)ignore\b/);
            my $trimmedAttr = VarNameTrim($attr);
            my $indirection = IndirectionGet($attr);
            
            push @$outputRef,
"    ioOut.TagSet(\"$trimmedAttr\");";
           
            if ($indirection > 0)
            {
                push @$outputRef,
"    ioOut << ".VarBaseNameGet($attr).";";
            }
            else
            {
                push @$outputRef,
"    ioOut << ".$attr.";";
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

    # OldHeaderStrip(\@$contentRef);
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

    # OldIncludeGuardStrip(\@$contentRef, $filename);
    IncludeGuardGenerate(\@$contentRef, $filename);
}

sub ProcessTouchCFile($$)
{
    my ($contentRef, $filename) = @_;
    my $counterpart = $filename;
    $counterpart =~ s/\.h$/\.cpp/;
    if ( -f $counterpart )
    {
        SourceProcess::ExtraFile($counterpart);
    }
    else
    {
        print "Header $filename has no counterpart $counterpart\n";
    }
}

sub DefinitionsWrite($$$)
{
    my ($outputRef, $infoRef, $command) = @_;
    
    # Standard
    if ($command =~ /\bgenerate.*\bstandard\b/)
    {            
        StandardFunctionGenerate($outputRef, $infoRef);
    }
    # BasicOperators
    if ($command =~ /\bgenerate.*\bbasic(.*)\b/)
    {            
        BasicOperatorsFunctionGenerate($outputRef, $infoRef);
    }
    # std::ostream
    if ($command =~ /\bgenerate.*\bostream\b/)
    {
        OstreamWriteFunctionGenerate($outputRef, $infoRef);
    }
    # MushcoreXMLOstream
    if ($command =~ /\bgenerate.*\bxml1(.*)\b/)
    {
        XMLIStreamWriteFunctionGenerate($outputRef, $infoRef);
        XMLOStreamWriteFunctionGenerate($outputRef, $infoRef);
    }
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
        $headerInfo{INLINE} = 0;
        $headerInfo{VIRTUAL} = "";
        
        # Member accessors and modifers
        AccessPrototypeGenerate(\@classPrototypes, \%headerInfo);

        for (my $i=0; $i < @$commandsRef; $i += 1)
        {
            $headerInfo{INLINE} = 1 if $$commandsRef[$i] =~ /\binline\b/;
            $headerInfo{INLINE} = 0 if $$commandsRef[$i] =~ /\bnotinline\b/;
            $headerInfo{VIRTUAL} = "virtual " if $$commandsRef[$i] =~ /\bvirtual\b/;
            $headerInfo{VIRTUAL} = "" if $$commandsRef[$i] =~ /\bnotvirtual\b/;
            
            # Standard functions
            if ($$commandsRef[$i] =~ /\bgenerate.*\bstandard\b/)
            {            
                StandardPrototypeGenerate(\@classPrototypes, \%headerInfo);
            }
            # BasicOperators
            if ($$commandsRef[$i] =~ /\bgenerate.*\bbasic(.*)\b/)
            {            
                BasicOperatorsPrototypeGenerate(\@classPrototypes, \%headerInfo);
                BasicOperatorsInlineGenerate(\@inlineHeader, \%headerInfo);
            }
            # std::ostream
            if ($$commandsRef[$i] =~ /\bgenerate.*\bostream\b/)
            {
                OstreamWritePrototypeGenerate(\@classPrototypes, \%headerInfo);
                OstreamOperatorGenerate(\@inlineHeader, \%headerInfo);
            }
 
            # MushcoreXMLOstream
            if ($$commandsRef[$i] =~ /\bgenerate.*\bxml1(.*)\b/)
            {
                XMLIStreamWritePrototypeGenerate(\@classPrototypes, \%headerInfo);
                # XMLIStreamOperatorGenerate(\@inlineNamespaced, \%headerInfo);
                XMLOStreamWritePrototypeGenerate(\@classPrototypes, \%headerInfo);
                # XMLOStreamOperatorGenerate(\@inlineheader, \%headerInfo);
            }
            
            if ($headerInfo{INLINE})
            {
                DefinitionsWrite(\@inlineHeader, \%headerInfo, $$commandsRef[$i]);
            }
        }
    }
    
    if (scalar @inlineNamespaced > 0)
    {
        # Add the namespace shell
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
    $headerInfo{INLINE} = 0;
    $headerInfo{VIRTUAL} = "";
    
    if (defined($commandsRef))
    {
        for (my $i=0; $i < @$commandsRef; $i += 1)
        {
            $headerInfo{INLINE} = 1 if $$commandsRef[$i] =~ /\binline\b/;
            $headerInfo{INLINE} = 0 if $$commandsRef[$i] =~ /\bnotinline\b/;
            $headerInfo{VIRTUAL} = "virtual " if $$commandsRef[$i] =~ /\bvirtual\b/;
            $headerInfo{VIRTUAL} = "" if $$commandsRef[$i] =~ /\bnotvirtual\b/;
            
            unless ($headerInfo{INLINE})
            {
                DefinitionsWrite(\@outOfLineCode, \%headerInfo, $$commandsRef[$i]);
            }
        }
    }
    SourceProcess::BlockReplace(\@$contentRef, \@outOfLineCode, 'outOfLineFunctions', @$contentRef);
}
