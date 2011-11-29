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
#ifndef __COCOS_GLSTATE_H__
#define __COCOS_GLSTATE_H__

#include "CCGL.h"

#if CC_ENABLE_GL_GLES2

namespace   cocos2d {
    
    
class GLProgram;

    
/** vertex attrib flags */
enum {
	kCCVertexAttribFlag_None		= 0,

	kCCVertexAttribFlag_Position	= 1 << 0,
	kCCVertexAttribFlag_Color		= 1 << 1,
	kCCVertexAttribFlag_TexCoords	= 1 << 2,

	kCCVertexAttribFlag_PosColorTex = ( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color | kCCVertexAttribFlag_TexCoords ),
};


#ifdef __cplusplus
extern "C" {
#endif	

/** @file A set of OpenGL helpers functions 
*/

/** Invalidates the GL state cache.
 If CC_ENABLE_GL_STATE_CACHE it will reset the GL state cache.
 @since v2.0.0
 */
void ccGLInvalidateStateCache( void );

/** Uses the GL program in case program is different than the current one.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glUseProgram() directly.
 @since v2.0.0
 */
void ccGLUseProgram( GLuint program );

/** Deletes the GL program. If it is the one that is being used, it invalidates it.
 If CC_ENABLE_GL_STATE_CACHE is disabled, it will the glDeleteProgram() directly.
 @since v2.0.0
 */
void ccGLDeleteProgram( GLuint program );

/** sets the ModelViewProjection Matrix in the GL program
 @since v2.0.0
 */
void ccGLUniformModelViewProjectionMatrix( GLProgram *shaderProgram );

/** sets the projection matrix as dirty
 @since v2.0.0
 */
void ccSetProjectionMatrixDirty( void );

/** Will enable the vertex attribs that are passed as flags.
 Possible flags:
	
	* kCCVertexAttribFlag_Position
	* kCCVertexAttribFlag_Color
	* kCCVertexAttribFlag_TexCoords
 
 These flags can be ORed. The flags that are not present, will be disabled.
 
 @since v2.0.0
 */
void ccGLEnableVertexAttribs( unsigned int flags );

#ifdef __cplusplus
}
#endif	

}

#endif
#endif