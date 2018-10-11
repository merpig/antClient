//
//  "Stuff" commonly used by lkd, (-:
//  15 Feb 2017
//

#ifndef _CommonLKD_
#define _CommonLKD_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MacLinux.h"
using namespace std;

// used for clearing background color to black (rgba)
#define BLACK_A 0,0,0,0

#define ORIGIN  0,0,0

#define WHITE   1,1,1
#define RED     1,0,0
#define GREEN   0,1,0
#define BLUE    0,0,1
#define BLACK   0,0,0

#define rROBIN_BLUE   142./255,219./255,245./255
#define ROBIN_BLUE    49./255,196./255,245./255

#define X_AXIS  1,0,0
#define Y_AXIS 0,1,0
#define Z_AXIS  0,0,1


// code for the keyboard escape key (ESC)
#define ESCAPE   27
#define UP       119
#define DOWN     115
#define RIGHT    97
#define LEFT     100

GLuint texture[1];

//double frame=0;

GLuint LoadTexture( const char * filename, int w, int h ) {
    GLuint texture;
    unsigned char * data;
    FILE * file;
    
    // read in binary format RAW files ( bmp )
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( w*h*3 );
    fread( data, w*h*3, 1, file );
    fclose( file );
    
    // 1. generate texture with loaded data
    glGenTextures( 1, &texture );
    // 2. bind to array
    glBindTexture( GL_TEXTURE_2D, texture );
    // 3. set environment vars for texture
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    // now set which textures to use when. MIN filter denotes quality to show
    //   when texture is in near view; MAG when far
    //      possible settings are:
    //        (worst)  GL_NEAREST
    //          ..     GL_LINEAR
    //          ..     GL_LINEAR_MIPMAP_NEAREST
    //        (best)   GL_LINEAR_MIPMAP_LINEAR
    // fyi, if need better than 'best' investigate anisotropic filtering textures
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    // use GL_REPEAT to prevent image appearing only once at edge of shape
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    // finally! generate texture with mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data );
    
    // free memory & return result handle
    free( data );
    return texture;
}


void drawLine(float x1, float y1, float z1
              , float x2, float y2, float z2
              , float r, float g, float b) {
    glColor3f(r,g,b);
    glBegin(GL_LINES);
    glVertex3f(x1,y1,z1);
    glVertex3f(x2,y2,z2);
    glEnd();
}

void drawSquare(float width, float length,
                float x1, float y1, float z1,
                float r, float g, float b,
                GLenum mode, bool tex){
    if(tex==true) glEnable(GL_TEXTURE_2D);
    

    glDisable(GL_LIGHTING);
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    /*glPolygonMode(GL_BACK,GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(r*1.6,g*1.6,b*1.6);
    glVertex3f(x1,y1,z1);
    glVertex3f(x1+width,y1,z1);
    glVertex3f(x1+width,y1+length,z1);
    glVertex3f(x1,y1+length,z1);
    glEnd();*/
    
    if (tex == false) glPolygonMode(GL_FRONT_AND_BACK,mode);
    glBegin(GL_QUADS);
    if (tex==false) glColor3f(r,g,b);
    else glColor3f(.1,.68,.1);
    
    if (tex == true) glTexCoord2d(0,0);
    glVertex3f(x1,y1,z1);
    
    if (tex == true) glTexCoord2d(1,0);
    glVertex3f(x1+width,y1,z1);
    
    if (tex == true) glTexCoord2d(1,1);
    glVertex3f(x1+width,y1+length,z1);
    
    if (tex == true) glTexCoord2d(0,1);
    glVertex3f(x1,y1+length,z1);
    glEnd();
    if(tex==true) glDisable(GL_TEXTURE_2D);


	glEnable(GL_LIGHTING);
	/*GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};     // none (ie, 0,0,0) black
        GLfloat light_diffuse[]={0.65, 0.65, 0.65, .8};   // not so BRIGHT WHITE
        GLfloat light_specular[]={0.0, 0.0, 0.0, 1.0};    // none (ie, 0,0,0) black
        //GLfloat light_position[]={0.0, 0.0, 45.0, 0.0}; // 10,10,10

        //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);*/
    //glFlush();
}

void drawString(const char *text,float x,float y,float z) {
    glRasterPos3f(x,y,z);
    for (int k=0; text[k] != 0;k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[k]);
}

void drawAxes(int length, float placeLabel) {
    
    drawLine(ORIGIN, length, 0, 0, RED  );
    drawString("X",placeLabel,0,0);
    
    drawLine(ORIGIN,  0,length, 0, GREEN);
    drawString("Y",0,placeLabel,0);
    
    drawLine(ORIGIN,  0, 0,length, ROBIN_BLUE );
    drawString("Z",0,0,placeLabel);
    
}
void drawAxes(void) {
    drawAxes( 50, 2 );
}



#endif 

