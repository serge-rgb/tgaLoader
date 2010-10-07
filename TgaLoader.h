#pragma once

#include <cstdio>
#include<stdlib.h>

//#define _WITH_GL

#ifdef _WITH_GL
#define TGA_BYTE GLubyte
#endif

#ifndef _WITH_GL
#define TGA_BYTE char
#define GL_RGB
#endif

typedef struct {
	char  idlength;
	char  colourmaptype;
	char  datatypecode;
	short int colourmaporigin;
	short int colourmaplength;
	char  colourmapdepth;
	short int x_origin;
	short int y_origin;
	short width;
	short height;
	char bitsperpixel;
	char imagedescriptor;
} t_tgaHeader;

typedef struct{
	int w,h;
	
#ifdef _WITH_GL
	int texFormat;
#endif

	TGA_BYTE *texels;
} t_texture;

class TgaLoader
{
public:
	TgaLoader(void);
#ifdef _WITH_GL
	GLuint newTex2d(string fname);
#endif
	~TgaLoader(void);
private:
	t_texture* tex;
	t_texture* load(string fname);
};
