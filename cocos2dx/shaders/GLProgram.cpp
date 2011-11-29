/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "GLProgram.h"
#include "ccGLState.h"
#include "ccMacros.h"
#include "CCFileUtils.h"
#include <stdlib.h>

#if CC_ENABLE_GL_GLES2

namespace   cocos2d {
    
GLProgram::GLProgram(const char* vShaderFilename,const char* fShaderFilename)
{
    program_ = glCreateProgram();
        
    vertShader_ = fragShader_ = 0;

    if( vShaderFilename ) {
        const char *fullname = CCFileUtils::fullPathFromRelativePath(vShaderFilename);

        if (!this->compileShader(&vertShader_, GL_VERTEX_SHADER, fullname))
            CCLOG("cocos2d: ERROR: Failed to compile vertex shader: %s", vShaderFilename);
    }
        
    // Create and compile fragment shader
    if( fShaderFilename ) {
        const char *fullname = CCFileUtils::fullPathFromRelativePath(fShaderFilename);

        if (!this->compileShader(&fragShader_, GL_FRAGMENT_SHADER, fullname))
            CCLOG("cocos2d: ERROR: Failed to compile fragment shader: %s", fShaderFilename);
    }
        
    if( vertShader_ )
        glAttachShader(program_, vertShader_);
		
    if( fragShader_ )
        glAttachShader(program_, fragShader_);
}

char * GLProgram::description(void)
{
    char *ret = new char[100];
	sprintf(ret, "<GLProgram = %p | Program = %i, VertexShader = %i, FragmentShader = %i>", this, program_, vertShader_, fragShader_);
	return ret;
}

bool GLProgram::compileShader(GLuint * shader, GLenum type, const char* file)
{
    GLint status;
    const GLchar *source;
    unsigned long shaderlen = 0;
    
    source = (GLchar *)CCFileUtils::getFileData(file, "r", &shaderlen);
    if (!source)
        return false;
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	
	if( ! status ) {
        char* logchar;
		if( type == GL_VERTEX_SHADER ){
            logchar = this->vertexShaderLog();
			CCLOG("cocos2d: %s: %s", file, logchar);
		}else{
            logchar = this->fragmentShaderLog();
			CCLOG("cocos2d: %s: %s", file, logchar );
        }
        free(logchar);
	}
    return status == GL_TRUE;
}

void GLProgram::addAttribute(const char * attributeName, GLuint index)
{
	glBindAttribLocation(program_, 
						 index,
						 attributeName);
}

void GLProgram::updateUniforms(void)
{
	// Since sample most probably won't change, set it to 0 now.
	
	uniforms_[kCCUniformMVPMatrix] = glGetUniformLocation(program_, kCCUniformMVPMatrix_s);

	uniforms_[kCCUniformSampler] = glGetUniformLocation(program_, kCCUniformSampler_s);
	
	ccGLUseProgram( program_ );
	glUniform1i( uniforms_[kCCUniformSampler], 0 );
}	

bool GLProgram::link(void)
{    
    glLinkProgram(program_);

#if DEBUG
	GLint status;
    glValidateProgram(program_);
    
    glGetProgramiv(program_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
		CCLOG(@"cocos2d: ERROR: Failed to link program: %p", program_);
		if( vertShader_ )
			glDeleteShader( vertShader_ );
		if( fragShader_ )
			glDeleteShader( fragShader_ );
		ccGLDeleteProgram( program_ );
		vertShader_ = fragShader_ = program_ = 0;
        return false;
	}
#endif
    
    if (vertShader_)
        glDeleteShader(vertShader_);
    if (fragShader_)
        glDeleteShader(fragShader_);
	
	vertShader_ = fragShader_ = 0;
		
    return true;
}

void GLProgram::use(void)
{
    ccGLUseProgram(program_);
}

char * GLProgram::logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc)
{
    GLint logLength = 0, charsWritten = 0;
    
    infoFunc(object, GL_INFO_LOG_LENGTH, &logLength);    
    if (logLength < 1)
        return NULL;
    
    char *logBytes = (char *)malloc(logLength);
    logFunc(object, logLength, &charsWritten, logBytes);
    return (logBytes);
}

char * GLProgram::vertexShaderLog(void)
{
    return this->logForOpenGLObject(vertShader_, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
    
}

char * GLProgram::fragmentShaderLog(void)
{
	return this->logForOpenGLObject(fragShader_, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

char * GLProgram::programLog(void)
{
    return this->logForOpenGLObject(program_, (GLInfoFunction)&glGetProgramiv ,(GLLogFunction)&glGetProgramInfoLog);
}
    
GLProgram::~GLProgram(void)
{
    char* logchar = this->description();
    CCLOGINFO( "cocos2d: deallocing %s", logchar);
    delete (logchar);
    
    if (program_)
        ccGLDeleteProgram(program_);
    
}

}

#endif