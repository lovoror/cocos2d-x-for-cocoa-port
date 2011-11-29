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
#ifndef __COCOS_GLPROGRAM_H__
#define __COCOS_GLPROGRAM_H__

#include "CCGL.h"
#include "CCObject.h"
#if CC_ENABLE_GL_GLES2

enum {
	kCCVertexAttrib_Position,
	kCCVertexAttrib_Color,
	kCCVertexAttrib_TexCoords,
	
	kCCVertexAttrib_MAX,
};

enum {
	kCCUniformMVPMatrix,
	kCCUniformSampler,

	kCCUniform_MAX,
};

#define kCCShader_PositionTextureColor		"ShaderPositionTextureColor"
#define kCCShader_PositionColor				"ShaderPositionColor"
#define kCCShader_PositionTexture			"ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor	"ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color	"ShaderPositionTextureA8Color"

// uniform names
#define kCCUniformMVPMatrix_s			"u_MVPMatrix"
#define kCCUniformSampler_s				"u_texture"

// Attribute names
#define	kCCAttributeNameColor			"a_color"
#define	kCCAttributeNamePosition		"a_position"
#define	kCCAttributeNameTexCoord		"a_texCoord"

namespace   cocos2d {
    
    
typedef void (*GLInfoFunction)(GLuint program, 
                                   GLenum pname, 
                                   GLint* params);
typedef void (*GLLogFunction) (GLuint program, 
                                   GLsizei bufsize, 
                                   GLsizei* length, 
                                   GLchar* infolog);
/** GLProgram
 */
class GLProgram : public CCObject 
{
public:
    
    GLProgram(const char* vShaderFilename, const char* fShaderFilename);
    
    ~GLProgram(void);
    
    void addAttribute(const char* attributeName, GLuint index);
    
    bool link(void);
    
    void use(void);
    /* It will create 3 uniforms:
     - kCCUniformPMatrix
     - kCCUniformMVMatrix
     - kCCUniformSampler
     
     And it will bind "kCCUniformSampler" to 0
     
     @since v2.0.0
     */
    void updateUniforms(void);
    
    char* vertexShaderLog(void);
    
    char* fragmentShaderLog(void);
    
    char* programLog(void);
    
    char* description(void);
private:
    
    bool compileShader(GLuint* shader, GLenum type,const char* file);
    
    char* logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc);
    
public:
	GLuint          program_,
					vertShader_,
					fragShader_;
	
	GLint			uniforms_[kCCUniform_MAX];
};

}

#endif
#endif