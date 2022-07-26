#pragma warning(disable:4996)

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>

GLuint texture[6]; //the array for our texture
double rotate_x = 0, rotate_z = 0, rotate_y = 0;

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0, angle = 0.0;
float positionx, positiony, positionz;
GLuint LoadTexture(const char* filename, int width, int height)
{
    GLuint texture;
    unsigned char* data;
    FILE* file;
    //The following code will read in our RAW file
    file = fopen(filename, "rb");
    if (file == NULL) return 0;
    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);
    glGenTextures(1, &texture); //generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it’s array
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //set texture environment parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Generate the texture
    //Please be informed to switch from GL_RGB to GL_BGR_EXT for bitmap image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    free(data); //free the texture
    return texture; //return whether it was successfull
}
void FreeTexture(GLuint texture) {
    glDeleteTextures(1, &texture);
}
void Position(void)
{
    srand(time(NULL));
    positionz = rand() % 10 + 5;
    positiony = rand() % 10 + 5;
    positionx = rand() % 10 + 5;
}
/*void enable(void) {
    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glEnable(GL_LIGHTING); //enable the lighting
    glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}*/
void camera(void)
{
    glRotatef(xrot, 1.0, 0.0, 0.0); //rotate our camera on teh x - axis(left andright)
    glRotatef(yrot, 0.0, 1.0, 0.0); //rotate our camera on the y - axis(up an down)
    glRotatef(zrot, 0.0, 0.0, 1.0); //rotate our camera on the y - axis(up an down)
    glTranslated(-xpos, -ypos, -zpos); //translate the screento the position of ourcamera
    glTranslatef(rotate_x, 1.0, 0.0);
    glTranslatef(rotate_y, 0.0, 1.0);
}

void init(void)
{
    glClearColor(0.6, 0.8, 1.0, 0.9);
    Position();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'k') { //move in x axis to the right( bkn rotate camera, die gerak dlm x axis)
        rotate_x -= 0.2;
    }
    if (key == 'h') { //move in x axis to the left
        rotate_x += 0.2;
    }
    if (key == 'p') {
        rotate_y += 0.2;
    }
    if (key == 'l') {
        rotate_y -= 0.2;
    }
    if (key == 's') { //rotate camera view to go down -y-axis
        xrot += 1;
        if (xrot > 360) xrot -= 360;
    }
    if (key == 'w') { //rotate camera view to go up. +y-axix
        xrot -= 1;
        if (xrot < -360) xrot += 360;
    }
    if (key == 'n') { //zoom in
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos += float(sin(yrotrad));
        zpos -= float(cos(yrotrad));
        ypos -= float(sin(xrotrad));
    }
    if (key == 'o') { //zoom out
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos -= float(sin(yrotrad));
        zpos += float(cos(yrotrad));
        ypos += float(sin(xrotrad));
    }

    if (key == 'u') { //move camera in z axis(gerak ke dpn dlm z axis)
        float xrotrad, zrotrad;
        zrotrad = (zrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos += float(sin(zrotrad));
        zpos -= float(cos(zrotrad));
        ypos -= float(sin(xrotrad));
    }
    if (key == 'j') { //move camera in z axis(gerak ke belakang dlm z axis)
        float xrotrad, zrotrad;
        zrotrad = (zrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos -= float(sin(zrotrad));
        zpos += float(cos(zrotrad));
        ypos += float(sin(xrotrad));
    }
    if (key == 'd') { //to rotate camera view to right
        yrot += 1;
        if (yrot > 360) yrot -= 360;
    }
    if (key == 'a') { //to rotate camera to the left
        yrot -= 1;
        if (yrot < -360)yrot += 360;
    }


    if (key == 'c')
    {
        glEnable(GL_LIGHTING);
    }
    else if (key == 'v')
    {
        glDisable(GL_LIGHTING);
    }

    if (key == 27) {
        exit(0);
    }
}

//--------------------------------- LOBBY 2 ----------------------------------
//code for building etc
void lobby2(void)
{
    //Back atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.9, 0.1);
    glVertex3f(-9, 1.5f, -4.0f); //bawah (L)
    glVertex3f(8, 1.5f, -4.0f); //bawah (R)
    glVertex3f(8, 17, -4.0f); //atas (R)
    glVertex3f(-9, 17, -4.0f); //bawah (L)
    glEnd();
    //depan atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.9, 0.1);
    glVertex3f(-9, 1.5f, 1.0f); //bawah (L)
    glVertex3f(8, 1.5f, 1.0f); //bawah (R)
    glVertex3f(8, 17, 1.0f); //atas (R)
    glVertex3f(-9, 17, 1.0f); //bawah (L)
    glEnd();
    //tapak

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0, 0.0f);    // 
    glVertex3f(8, 1.5f, 1.0f);    // depan (R)
    glVertex3f(-9, 1.5f, 1.0f);    // depan (L)
    glVertex3f(-9, 1.5f, -4.0f);    // belakang (L)
    glVertex3f(8, 1.5f, -4.0f);    // belakang (R)
    glEnd();
    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 1.5, 1.0); //depan bawah
    glVertex3f(-9, 17, 1);//dpn atas
    glVertex3f(-9, 17, -4);//blkg atas
    glVertex3f(-9, 1.5, -4);//blkg bawah
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);    // Color Violet
    glVertex3f(8, 17, 1.0f);    // atas  dpn
    glVertex3f(8, 1.5f, 1.0f);    // bawah dpn
    glVertex3f(8, 1.5f, -4.0f);    // bawah belakang
    glVertex3f(8, 17, -4.0f);    // atas belakang
    glEnd();
}

//-------------------------------- LOBBY ----------------------------------
void lobby(void)
{
    //bumbunglobby
    glPushMatrix();
    glTranslatef(-0.6, 17, -4);
    glColor3f(1, 1, 1);
    glScalef(18, 0.5, 8);
    glutSolidCube(1);
    glPopMatrix();

    //Bottom- tapak dia

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0, 0.0f);
    glVertex3f(8.0f, -1.5f, 1.0f);    // depan (R)
    glVertex3f(-9.0f, -1.5f, 1.0f);    // depan (L)
    glVertex3f(-9.0f, -1.5f, -4.0f);    // belakang (L)
    glVertex3f(8.0f, -1.5f, -4.0f);    // belakang (R)
    glEnd();

    //Back
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.9, 0.1);
    glVertex3f(-9, -1.5f, -4.0f); //bawah (L)
    glVertex3f(8, -1.5f, -4.0f); //bawah (R)
    glVertex3f(8, 1.5f, -4.0f); //atas (R)
    glVertex3f(-9, 1.5f, -4.0f); //bawah (L)
    glEnd();

    //pintu lobby tampalan
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-2.8f, -1.5f, 1.0f);
    glVertex3f(-2.8f, 1.5f, 1.0f);
    glVertex3f(1.5f, 1.5f, 1.0f);//-pintudepan bawah (R)
    glVertex3f(1.5f, -1.5f, 1.0f);    // depan bawah (R)
    glEnd();


    //Front
    //part1-kiri pintu
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.9, 0.1);
    glVertex3f(-9, -1.5f, 1.0f);    // bawah (L)            
    glVertex3f(-2.8f, -1.5f, 1.0f);//-pintudepan bawah (R)     
    glVertex3f(-2.8f, 1.5f, 1.0f);//-pintudepan atas (R)        
    glVertex3f(-9, 1.5f, 1.0f);    //  atas (L)              
    glEnd();

    //part2-atas pintu
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-2.8f, 1.5f, 1.0f);//-pintudepan atas (R)       
    glVertex3f(-2.8f, 1.0f, 1.0f);//-pintu dpn bawah (R)
    glVertex3f(1.5f, 1.0f, 1.0f);//-pintu dpn bawah (L)
    glVertex3f(1.5f, 1.5f, 1.0f);//-pintu dpn bawah (R)
    glEnd();

    //part3-kanan pintu
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.9, 0.1);
    glVertex3f(1.5f, -1.5f, 1.0f);//-pintudepan bawah (R)
    glVertex3f(8.0f, -1.5f, 1.0f);    // depan bawah (R)
    glVertex3f(8.0f, 1.5f, 1.0f);    //  atas (R)
    glVertex3f(1.5f, 1.5f, 1.0f);    //  atas (L)
    glEnd();

    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, -1.5, 1.0); //depan bawah
    glVertex3f(-9, 1.5, 1);//dpn atas
    glVertex3f(-9, 1.5, -4);//blkg atas
    glVertex3f(-9, -1.5, -4);//blkg bawah
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(8, 1.5f, 1.0f);    // atas  dpn
    glVertex3f(8, -1.5f, 1.0f);    // bawah dpn
    glVertex3f(8, -1.5f, -4.0f);    // bawah belakang
    glVertex3f(8, 1.5f, -4.0f);    // atas belakang
    glEnd();
    //line pintu -kiri
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-2.5, 0.8, 1.01f);
    glVertex3f(-2.5, -1.5, 1.01);
    glVertex3f(-1.0, -1.5, 1.01);
    glVertex3f(-1.0, 0.8, 1.01);
    glEnd();
    //line pintu-kanan
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-0.3, 0.8, 1.01);
    glVertex3f(-0.3, -1.5, 1.01);
    glVertex3f(1.2, -1.5, 1.01);
    glVertex3f(1.2, 0.8, 1.01);
    glEnd();
}

//-------------------------------- JEJANTAS L ----------------------------------
void jejantasL(void)
{
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 4, 4); //belakang kanan
    glVertex3f(-9, 4, 8);//depan kanan
    glVertex3f(-16, 4, 5);//depan kiri
    glVertex3f(-16, 4, 1);//belakang kiri
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 4, 4); //belakang kanan
    glVertex3f(-9, 5, 4);//depan kanan
    glVertex3f(-16, 5, 1);//depan kiri
    glVertex3f(-16, 4, 1);//belakang kiri
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 4, 8); //belakang kanan
    glVertex3f(-9, 5, 8);//depan kanan
    glVertex3f(-16, 5, 5);//depan kiri
    glVertex3f(-16, 4, 5);//belakang kiri
    glEnd();


    //jejantas 2 belah kiri
     //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 10, 4); //belakang kanan
    glVertex3f(-9, 10, 8);//depan kanan
    glVertex3f(-16, 10, 5);//depan kiri
    glVertex3f(-16, 10, 1);//belakang kiri
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 10, 4); //belakang kanan
    glVertex3f(-9, 11, 4);//depan kanan
    glVertex3f(-16, 11, 1);//depan kiri
    glVertex3f(-16, 10, 1);//belakang kiri
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 10, 8); //belakang kanan
    glVertex3f(-9, 11, 8);//depan kanan
    glVertex3f(-16, 11, 5);//depan kiri
    glVertex3f(-16, 10, 5);//belakang kiri
    glEnd();

    //jejantas 3 belah kiri
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 15, 4); //belakang kanan
    glVertex3f(-9, 15, 8);//depan kanan
    glVertex3f(-16, 15, 5);//depan kiri
    glVertex3f(-16, 15, 1);//belakang kiri
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 15, 4); //belakang kanan
    glVertex3f(-9, 16, 4);//depan kanan
    glVertex3f(-16, 16, 1);//depan kiri
    glVertex3f(-16, 15, 1);//belakang kiri
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-9, 15, 8); //belakang kanan
    glVertex3f(-9, 16, 8);//depan kanan
    glVertex3f(-16, 16, 5);//depan kiri
    glVertex3f(-16, 15, 5);//belakang kiri
    glEnd();

}

//-------------------------------- JEJANTAS R ----------------------------------
void jejantasR(void)
{

    //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 4, 4); //belakang kanan
    glVertex3f(8, 4, 8);//depan kanan
    glVertex3f(15, 4, 5);//depan kiri
    glVertex3f(15, 4, 1);//belakang kiri
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 4, 4); //belakang kanan
    glVertex3f(8, 5, 4);//depan kanan
    glVertex3f(15, 5, 1);//depan kiri
    glVertex3f(15, 4, 1);//belakang kiri
    glEnd();
    //depan
     //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 4, 8); //belakang kanan
    glVertex3f(8, 5, 8);//depan kanan
    glVertex3f(15, 5, 5);//depan kiri
    glVertex3f(15, 4, 5);//belakang kiri
    glEnd();

    //jejantas2
     //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 10, 4); //belakang kanan
    glVertex3f(8, 10, 8);//depan kanan
    glVertex3f(15, 10, 5);//depan kiri
    glVertex3f(15, 10, 1);//belakang kiri
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 10, 4); //belakang kanan
    glVertex3f(8, 11, 4);//depan kanan
    glVertex3f(15, 11, 1);//depan kiri
    glVertex3f(15, 10, 1);//belakang kiri
    glEnd();
    //depan
     //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 10, 8); //belakang kanan
    glVertex3f(8, 11, 8);//depan kanan
    glVertex3f(15, 11, 5);//depan kiri
    glVertex3f(15, 10, 5);//belakang kiri
    glEnd();
    //jejantas3
   //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 15, 4); //belakang kanan
    glVertex3f(8, 15, 8);//depan kanan
    glVertex3f(15, 15, 5);//depan kiri
    glVertex3f(15, 15, 1);//belakang kiri
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 15, 4); //belakang kanan
    glVertex3f(8, 16, 4);//depan kanan
    glVertex3f(15, 16, 1);//depan kiri
    glVertex3f(15, 15, 1);//belakang kiri
    glEnd();
    //depan
     //back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(8, 15, 8); //belakang kanan
    glVertex3f(8, 16, 8);//depan kanan
    glVertex3f(15, 16, 5);//depan kiri
    glVertex3f(15, 15, 5);//belakang kiri
    glEnd();
}

//-------------------------------- BLOCK L ----------------------------------

void logoftmk(void) {
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.1);
    glTexCoord2d(0.15, 0.0); glVertex3f(-3.5, 13, 12.01f); //bawah (L)
    glTexCoord2d(1.1, 0.0);  glVertex3f(2.4, 13, 12.01f); //bawah (R)
    glTexCoord2d(1.1, 1.0); glVertex3f(2.4, 16, 12.01f); //atas (R)
    glTexCoord2d(0.15, 1.0); glVertex3f(-3.5, 16, 12.01f); //bawah (L)
    glEnd();
}
void blockL(void)
{
    //bumbung
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0, 1.0f);    // 
    glVertex3f(-31, 20, 2);    // depan (R)
    glVertex3f(-15.0f, 20, 5.0);    // depan (L)
    glVertex3f(-15.0f, 20, 1.0f);    // belakang (L)
    glVertex3f(-31, 20, -2.0f);    // belakang (R)
    glEnd();
    //bumbung
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0, 1.0f);    // 
    glVertex3f(-31, 22, 2);    // depan (R)
    glVertex3f(-15.0f, 22, 5.0);    // depan (L)
    glVertex3f(-15.0f, 22, 1.0f);    // belakang (L)
    glVertex3f(-31, 22, -2.0f);    // belakang (R)
    glEnd();
    //Back
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-16, 20, 1.0f); //bawah (L)
    glVertex3f(-30, 20, -2.0f); //bawah (R)
    glVertex3f(-30, 22, -2.0f); //atas (R)
    glVertex3f(-16, 22, 1.0f); //bawah (L)
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-15, 20, 5.0f); //bawah (L)
    glVertex3f(-31, 20, 2.0f); //bawah (R)
    glVertex3f(-31, 22, 2.0f); //atas (R)
    glVertex3f(-15, 22, 5.0f); //bawah (L)
    glEnd();

    //---tingkap aras 1
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-18, 3, 5.01f); //bawah (L)
    glVertex3f(-22, 3, 4.01f); //bawah (R)
    glVertex3f(-22, 6, 4.01f); //atas (R)
    glVertex3f(-18, 6, 5.01f); //bawah (L)
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-23, 3, 4.01f); //bawah (L)
    glVertex3f(-27, 3, 3.01f); //bawah (R)
    glVertex3f(-27, 6, 3.01f); //atas (R)
    glVertex3f(-23, 6, 4.01f); //bawah (L)
    glEnd();

    //aras 2
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-18, 9, 5.01f); //bawah (L)
    glVertex3f(-22, 9, 4.01f); //bawah (R)
    glVertex3f(-22, 12, 4.01f); //atas (R)
    glVertex3f(-18, 12, 5.01f); //bawah (L)
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-23, 9, 4.01f); //bawah (L)
    glVertex3f(-27, 9, 3.01f); //bawah (R)
    glVertex3f(-27, 12, 3.01f); //atas (R)
    glVertex3f(-23, 12, 4.01f); //bawah (L)
    glEnd();

    //aras 3
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-18, 15, 5.01f); //bawah (L)
    glVertex3f(-22, 15, 4.01f); //bawah (R)
    glVertex3f(-22, 18, 4.01f); //atas (R)
    glVertex3f(-18, 18, 5.01f); //bawah (L)
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(-23, 15, 4.01f); //bawah (L)
    glVertex3f(-27, 15, 3.01f); //bawah (R)
    glVertex3f(-27, 18, 3.01f); //atas (R)
    glVertex3f(-23, 18, 4.01f); //bawah (L)
    glEnd();

    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-31, 20, 2.0); //depan bawah
    glVertex3f(-31, 22, 2);//dpn atas
    glVertex3f(-31, 22, -2);//blkg atas
    glVertex3f(-31, 20, -2);//blkg bawah
    glEnd();
    //right
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-15, 20, 5.0); //depan bawah
    glVertex3f(-15, 22, 5);//dpn atas
    glVertex3f(-15, 22, 1);//blkg atas
    glVertex3f(-15, 20, 1);//blkg bawah
    glEnd();
    //--bangunan
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0, 0.0f);    // 
    glVertex3f(-30, -1.5f, 2);    // depan (R)
    glVertex3f(-16.0f, -1.5f, 5.0);    // depan (L)
    glVertex3f(-16.0f, -1.5f, 1.0f);    // belakang (L)
    glVertex3f(-30, -1.5f, -2.0f);    // belakang (R)
    glEnd();
    //Back
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(-16, -1.5f, 1.0f); //bawah (L)
    glVertex3f(-30, -1.5f, -2.0f); //bawah (R)
    glVertex3f(-30, 20, -2.0f); //atas (R)
    glVertex3f(-16, 20, 1.0f); //bawah (L)
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(-16, -1.5f, 5.0f); //bawah (L)
    glVertex3f(-30, -1.5f, 2.0f); //bawah (R)
    glVertex3f(-30, 20, 2.0f); //atas (R)
    glVertex3f(-16, 20, 5.0f); //bawah (L)
    glEnd();
    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(-30, -1.5, 2.0); //depan bawah
    glVertex3f(-30, 20, 2);//dpn atas
    glVertex3f(-30, 20, -2);//blkg atas
    glVertex3f(-30, -1.5, -2);//blkg bawah
    glEnd();
    //right
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(-16, -1.5, 5.0); //depan bawah
    glVertex3f(-16, 20, 5);//dpn atas
    glVertex3f(-16, 20, 1);//blkg atas
    glVertex3f(-16, -1.5, 1);//blkg bawah
    glEnd();
    //cat

      //depan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0);
    glVertex3f(-16, -1.5f, 5.01f); //bawah (L)
    glVertex3f(-30, -1.5f, 2.01f); //bawah (R)
    glVertex3f(-30, 1.5, 2.01f); //atas (R)
    glVertex3f(-16, 1.5, 5.01f); //bawah (L)
    glEnd();
    /* glBegin(GL_POLYGON);
     glColor3f(1, 1, 0);
     glVertex3f(-16, -1.5, 5.01); //depan bawah
     glVertex3f(-16, 1.5, 5.01);//dpn atas
     glVertex3f(-16, 1.5, 1.01);//blkg atas
     glVertex3f(-16, -1.5, 1.01);//blkg bawah
     glEnd();
     glBegin(GL_POLYGON);
     glColor3f(1, 1, 0);
     glVertex3f(-30, -1.5, 2.01); //depan bawah
     glVertex3f(-30, 1.5, 2.01);//dpn atas
     glVertex3f(-30, 1.5, -2.01);//blkg atas
     glVertex3f(-30, -1.5, -2.01);//blkg bawah
     glEnd();*/

}

//-------------------------------- INTERIOR CLASS L ----------------------------------

void InteriorClassroomKiri(void)
{

    //Frame 1 (Kiri)
    glPushMatrix();
    glTranslatef(-30, 1.34, -0.2);
    glColor3f(1, 1, 1);
    glScalef(-0.5, -0.3, -0.1);
    //glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 1.33, -0.35);
    glColor3f(1, 1, 1);
    glScalef(-0.2, -0.1, -0.5);
    //glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
    glutSolidCube(0.5);
    glPopMatrix();





    //Jam Dinding
    glPushMatrix();
    glTranslatef(-30, 1.3, -0.2);
    glColor3f(0.5, 0.6, 0.5);
    glScalef(-0.1, 0.6, 0.6);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    //--------Whiteboard
    glPushMatrix();
    glTranslatef(-29.99, -0.1, -0);
    glColor3f(1, 1, 1);
    glScalef(-0.2, 2.8, 4.8);
    glutSolidCube(0.6);
    glPopMatrix();
    //--------MEJA 1 KIRI DEPAN KELAS-------------
    //Meja 1 (Kiri depan)
    glPushMatrix();
    glTranslatef(-25.9, -0.8, 1.9);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.7, 0.2, 1.5);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja 1 depan (Kiri)
    glPushMatrix();
    glTranslatef(-26.1, -1.2, 2.4);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 1 belakang (Kiri)
    glPushMatrix();
    glTranslatef(-26.1, -1.2, 1.3);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 1 depan (R)
    glPushMatrix();
    glTranslatef(-25.7, -1.2, 2.4);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 1 belakang (R)
    glPushMatrix();
    glTranslatef(-25.7, -1.2, 1.3);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------MEJA 2 KIRI DEPAN KELAS-------------
     //Meja 2 (Kiri depan)
    glPushMatrix();
    glTranslatef(-25.9, -0.8, -0.35);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.7, 0.2, 1.5);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja 2 depan (Kiri)
    glPushMatrix();
    glTranslatef(-26.1, -1.2, 0.2);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 2 belakang (Kiri)
    glPushMatrix();
    glTranslatef(-26.1, -1.2, -0.9);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 2 depan (R)
    glPushMatrix();
    glTranslatef(-25.7, -1.2, 0.2);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 2 belakang (R)
    glPushMatrix();
    glTranslatef(-25.7, -1.2, -0.9);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //-----------kerusi meja 2-----------------------
   //tempat duduk
    glPushMatrix();
    glTranslatef(-25.3, -1.0, -0.3);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.6, 0.1, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //sandar kerusi
    glPushMatrix();
    glTranslatef(-25, -0.8, -0.3);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();

    //kaki kerusi 1
    glPushMatrix();
    glTranslatef(-25, -1.2, -0.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 2
    glPushMatrix();
    glTranslatef(-25, -1.2, -0.5);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 3
    glPushMatrix();
    glTranslatef(-25.5, -1.23, -0.5);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 4
    glPushMatrix();
    glTranslatef(-25.5, -1.23, -0.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();


    //kerusi meja 1

     //-----------kerusi meja 1-----------------------
    //tempat duduk
    glPushMatrix();
    glTranslatef(-25.3, -1.0, 1.9);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.6, 0.1, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //sandar kerusi
    glPushMatrix();
    glTranslatef(-25, -0.8, 1.9);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();

    //kaki kerusi 1
    glPushMatrix();
    glTranslatef(-25, -1.2, 1.7);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 2
    glPushMatrix();
    glTranslatef(-25, -1.2, 2.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 3
    glPushMatrix();
    glTranslatef(-25.5, -1.23, 1.7);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 4
    glPushMatrix();
    glTranslatef(-25.5, -1.23, 2.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();


    //------------MEJA 3 KE KANAN SKIT----------
    glPushMatrix();
    glTranslatef(-23.9, -0.8, 2.55);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.7, 0.2, 1.5);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja depan (Kiri)
    glPushMatrix();
    glTranslatef(-24.1, -1.2, 3);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja belakang (Kiri)
    glPushMatrix();
    glTranslatef(-24.1, -1.2, 2);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    //Kaki meja depan (R)
    glPushMatrix();
    glTranslatef(-23.7, -1.2, 3);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    //Kaki meja belakang (Kiri)
    glPushMatrix();
    glTranslatef(-23.7, -1.2, 2);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //-----------kerusi meja -----------------------
//tempat duduk
    glPushMatrix();
    glTranslatef(-23, -1.0, 2.6);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.6, 0.1, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //sandar kerusi
    glPushMatrix();
    glTranslatef(-22.7, -0.8, 2.6);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();

    //kaki kerusi 1
    glPushMatrix();
    glTranslatef(-22.7, -1.2, 2.8);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 2
    glPushMatrix();
    glTranslatef(-22.7, -1.2, 2.4);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();

    //kaki kerusi 3
    glPushMatrix();
    glTranslatef(-23.2, -1.3, 2.8);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 4
    glPushMatrix();
    glTranslatef(-23.2, -1.3, 2.4);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();

    //-----MEJA 4 KE KANAN SKIT TP BELAKANG

    glPushMatrix();
    glTranslatef(-23.9, -0.8, 0.2);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.7, 0.2, 1.5);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja depan (Kiri)
    glPushMatrix();
    glTranslatef(-24.1, -1.2, 0.7);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    //Kaki meja depan (R)
    glPushMatrix();
    glTranslatef(-23.7, -1.2, 0.7);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja belakang (Kiri)
    glPushMatrix();
    glTranslatef(-24.1, -1.2, -0.4);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja belakang (R)
    glPushMatrix();
    glTranslatef(-23.5, -1.2, -0.4);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.3, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //-----------kerusi meja4 -----------------------
//tempat duduk
    glPushMatrix();
    glTranslatef(-23, -1.0, 0.2);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.6, 0.1, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //sandar kerusi
    glPushMatrix();
    glTranslatef(-22.7, -0.8, 0.2);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 1
    glPushMatrix();
    glTranslatef(-22.7, -1.2, 0.4);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 2
    glPushMatrix();
    glTranslatef(-22.7, -1.2, 0);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 3
    glPushMatrix();
    glTranslatef(-23.2, -1.25, 0.4);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 4
    glPushMatrix();
    glTranslatef(-23.2, -1.25, 0);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();



}

//-------------------------------- INTERIOR CLASS R ----------------------------------
void InteriorClassroomKanan(void)
{

    //Whiteboard
    glPushMatrix();
    glTranslatef(29.6, -0.1, -0);
    glColor3f(0.5, 0.8, 0.8);
    glScalef(-0.5, 2.8, 4.8);
    glutSolidCube(0.6);
    glPopMatrix();

    //--------MEJA 1 KIRI DEPAN KELAS-------------
   //Meja 1 (Kiri depan)
    glPushMatrix();
    glTranslatef(25.9, -0.8, 1.9);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.7, 0.2, 1.5);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja 1 depan (Kiri)
    glPushMatrix();
    glTranslatef(26.1, -1.2, 2.4);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 1 belakang (Kiri)
    glPushMatrix();
    glTranslatef(26.1, -1.2, 1.3);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 1 depan (R)
    glPushMatrix();
    glTranslatef(25.7, -1.2, 2.4);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 1 belakang (R)
    glPushMatrix();
    glTranslatef(25.7, -1.2, 1.3);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------MEJA 2 KIRI DEPAN KELAS-------------
   //Meja 2 (Kiri depan)
    glPushMatrix();
    glTranslatef(25.9, -0.8, -0.35);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.7, 0.2, 1.5);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja 2 depan (Kiri)
    glPushMatrix();
    glTranslatef(26.1, -1.2, 0.2);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 2 belakang (Kiri)
    glPushMatrix();
    glTranslatef(26.1, -1.2, -0.9);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 2 depan (R)
    glPushMatrix();
    glTranslatef(25.7, -1.2, 0.2);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja 2 belakang (R)
    glPushMatrix();
    glTranslatef(25.7, -1.2, -0.9);
    glColor3f(0.7, 0.7, 0.7);
    glScalef(-0.1, 1.25, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    //-----------kerusi meja 2-----------------------
   //tempat duduk
    glPushMatrix();
    glTranslatef(25.3, -1.0, -0.3);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.6, 0.1, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //sandar kerusi
    glPushMatrix();
    glTranslatef(25, -0.8, -0.3);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();

    //kaki kerusi 1
    glPushMatrix();
    glTranslatef(25, -1.2, -0.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 2
    glPushMatrix();
    glTranslatef(25, -1.2, -0.5);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 3
    glPushMatrix();
    glTranslatef(25.5, -1.23, -0.5);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 4
    glPushMatrix();
    glTranslatef(25.5, -1.23, -0.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();

    //kerusi meja 1

     //-----------kerusi meja 1-----------------------
    //tempat duduk
    glPushMatrix();
    glTranslatef(25.3, -1.0, 1.9);
    glColor3f(0.5, 0.3, 0);
    glScalef(0.6, 0.1, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();
    //sandar kerusi
    glPushMatrix();
    glTranslatef(25, -0.8, 1.9);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.7);
    glutSolidCube(0.9);
    glPopMatrix();

    //kaki kerusi 1
    glPushMatrix();
    glTranslatef(25, -1.2, 1.7);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 2
    glPushMatrix();
    glTranslatef(25, -1.2, 2.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 3
    glPushMatrix();
    glTranslatef(25.5, -1.23, 1.7);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();
    //kaki kerusi 4
    glPushMatrix();
    glTranslatef(25.5, -1.23, 2.1);
    glColor3f(0.5, 0.4, 0);
    glScalef(0.1, 0.6, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();

}
//-------------------------------- BLOCK R ----------------------------------
//texture mapping utem

void blockR(void)
{
    //bumbung
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0, 1.0f);    // 
    glVertex3f(31, 22, 2.0f);    // depan (R)
    glVertex3f(14, 22, 5.0f);    // depan (L)
    glVertex3f(14, 22, 1.0f);    // belakang (L)
    glVertex3f(31, 22, -2.0f);    // belakang (R)
    glEnd();
    //Back bumbung
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(14, 20, 1.0f); //bawah (L)
    glVertex3f(31, 20, -2.0f); //bawah (R)
    glVertex3f(31, 22, -2.0f); //atas (R)
    glVertex3f(14, 22, 1.0f); //bawah (L)
    glEnd();
    //right
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(31, 20, 2.0); //depan bawah
    glVertex3f(31, 22, 2);//dpn atas
    glVertex3f(31, 22, -2.0);//blkg atas
    glVertex3f(31, 20, -2.0);//blkg bawah
    glEnd();
    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(14, 20, 5.0); //depan bawah
    glVertex3f(14, 22, 5);//dpn atas
    glVertex3f(14, 22, 1.0);//blkg atas
    glVertex3f(14, 20, 1.0);//blkg bawah
    glEnd();
    //depan bumbung
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(14, 20, 5.0f); //bawah (L)
    glVertex3f(31, 20, 2.0f); //bawah (R)
    glVertex3f(31, 22, 2.0f); //atas (R)
    glVertex3f(14, 22, 5.0f); //bawah (L)
    glEnd();
    //bumbung
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0, 1.0f);    // 
    glVertex3f(31, 20, 2.0f);    // depan (R)
    glVertex3f(14, 20, 5.0f);    // depan (L)
    glVertex3f(14, 20, 1.0f);    // belakang (L)
    glVertex3f(31, 20, -2.0f);    // belakang (R)
    glEnd();

    //bangunan
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0, 0.0f);    // 
    glVertex3f(30, -1.5f, 2.0f);    // depan (R)
    glVertex3f(15, -1.5f, 5.0f);    // depan (L)
    glVertex3f(15, -1.5f, 1.0f);    // belakang (L)
    glVertex3f(30, -1.5f, -2.0f);    // belakang (R)
    glEnd();
    //Back
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(15, -1.5f, 1.0f); //bawah (L)
    glVertex3f(30, -1.5f, -2.0f); //bawah (R)
    glVertex3f(30, 20, -2.0f); //atas (R)
    glVertex3f(15, 20, 1.0f); //bawah (L)
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(15, -1.5f, 5.0f); //bawah (L)
    glVertex3f(30, -1.5f, 2.0f); //bawah (R)
    glVertex3f(30, 20, 2.0f); //atas (R)
    glVertex3f(15, 20, 5.0f); //bawah (L)
    glEnd();
    //-----tingkap----------
    //tingkap aras 1
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(17, 3, 5.01f); //bawah (L)
    glVertex3f(21, 3, 4.01f); //bawah (R)
    glVertex3f(21, 6, 4.01f); //atas (R)
    glVertex3f(17, 6, 5.01f); //bawah (L)
    glEnd();
    //tingkap 2 aras 1
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(23, 3, 4.01f); //bawah (L)
    glVertex3f(27, 3, 3.01f); //bawah (R)
    glVertex3f(27, 6, 3.01f); //atas (R)
    glVertex3f(23, 6, 4.01f); //bawah (L)
    glEnd();
    //tingkap aras 2
     //tingkap
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(17, 9, 5.01f); //bawah (L)
    glVertex3f(21, 9, 4.01f); //bawah (R)
    glVertex3f(21, 12, 4.01f); //atas (R)
    glVertex3f(17, 12, 5.01f); //bawah (L)
    glEnd();
    //tingkap 2 aras 1
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(23, 9, 4.01f); //bawah (L)
    glVertex3f(27, 9, 3.01f); //bawah (R)
    glVertex3f(27, 12, 3.01f); //atas (R)
    glVertex3f(23, 12, 4.01f); //bawah (L)
    glEnd();
    //tingkap3
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(17, 15, 5.01f); //bawah (L)
    glVertex3f(21, 15, 4.01f); //bawah (R)
    glVertex3f(21, 18, 4.01f); //atas (R)
    glVertex3f(17, 18, 5.01f); //bawah (L)
    glEnd();
    //tingkap 2 aras 1
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);
    glVertex3f(23, 15, 4.01f); //bawah (L)
    glVertex3f(27, 15, 3.01f); //bawah (R)
    glVertex3f(27, 18, 3.01f); //atas (R)
    glVertex3f(23, 18, 4.01f); //bawah (L)
    glEnd();


    //bangunan
    //right
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(30, -1.5, 2.0); //depan bawah
    glVertex3f(30, 20, 2);//dpn atas
    glVertex3f(30, 20, -2.0);//blkg atas
    glVertex3f(30, -1.5, -2.0);//blkg bawah
    glEnd();
    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(15, -1.5, 5.0); //depan bawah
    glVertex3f(15, 20, 5);//dpn atas
    glVertex3f(15, 20, 1.0);//blkg atas
    glVertex3f(15, -1.5, 1.0);//blkg bawah
    glEnd();

    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(15, -1.5f, 5.01f); //bawah (L)
    glVertex3f(30, -1.5f, 2.01f); //bawah (R)
    glVertex3f(30, 1.5, 2.01f); //atas (R)
    glVertex3f(15, 1.5, 5.01f); //bawah (L)
    glEnd();
    /* //right
     glBegin(GL_POLYGON);
     glColor3f(1, 1, 0);
     glVertex3f(30, -1.5, 2.01); //depan bawah
     glVertex3f(30, 1.5, 2.01);//dpn atas
     glVertex3f(30, 1.5, -2.01);//blkg atas
     glVertex3f(30, -1.5, -2.01);//blkg bawah
     glEnd();
     //Left
     glBegin(GL_POLYGON);
     glColor3f(1, 1, 0);
     glVertex3f(15, -1.5, 5.01); //depan bawah
     glVertex3f(15, 1.5, 5.01);//dpn atas
     glVertex3f(15, 1.5, 1.01);//blkg atas
     glVertex3f(15, -1.5, 1.01);//blkg bawah
     glEnd();

     */
}

//-------------------------------- BLOCK TENGAH ----------------------------------
void blocktengah()
{
    //blockcentrekanan
    glPushMatrix();
    glTranslatef(5, 11, 6);
    glColor3f(1, 5, 0.7);
    glScalef(7, 18, 6);
    glutSolidCube(1);
    glPopMatrix();

    //blockcentrekiri
    glPushMatrix();
    glTranslatef(-6.4, 11, 6);
    glColor3f(1, 5, 0.7);
    glScalef(7, 18, 6);
    glutSolidCube(1);
    glPopMatrix();


    //blockcentretengah
    glPushMatrix();
    glTranslatef(0, 9, 5.5);
    glColor3f(1.0, 0.9, 0.1);
    glScalef(6, 15, 0.8);
    glutSolidCube(1);
    glPopMatrix();

    //blockcentretengahatas
    glPushMatrix();
    glTranslatef(0, 18, 6);
    glColor3f(1, 5, 0.7);
    glScalef(6, 4, 6);
    glutSolidCube(1);
    glPopMatrix();

    //tiangkiri1
    glPushMatrix();
    glTranslatef(-9.2, 0, 8.2);
    glColor3f(1.0, 1.0, 0);
    glScalef(1, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //tiangkiri2
    glPushMatrix();
    glTranslatef(-3.5, 0, 8.2);
    glColor3f(1.0, 1.0, 0);
    glScalef(1, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //tiangkanan1
    glPushMatrix();
    glTranslatef(2.5, 0, 8.2);
    glColor3f(1.0, 1.0, 0);
    glScalef(1, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //tiangkanan1
    glPushMatrix();
    glTranslatef(7.8, 0, 8.2);
    glColor3f(1.0, 1.0, 0);
    glScalef(1, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowrightlevel1
    glPushMatrix();
    glTranslatef(5, 5, 8.8);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowrightlevel2
    glPushMatrix();
    glTranslatef(5, 10, 8.8);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowrightlevel3
    glPushMatrix();
    glTranslatef(5, 15, 8.8);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowleftlevel1
    glPushMatrix();
    glTranslatef(-6.8, 5, 8.8);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowleftlevel2
    glPushMatrix();
    glTranslatef(-6.8, 10, 8.8);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowleftlevel3
    glPushMatrix();
    glTranslatef(-6.8, 15, 8.8);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowtengahlevel1
    glPushMatrix();
    glTranslatef(-0.6, 5, 6);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //windowtengahlevel2
    glPushMatrix();
    glTranslatef(-0.6, 10, 6);
    glColor3f(0, 0.8, 1);
    glScalef(2, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    //bangunankeciktengah
    glPushMatrix();
    glTranslatef(-0.6, 15, 10);
    glColor3f(1.0, 1.0, 0);
    glScalef(6, 4, 4);
    glutSolidCube(1);
    glPopMatrix();

    //bumbungbangunankeciktengah
    glPushMatrix();
    glTranslatef(-0.6, 17.8, 10);
    glColor3f(1, 1, 1);
    glScalef(7, 0.5, 4);
    glutSolidCube(1);
    glPopMatrix();

    //bumbungtengah
    glPushMatrix();
    glTranslatef(-0.6, 20, 6);
    glColor3f(1, 1, 1);
    glScalef(20, 0.5, 8);
    glutSolidCube(1);
    glPopMatrix();

    //catkiri
    glPushMatrix();
    glTranslatef(-6.4, 1.5, 6);
    glColor3f(1.0, 1.0, 0);
    glScalef(7, 1, 6);
    glutSolidCube(1);
    glPopMatrix();

    //catkanan
    glPushMatrix();
    glTranslatef(5, 1.5, 6);
    glColor3f(1.0, 1.0, 0);
    glScalef(7, 1, 6);
    glutSolidCube(1);
    glPopMatrix();
}

//-------------------------------- TAPAK ----------------------------------
void tapak(void)
{
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-6, -1.51, -1.5);
    glVertex3f(7, -1.51, -1.5);
    glVertex3f(7, -1.51, 7.5);
    glVertex3f(-6, -1.51, 7.5);
    glEnd();
}

//--------------------------------PASU BUNGA-------------------------------
void pasubunga()
{
    //bunga1
    glPushMatrix();
    glTranslatef(0, -0.2, 40);
    glColor3f(0.7, 0.0, 0.0);
    glScalef(0.05, 0.05, 0.05);
    glutSolidSphere(1.5f, 40, 40);
    glPopMatrix();
    //bunga2
    glPushMatrix();
    glTranslatef(0.1, -0.2, 40);
    glColor3f(0.7, 0.0, 0.0);
    glScalef(0.05, 0.05, 0.05);
    glutSolidSphere(1.5f, 40, 40);
    glPopMatrix();
    //pokok
    glPushMatrix();
    glTranslatef(0, -0.55, 40);
    glColor3f(0.6, 0.8, 0.1);
    glScalef(0.2, 0.2, 0.2);
    glutSolidSphere(1.5f, 40, 40);
    glPopMatrix();
    //pasu
    glPushMatrix();
    glTranslatef(0, -1, 40);
    glColor3f(00.7, 0.5, 0.2);
    glScalef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

//-----------------------------------TONG SAMPAH--------------------------------
void tongsampah()
{
    //penutup
    glPushMatrix();
    glTranslatef(1.5, -0.55, 8.5);
    glColor3f(0.8, 0.8, 0.6);
    glScalef(0.8, 0.2, 0.8);
    glutSolidCube(1);
    glPopMatrix();
    //tong
    glPushMatrix();
    glTranslatef(1.5, -1, 8.5);
    glColor3f(0, 0, 0);
    glScalef(0.6, 0.9, 0.6);
    glutSolidCube(1);
    glPopMatrix();
}
//-------------------------------- EXTERIOR DESIGN ----------------------------------
void exteriordesign(void)
{
    //VENDING MACHINE KIRI------------------------------
    //vending machine
    glPushMatrix();
    glTranslatef(-9.2, -0.2, 10);
    glColor3f(0.8, 0.8, 0.8);
    glScalef(1.5, 2.6, 1);
    glutSolidCube(1);
    glPopMatrix();

    //vending machine cermin1
    glPushMatrix();
    glTranslatef(-9.2, 0.6, 10.5);
    glColor3f(0.4, 0.8, 1);
    glScalef(1.3, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    //vending machine cermin2
    glPushMatrix();
    glTranslatef(-9.2, 0, 10.5);
    glColor3f(0.4, 0.8, 1);
    glScalef(1.3, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    //vending machine cermin3
    glPushMatrix();
    glTranslatef(-9.2, -0.8, 10.5);
    glColor3f(1, 1, 1);
    glScalef(0.8, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    //VENDING MACHINE KANAN------------------------------
   //vending machine
    glPushMatrix();
    glTranslatef(7.8, -0.2, 10);
    glColor3f(0.8, 0.8, 0.8);
    glScalef(1.5, 2.6, 1);
    glutSolidCube(1);
    glPopMatrix();

    //vending machine cermin1
    glPushMatrix();
    glTranslatef(7.8, 0.6, 10.5);
    glColor3f(0.4, 0.8, 1);
    glScalef(1.3, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    //vending machine cermin2
    glPushMatrix();
    glTranslatef(7.8, 0, 10.5);
    glColor3f(0.4, 0.8, 1);
    glScalef(1.3, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    //vending machine cermin3
    glPushMatrix();
    glTranslatef(7.8, -0.8, 10.5);
    glColor3f(1, 1, 1);
    glScalef(0.8, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    //pokokkanan1
    glPushMatrix();
    glTranslatef(5, 1.7, 20);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkanan1
    glPushMatrix();
    glTranslatef(5, -0.6, 20);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //pokokkanan2
    glPushMatrix();
    glTranslatef(5, 1.7, 24);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkanan2
    glPushMatrix();
    glTranslatef(5, -0.6, 24);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //pokokkanan3
    glPushMatrix();
    glTranslatef(5, 1.7, 28);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkanan3
    glPushMatrix();
    glTranslatef(5, -0.6, 28);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //pokokkanan4
    glPushMatrix();
    glTranslatef(5, 1.7, 32);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkanan4
    glPushMatrix();
    glTranslatef(5, -0.6, 32);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();


    //pokokkiri1
    glPushMatrix();
    glTranslatef(-6, 1.7, 20);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkiri1
    glPushMatrix();
    glTranslatef(-6, -0.6, 20);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();


    //pokokkiri2
    glPushMatrix();
    glTranslatef(-6, 1.7, 24);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkiri2
    glPushMatrix();
    glTranslatef(-6, -0.6, 24);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //pokokkiri3
    glPushMatrix();
    glTranslatef(-6, 1.7, 28);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkiri3
    glPushMatrix();
    glTranslatef(-6, -0.6, 28);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //pokokkiri4
    glPushMatrix();
    glTranslatef(-6, 1.7, 32);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokokkiri4
    glPushMatrix();
    glTranslatef(-6, -0.6, 32);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraight
    glPushMatrix();
    glTranslatef(-0.9, -1.5, 19);
    glColor3f(0.4, 0.5, 0.5);
    glScalef(8.5, 0, 35);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraightputih
    glPushMatrix();
    glTranslatef(-1, -1.4, 8);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.02, 2.8);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraightputih
    glPushMatrix();
    glTranslatef(-1, -1.4, 15);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.02, 2.8);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraightputih
    glPushMatrix();
    glTranslatef(-1, -1.4, 22);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.02, 2.8);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraightputih
    glPushMatrix();
    glTranslatef(-1, -1.4, 29);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.02, 2.8);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraightkiri
    glPushMatrix();
    glTranslatef(-4.8, -1.2, 17.1);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.6, 32);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayastraightkanan
    glPushMatrix();
    glTranslatef(3.6, -1.2, 17.1);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.6, 32);
    glutSolidCube(1.0);
    glPopMatrix();

    //tongsampahkanan
    glPushMatrix();
    tongsampah();
    glPopMatrix();

    //tongsampahkiri
    glPushMatrix();
    glTranslatef(-4, 0, 0);
    tongsampah();
    glPopMatrix();

    //pasubunga1
    glPushMatrix();
    glTranslatef(-15, -0.25, 12);
    pasubunga();
    glPopMatrix();

    //pasubunga2
    glPushMatrix();
    glTranslatef(13, -0.25, -6);
    pasubunga();
    glPopMatrix();

    //pasubunga3
    glPushMatrix();
    glTranslatef(-15, -0.25, -6);
    pasubunga();
    glPopMatrix();

    //pasubunga4
    glPushMatrix();
    glTranslatef(13, -0.25, 12);
    pasubunga();
    glPopMatrix();

    //jalanrayapetak
    glPushMatrix();
    glTranslatef(-1, -1.5, 43);
    glColor3f(0.4, 0.5, 0.5);
    glScalef(30, 0, 20);
    glutSolidCube(1.0);
    glPopMatrix();

    //rumput
    glPushMatrix();
    glTranslatef(-1, -1.6, 44);
    glColor3f(0, 0.5, 0.1);
    glScalef(20, 0, 20);
    glutSolidCube(20);
    glPopMatrix();

    //jalanrayapetakborderkanan
    glPushMatrix();
    glTranslatef(14, -1.2, 43);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.6, 20);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayapetakborderkiri
    glPushMatrix();
    glTranslatef(-16, -1.2, 43);
    glColor3f(1, 1, 1);
    glScalef(0.5, 0.6, 20);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayapetakborderkirimelintang1
    glPushMatrix();
    glTranslatef(-10.4, -1.2, 33);
    glColor3f(1, 1, 1);
    glScalef(11.7, 0.6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayapetakborderkananmelintang2
    glPushMatrix();
    glTranslatef(-10.4, -1.2, 53);
    glColor3f(1, 1, 1);
    glScalef(11.7, 0.6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayapetakborderkananmelintang1
    glPushMatrix();
    glTranslatef(8.8, -1.2, 33);
    glColor3f(1, 1, 1);
    glScalef(10.9, 0.6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //jalanrayapetakborderkananmelintang2
    glPushMatrix();
    glTranslatef(8.8, -1.2, 53);
    glColor3f(1, 1, 1);
    glScalef(10.9, 0.6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //signboardkakikiri
    glPushMatrix();
    glTranslatef(-4.3, 1.5, 53);
    glColor3f(0.8, 0.8, 0.8);
    glScalef(0.5, 6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //signboardkakikanan
    glPushMatrix();
    glTranslatef(3.1, 1.5, 53);
    glColor3f(0.8, 0.8, 0.8);
    glScalef(0.5, 6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //signboardbusstop
    glPushMatrix();
    glTranslatef(38, 1.4, 56);
    glColor3f(0.8, 0.8, 0.8);
    glScalef(0.5, 6, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();


    //busstopbumbung
    glPushMatrix();
    glTranslatef(28, 4, 53);
    glColor3f(0, 0.1, 0.4);
    glScalef(18, 0.8, 5);
    glutSolidCube(0.9);
    glPopMatrix();

    //busstoptempatduduk
    glPushMatrix();
    glTranslatef(28, -0.5, 53);
    glColor3f(0, 0, 0);
    glScalef(16, 0.6, 3);
    glutSolidCube(0.9);
    glPopMatrix();

    //busstopsandar
    glPushMatrix();
    glTranslatef(28, 1.2, 52);
    glColor3f(0, 0.7, 0.9);
    glScalef(16, 2, 0.1);
    glutSolidCube(0.9);
    glPopMatrix();

    //tiangkiribusstop
    glPushMatrix();
    glTranslatef(21, 1.3, 53);
    glColor3f(0, 0.1, 0.4);
    glScalef(0.5, 6, 3);
    glutSolidCube(1.0);
    glPopMatrix();

    //tiangkananbusstop
    glPushMatrix();
    glTranslatef(35, 1.3, 53);
    glColor3f(0, 0.1, 0.4);
    glScalef(0.5, 6, 3);
    glutSolidCube(1.0);
    glPopMatrix();

    //GUARD HOUSE---------------------------
    //bumbung
    glPushMatrix();
    glTranslatef(-8, 2, 58);
    glColor3f(0.5, 0.3, 0.1);
    glRotatef(-90.0f, 6.0f, 1.0f, 1.0f);
    glutSolidCone(3, 1.4, 6, 16);
    glPopMatrix();

    //rumah
    glPushMatrix();
    glTranslatef(-8, 0.3, 58);
    glColor3f(1, 0.9, 0.3);
    glScalef(1.6, 1.8, 1.6);
    glutSolidCube(2);
    glPopMatrix();

    //tingkap
    glPushMatrix();
    glTranslatef(-8, 1, 59.6);
    glColor3f(0.2, 0.7, 0.9);
    glScalef(2, 1, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    //meja
    glPushMatrix();
    glTranslatef(-8, 0.5, 59.6);
    glColor3f(1, 1, 1);
    glScalef(2, 0.15, 1);
    glutSolidCube(1);
    glPopMatrix();

    //penghadang----------------------------------
     //penghadang1
    glPushMatrix();
    glTranslatef(-5, -0.2, 58);
    glColor3f(1, 1, 0.5);
    glScalef(0.8, 2.8, 0.8);
    glutSolidCube(1);
    glPopMatrix();

    //penghadang2
    glPushMatrix();
    glTranslatef(-1, -0.2, 58);
    glColor3f(0, 0, 0);
    glScalef(8, 0.5, 0.18);
    glutSolidCube(1);
    glPopMatrix();

    //---------------------PONDOKECIKKANAN---------------------------

    //pondokkecik
    glPushMatrix();
    glTranslatef(14.5, 1.5, 18.5);
    glColor3f(0.5, 0.3, 0.1);
    glRotatef(-90.0f, 6.0f, 1.0f, 1.0f);
    glutSolidCone(4, 1.8, 32, 16);
    glPopMatrix();

    //pondokkeciktempatduduk1
    glPushMatrix();
    glTranslatef(14.5, -0.8, 17);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(5, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

    //pondokkeciktempatduduk2
    glPushMatrix();
    glTranslatef(14.5, -0.8, 20);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(5, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

    //kakipondokkiri1
    glPushMatrix();
    glTranslatef(12, 0, 17);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //kakipondokkiri2
    glPushMatrix();
    glTranslatef(12, 0, 20);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //kakipondokkanan1
    glPushMatrix();
    glTranslatef(17, 0, 17);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //kakipondokkanan2
    glPushMatrix();
    glTranslatef(17, 0, 20);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------PONDOKECIKKIRI---------------------------

    //pondokkecik
    glPushMatrix();
    glTranslatef(-15, 1.5, 18.5);
    glColor3f(0.5, 0.3, 0.1);
    glRotatef(-90.0f, 6.0f, 1.0f, 1.0f);
    glutSolidCone(4, 1.8, 32, 16);
    glPopMatrix();

    //pondokkeciktempatduduk1
    glPushMatrix();
    glTranslatef(-15, -0.8, 17);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(5, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

    //pondokkeciktempatduduk2
    glPushMatrix();
    glTranslatef(-15, -0.8, 20);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(5, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

    //kakipondokkanan1
    glPushMatrix();
    glTranslatef(-12.5, 0, 17);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //kakipondokkanan2
    glPushMatrix();
    glTranslatef(-12.5, 0, 20);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //kakipondokkiri1
    glPushMatrix();
    glTranslatef(-17.5, 0, 17);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //kakipondokkiri2
    glPushMatrix();
    glTranslatef(-17.5, 0, 20);
    glColor3f(0.5, 0.2, 0.1);
    glScalef(0.2, 3, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();



}

//------------------------ STREET LAMP --------------------------
void lamp(void)
{
    //---------------------------- LAMP 1R ----------------------------
        //lampu

    glPushMatrix();
    glTranslatef(5, 3.5, 14);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(5, 1, 14);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    //--------------------------- LAMP 2R ---------------------------
        //lampu
    glPushMatrix();
    glTranslatef(6.5, 3.5, 32);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(6.5, 1, 32);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 3R ----------------------------
        //lampu
    glPushMatrix();
    glTranslatef(15, 3.5, 32);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(15, 1, 32);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 4R ----------------------------
        //lampu
    glPushMatrix();
    glTranslatef(15, 3.5, 42.5);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(15, 1, 42.5);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 5R ----------------------------
        //lampu
    glPushMatrix();
    glTranslatef(15, 3.5, 53);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(15, 1, 53);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 1L ----------------------------
        //lampu

    glPushMatrix();
    glTranslatef(-6, 3.5, 14);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(-6, 1, 14);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    //--------------------------- LAMP 2L ---------------------------
        //lampu
    glPushMatrix();
    glTranslatef(-7.5, 3.5, 32);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(-7.5, 1, 32);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 3L ----------------------------
        //lampu
    glPushMatrix();
    glTranslatef(-16, 3.5, 32);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(-16, 1, 32);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 4L ----------------------------
        //lampu
    glPushMatrix();
    glTranslatef(-16, 3.5, 42.5);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(-16, 1, 42.5);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //---------------------------- LAMP 5L ----------------------------
        //lampu
    glPushMatrix();
    glTranslatef(-16, 3.5, 53);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(0.60f, 40, 40);
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(-16, 1, 53);
    glColor3f(0, 0, 0);
    glScalef(0.4, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
}

//---------------------------------- KIOSK -------------------------------------------
void Kioskkiri()
{
    //Meja
    glPushMatrix();
    glTranslatef(-7.3, -1.0, 1.8);
    glColor3f(0.3, 0, 0.1);
    glScalef(3.0, -1.2, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Bumbung
    glPushMatrix();
    glTranslatef(-7.3, 0.3, 1.8);
    glColor3f(0.8, 0.5, 0.4);
    glScalef(3.2, -0.1, 1.0);
    glutSolidCube(0.9);
    glPopMatrix();

    //Tiang belakang (Kanan)
    glPushMatrix();
    glTranslatef(-6.0, -0.1, 1.5);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tiang depan (Kanan)
    glPushMatrix();
    glTranslatef(-6.0, -0.1, 2.1);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tiang belakang (Kiri)
    glPushMatrix();
    glTranslatef(-8.6, -0.1, 1.5);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tiang depan (Kiri)
    glPushMatrix();
    glTranslatef(-8.6, -0.1, 2.1);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

}

void transport(void)
{
    //--------------------------------- CAR 1 (R) -------------------------------------
     //---------- body car----------
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(10.5, -0.4, 36.5);
    glScalef(10, 2, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Depan
    glPushMatrix();
    glColor3f(0.2, 0, 0.7);
    glTranslatef(11.5, 0.1, 36.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tengah
    glPushMatrix();
    glColor3f(0.2, 0, 0.7);
    glTranslatef(10.4, 0.35, 36.5);
    glScalef(4, 2.5, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glColor3f(0.2, 0, 0.7);
    glTranslatef(9.5, 0.1, 36.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------------------------------- WHEEL 1 (R) -------------------------------------
    // wheel 1 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(12, -1.1, 37.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(9, -1.1, 37.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //glTranslatef(0, 0, -1);

    // wheel 1 (L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(12, -1.1, 35.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 ((L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(9, -1.1, 35.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //--------------------------------- CAR 2 (R) -------------------------------------
        //---------- body car----------
    glPushMatrix();
    glColor3f(0.6, 0.5, 0);
    glTranslatef(10.5, -0.4, 41.5);
    glScalef(10, 2, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Depan
    glPushMatrix();
    glColor3f(0.6, 0.5, 0.5);
    glTranslatef(11.5, 0.1, 41.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tengah
    glPushMatrix();
    glColor3f(0.6, 0.5, 0.5);
    glTranslatef(10.4, 0.35, 41.5);
    glScalef(4, 2.5, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glColor3f(0.6, 0.5, 0.5);
    glTranslatef(9.5, 0.1, 41.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------------------------------- WHEEL 2 (R) -------------------------------------
    // wheel 1 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(12, -1.1, 42.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(9, -1.1, 42.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //glTranslatef(0, 0, -1);

    // wheel 1 (L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(12, -1.1, 40.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 ((L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(9, -1.1, 40.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //--------------------------------- CAR 3 (R) -------------------------------------
        //---------- body car----------
    glPushMatrix();
    glColor3f(0, 0.4, 0.3);
    glTranslatef(10.5, -0.4, 46.5);
    glScalef(10, 2, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Depan
    glPushMatrix();
    glColor3f(0.1, 0, 0.1);
    glTranslatef(11.5, 0.1, 46.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tengah
    glPushMatrix();
    glColor3f(0.1, 0, 0.1);
    glTranslatef(10.4, 0.35, 46.5);
    glScalef(4, 2.5, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glColor3f(0.1, 0, 0.1);
    glTranslatef(9.5, 0.1, 46.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------------------------------- WHEEL 3 (R) -------------------------------------
    // wheel 1 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(12, -1.1, 47.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(9, -1.1, 47.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //glTranslatef(0, 0, -1);

    // wheel 1 (L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(12, -1.1, 45.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 ((L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(9, -1.1, 45.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //--------------------------------- CAR 4 (L) -------------------------------------
    //---------- body car----------
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-12.5, -0.4, 36.5);
    glScalef(10, 2, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Depan
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-13.5, 0.1, 36.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tengah
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-12.6, 0.35, 36.5);
    glScalef(4, 2.5, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-11.5, 0.1, 36.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------------------------------- WHEEL 4 (L)  -------------------------------------
    // wheel 1 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-11, -1.1, 37.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-14, -1.1, 37.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //glTranslatef(0, 0, -1);

    // wheel 1 (L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-11, -1.1, 35.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 ((L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-14, -1.1, 35.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //--------------------------------- CAR 5 (L) -------------------------------------
    //---------- body car----------
    glPushMatrix();
    glColor3f(0.9, 1, 0.1);
    glTranslatef(-12.5, -0.4, 41.5);
    glScalef(10, 2, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Depan
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.7);
    glTranslatef(-13.5, 0.1, 41.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tengah
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.7);
    glTranslatef(-12.6, 0.35, 41.5);
    glScalef(4, 2.5, 4);
    glutSolidCube(.5);
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.7);
    glTranslatef(-11.5, 0.1, 41.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //--------------------------------- WHEEL 5 (L)  -------------------------------------
    // wheel 1 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-11, -1.1, 40.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-14, -1.1, 40.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //glTranslatef(0, 0, -1);

    // wheel 1 (L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-11, -1.1, 42.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    // wheel 2 ((L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-14, -1.1, 42.5);
    glutSolidTorus(0.2, 0.3, 8, 8);
    glPopMatrix();

    //--------------------------------- BUS (L) -------------------------------------
    //---------- body car----------
    glPushMatrix();
    glColor3f(0.2, 0.2, 1);
    glTranslatef(-11.5, -0.4, 47.5);
    glScalef(15, 4, 8);
    glutSolidCube(.5);
    glPopMatrix();

    //Tengah
    glPushMatrix();
    glColor3f(0.7, 0.8, 0.9);
    glTranslatef(-11.5, 1, 47.5);
    glScalef(15, 2, 8);
    glutSolidCube(.5);
    glPopMatrix();

    // Bingkai Pintu
    glPushMatrix();
    glColor3f(0.7, 0.8, 0.9);
    glTranslatef(-10.5, -0.25, 49.5);
    glScalef(3, 4, 0.1);
    glutSolidCube(.5);
    glPopMatrix();

    // Pintu
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-10.5, -0.25, 49.55);
    glScalef(2.5, 3.5, 0.1);
    glutSolidCube(.5);
    glPopMatrix();

    /*//Depan
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.7);
    glTranslatef(-13.5, 0.1, 47.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.7);
    glTranslatef(-11.5, 0.1, 47.5);
    glScalef(3, 2.5, 4);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(0.5);
    glPopMatrix();*/

    //--------------------------------- WHEEL (L)  -------------------------------------
    // wheel 1 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-9, -0.95, 49.5);
    glutSolidTorus(0.3, 0.4, 8, 8);
    glPopMatrix();

    // wheel 2 (R)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-14, -0.95, 49.5);
    glutSolidTorus(0.3, 0.4, 8, 8);
    glPopMatrix();

    //glTranslatef(0, 0, -1);

    // wheel 1 (L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-9, -0.95, 45.5);
    glutSolidTorus(0.3, 0.4, 8, 8);
    glPopMatrix();

    // wheel 2 ((L)
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-14, -0.95, 45.5);
    glutSolidTorus(0.3, 0.4, 8, 8);
    glPopMatrix();

    glFlush();
}

void Kioskkanan()
{
    //Meja
    glPushMatrix();
    glTranslatef(6.0, -1.0, 1.8);
    glColor3f(0.3, 0, 0.1);
    glScalef(3.0, -1.2, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Bumbung
    glPushMatrix();
    glTranslatef(6.0, 0.3, 1.8);
    glColor3f(0.8, 0.5, 0.4);
    glScalef(3.2, -0.1, 1.0);
    glutSolidCube(0.9);
    glPopMatrix();

    //Tiang belakang (Kanan)
    glPushMatrix();
    glTranslatef(7.3, -0.1, 1.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tiang depan (Kanan)
    glPushMatrix();
    glTranslatef(7.3, -0.1, 2.1);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tiang belakang (Kiri)
    glPushMatrix();
    glTranslatef(4.8, -0.1, 1.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tiang depan (Kiri)
    glPushMatrix();
    glTranslatef(4.8, -0.1, 2.1);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 1.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

}

//--------------------------------PICNIC TABLE----------------------------------------
void Picnictablekiri()
{
    //Meja
    glPushMatrix();
    glTranslatef(-7.3, -1.0, 4.5);
    glColor3f(0.8, 0.5, 0.3);
    glScalef(3.0, -0.1, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja belakang (kanan)
    glPushMatrix();
    glTranslatef(-6.0, -1.3, 4.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja depan (kanan)
    glPushMatrix();
    glTranslatef(-6.0, -1.3, 4.8);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja belakang (Kiri)
    glPushMatrix();
    glTranslatef(-8.6, -1.3, 4.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja depan (Kiri)
    glPushMatrix();
    glTranslatef(-8.6, -1.3, 4.8);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kerusi belakang
    glPushMatrix();
    glTranslatef(-7.3, -1.2, 3.7);
    glColor3f(0.8, 0.7, 0.6);
    glScalef(2.7, -0.1, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki kerusi (kanan)
    glPushMatrix();
    glTranslatef(-6.3, -1.4, 3.7);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi (kiri)
    glPushMatrix();
    glTranslatef(-8.3, -1.4, 3.7);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kerusi depan
    glPushMatrix();
    glTranslatef(-7.3, -1.2, 5.2);
    glColor3f(0.8, 0.7, 0.6);
    glScalef(2.7, -0.1, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki kerusi (kanan)
    glPushMatrix();
    glTranslatef(-6.3, -1.4, 5.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi (kiri)
    glPushMatrix();
    glTranslatef(-8.3, -1.4, 5.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();
}

void Picnictablekanan()
{
    //Meja
    glPushMatrix();
    glTranslatef(6.0, -1.0, 4.5);
    glColor3f(0.8, 0.5, 0.3);
    glScalef(3.0, -0.1, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki meja belakang (kanan)
    glPushMatrix();
    glTranslatef(7.3, -1.3, 4.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja depan (kanan)
    glPushMatrix();
    glTranslatef(7.3, -1.3, 4.8);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja belakang (Kiri)
    glPushMatrix();
    glTranslatef(4.7, -1.3, 4.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki meja depan (kiri)
    glPushMatrix();
    glTranslatef(4.7, -1.3, 4.8);
    glColor3f(0, 0, 0);
    glScalef(0.1, 1.0, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kerusi belakang
    glPushMatrix();
    glTranslatef(6.0, -1.2, 3.7);
    glColor3f(0.8, 0.7, 0.6);
    glScalef(2.7, -0.1, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki kerusi (kanan)
    glPushMatrix();
    glTranslatef(7.1, -1.4, 3.7);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi (kiri)
    glPushMatrix();
    glTranslatef(4.9, -1.4, 3.7);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kerusi depan
    glPushMatrix();
    glTranslatef(6.0, -1.2, 5.2);
    glColor3f(0.8, 0.7, 0.6);
    glScalef(2.7, -0.1, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki kerusi (kanan)
    glPushMatrix();
    glTranslatef(7.1, -1.4, 5.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi (kiri)
    glPushMatrix();
    glTranslatef(4.9, -1.4, 5.2);
    glColor3f(0, 0, 0);
    glScalef(0.1, 0.7, 1.4);
    glutSolidCube(0.5);
    glPopMatrix();
}

//-------------------------------- INTERIOR LOBBY ----------------------------------
/*void InteriorLobby(void)
{
    //Frame utk logo ftmk reception
    glPushMatrix();
    glTranslatef(-0.9, 0.28, -3.2);
    glColor3f(128, 128, 128);
    glScalef(-2.4, -1.1, -0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    //Kaki Meja reception
    glPushMatrix();
    glTranslatef(-0.69, -1.0, -2.3);
    glColor3f(128, 128, 0);
    glScalef(-3.0, -0.8, -0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    //Meja Reception(Kanan)
    glPushMatrix();
    glTranslatef(-0.66, -0.5, -2.3);
    glColor3f(0, 0, 0);
    glScalef(3.0, -0.3, -0.3);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kerusi sandar (Kanan)
    glPushMatrix();
    glTranslatef(4.5, -0.8, 0.9);
    glColor3f(0, 128, 0);
    glScalef(5.8, -0.5, -0.1);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kerusi (Kanan)
    glPushMatrix();
    glTranslatef(4.5, -1.2, 0.5);
    glColor3f(255, 0, 0);
    glScalef(5.8, -0.2, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki kerusi 1 belakang (Kiri)
    glPushMatrix();
    glTranslatef(6.5, -1.4, 0.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.4, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi 1 depan (Kiri)
    glPushMatrix();
    glTranslatef(6.8, -1.3, 0.2);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi 2 belakang (Kanan)
    glPushMatrix();
    glTranslatef(2.5, -1.4, 0.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.4, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi 2 depan (Kanan)
    glPushMatrix();
    glTranslatef(2.1, -1.3, 0.2);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //-----------------------------------------------------------
     //Kerusi sandar (Kiri)
    glPushMatrix();
    glTranslatef(-6, -0.8, 0.9);
    glColor3f(0, 128, 0);
    glScalef(5.8, -0.5, -0.1);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kerusi (Kiri)
    glPushMatrix();
    glTranslatef(-6, -1.2, 0.5);
    glColor3f(255, 0, 0);
    glScalef(5.8, -0.2, 0.9);
    glutSolidCube(0.9);
    glPopMatrix();

    //Kaki kerusi 1 belakang (Kiri)
    glPushMatrix();
    glTranslatef(-8, -1.4, 0.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.4, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi 1 depan (Kiri)
    glPushMatrix();
    glTranslatef(-7.5, -1.3, 0.2);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi 2 belakang (Kanan)
    glPushMatrix();
    glTranslatef(-4, -1.4, 0.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.4, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki kerusi 2 depan (Kanan)
    glPushMatrix();
    glTranslatef(-4.5, -1.3, 0.2);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.1, 0.6, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();
}*/
void InteriorLobby(void) {
    //Kaki Meja reception
    glPushMatrix();
    glTranslatef(-0.25, -1.0, -2.3);
    glColor3f(128, 128, 0);
    glScalef(-3.0, -0.8, 0.6);
    glutSolidCube(1.0);
    glPopMatrix();

    //Meja Reception(Kanan)
    glPushMatrix();
    glTranslatef(-0.25, -0.55, -2.3);
    glColor3f(0, 0, 0);
    glScalef(3.5, -0.1, -0.9);
    glutSolidCube(0.9);
    glPopMatrix();




    //--------------kerusi sandar kiri--------------

     //depan sandar dinding
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -1.2, 0.99);
    glVertex3f(-7, -0.1, 0.99);
    glVertex3f(-4, -0.1, 0.99);
    glVertex3f(-4, -1.2, 0.99);
    glEnd();
    //blkg sandar
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -1.2, 0.9);
    glVertex3f(-7, -0.1, 0.9);
    glVertex3f(-4, -0.1, 0.9);
    glVertex3f(-4, -1.2, 0.9);
    glEnd();
    //penutup atas kerusi
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -0.1, 0.99);
    glVertex3f(-7, -0.1, 0.9);
    glVertex3f(-4, -0.1, 0.9);
    glVertex3f(-4, -0.1, 0.99);
    glEnd();
    //penutup kerusi atas
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -1.2, 0.99);
    glVertex3f(-7, -1.2, 0.3);
    glVertex3f(-4, -1.2, 0.3);
    glVertex3f(-4, -1.2, 0.99);
    glEnd();
    //bawah kerusi atas-2
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -1.3, 0.99);
    glVertex3f(-7, -1.3, 0.3);
    glVertex3f(-4, -1.3, 0.3);
    glVertex3f(-4, -1.3, 0.99);
    glEnd();
    //kiri kerusi 
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -1.3, 0.3);
    glVertex3f(-7, -1.2, 0.3);
    glVertex3f(-4, -1.2, 0.3);
    glVertex3f(-4, -1.3, 0.3);
    glEnd();
    //kiri kerusi 
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(-7, -1.3, 0.99);
    glVertex3f(-7, -1.2, 0.99);
    glVertex3f(-4, -1.2, 0.99);
    glVertex3f(-4, -1.3, 0.99);
    glEnd();

    //--------------kerusi sandar kanan--------------
 //depan sandar dinding
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -1.2, 0.99);
    glVertex3f(3, -0.1, 0.99);
    glVertex3f(6, -0.1, 0.99);
    glVertex3f(6, -1.2, 0.99);
    glEnd();
    //blkg sandar
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -1.2, 0.9);
    glVertex3f(3, -0.1, 0.9);
    glVertex3f(6, -0.1, 0.9);
    glVertex3f(6, -1.2, 0.9);
    glEnd();
    //top kerusi
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -0.1, 0.99);
    glVertex3f(3, -0.1, 0.9);
    glVertex3f(6, -0.1, 0.9);
    glVertex3f(6, -0.1, 0.99);
    glEnd();
    //bawah kerusi atas
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -1.2, 0.99);
    glVertex3f(3, -1.2, 0.3);
    glVertex3f(6, -1.2, 0.3);
    glVertex3f(6, -1.2, 0.99);
    glEnd();
    //bawah kerusi atas-2
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -1.3, 0.99);
    glVertex3f(3, -1.3, 0.3);
    glVertex3f(6, -1.3, 0.3);
    glVertex3f(6, -1.3, 0.99);
    glEnd();
    //kiri kerusi 
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -1.3, 0.3);
    glVertex3f(3, -1.2, 0.3);
    glVertex3f(6, -1.2, 0.3);
    glVertex3f(6, -1.3, 0.3);
    glEnd();
    //kiri kerusi 
    glBegin(GL_POLYGON); glColor3f(1, 0, 0.1);
    glVertex3f(3, -1.3, 0.99);
    glVertex3f(3, -1.2, 0.99);
    glVertex3f(6, -1.2, 0.99);
    glVertex3f(6, -1.3, 0.99);
    glEnd();

    //whiteboard?
    glBegin(GL_POLYGON); glColor3f(1, 1, 1);
    glVertex3f(-2.8, 1.2, -3.99);
    glVertex3f(-2.8, -0.5, -3.99);
    glVertex3f(2, -0.5, -3.99);
    glVertex3f(2, 1.2, -3.99);
    glEnd();
    //blkg sandar
    glBegin(GL_POLYGON); glColor3f(1, 1, 1);
    glVertex3f(-2.8, 1.2, -3.8);
    glVertex3f(-2.8, -0.5, -3.8);
    glVertex3f(2, -0.5, -3.8);
    glVertex3f(2, 1.2, -3.8);
    glEnd();
    //top 
    glBegin(GL_POLYGON); glColor3f(1, 1, 1);
    glVertex3f(-2.8, 1.2, -3.99);
    glVertex3f(-2.8, 1.2, -3.8);
    glVertex3f(2, 1.2, -3.8);
    glVertex3f(2, 1.2, -3.99);
    glEnd();
    //bawah 
    glBegin(GL_POLYGON); glColor3f(1, 1, 1);
    glVertex3f(-2.8, -0.5, -3.99);
    glVertex3f(-2.8, -0.5, -3.8);
    glVertex3f(2, -0.5, -3.8);
    glVertex3f(2, -0.5, -3.99);
    glEnd();

}
//-------------------------------- BLOCK HUJUNG R ----------------------------------
void blockhujungR(void) {

    //----------------bumbung-----------------------
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0, 1.0f);    //                                                   
    glVertex3f(46, 20, -1.0f);    // depan (R)           
    glVertex3f(29, 20, 2.0f);    // depan (L)          
    glVertex3f(29, 20, 10.0f);    // belakang (L)
    glVertex3f(46, 20, 7.0f);    // belakang (R)
    glEnd();
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0, 1.0f);    //                                                   
    glVertex3f(46, 22, -1.0f);    // depan (R)           
    glVertex3f(29, 22, 2.0f);    // depan (L)          
    glVertex3f(29, 22, 10.0f);    // belakang (L)
    glVertex3f(46, 22, 7.0f);    // belakang (R)
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);    //                                                   
    glVertex3f(46, 20, -1.0f);    // depan (R)           
    glVertex3f(29, 20, 2.0f);    // depan (L)          
    glVertex3f(29, 22.0f, 2.0f);    // belakang (L)
    glVertex3f(46, 22, -1.0f);    // belakang (R)
    glEnd();

    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);    //                                                   
    glVertex3f(46, 20, 7.0f);    // depan (R)           
    glVertex3f(29, 20, 10.0f);    // depan (L)          
    glVertex3f(29, 22.0f, 10.0f);    // belakang (L)
    glVertex3f(46, 22, 7.0f);    // belakang (R)
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);    //                                                   
    glVertex3f(29, 20, 2.0f);    // depan (R)           
    glVertex3f(29, 20, 10.0f);    // depan (L)          
    glVertex3f(29, 22, 10.0f);    // belakang (L)
    glVertex3f(29, 22, 2.0f);    // belakang (R)
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);    //                                                   
    glVertex3f(46, 20, -1.0f);    // depan (R)           
    glVertex3f(46, 20, 7.0f);    // depan (L)          
    glVertex3f(46, 22, 7.0f);    // belakang (L)
    glVertex3f(46, 22, -1.0f);    // belakang (R)
    glEnd();
    //bangunan
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0, 0.0f);    //                                                   
    glVertex3f(45, -1.5f, -1.0f);    // depan (R)           
    glVertex3f(30, -1.5f, 2.0f);    // depan (L)          
    glVertex3f(30, -1.5f, 10.0f);    // belakang (L)
    glVertex3f(45, -1.5f, 7.0f);    // belakang (R)
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(45, -1.5f, -1.0f);    // depan (R)           
    glVertex3f(30, -1.5f, 2.0f);    // depan (L)          
    glVertex3f(30, 20.0f, 2.0f);    // belakang (L)
    glVertex3f(45, 20, -1.0f);    // belakang (R)
    glEnd();

    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);    //                                                   
    glVertex3f(45, -1.5f, 7.0f);    // depan (R)           
    glVertex3f(30, -1.5f, 10.0f);    // depan (L)          
    glVertex3f(30, 20.0f, 10.0f);    // belakang (L)
    glVertex3f(45, 20, 7.0f);    // belakang (R)
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);    //                                                   
    glVertex3f(30, -1.5f, 2.0f);    // depan (R)           
    glVertex3f(30, -1.5f, 10.0f);    // depan (L)          
    glVertex3f(30, 20.0f, 10.0f);    // belakang (L)
    glVertex3f(30, 20, 2.0f);    // belakang (R)
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);    //                                                   
    glVertex3f(45, -1.5f, -1.0f);    // depan (R)           
    glVertex3f(45, -1.5f, 7.0f);    // depan (L)          
    glVertex3f(45, 20.0f, 7.0f);    // belakang (L)
    glVertex3f(45, 20, -1.0f);    // belakang (R)
    glEnd();
    //cat
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0.0);    //                                                   
    glVertex3f(45, -1.5f, 7.01);    // depan (R)           
    glVertex3f(30, -1.5f, 10.01);    // depan (L)          
    glVertex3f(30, 1.5f, 10.01f);    // belakang (L)
    glVertex3f(45, 1.5, 7.01f);    // belakang (R)
    glEnd();



    //-------------tingkap
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);    //                                                   
    glVertex3f(42, 3, 7.6f);    // depan (R)           
    glVertex3f(32, 3, 9.7f);    // depan (L)          
    glVertex3f(32, 6, 9.7f);    // belakang (L)
    glVertex3f(42, 6, 7.6f);    // belakang (R)
    glEnd();

    //depan
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);    //                                                   
    glVertex3f(42, 9, 7.6f);    // depan (R)           
    glVertex3f(32, 9, 9.7f);    // depan (L)          
    glVertex3f(32, 12, 9.7f);    // belakang (L)
    glVertex3f(42, 12, 7.6f);    // belakang (R)
    glEnd();

    //depan
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);    //                                                   
    glVertex3f(42, 15, 7.6f);    // depan (R)           
    glVertex3f(32, 15, 9.7f);    // depan (L)          
    glVertex3f(32, 18, 9.7f);    // belakang (L)
    glVertex3f(42, 18, 7.6f);    // belakang (R)
    glEnd();

}

//-------------------------------- BENCH R ----------------------------------
void bench()
{


    //-------------------------- BENCH 1 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(35, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(36, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(35, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(36, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(35.5, -0.8, 11.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(35.5, -1.05, 11.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- BENCH 2 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(40, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(41, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(40, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(41, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(40.5, -0.8, 11.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(40.5, -1.05, 11.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- BENCH 3 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(25, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(26, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(25, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(26, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(25.5, -0.8, 5.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(25.5, -1.05, 5.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- BENCH 4 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(20, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(21, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(20, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(21, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(20.5, -0.8, 5.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(20.5, -1.05, 5.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- POKOK 1 -----------------------------
    //pokok
    glPushMatrix();
    glTranslatef(23, 1.7, 5.75);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokok
    glPushMatrix();
    glTranslatef(23, -0.6, 5.75);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //-------------------------- POKOK 2 -----------------------------
    //pokok
    glPushMatrix();
    glTranslatef(38, 1.7, 11.75);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokok
    glPushMatrix();
    glTranslatef(38, -0.6, 11.75);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
}

//-------------------------------- BENCH L ----------------------------------
void benchL()
{

    //-------------------------- BENCH 1 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(-35, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(-36, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(-35, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(-36, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(-35.5, -0.8, 11.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(-35.5, -1.05, 11.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- BENCH 2 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(-40, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(-41, -1.3, 12);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(-40, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(-41, -1.3, 11.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(-40.5, -0.8, 11.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(-40.5, -1.05, 11.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- BENCH 3 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(-25, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(-26, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(-25, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(-26, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(-25.5, -0.8, 5.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(-25.5, -1.05, 5.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- BENCH 4 -----------------------------
    //Kaki depan R
    glPushMatrix();
    glTranslatef(-20, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki depan L
    glPushMatrix();
    glTranslatef(-21, -1.3, 6);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang R
    glPushMatrix();
    glTranslatef(-20, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Kaki belakang L
    glPushMatrix();
    glTranslatef(-21, -1.3, 5.5);
    glColor3f(0.3, 0, 0.2);
    glScalef(0.2, 1, 0.2);
    glutSolidCube(0.5);
    glPopMatrix();

    //Sandar
    glPushMatrix();
    glTranslatef(-20.5, -0.8, 5.5);
    glColor3f(0.6, 0.3, 0.3);
    glScalef(4, 1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    //Tempat duduk
    glPushMatrix();
    glTranslatef(-20.5, -1.05, 5.75);
    glColor3f(0.5, 0.2, 0);
    glScalef(4, 0.1, 1.5);
    glutSolidCube(0.5);
    glPopMatrix();

    //-------------------------- POKOK 1 -----------------------------
    //pokok
    glPushMatrix();
    glTranslatef(-23, 1.7, 5.75);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokok
    glPushMatrix();
    glTranslatef(-23, -0.6, 5.75);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //-------------------------- POKOK 2 -----------------------------
    //pokok
    glPushMatrix();
    glTranslatef(-38, 1.7, 11.75);
    glColor3f(0, 0.6, 0.3);
    glScalef(1.5, 3, 1.5);
    glutSolidSphere(0.6, 10, 10);
    glPopMatrix();

    //batang pokok
    glPushMatrix();
    glTranslatef(-38, -0.6, 11.75);
    glColor3f(0.5, 0.3, 0.1);
    glScalef(0.5, 2, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
}
//-------------------------------- BLOCK HUJUNG L ----------------------------------
//----------papan parking------------------------------
void parkinglogo(void) {
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0.15, 0.0); glVertex3f(-5, 5, 53);
    glTexCoord2d(1.1, 0.0);  glVertex3f(4, 5, 53);
    glTexCoord2d(1.1, 1.0); glVertex3f(4, 3, 53);
    glTexCoord2d(0.15, 1.0); glVertex3f(-5, 3, 53);
    glEnd();

}

void logobus(void) {
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0.15, 0.0); glVertex3f(37, 6, 56);
    glTexCoord2d(1.1, 0.0);  glVertex3f(39, 6, 56);
    glTexCoord2d(1.1, 1.0); glVertex3f(39, 4, 56);
    glTexCoord2d(0.15, 1.0); glVertex3f(37, 4, 56);
    glEnd();

}
void blockhujungL() {
    //------------bumbung---------
       //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);    // 
    glVertex3f(-46, 20, -5);    // depan (R)
    glVertex3f(-29.0f, 20, -2.0);    // depan (L)
    glVertex3f(-29.0f, 20, 6.0f);    // belakang (L)
    glVertex3f(-46, 20, 3.0f);    // belakang (R)
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);    // 
    glVertex3f(-46, 20, -5);    // depan (R)
    glVertex3f(-29.0f, 20, -2.0);    // depan (L)
    glVertex3f(-29.0f, 22, -2.0f);    // belakang (L)
    glVertex3f(-46, 22, -5.0f);    // belakang (R)
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1, 1);    // 
    glVertex3f(-46, 20, 3);    // depan (R)
    glVertex3f(-29.0f, 20, 6);    // depan (L)
    glVertex3f(-29.0f, 22, 6);    // belakang (L)
    glVertex3f(-46, 22, 3);    // belakang (R)
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1, 1);    // 
    glVertex3f(-46, 20, 3);    // depan (R)
    glVertex3f(-46.0f, 20, -5);    // depan (L)
    glVertex3f(-46.0f, 22, -5);    // belakang (L)
    glVertex3f(-46, 22, 3);    // belakang (R)
    glEnd();
    //kanan 
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1, 1);    // 
    glVertex3f(-29, 20, -2);    // depan (R)
    glVertex3f(-29.0f, 20, 6);    // depan (L)
    glVertex3f(-29.0f, 22, 6);    // belakang (L)
    glVertex3f(-29, 22, -2);    // belakang (R)
    glEnd();


    //------------bangunan-------------
      //tapak
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0, 0.0f);    // 
    glVertex3f(-45, -1.5f, -5);    // depan (R)
    glVertex3f(-30.0f, -1.5f, -2.0);    // depan (L)
    glVertex3f(-30.0f, -1.5f, 6.0f);    // belakang (L)
    glVertex3f(-45, -1.5f, 3.0f);    // belakang (R)
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);
    glVertex3f(-45, -1.5f, -5);    // depan (R)
    glVertex3f(-30.0f, -1.5f, -2.0);    // depan (L)
    glVertex3f(-30.0f, 20, -2.0f);    // belakang (L)
    glVertex3f(-45, 20, -5.0f);    // belakang (R)
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);    // 
    glVertex3f(-45, -1.5f, 3);    // depan (R)
    glVertex3f(-30.0f, -1.5f, 6);    // depan (L)
    glVertex3f(-30.0f, 20, 6);    // belakang (L)
    glVertex3f(-45, 20, 3);    // belakang (R)
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);    // 
    glVertex3f(-45, -1.5f, 3);    // depan (R)
    glVertex3f(-45.0f, -1.5f, -5);    // depan (L)
    glVertex3f(-45.0f, 20, -5);    // belakang (L)
    glVertex3f(-45, 20, 3);    // belakang (R)
    glEnd();
    //kanan 
    glBegin(GL_POLYGON);
    glColor3f(1, 5, 0.7);    // 
    glVertex3f(-30, -1.5f, -2);    // depan (R)
    glVertex3f(-30.0f, -1.5f, 6);    // depan (L)
    glVertex3f(-30.0f, 20, 6);    // belakang (L)
    glVertex3f(-30, 20, -2);    // belakang (R)
    glEnd();
    //------------cat-------------------

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);    // 
    glVertex3f(-45, -1.5f, 3.01);    // depan (R)
    glVertex3f(-30.0f, -1.5f, 6.01);    // depan (L)
    glVertex3f(-30.0f, 1.5, 6.01);    // belakang (L)
    glVertex3f(-45, 1.5, 3.01);    // belakang (R)
    glEnd();
    //--------tingkap--------

     //depan
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);    // 
    glVertex3f(-44.5, 3, 3.01);    // depan (R)
    glVertex3f(-32.0f, 3, 6.01);    // depan (L)
    glVertex3f(-32.0f, 6, 6.01);    // belakang (L)
    glVertex3f(-44.5, 6, 3.01);    // belakang (R)
    glEnd();
    //t2
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);    // 
    glVertex3f(-44.5, 9, 3.01);    // depan (R)
    glVertex3f(-32.0f, 9, 6.01);    // depan (L)
    glVertex3f(-32.0f, 12, 6.01);    // belakang (L)
    glVertex3f(-44.5, 12, 3.01);    // belakang (R)
    glEnd();
    //t3
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 1);    // 
    glVertex3f(-44.5, 15, 3.01);    // depan (R)
    glVertex3f(-32.0f, 15, 6.01);    // depan (L)
    glVertex3f(-32.0f, 18, 6.01);    // belakang (L)
    glVertex3f(-44.5, 18, 3.01);    // belakang (R)
    glEnd();

}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0.0, 0.0, 18.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    // Isometric view
    //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    //glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

    // glTranslatef(rotate_x, 1.0, 0.0);
     //glTranslatef(rotate_y, 0.0, 1.0);
     //glRotatef(rotate_x, 1.0, 0.0, 0.0);
     //glRotatef(rotate_y, 0.0, 1.0, 0.0);
    camera();
    //enable();
 //   compound();
    glEnable(GL_TEXTURE_2D);

    logoftmk();
    parkinglogo();
    logobus();
    glDisable(GL_TEXTURE_2D);
    blockL();
    blockR();
    exteriordesign();
    lamp();
    transport();
    InteriorClassroomKiri();
    lobby();
    InteriorLobby();
    lobby2();
    jejantasL();
    jejantasR();
    bench();
    benchL();
    Kioskkiri();
    Kioskkanan();
    Picnictablekiri();
    Picnictablekanan();
    InteriorClassroomKanan();
    blocktengah();
    blockhujungR();
    blockhujungL();




    glutSwapBuffers();

    angle++;
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspectiv (angle of sight, width, height, , depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    //we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    texture[0] = LoadTexture("ftmk.bmp", 298, 169);

    texture[1] = LoadTexture("utem1.bmp", 303, 206);
    texture[2] = LoadTexture("bus.bmp", 272, 190);


    glutMainLoop();
    FreeTexture(texture[0]);
    FreeTexture(texture[1]);
    FreeTexture(texture[2]);

    /*FreeTexture(texture[3]);
    FreeTexture(texture[4]);
    FreeTexture(texture[5]);*/
    return 0;
}