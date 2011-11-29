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


#include "CCShaderCache.h"
#include "GLProgram.h"
#include "ccMacros.h"

#if CC_ENABLE_GL_GLES2

namespace   cocos2d {
    
static CCShaderCache *_sharedShaderCache;

CCShaderCache * CCShaderCache::sharedShaderCache(void)
{
	if (!_sharedShaderCache)
		_sharedShaderCache = new CCShaderCache();
	return _sharedShaderCache;
}

void CCShaderCache::purgeSharedShaderCache(void)
{
	_sharedShaderCache->release();
	_sharedShaderCache = NULL;	
}


CCShaderCache::CCShaderCache(void)
{
    programs_ = new CCMutableDictionary<std::string, GLProgram*>();
    this->loadDefaultShaders();
}
    
CCShaderCache::~CCShaderCache(void)
{
    programs_->release();
}


void CCShaderCache::purgeSharedTextureCache(void)
{
	_sharedShaderCache->release();
	_sharedShaderCache = NULL;
}


void CCShaderCache::loadDefaultShaders(void)
{
	// Position Texture Color shader
	GLProgram *p = new GLProgram("PositionTextureColor.vsh", "PositionTextureColor.fsh");
    
	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	
	p->link();
	p->updateUniforms();
		
    programs_->setObject(p, std::string(kCCShader_PositionTextureColor));
	p->release();
	
	//
	// Position, Color shader
	//
    p = new GLProgram("PositionColor.vsh", "PositionColor.fsh");

    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    
	p->link();
	p->updateUniforms();
    	
    programs_->setObject(p, std::string(kCCShader_PositionColor));
	p->release();
	
	//
	// Position Texture shader
	//
    p = new GLProgram("PositionTexture.vsh", "PositionTexture.fsh");
	
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	
	p->link();
	p->updateUniforms();
    
    programs_->setObject(p, std::string(kCCShader_PositionTexture));
	p->release();

	//
	// Position, Texture attribs, 1 Color as uniform shader
	//
    p = new GLProgram("PositionTexture_uColor.vsh", "PositionTexture_uColor.fsh");
    
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
    p->link();
	p->updateUniforms();
    
    programs_->setObject(p, std::string(kCCShader_PositionTexture_uColor));
	p->release();


	//
	// Position Texture A8 Color shader
	//
    p = new GLProgram("PositionTextureA8Color.vsh", "PositionTextureA8Color.fsh");
	
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	
    p->link();
	p->updateUniforms();
    
    programs_->setObject(p, std::string(kCCShader_PositionTextureA8Color));
	p->release();

}

GLProgram * CCShaderCache::programForKey(const char * key)
{
	return programs_->objectForKey(std::string(key));
}

void CCShaderCache::addProgram(GLProgram* program, const char* key)
{
    programs_->setObject(program, std::string(key));
}
    
}

#endif
