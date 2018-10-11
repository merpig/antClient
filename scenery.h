//  Sasha Peters
//  Scenery
//  15 Feb 2017
//

#ifndef _SCENERY_
#define _SCENERY_

#include "common.h"

void drawScenery(){
    // Draws the floor
    glPushMatrix();
    for (int i = -45;i<45;i+=5)
        for(int j = -45; j<45; j+=5)
            drawSquare(5,5,
                       i,j,0,
                       0,1,0,
                       GL_LINE, true);
    glPopMatrix();
    
    // Draw the sun
    glPushMatrix();
    glTranslatef(0,-32,24);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
        glColor3f(1,1,0);
        glutSolidSphere(1,10,10);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPopMatrix();
    
    // Draws the sky
    glPushMatrix();
    glTranslatef(0,0,-5);
    glRotatef(90,1,0,0);
    glRotatef(180,0,0,1);
    glRotatef(-90,0,1,0);
    for(int i = 0; i<180; i++){
        glRotatef(-1,0,0,1);
        float r = (80-i*.2)/255.0;
        float g = (219-i*.2*5)/255.0;
        float b = (255-i*.2)/255.0;
        
        for(int j = 0; j<60; j++){
            glRotatef(6,0,1,0);
            
            glTranslatef(0,0,-45);
            
            drawSquare(5,5,
                       -2.5,-2.5,0,
                       r,g,b,
                       GL_FILL, false);
            glTranslatef(0,0,45);
        }
    }
    glRotatef(90,0,1,0);
    
    glPopMatrix();
}





#endif

