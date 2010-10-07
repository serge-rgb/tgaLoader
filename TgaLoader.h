#pragma once

#include "Common.h"

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
	int texType;
	int texFormat;
	GLubyte *texels;
} t_texture;

class TgaLoader
{
public:
	TgaLoader(void);
	GLuint newTex2d(char *fname);
	~TgaLoader(void);
private:
	t_texture* tex;
	t_texture* load(char *fname);
};
