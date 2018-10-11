//  Sasha Peters
//  Animated Ant
//
//  antClient.cpp
//
//
//  Created on 5/4/17.
//
//  drawSquare is a flexible square function I created to use for
//  buttons, menus, and drawing scenery. Easily expandable, so I
//  could have allowed for letting user enter in their own textures.
//  Function is located in common.h

#import "common.h"
#import <ctime>
#import "ant.h"
#import "scenery.h"

#define W 1000
#define H 1000

// Function definitions

void guiSetup();
void reshape(int w, int h);
void display(void);
void mouse(int btn, int state, int x, int y);
void keyboard(int key, int x, int y);
void myinit();

static GLfloat theta[]    = {0,0,0,0,0,0,0,0,0};
static GLfloat legTheta[] = {0,0,
                             0,0,
                             0,0};
// Global variables for camera angles
float cameraY = -60, cameraX = 0;
int  zoom = 30;

// ID for animation to use
int animID = 0;

// Variables to move the ant
float moveY  = 0;
float rotatZ = 0;
float animID2[6];

// Boolean for drawing
bool drawAnt = false, drawScene = false;

// Function for menu options
int menuID  = 0; // Which menu is open
int pressed = 0; // Which button is pressed
void guiSetup(){
    
    // Keeps menu updates from overwritting other graphic's area
    glEnable(GL_SCISSOR_TEST);
    glScissor(0,H-100,W,H-100);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Borders
    drawLine(0,80,0,
             W,80,0,
             211/255.0,211/255.0,211/255.0);
    drawLine(0,1,0,
             W,1,0,
             211/255.0,211/255.0,211/255.0);
    
    // Default menu layout when no menus are selected
    if(menuID == 0){
        glColor3f(0,0,0);
        drawString("Ants are eusocial insects of the family Formicidae and, along with the related wasps and bees,",10,62,0);
        drawString("belong to the order Hymenoptera.",  10, 42, 0);
        drawString("Scientific name: Formicidae",  10, 22, 0);
        drawString("Phylum: Arthropoda",  10, 02, 0);
    }
    
    // File menu
    if(menuID == 1){
        glPushMatrix();
        drawSquare(80,20,
                   0,80,0,
                   0,0,1,
                   GL_FILL, false);
        drawSquare(100,80,
                   0,0,0,
                   .7,.7,.7,
                   GL_FILL, false);
        
        drawString("Reset", 10, 62, 0);
        drawString("Quit",  10, 42, 0);
        glPopMatrix();
    }
    
    // Camera controls menu
    if(menuID == 2){
        glPushMatrix();
        drawSquare(80,20,
                   80,80,0,
                   0,0,1,
                   GL_FILL, false);
        drawSquare(450,80,
                   0,0,0,
                   .7,.7,.7,
                   GL_FILL, false);
        if(pressed != 21){
            
            drawSquare(40,40,
                       500,20,0,
                       .8,.8,.8,
                       GL_FILL, false);
            drawSquare(20,10,
                       510,35,0,
                       .2,.8,.2,
                       GL_FILL,false);
        }
        if(pressed != 22){
            
            drawSquare(40,40,
                       550,20,0,
                       .8,.8,.8,
                       GL_FILL, false);
            drawSquare(20,10,
                       560,35,0,
                       .2,.8,.2,
                       GL_FILL,false);
            drawSquare(10,20,
                       565,30,0,
                       .2,.8,.2,
                       GL_FILL,false);
        }
        
        if(pressed != 23){
            
            drawSquare(35,35,
                       750,45,0,
                       .8,.8,.8,
                       GL_FILL, false);
            drawString("UP",755,55,0);
        }
        if(pressed != 24){
            
            drawSquare(35,35,
                       750,0,0,
                       .8,.8,.8,
                       GL_FILL, false);
            drawString("D",760,10,0);
        }
        if(pressed != 25){
            
            drawSquare(35,35,
                       705,0,0,
                       .8,.8,.8,
                       GL_FILL, false);
            drawString("L",715,10,0);
        }
        if(pressed != 26){
            
            drawSquare(35,35,
                       795,0,0,
                       .8,.8,.8,
                       GL_FILL, false);
            drawString("R",805,10,0);
        }
        if(pressed == 21){
            if(zoom<40) zoom+=1;
            drawSquare(40,40,
                       500,20,0,
                       .2,.8,.2,
                       GL_FILL, false);
            drawSquare(20,10,
                       510,35,0,
                       .8,.8,.8,
                       GL_FILL,false);
        }
        if(pressed == 22){
            if(zoom > 10) zoom-=1;
            drawSquare(40,40,
                       550,20,0,
                       .2,.8,.2,
                       GL_FILL, false);
            drawSquare(20,10,
                       560,35,0,
                       .8,.8,.8,
                       GL_FILL,false);
            drawSquare(10,20,
                       565,30,0,
                       .8,.8,.8,
                       GL_FILL,false);
        }
        
        if(pressed == 23){
            if(cameraY < -20)cameraY+=1;
            drawSquare(35,35,
                       750,45,0,
                       .2,.8,.2,
                       GL_FILL, false);
            drawString("UP",755,55,0);
        }
        if(pressed == 24){
            if(cameraY > -80)cameraY-=1;
            drawSquare(35,35,
                       750,0,0,
                       .2,.8,.2,
                       GL_FILL, false);
            drawString("D",760,10,0);
        }
        if(pressed == 25){
            cameraX+=1;
            drawSquare(35,35,
                       705,0,0,
                       .2,.8,.2,
                       GL_FILL, false);
            drawString("L",715,10,0);
        }
        if(pressed == 26){
            cameraX-=1;
            drawSquare(35,35,
                       795,0,0,
                       .2,.8,.2,
                       GL_FILL, false);
            drawString("R",805,10,0);
        }
        drawString("Rotate camera with arrows keys, or these buttons ->", 10, 62, 0);
        drawString("Zoom out and in with scroll, or click the - or + ->", 10, 42, 0);
        glPopMatrix();
    }
    
    if(menuID == 3){
        glPushMatrix();
        drawSquare(80,20,
                   160,80,0,
                   0,0,1,
                   GL_FILL, false);
        drawSquare(200,80,
                   0,0,0,
                   .7,.7,.7,
                   GL_FILL, false);
        
        drawString("Draw Scenery", 10, 62, 0);
        drawString("Draw Ant",  10, 42, 0);
        drawString("Standstill Animation",10,22,0);
        drawString("Walking Animation",10,02,0);
        glPopMatrix();
    }
    
    glColor3f(0,0,0);
    drawString("File"   ,5,82,0);
    drawString("Camera" ,85,82,0);
    drawString("Animate",165,82,0);
    
    glDisable(GL_SCISSOR_TEST);
    glutPostRedisplay();
}


     
// Display function
void display(void){
    GLfloat light_position[]={0.0, -45.0, 30.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    if(animID == 2){
        animID2[0] = legTheta[0]-45;
        animID2[1] = legTheta[0];
        animID2[2] = legTheta[0]*.75;
        animID2[3] = legTheta[0]*.75-30;
        animID2[4] = legTheta[0]*.5;
        animID2[5] = legTheta[0]*.5-45/2;
    }
    else {
        animID2[0] = 0;
        animID2[1] = 0;
        animID2[2] = 0;
        animID2[3] = 0;
        animID2[4] = 0;
        animID2[5] = 0;
    }
        
    // Keep the menu area from being overwritten
    glEnable(GL_SCISSOR_TEST);
    glScissor(0,0,W,H-100);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    if(drawScene == true) drawScenery();

    if(drawAnt == true){
    
        glPushMatrix();
    
        glTranslatef(0,moveY,0);
        glRotatef(rotatZ,0,0,1);
    
        //glRotatef(theta[0],0,0,1);
        thorax();
    
        glRotatef(theta[1],1,0,0);
        middle1();
    
        glRotatef(theta[0],0,0,1);
    
        leg(-90,
            .3,-.75,1.5,
            45+animID2[0],-60-theta[1]-legTheta[1],-60+theta[1],
            3,9,12,5.9);
    
        leg(-90,
            -.3,-.75,1.5,
            135+animID2[1],-60-theta[1]-legTheta[2],-60+theta[1],
            3,9,12,5.9);
    
        leg(-90,
            .3,-1,1.5,
            0-animID2[2],-60-theta[1]-legTheta[2],-45+theta[1],
            3,7,8,8.2);
    
        leg(-90,
            -.3,-1,1.5,
            180-animID2[3],-60-theta[1]-legTheta[1],-45+theta[1],
            3,7,8,8.2);
    
        leg(-90,
            .3,-1.5,1.8,
            -45+animID2[4],-30-theta[1]-legTheta[1],-90+theta[1],
            3,6,8,8);
    
        leg(-90,
            -.3,-1.5,1.8,
            225+animID2[5],-30-theta[1]-legTheta[2],-90+theta[1],
            3,6,8,8);
    
        middle2();
        middle3();
    
        head();
        eye(0.4);
        eye(-0.4);
    
        antena1(0.2,theta[5]);
        antena2(0.2,theta[5],theta[6]);
        
        antena1(-0.2,theta[7]);
        antena2(-0.2,theta[7],theta[8]);
    
        glPopMatrix();
        
    }
    
    glutSwapBuffers();
    
}


// Mouse controls function
void mouse(int btn, int state, int x, int y){

    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN && y <= 100){
        if(x <=80 && y <=20 && menuID != 1) menuID = 1;
        else if(x <=80 && y <=20 && menuID == 1) menuID = 0;
        else if(x <=100 && y <=40 && menuID == 1){
            system("(sleep 1; ./antClient) &");
            exit(0);
        }
        else if(x <=100 && y <=60 && menuID == 1) exit(0);
        else if(x > 80 && x <= 160 && y <= 20 && menuID != 2) menuID = 2;
        else if(x > 80 && x <= 160 && y <= 20 && menuID == 2) menuID = 0;
        else if(x >= 500 && x <= 540 && y <= 70 && y >= 30 && menuID == 2)
            pressed = 21;
        else if(x >= 550 && x <= 590 && y <= 70 && y >= 30 && menuID == 2)
            pressed = 22;
        else if(x >= 750 && x <= 785 && y <= 55 && y >= 20 && menuID == 2)
            pressed = 23;
        else if(x >= 750 && x <= 785 && y <= 100 && y >= 65 && menuID == 2)
            pressed = 24;
        else if(x >= 705 && x <= 740 && y <= 100 && y >= 65 && menuID == 2)
            pressed = 25;
        else if(x >= 795 && x <= 830 && y <= 100 && y >= 65 && menuID == 2)
            pressed = 26;
        else if(x > 160 && x <= 240 && y <= 20 && menuID != 3) menuID = 3;
        else if(x > 160 && x <= 240 && y <= 20 && menuID == 3) menuID = 0;
        else if(x <=200 && y <=40 && menuID == 3) drawScene =  !drawScene;
        else if(x <=200 && y <=60 && menuID == 3) drawAnt   =    !drawAnt;
        else if(x <=200 && y <=80 && menuID == 3)  animID = 1;
        else if(x <=200 && y <=100 && menuID == 3) animID = 2;
        

    }
    
    else if(btn==GLUT_LEFT_BUTTON && state == GLUT_UP){
        if(pressed!=0) pressed = 0;
    }
    
    
    if(btn==3 && GLUT_UP){
        if (zoom > 10) zoom--;
    }
    if(btn==4 && GLUT_UP){
        if (zoom < 40) zoom++;
    }

    
    
    reshape(W,H);
}

// Special keys function for arrow keys
void specialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP && cameraY < -20){
        cameraY+=5;
        reshape(W,H-100);
    }
    if(key == GLUT_KEY_DOWN && cameraY > -80){
        cameraY-=5;
        reshape(W,H-100);
    }
    if(key == GLUT_KEY_RIGHT){
        cameraX-=5;
        reshape(W,H-100);
    }
    if(key == GLUT_KEY_LEFT){
        cameraX+=5;
        reshape(W,H-100);
    }
}

// Init function
void myinit(){
    
    glClearColor(WHITE,1);
    texture[0] = LoadTexture("grass03.bmp", 256, 256);
    
}

// Reshape function
void reshape(int w, int h){
    
    /*********  Menu Display view   ********/
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glViewport(0,H-100,W,100);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,W,0,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    guiSetup();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    
    
    /********* Animated Display view ********/
    glViewport(0, 0, W, H-100);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(GLfloat)w/((GLfloat)H-100), .1, 150);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,zoom,    0,0,0,    0,1,0);
    glRotatef(cameraY,1,0,0);
    glRotatef(cameraX,0,0,1);
    glutPostRedisplay();
}


// variables used in motion
float inc0      =  .01;
float inc1      =  .01;

int baseAngle   =    0;
float angle0    =    0;

float angle1    =    0;

int baseAntena1 =    0;
float angle2    =    0;

int baseAntena2 =    0;
float angle3    =    0;

int endAntena1  =    0;
float angle4    =    0;

int endAntena2  =    0;
float angle5    =    0;

float inc2      =    1;

float moveInc   =   .02;

// Idle function for movements
void idle(){
    
    // Makes antenas move if ant is animated
    if(animID != 0){
        
    if (baseAntena1==(int)angle2) baseAntena1 = rand() % 10;
    if (baseAntena2==(int)angle3) baseAntena2 = rand() % 10;
    if (endAntena1==(int)angle4) endAntena1 = rand() % 15;
    if (endAntena2==(int)angle5) endAntena2 = rand() % 15;
        
    // Top part of antena
    if(angle4 < endAntena1) {
        angle4  += inc0*10;
        theta[6] = angle4;
    }
    else if(angle4 > endAntena1) {
        angle4  -= inc0*10;
        theta[6] = angle4;
    }
    if(angle5 < endAntena2) {
        angle5  += inc0*10;
        theta[8] = angle5;
    }
    else if(angle5 > endAntena2) {
        angle5  -= inc0*10;
        theta[8] = angle5;
    }
    // Antena base
    if(angle2 < baseAntena1) {
        angle2  += inc0*10;
        theta[5] = angle2;
    }
    else if(angle2 > baseAntena1) {
        angle2  -= inc0*10;
        theta[5] = angle2;
    }
    if(angle3 < baseAntena2) {
        angle3  += inc0*10;
        theta[7] = angle3;
    }
    else if(angle3 > baseAntena2) {
        angle3  -= inc0*10;
        theta[7] = angle3;
    }
    }
    
    // Standstill animation
    if (animID == 1){
    if(angle1 < -1) {inc1  =  .01;angle1=-.999;}
    if(angle1 >  1) {inc1  = -.01;angle1= .999;}
    angle1+=inc1;
    if (baseAngle==(int)angle0) baseAngle = rand() % 5 - 2;
    
    

    // Main body (head to thorax) motion
    else if (angle0 < baseAngle){
        angle0  += inc0;
        theta[0] = angle0;
        theta[1] = angle1;
    }
    else if (angle0 > baseAngle){
        angle0  -= inc0;
        theta[0] = angle0;
        theta[1] = angle1;
    }


    }
    
    // Makes the ant walk
    else if (animID == 2){
        if(inc2 < 0){
            legTheta[2] = 0;
            if(legTheta[0] > 45/2.0) legTheta[1] += 1;
            else if(legTheta[0] < 45/2.0) legTheta[1] -= 1;
        }
        else {
            legTheta[1] = 0;
            if(legTheta[0] > 45/2.0) legTheta[2] -= 1;
            else if(legTheta[0] < 45/2.0) legTheta[2] += 1;
        }
        if(legTheta[0] == 45)     {inc2 = -1;}
        else if(legTheta[0] == 0) inc2 =  1;
        legTheta[0] += inc2;
        if(moveY < -5) {
            
            moveInc*=-1;
            rotatZ = 180;
            theta[0] = -theta[0];
        }
        else if(moveY >  5) {

            moveInc*=-1;
            rotatZ = 0;
            theta[0] = -theta[0];
        }
            
        moveY-=moveInc;
        
        
        
    }
    

    reshape(W,H);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(W, H);
    glutCreateWindow("Sasha Peters | Formicidae");
    myinit();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutSpecialFunc(specialKeys);
    
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
