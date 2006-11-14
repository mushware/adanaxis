//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLShader.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } bQ20AxcHOjJNfCG2TxDNVg
/*
 * $Id: MushGLShader.cpp,v 1.7 2006/10/06 11:54:57 southa Exp $
 * $Log: MushGLShader.cpp,v $
 * Revision 1.7  2006/10/06 11:54:57  southa
 * Scaled rendering
 *
 * Revision 1.6  2006/09/12 15:28:50  southa
 * World sphere
 *
 * Revision 1.5  2006/09/10 10:30:52  southa
 * Shader billboarding
 *
 * Revision 1.4  2006/09/09 15:59:28  southa
 * Shader colour calculations
 *
 * Revision 1.3  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.2  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.1  2006/09/07 10:02:37  southa
 * Shader interface
 *
 */

#include "MushGLShader.h"

#include "MushGLAttribs.h"
#include "MushGLProjection.h"
#include "MushGLUtil.h"
#include "MushGLV.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLShader);

MushGLShader::MushGLShader() :
    m_programHandle(kGLHandleNull),
    m_fragmentShaderHandle(kGLHandleNull),
    m_vertexShaderHandle(kGLHandleNull),
    m_made(false)
{
}

std::string
MushGLShader::SourceGet(Mushware::GLHandle inShader) const
{
    ostringstream sourceStream;
    if (inShader != kGLHandleNull)
    {
        GLint subType;
        MushGLV::Sgl().GetObjectParameteriv(inShader,
                                            GL_OBJECT_SUBTYPE_ARB,
                                            &subType);
        std::string subTypeStr;
        switch (subType)
        {
            case GL_FRAGMENT_SHADER_ARB:
                subTypeStr = "Fragment";
                break;
                
            case GL_VERTEX_SHADER_ARB:
                subTypeStr = "Vertex";
                break;
                
            default:
                subTypeStr = "Unknown";
                break;            
        }
        
        
        GLint sourceSize;
        MushGLV::Sgl().GetObjectParameteriv(inShader,
                                      GL_OBJECT_SHADER_SOURCE_LENGTH_ARB,
                                      &sourceSize);
        sourceStream << subTypeStr << " shader, " << sourceSize << " source bytes, ";
        sourceStream << (CompileStatusGet(inShader) ? "compiled" : "not compiled") << endl;
        
        GLChar sourceBuffer[sourceSize+2];
        sourceBuffer[sourceSize+1] = 'A';
        MushGLV::Sgl().GetShaderSource(inShader, sourceSize, NULL, sourceBuffer);
        if (sourceBuffer[sourceSize+1] != 'A')
        {
            throw MushcoreLogicFail("Buffer overrun in GetShaderSource");
        }
        if (sourceSize > 0 && sourceBuffer[sourceSize-1] != '\0')
        {
            MushcoreLog::Sgl().WarningLog() << "GetShaderSource terminator not where expected" << endl;
        }
        
        sourceStream << sourceBuffer;
    }
    return sourceStream.str();
}

std::string
MushGLShader::InfoLogGet(Mushware::GLHandle inShader) const
{
    ostringstream infoLogStream;
    if (inShader != kGLHandleNull)
    {      
        GLint infoLogSize;
        MushGLV::Sgl().GetObjectParameteriv(inShader,
                                            GL_OBJECT_INFO_LOG_LENGTH_ARB,
                                            &infoLogSize);
        GLChar infoLogBuffer[infoLogSize+2];
        infoLogBuffer[infoLogSize+1] = 'A';
        MushGLV::Sgl().GetInfoLog(inShader, infoLogSize, NULL, infoLogBuffer);
        if (infoLogBuffer[infoLogSize+1] != 'A')
        {
            throw MushcoreLogicFail("Buffer overrun in GetShaderSource");
        }
        if (infoLogSize > 0 && infoLogBuffer[infoLogSize-1] != '\0')
        {
            MushcoreLog::Sgl().WarningLog() << "GetShaderSource terminator not where expected" << endl;
        }
        
        infoLogStream << infoLogBuffer;
    }
    return infoLogStream.str();
}

bool
MushGLShader::CompileStatusGet(Mushware::GLHandle inShader) const
{
    GLint compileStatus = 0;
    if (inShader != kGLHandleNull)
    {
        MushGLV::Sgl().GetObjectParameteriv(inShader,
                                            GL_OBJECT_COMPILE_STATUS_ARB,
                                            &compileStatus);        
    }
    return (compileStatus == 1);
}

bool
MushGLShader::LinkStatusGet(Mushware::GLHandle inProgram) const
{
    GLint linkStatus = 0;
    if (inProgram != kGLHandleNull)
    {
        MushGLV::Sgl().GetObjectParameteriv(inProgram,
                                            GL_OBJECT_LINK_STATUS_ARB,
                                            &linkStatus);        
    }
    return (linkStatus == 1);
}

bool
MushGLShader::ValidateStatusGet(Mushware::GLHandle inProgram) const
{
    GLint validateStatus = 0;
    if (inProgram != kGLHandleNull)
    {
        MushGLV::Sgl().GetObjectParameteriv(inProgram,
                                            GL_OBJECT_VALIDATE_STATUS_ARB,
                                            &validateStatus);        
    }
    return (validateStatus == 1);
}

void
MushGLShader::Dump(std::ostream& ioOut) const
{
    ioOut << "Program handle " << m_programHandle << ", fragment shader handle " << m_fragmentShaderHandle << ", vertex shader handle " << m_vertexShaderHandle << endl;
    if (m_programHandle == kGLHandleNull)
    {
        ioOut << "Program not compiled.  Local source follows." << endl;
        ioOut << "Fragment shader: " << endl << m_fragmentShader << endl;
        ioOut << "Vertex shader: " << endl << m_vertexShader << endl;
    }
    else
    {
        std::string infoLog;
        ioOut << SourceGet(m_fragmentShaderHandle) << endl;
        infoLog = InfoLogGet(m_fragmentShaderHandle);
        if (infoLog != "") ioOut << "Fragment shader info:" << endl << infoLog << endl;
        ioOut << SourceGet(m_vertexShaderHandle) << endl;
        infoLog = InfoLogGet(m_vertexShaderHandle);
        if (infoLog != "") ioOut << "Vertex shader info:" << endl << infoLog << endl;
        
        ioOut << "Program " << (LinkStatusGet(m_programHandle) ? "linked sucessfully" : "not linked" ) << endl;
        infoLog = InfoLogGet(m_programHandle);
        if (infoLog != "") ioOut << "Program info:" << endl << infoLog << endl;
    }
}

void
MushGLShader::UniformDump(std::ostream& ioOut) const
{
    ioOut << "Uniform variables:" << endl;

    if (m_programHandle != kGLHandleNull)
    {
        GLint numUniforms = 0;
        MushGLV::Sgl().GetObjectParameteriv(m_programHandle,
                                            GL_OBJECT_ACTIVE_UNIFORMS_ARB,
                                            &numUniforms);
        GLint maxLength = 0;
        MushGLV::Sgl().GetObjectParameteriv(m_programHandle,
                                            GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB,
                                            &maxLength);

        for (GLint i=0; i<numUniforms; ++i)
        {
            GLChar buffer[maxLength+2];
            GLsizei length = 0;
            GLint size = 0;
            GLenum type = 0;
            
            MushGLV::Sgl().GetActiveUniform(m_programHandle,
                                            i,
                                            maxLength,
                                            &length,
                                            &size,
                                            &type,
                                            buffer);
            
            ioOut << "Uniform " << i << " " << MushGLUtil::DataTypeToString(type);
            ioOut << " (size " << size << "): " << buffer << endl;                      
        }
    }
}    

GLint
MushGLShader::UniformLocationGet(const std::string& inName)
{
    GLint retVal = -1;
    
    if (m_programHandle != kGLHandleNull)
    {
        retVal = MushGLV::Sgl().GetUniformLocation(m_programHandle, inName.c_str());
    }
    
    return retVal;
}


void
MushGLShader::AttribsApply(const MushGLAttribs& inAttribs)
{
    const Mushware::t4x4o4Val& projMattress = inAttribs.Projection().Mattress();
    
    Mushware::t4x4o4Val modelViewMattress;
    
    switch (inAttribs.TransformType())
    {
        case MushMesh4Mesh::kTransformTypeNormal:
            modelViewMattress = inAttribs.View() * inAttribs.Model();
            break;
    
        case MushMesh4Mesh::kTransformTypeBillboard:
        {
            modelViewMattress = inAttribs.View() * inAttribs.Model();
            modelViewMattress.MatrixSet(inAttribs.Model().Matrix());
        }
        break;

        case MushMesh4Mesh::kTransformTypeBillboardRandom:
        {
            modelViewMattress = inAttribs.View() * inAttribs.Model();
            modelViewMattress.MatrixSet(inAttribs.Model().Matrix());
        }
        break;
            
        default:
            throw MushcoreDataFail("AttribsApply: Bad transform type");
            break;
    }
    
    MushGLUtil::ProjectionMatrixSet(projMattress.Matrix());
    MushGLUtil::ModelViewMatrixSet(modelViewMattress.Matrix());
    // The gl_ProjectionModelView matrix is calculated internally by OpenGL
    
    if (m_mush_ProjectionOffset >= 0)
    {
        t4GLVal projOffset(projMattress.Offset());
        MushGLV::Sgl().Uniform4fv(m_mush_ProjectionOffset, 1, &projOffset[0]);
    }
    if (m_mush_ModelViewOffset >= 0)
    {
        t4GLVal modelViewOffset(modelViewMattress.Offset());
        MushGLV::Sgl().Uniform4fv(m_mush_ModelViewOffset, 1, &modelViewOffset[0]);
    }
    if (m_mush_ModelViewProjectionOffset >= 0)
    {
        // Need to calculate the offset
        Mushware::t4x4o4Val mvpMattress(projMattress * modelViewMattress);
        t4GLVal mvpOffset(mvpMattress.Offset());
        MushGLV::Sgl().Uniform4fv(m_mush_ModelViewProjectionOffset, 1, &mvpOffset[0]);
    }
    if (m_mush_FValue >= 0)
    {
        MushGLV::Sgl().Uniform1f(m_mush_FValue, inAttribs.Projection().FValue());
    }
    
    // Apply colours
    const MushGLAttribs::tColours& coloursRef = inAttribs.Colours();
    
    U32 colourSize = coloursRef.size();
    
    if (colourSize > kNumColourAttrib)
    {
        throw MushcoreRequestFail("Too many colour attributes");
    }
    MUSHCOREASSERT(m_mush_Colours.size() == kNumColourAttrib);
    
    for (U32 i=0; i < colourSize; ++i)
    {
        MushGLV::Sgl().Uniform4fv(m_mush_Colours[i], 1, &coloursRef[i][0]);
    }
}    

void
MushGLShader::Make(void)
{
    if (!MushGLV::Sgl().ContextValid())
    {
        throw MushcoreRequestFail("Attempt to make GL shader before OpenGL is ready");
    }
    
    MushGLUtil::CheckGLError("Before creating shader");
    if (m_fragmentShader != "" && m_fragmentShaderHandle == kGLHandleNull)
    {
        m_fragmentShaderHandle = MushGLV::Sgl().CreateShaderObject(GL_FRAGMENT_SHADER_ARB);
    }
    if (m_vertexShader != "" && m_vertexShaderHandle == kGLHandleNull)
    {
        m_vertexShaderHandle = MushGLV::Sgl().CreateShaderObject(GL_VERTEX_SHADER_ARB);
    }
    if (m_programHandle == kGLHandleNull)
    {
        m_programHandle = MushGLV::Sgl().CreateProgramObject();
    }
    MushGLUtil::ThrowIfGLError("Creating shader handles");
    
    if (m_fragmentShaderHandle != kGLHandleNull)
    {
        const GLChar *charPtr = m_fragmentShader.c_str();
        MushGLV::Sgl().ShaderSource(m_fragmentShaderHandle,
                                    1,
                                    &charPtr,
                                    NULL);
    }
    
    if (m_vertexShaderHandle != kGLHandleNull)
    {
        const GLChar *charPtr = m_vertexShader.c_str();
        MushGLV::Sgl().ShaderSource(m_vertexShaderHandle,
                                    1,
                                    &charPtr,
                                    NULL);
    }
    
    MushGLUtil::ThrowIfGLError("Adding shader source");

    if (m_fragmentShaderHandle != kGLHandleNull)
    {
        MushGLV::Sgl().CompileShader(m_fragmentShaderHandle);

        std::string infoLog = InfoLogGet(m_fragmentShaderHandle);

        if (!CompileStatusGet(m_fragmentShaderHandle))
        {
#ifdef MUSHCORE_DEBUG
            Dump(MushcoreLog::Sgl().ErrorLog());
#endif
            throw MushcoreSyntaxFail("Fragment shader compilation failed: " + infoLog);
        }
        if (infoLog != "")
        {
            MushcoreLog::Sgl().InfoLog() << "Shader compilation info:" << endl;
            MushcoreLog::Sgl().InfoLog() << infoLog << endl;
        }
    }
    
    if (m_vertexShaderHandle != kGLHandleNull)
    {
        MushGLV::Sgl().CompileShader(m_vertexShaderHandle);

        std::string infoLog = InfoLogGet(m_vertexShaderHandle);

        if (!CompileStatusGet(m_vertexShaderHandle))
        {
#ifdef MUSHCORE_DEBUG
            Dump(MushcoreLog::Sgl().ErrorLog());
#endif
            throw MushcoreSyntaxFail("Vertex shader compilation failed: " + infoLog);
        }
        if (infoLog != "")
        {
            MushcoreLog::Sgl().InfoLog() << "Shader compilation info:" << endl;
            MushcoreLog::Sgl().InfoLog() << infoLog << endl;
        }
    }
    
    MushGLUtil::ThrowIfGLError("Compiling shader");

    if (m_fragmentShaderHandle != kGLHandleNull)
    {
        MushGLV::Sgl().AttachObject(m_programHandle, m_fragmentShaderHandle);
    }
    if (m_vertexShaderHandle != kGLHandleNull)
    {
        MushGLV::Sgl().AttachObject(m_programHandle, m_vertexShaderHandle);
    }
    
    MushGLUtil::ThrowIfGLError("Attaching shader objects to program");
    
    MushGLV::Sgl().LinkProgram(m_programHandle);
    
    std::string infoLog = InfoLogGet(m_programHandle);
    
    if (!LinkStatusGet(m_programHandle))
    {
#ifdef MUSHCORE_DEBUG
        Dump(MushcoreLog::Sgl().ErrorLog());
#endif
        throw MushcoreSyntaxFail("Shader linker failed: " + infoLog);
    }
    if (infoLog != "")
    {
        MushcoreLog::Sgl().InfoLog() << "Shader link info:" << endl;
        MushcoreLog::Sgl().InfoLog() << infoLog << endl;
    }
    
    MushGLUtil::ThrowIfGLError("Linking shader");
    
#ifdef MUSHCORE_DEBUG
    MushGLV::Sgl().ValidateProgram(m_programHandle);
    
    infoLog = InfoLogGet(m_programHandle);
    
    if (!ValidateStatusGet(m_programHandle))
    {
        Dump(MushcoreLog::Sgl().ErrorLog());
        throw MushcoreSyntaxFail("Shader validation failed: " + infoLog);
    }
    if (infoLog != "")
    {
        MushcoreLog::Sgl().InfoLog() << "Shader validation info:" << endl;
        MushcoreLog::Sgl().InfoLog() << infoLog << endl;
    } 
#endif
    
    // Read standard uniform variable locations
    m_mush_ProjectionOffset = UniformLocationGet("mush_ProjectionOffset");
    m_mush_ModelViewOffset = UniformLocationGet("mush_ModelViewOffset");
    m_mush_ModelViewProjectionOffset = UniformLocationGet("mush_ModelViewProjectionOffset");
    m_mush_FValue = UniformLocationGet("mush_FValue");
    
    m_mush_Colours.resize(kNumColourAttrib);
    for (U32 i=0; i<m_mush_Colours.size(); ++i)
    {
        ostringstream nameStream;
        nameStream << "mush_Colour" << i;
        m_mush_Colours[i] = UniformLocationGet(nameStream.str());
    }
    
    m_made = true;
}

void
MushGLShader::Bind(void)
{
    if (!m_made)
    {
        Make();
    }
    if (m_made)
    {
        MushGLUtil::CheckGLError();
        MushGLV::Sgl().UseProgramObject(m_programHandle);
        MushGLUtil::ThrowIfGLError("Binding shader");
    }
}

void
MushGLShader::Test(void)
{
    Bind();
    Purge();
}

void
MushGLShader::Purge(void)
{
    MushGLUtil::CheckGLError();

    m_made = false;
    
    if (m_programHandle != kGLHandleNull)
    {
        MushGLV::Sgl().DeleteObject(m_programHandle);
        m_programHandle = kGLHandleNull;
    }
    if (m_fragmentShaderHandle != kGLHandleNull)
    {
        MushGLV::Sgl().DeleteObject(m_fragmentShaderHandle);
        m_fragmentShaderHandle = kGLHandleNull;
    }
    if (m_vertexShaderHandle != kGLHandleNull)
    {
        MushGLV::Sgl().DeleteObject(m_vertexShaderHandle);
        m_vertexShaderHandle = kGLHandleNull;
    }
    
    MushGLUtil::CheckGLError("Purging shader");
}    

//%outOfLineFunctions {

const char *MushGLShader::AutoName(void) const
{
    return "MushGLShader";
}

MushcoreVirtualObject *MushGLShader::AutoClone(void) const
{
    return new MushGLShader(*this);
}

MushcoreVirtualObject *MushGLShader::AutoCreate(void) const
{
    return new MushGLShader;
}

MushcoreVirtualObject *MushGLShader::AutoVirtualFactory(void)
{
    return new MushGLShader;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLShader", MushGLShader::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLShader::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "programHandle=" << m_programHandle << ", ";
    ioOut << "fragmentShaderHandle=" << m_fragmentShaderHandle << ", ";
    ioOut << "vertexShaderHandle=" << m_vertexShaderHandle << ", ";
    ioOut << "fragmentShader=" << m_fragmentShader << ", ";
    ioOut << "vertexShader=" << m_vertexShader << ", ";
    ioOut << "made=" << m_made << ", ";
    ioOut << "mush_ProjectionOffset=" << m_mush_ProjectionOffset << ", ";
    ioOut << "mush_ModelViewOffset=" << m_mush_ModelViewOffset << ", ";
    ioOut << "mush_ModelViewProjectionOffset=" << m_mush_ModelViewProjectionOffset << ", ";
    ioOut << "mush_Colours=" << m_mush_Colours << ", ";
    ioOut << "mush_FValue=" << m_mush_FValue;
    ioOut << "]";
}
bool
MushGLShader::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "fragmentShader")
    {
        ioIn >> m_fragmentShader;
    }
    else if (inTagStr == "vertexShader")
    {
        ioIn >> m_vertexShader;
    }
    else if (inTagStr == "made")
    {
        ioIn >> m_made;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLShader::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("fragmentShader");
    ioOut << m_fragmentShader;
    ioOut.TagSet("vertexShader");
    ioOut << m_vertexShader;
    ioOut.TagSet("made");
    ioOut << m_made;
}
//%outOfLineFunctions } +heUpytkt5CS/rZdXOBScw
