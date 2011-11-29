#import <Foundation/Foundation.h>

#include <string>
#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "CCString.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCSAXParser.h"

#define MAX_PATH 560

using namespace cocos2d;

static const char* static_fullPathFromRelativePath(const char *pszRelativePath)

{
    
    // NSAssert(pszRelativePath != nil, @"CCFileUtils: Invalid path");
    
    // do not convert an absolute path (starting with '/')
    NSString *relPath = [NSString stringWithUTF8String: pszRelativePath];
    NSString *fullpath = nil;
	
	// only if it is not an absolute path
	if( ! [relPath isAbsolutePath] )
	{
		NSString *file = [relPath lastPathComponent];
		NSString *imageDirectory = [relPath stringByDeletingLastPathComponent];
		
		fullpath = [[NSBundle mainBundle] pathForResource:file
												   ofType:nil
											  inDirectory:imageDirectory];
	}
	
	if (fullpath == nil)
		fullpath = relPath;
	
	return [fullpath UTF8String];	
}

namespace cocos2d {
    
    void CCFileUtils::setResourcePath(const char *pszResourcePath)
    {
        assert(0);
    }
    
    int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
    {
        CCAssert( out, "ccLoadFileIntoMemory: invalid 'out' parameter");
        CCAssert( &*out, "ccLoadFileIntoMemory: invalid 'out' parameter");
        
        size_t size = 0;
        FILE *f = fopen(filename, "rb");
        if( !f ) { 
            *out = NULL;
            return -1;
        } 
        
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        *out = (unsigned char*)malloc(size);
        size_t read = fread(*out, 1, size, f);
        if( read != size ) { 
            free(*out);
            *out = NULL;
            return -1;
        }
        
        fclose(f);
        
        return size;
    }

    const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
    {
        return static_fullPathFromRelativePath(pszRelativePath);
    }
    
    const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
    {
        std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
        CCString *pRet = new CCString();
        pRet->autorelease();
        pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
        pRet->m_sString += pszFilename;
        return pRet->m_sString.c_str();
    }

    unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
    {
        unsigned char * pBuffer = NULL;
        
        do 
        {
            // read the file from hardware
            FILE *fp = fopen(pszFileName, pszMode);
            CC_BREAK_IF(!fp);
            
            fseek(fp,0,SEEK_END);
            *pSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pBuffer = new unsigned char[*pSize];
            *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
            fclose(fp);
        } while (0);
        
        if (! pBuffer && getIsPopupNotify()) 
        {
            std::string title = "Notification";
            std::string msg = "Get data from file(";
            msg.append(pszFileName).append(") failed!");
            
            CCMessageBox(msg.c_str(), title.c_str());
        }
        return pBuffer;
    }
    
    void CCFileUtils::setResource(const char* pszZipFileName)
    {
        CCAssert(0, "Have not implement!");
    }
    
    std::string CCFileUtils::getWriteablePath()
    {
        // save to document folder
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        std::string strRet = [documentsDirectory UTF8String];
        strRet.append("/");
        return strRet;
    }
    
}//namespace cocos2d

