#pragma once

//#define _WITH_GL

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
#ifdef _WITH_GL
	GLubyte *texels;
#endif
} t_texture;

class TgaLoader
{
public:
	TgaLoader(void);
#ifdef _WITH_GL
	GLuint newTex2d(char *fname);
#endif
	~TgaLoader(void);
private:
	t_texture* tex;
	t_texture* load(char *fname);
};
