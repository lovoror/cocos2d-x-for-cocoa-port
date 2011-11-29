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


#include "ccGLState.h"
#include "GLProgram.h"
#include "CCDirector.h"
#include "ccConfig.h"
#if CC_ENABLE_GL_GLES2

// extern
#include "kazmath/GL/matrix.h"
#include "kazmath/kazmath.h"

namespace   cocos2d {
    
    
static GLuint	_ccCurrentProjectionMatrix = -1;
static bool		_vertexAttribPosition = false;
static bool		_vertexAttribColor = false;
static bool		_vertexAttribTexCoords = false;

#if CC_ENABLE_GL_STATE_CACHE
static GLuint	_ccCurrentShaderProgram = -1;
static GLuint	_ccCurrentBoundTexture = -1;
static GLenum	_ccBlendingSource = -1;
static GLenum	_ccBlendingDest = -1;
#endif // CC_ENABLE_GL_STATE_CACHE

void ccGLInvalidateStateCache( void )
{
	kmGLFreeAll();

#if CC_ENABLE_GL_STATE_CACHE
	_ccCurrentShaderProgram = -1;
	_ccCurrentBoundTexture = -1;
	_ccBlendingSource = -1;
	_ccBlendingDest = -1;
#endif
}

void ccGLDeleteProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
	if( program == _ccCurrentShaderProgram )
		_ccCurrentShaderProgram = -1;
#endif // CC_ENABLE_GL_STATE_CACHE

	glDeleteProgram( program );
}

void ccGLUseProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
	if( program != _ccCurrentShaderProgram ) {
		_ccCurrentShaderProgram = program;
		glUseProgram(program);
	}
#else
	glUseProgram(program);	
#endif // CC_ENABLE_GL_STATE_CACHE
}

void ccGLEnableVertexAttribs( unsigned int flags )
{
	/* Position */
	bool enablePosition = flags & kCCVertexAttribFlag_Position;

	if( enablePosition != _vertexAttribPosition ) {
		if( enablePosition )
			glEnableVertexAttribArray( kCCVertexAttrib_Position );
		else
			glDisableVertexAttribArray( kCCVertexAttrib_Position );

		_vertexAttribPosition = enablePosition;
	}

	/* Color */
	bool enableColor = flags & kCCVertexAttribFlag_Color;
	
	if( enableColor != _vertexAttribColor ) {
		if( enableColor )
			glEnableVertexAttribArray( kCCVertexAttrib_Color );
		else
			glDisableVertexAttribArray( kCCVertexAttrib_Color );
		
		_vertexAttribColor = enableColor;
	}

	/* Tex Coords */
	bool enableTexCoords = flags & kCCVertexAttribFlag_TexCoords;

	if( enableTexCoords != _vertexAttribTexCoords ) {
		if( enableTexCoords ) 
			glEnableVertexAttribArray( kCCVertexAttrib_TexCoords );
		else
			glDisableVertexAttribArray( kCCVertexAttrib_TexCoords );
		
		_vertexAttribTexCoords = enableTexCoords;
	}
}

void ccGLUniformModelViewProjectionMatrix( GLProgram* shaderProgram )
{
	kmMat4 matrixP;
	kmMat4 matrixMV;
	kmMat4 matrixMVP;

	kmGLGetMatrix(KM_GL_PROJECTION, &matrixP );
	kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV );
	
	kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
	
	glUniformMatrix4fv(shaderProgram->uniforms_[kCCUniformMVPMatrix], 1, GL_FALSE, matrixMVP.mat);
}

void ccSetProjectionMatrixDirty( void )
{
	_ccCurrentProjectionMatrix = -1;
}
    
}

#endif
