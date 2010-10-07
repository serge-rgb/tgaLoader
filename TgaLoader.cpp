#include "TgaLoader.h"

TgaLoader::TgaLoader(void)
{
}

t_texture * TgaLoader::load(char *fname){
	t_tgaHeader header;
	t_texture *texture = tex;
	FILE *fd;
	long int offset = 4*sizeof(char)+4*sizeof(short int);
	
	texture = (t_texture *)malloc(sizeof(t_texture));
	
	fd = fopen(fname,"rb");
	if(!fd){
		printf("File %s not found\n",fname);
		exit(-1);
	}
	
	/*Fill our header.*/
	/*Skip useless stuff*/
	fseek(fd,offset,SEEK_SET);
	
	fread(&header.width,sizeof(short),1,fd);
	fread(&header.height,sizeof(short),1,fd);
	fread(&header.bitsperpixel,sizeof(char),1,fd);
	fread(&header.imagedescriptor,sizeof(char),1,fd);
	
	texture->w = header.width;
	texture->h = header.height;

#ifdef _WITH_GL
	switch(header.bitsperpixel){
		case 24:
			texture->texType = 3;
			texture->texFormat = GL_RGB;
			break;
		case 32:
			texture->texType = 4;
			texture->texFormat = GL_RGBA ;
			break;
		default:
			printf("Unsupported BPP\n");
			exit(-1);
			break;
	}
#endif
	
	/*Allocate memory*/
	texture->texels = (TGA_BYTE *) malloc(texture->w*texture->h*texture->texType*sizeof(TGA_BYTE));
	
	int pixnum = header.width * header.height;
	
	/*Start reading our image!*/
	int i;
	if(header.bitsperpixel == 32){
	for(i=0;i<pixnum;i++){
		/*BGRA --> RGBA*/
		texture->texels[i*4+2]=fgetc(fd);
		texture->texels[i*4+1]=fgetc(fd);
		texture->texels[i*4+0]=fgetc(fd);
		texture->texels[i*4+3]=fgetc(fd);
	}
	}
	if(header.bitsperpixel == 24){
	for(i=0;i<pixnum;i++){
		texture->texels[i*3+2]=fgetc(fd);
		texture->texels[i*3+1]=fgetc(fd);
		texture->texels[i*3+0]=fgetc(fd);
	}
	}
	
	fclose(fd);
	
	printf("Loaded %i bit TGA file'\n",header.bitsperpixel);
	
	return texture;
}

#ifdef _WITH_GL
GLuint TgaLoader::newTex2d(char *fname)
{
	GLuint name;
	//t_texture *tex;
	tex = load(fname);
	
	glPixelStorei(GL_PACK_ALIGNMENT,1);
	
	glGenTextures(1, &name);
	glBindTexture(GL_TEXTURE_2D,name);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,tex->texType,tex->w,tex->h,0,tex->texFormat,GL_UNSIGNED_BYTE,tex->texels);

	/*The texture is now inside OpenGL*/
	return name;
}
#endif

TgaLoader::~TgaLoader(void)
{
	if(tex!=NULL){
	if(tex->texels)
		free(tex->texels);
	free(tex);
	}
}
