//
//  Ant Body parts
//  15 Feb 2017
//

#ifndef _ANT_
#define _ANT_


void thorax(){
    
    GLfloat mat_diffuse[]={.8, .4, 0.0, 1.0};
    GLfloat mat_ambient[]={.4,.2, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(0.0, 1.5,1.5);
    glRotatef(-15,1,0,0);
    glScalef(1, 1.5, 1);
    glutSolidSphere(1.0,50,50);
    glPopMatrix();
}

void middle1(){
    
    GLfloat mat_diffuse[]={1, .4, 0.0, 1.0};
    GLfloat mat_ambient[]={1,.4, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(0, 0,1.5);
    glRotatef(-90,1,0,0);
    glScalef(1, 1, 1.5);
    glutSolidSphere(.35,50,3);
    glPopMatrix();
}

void middle2(){
    
    GLfloat mat_diffuse[]={1, .4, 0.0, 1.0};
    GLfloat mat_ambient[]={1,.4, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(0, -1.6*.5,1.65);
    glRotatef(-110,1,0,0);
    glScalef(1, 1, 1.6);
    glutSolidSphere(.35,50,3);
    glPopMatrix();
}
void middle3(){
    
    GLfloat mat_diffuse[]={1, .4, 0.0, 1.0};
    GLfloat mat_ambient[]={1,.4, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(0, 2*(-1.6*.5),2);
    glRotatef(-120,1,0,0);
    glScalef(1, 1, 1.6);
    glutSolidSphere(.35,50,3);
    glPopMatrix();
}

void head(){
    
    GLfloat mat_diffuse[]={1, .4, 0.0, 1.0};
    GLfloat mat_ambient[]={1,.4, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(0.0, 3.4*(-1.6*.5),2.5);
    glRotatef(10,1,0,0);
    glScalef(1, 1.25, .75);
    glutSolidSphere(.75,50,50);
    glPopMatrix();
}

void eye(float y){
    
    GLfloat mat_diffuse[]={1, 1, 1, 1.0};
    GLfloat mat_ambient[]={1,1, 1, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(y, 3.7*(-1.6*.5),2.9);
    glRotatef(10,1,0,0);
    glScalef(1, 1.5, 1);
    glutSolidSphere(.1,50,50);
    glPopMatrix();
    
    // Pupil
    GLfloat mat_diffuse1[]={0, 0, 0.0, 1.0};
    GLfloat mat_ambient1[]={0, 0, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    
    glPushMatrix();
    glTranslatef(y, 3.88*(-1.6*.5),2.9);
    glRotatef(-20,1,0,0);
    glScalef(1, .3, 1);
    glutSolidSphere(.04,4,4);
    glPopMatrix();
}

void antena1(float x, float antena1Angle){
    
    GLfloat mat_diffuse[]={1, .25, 0, 1.0};
    GLfloat mat_ambient[]={1, .15, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(x, 4*(-1.6*.5),2.9);
    glRotatef(55+antena1Angle,1,0,0);
    if(x<0) glRotatef(-10,0,1,0);
    if(x>0) glRotatef( 10,0,1,0);
    glScalef(1, 1, .1);
    glutSolidSphere(.04,4,4);
    glScalef(.01, .01, 5);
    //glScalef(.5, .5, 15);
    glTranslatef(0,0,1);
    glutSolidSphere(1,4,4);
    glPopMatrix();
}
void antena2(float x,float antena1Angle,float antena2Angle){
    
    GLfloat mat_diffuse[]={1, .25, 0, 1.0};
    GLfloat mat_ambient[]={1, .15, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    
    glTranslatef(x, 4*(-1.6*.5),2.9);
    glRotatef(55+antena1Angle,1,0,0);
    
    if(x<0) glRotatef(-10,0,1,0);
    if(x>0) glRotatef( 10,0,1,0);
    glTranslatef(0,0,1);
    glRotatef(20+antena2Angle,1,0,0);
    glTranslatef(0,0,.5);
    glScalef(1, 1, .1);

    glScalef(.01, .01, 5);

    
    glutSolidSphere(1,4,4);
    glPopMatrix();
}

// Generalized leg function
void leg(float initialAngle,
         float      x, float      y, float      z,
         float angle1, float angle2, float angle3,
         float scale1, float scale2, float scale3, float scale4){
    
    GLfloat mat_diffuse[]={.8, .4, 0.0, 1.0};
    GLfloat mat_ambient[]={.4,.2, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    
    glTranslatef(x, y, z);
    glRotatef(initialAngle,0,1,0);
    glRotatef( angle1,1,0,0);
    glPushMatrix();
    glScalef(1, 1, scale1);
    glutSolidSphere(.1,50,3);
    glPopMatrix();
    
    glTranslatef(0,0,-.1*scale1);
    glRotatef(angle2,0,1,0);
    glTranslatef(0,0,-.1*scale2);
    glPushMatrix();
    glScalef(1, 1, scale2);
    glutSolidSphere(.1,50,3);
    glPopMatrix();
    
    glTranslatef(0,0,-.1*scale2);
    glRotatef(angle3,0,1,0);
    glTranslatef(0,0,.1*scale3);
    glPushMatrix();
    glScalef(1, 1, scale3);
    glutSolidSphere(.1,50,3);
    glPopMatrix();
    
    
    GLfloat mat_diffuse1[]={1, .4, 0.0, 1.0};
    GLfloat mat_ambient1[]={1,.4, 0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    
    
    glTranslatef(0,0,.1*scale3*1.5);
    glPushMatrix();
    glScalef(.5, .5, scale4);
    glutSolidSphere(.1,50,3);
    glPopMatrix();
    
    
    
    glTranslatef(-.075,0,.1*scale4-.1);
    glPushMatrix();
    glScalef(1.2,1,1);
    glutSolidSphere(.1,50,3);
    glPopMatrix();
    
    glPopMatrix();
}




#endif

