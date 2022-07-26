
//please zoom out first after you run the coding. Press o for zoom out
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
void Position(void) {
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
void camera(void) {
    glRotatef(xrot, 1.0, 0.0, 0.0); //rotate our camera on teh x - axis(left andright)
    glRotatef(yrot, 0.0, 1.0, 0.0); //rotate our camera on the y - axis(up an down)
    glRotatef(zrot, 0.0, 0.0, 1.0); //rotate our camera on the y - axis(up an down)
    glTranslated(-xpos, -ypos, -zpos); //translate the screento the position of ourcamera
    glTranslatef(rotate_x, 1.0, 0.0);
    

}
void init(void)
{
    glClearColor(0.6, 0.8, 1.0, 0.9);
    Position();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'k') { //move in x axis to the right( bkn rotate camera, die gerak dlm x axis)
        rotate_x -= 0.2;
    }
    if (key == 'h') { //move in x axis to the left
        rotate_x += 0.2;
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

//code for building etc

void kedai(void) {

    //Bottom- tapak dia
   
    glBegin(GL_POLYGON); 
    glColor3f(0.0f, 0.0, 0.0f);    // 
    glVertex3f(2.5f, -1.5f, 1.0f);    // depan (R)
    glVertex3f(-1.0f, -1.5f, 1.0f);    // depan (L)
    glVertex3f(-1.0f, -1.5f, -1.0f);    // belakang (L)
    glVertex3f(2.5f, -1.5f, -1.0f);    // belakang (R)
    glEnd();  

    //Back
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0); 
    glVertex3f(-1.0f, -1.5f, -1.0f); //bawah (L)
    glVertex3f(2.5f, -1.5f, -1.0f); //bawah (R)
    glVertex3f(2.5f, 1.5f, -1.0f); //atas (R)
    glVertex3f(-1.0f, 1.5f, -1.0f); //bawah (L)
    glEnd();

    //pintu lobby tampalan
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0, 0);
    glVertex3f(-0.2f, -1.5f, 1.0f);
    glVertex3f(-0.2f, 1.0f, 1.0f);
    glVertex3f(1.5f, 1.0f, 1.0f);//-pintudepan bawah (R)
    glVertex3f(1.5f, -1.5f, 1.0f);    // depan bawah (R)
    glEnd();

  
    //Front
    //part1-kiri pintu
    glBegin(GL_POLYGON);                                       //_____________
    glColor3f(1.0f, 0.0f, 0.0f);    // Color Red                |             |
    glVertex3f(-1.0f, -1.5f, 1.0f);    // bawah (L)             |             |
    glVertex3f(-0.2f, -1.5f, 1.0f);//-pintudepan bawah (R)      |    _____    |
    glVertex3f(-0.2f, 1.5f, 1.0f);//-pintudepan atas (R)        |    |   |    |
    glVertex3f(-1.0f, 1.5f, 1.0f);    //  atas (L)              |____|___|____|
    glEnd();

    //part2-atas pintu
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 1.5f, 1.0f);//-pintudepan atas (R)       
    glVertex3f(-0.2f, 1.0f, 1.0f);//-pintu dpn bawah (R)
    glVertex3f(1.5f, 1.0f, 1.0f);//-pintu dpn bawah (L)
    glVertex3f(1.5f, 1.5f, 1.0f);//-pintu dpn bawah (R)
    glEnd();

    //part3-kanan pintu
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.5f, -1.5f, 1.0f);//-pintudepan bawah (R)
    glVertex3f(2.5f, -1.5f, 1.0f);    // depan bawah (R)
    glVertex3f(2.5f, 1.5f, 1.0f);    //  atas (R)
    glVertex3f(1.5f, 1.5f, 1.0f);    //  atas (L)
    glEnd();

    //Left
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-1.0, -1.5, 1.0); //depan bawah
    glVertex3f(-1.0, 1.5, 1);//dpn atas
    glVertex3f(-1.0, 1.5, -1);//blkg atas
    glVertex3f(-1.0, -1.5, -1);//blkg bawah
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);    // Color Violet
    glVertex3f(2.5f, 1.5f, 1.0f);    // atas  dpn
    glVertex3f(2.5f, -1.5f, 1.0f);    // bawah dpn
    glVertex3f(2.5f, -1.5f, -1.0f);    // bawah belakang
    glVertex3f(2.5f, 1.5f, -1.0f);    // atas belakang
    glEnd();
    //line pintu -kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-0.1, 0.8, 1.01f);
    glVertex3f(-0.1, -1.5, 1.01);
    glVertex3f(0.6, -1.5, 1.01);
    glVertex3f(0.6, 0.8, 1.01);
    glEnd();
    //line pintu-kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(0.7, 0.8, 1.01);
    glVertex3f(0.7, -1.5, 1.01);
    glVertex3f(1.4, -1.5, 1.01);
    glVertex3f(1.4, 0.8, 1.01);
    glEnd();
}
void logotandas(void) {
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //depan tandas 
    glBegin(GL_POLYGON);
    glColor3f(1, 1.0, 1); //putih
     glTexCoord2d(1.1, 0.0); glVertex3f(-2.5f,0, 1.0f); //bawah (L)
    glTexCoord2d(0.15, 0.0);  glVertex3f(-3.5, 0, 1.0f); //bawah (R)
       glTexCoord2d(0.2, 1.0); glVertex3f(-3.5, 1.0, 1.0f); //atas (R)
       glTexCoord2d(1.0, 1.0); glVertex3f(-2.5f, 1.0f, 1.0f); //bawah (L)
    glEnd();
}
void kiritandas(void) {
    //jalan tandas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1, 1);    // 
    glVertex3f(-1.0f, -1.5f, 1.0f);    // depan (R)
    glVertex3f(-2.0f, -1.5f, 1.0f);    // depan (L)
    glVertex3f(-2.0f, -1.5f, -1.0f);    // belakang (L)
    glVertex3f(-1.0f, -1.5f, -1.0f);    // belakang (R)
    glEnd();
    //Bottom- tapak tandas

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);    // Color Orange
    glVertex3f(-2.0f, -1.5f, 1.0f);    // depan (R)
    glVertex3f(-4.0f, -1.5f, 1.0f);    // depan (L)
    glVertex3f(-4.0f, -1.5f, -1.0f);    // belakang (L)
    glVertex3f(-2.0f, -1.5f, -1.0f);    // belakang (R)
    glEnd();
   
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1,0,0); //putih
    glVertex3f(-2.0f, -1.5f, -1.0f); //bawah (L)
    glVertex3f(-4.0, -1.5f, -1.0f); //bawah (R)
    glVertex3f(-4, 1.5f, -1.0f); //atas (R)
    glVertex3f(-2.0f, 1.5f, -1.0f); //bawah (L)
    glEnd();

    //Left
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(-4.0, -1.5, 1.0); //depan bawah
    glVertex3f(-4.0, 1.5, 1);//dpn atas
    glVertex3f(-4.0, 1.5, -1);//blkg atas
    glVertex3f(-4.0, -1.5, -1);//blkg bawah
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.0f, 0.0f);    
    glVertex3f(-2.0f, 1.5f, 1.0f);    // atas  dpn
    glVertex3f(-2.0f, -1.5f, 1.0f);    // bawah dpn
    glVertex3f(-2.0f, -1.5f, -1.0f);    // bawah belakang
    glVertex3f(-2.0f, 1.5f, -1.0f);    // atas belakang
    glEnd();

    //pintu tandas tepi bangunan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);    
    glVertex3f(-1.99f, 1.3f, 0.8f);    // atas  dpn
    glVertex3f(-1.99f, -1.5f, 0.8f);    // bawah dpn
    glVertex3f(-1.99f, -1.5f, 0.1f);    // bawah belakang
    glVertex3f(-1.99f, 1.3f, 0.1f);    // atas belakang
    glEnd();

    //pintu tandas tepi bangunan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);    
    glVertex3f(-1.99f, 1.3f, -0.8f);    // atas  dpn
    glVertex3f(-1.99f, -1.5f, -0.8f);    // bawah dpn
    glVertex3f(-1.99f, -1.5f, -0.1f);    // bawah belakang
    glVertex3f(-1.99f, 1.3f, -0.1f);    // atas belakang
    glEnd();

    //depan tandas 
    glBegin(GL_POLYGON);
    glColor3f(1,0,0); //putih
    glVertex3f(-2.0f, -1.5f, 1.0f); //bawah (L)
    glVertex3f(-4.0, -1.5f, 1.0f); //bawah (R)
    glVertex3f(-4, 1.5f, 1.0f); //atas (R)
    glVertex3f(-2.0f, 1.5f, 1.0f); //bawah (L)
    glEnd();
}
void tandaslogo(void) {
    //nk letak logo tandas kt gerbang antara kedai dgn tandas punye bgunan
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1); //putih
    glTexCoord2d(0.15, 0.0);  glVertex3f(-2.0, 1.0f, 1.01f); //bawah (R)
    glTexCoord2d(0.2, 1.0);   glVertex3f(-2, 1.5f, 1.01f);   
    glTexCoord2d(1.0, 1.0);  glVertex3f(-1.0f, 1.5f, 1.01f); //bawah (L)
    glTexCoord2d(1.1, 0.0);  glVertex3f(-1.0f, 1.0f, 1.01f); //bawah (L)
    glEnd();
}
void stesenB(void) {
   

    //back
    glBegin(GL_POLYGON);
    glColor3f(0.7,0,0);
    glVertex3f(1, -1.5, 2.5);//L-bawah
    glVertex3f(2, -1.5, 2.5);//R-bawh
    glVertex3f(2, 0, 2.5);//R-atas
    glVertex3f(1, 0, 2.5);//L-atas
    glEnd();

    //lubang kt blkg(mcm lcd )
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(1.8, -0.5, 2.49);//L-bawah
    glVertex3f(1.2, -0.5, 2.49);//R-bawh
    glVertex3f(1.2, -0.2, 2.49);//R-atas
    glVertex3f(1.8, -0.2, 2.49);//L-atas
    glEnd();

      //Left
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0,0);
    glVertex3f(2, -1.5, 3);//depanbawah
    glVertex3f(2, -1.5, 2.5);//bawah blkg
    glVertex3f(2, 0, 2.5);//atas blkg
    glVertex3f(2, 0, 3);
    glEnd();

    //Left
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(1, -1.5, 2.5);//blkg bawah
    glVertex3f(1, -1.5, 3);//depan bawah
    glVertex3f(1, 0, 3);//depan atas
    glVertex3f(1, 0, 2.5);
    glEnd();

    //front
    glBegin(GL_POLYGON);
    glColor3f(0.7,0,0);
    glVertex3f(2, -1.5, 3);//L-bawah
    glVertex3f(1, -1.5, 3);//R-bawh
    glVertex3f(1, 0, 3);//R-atas
    glVertex3f(2, 0, 3);//L-atas
    glEnd();

    //lubang kt depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(1.8, -0.5, 3.01);//L-bawah
    glVertex3f(1.2, -0.5, 3.01);//R-bawh
    glVertex3f(1.2, -0.2, 3.01);//R-atas
    glVertex3f(1.8, -0.2, 3.01);//L-atas
    glEnd();

    /*   //Isi minyak
       glBegin(GL_POLYGON);
       glColor3f(1, 1, 1);
       glVertex3f(-0.7, -0.95, 3.1);//R-atas
       glVertex3f(-0.8, -0.95, 3.1);//L-atas
       glVertex3f(-0.8, -1, 3.1);//L-bawah
       glVertex3f(-0.7, -1, 3.1);//R-bawh
       glEnd();*/


}
void stesen(void) {
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0,0);
    glVertex3f(-1, -1.5, 2.5);//belakang- L
    glVertex3f(2, -1.5, 2.5);//belakang-R
    glVertex3f(2, -1.5, 3);//depan-R
    glVertex3f(-1, -1.5, 3);//depan-L
    glEnd();

    //back
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(-1,-1.5 , 2.5);//L-bawah
    glVertex3f(0,-1.5,2.5);//R-bawh
    glVertex3f(0, 0, 2.5);//R-atas
    glVertex3f(-1, 0, 2.5);//L-atas
    glEnd();

    //lubang kt blkg(mcm lcd )
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-0.8, -0.5, 2.49);//L-bawah
    glVertex3f(-0.2, -0.5, 2.49);//R-bawh
    glVertex3f(-0.2, -0.2, 2.49);//R-atas
    glVertex3f(-0.8, -0.2, 2.49);//L-atas
    glEnd();


    //Left
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(-1,-1.5,3);//depanbawah
    glVertex3f(-1, -1.5, 2.5);//bawah blkg
    glVertex3f(-1, 0, 2.5);//atas blkg
    glVertex3f(-1,0,3);
    glEnd();

    //kanann
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(0,-1.5,2.5);//blkg bawah
    glVertex3f(0, -1.5, 3);//depan bawah
    glVertex3f(0, 0, 3);//depan atas
    glVertex3f(0, 0, 2.5);
    glEnd();

    //front
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.0, 0);
    glVertex3f(-1, -1.5, 3);//L-bawah
    glVertex3f(0, -1.5, 3);//R-bawh
    glVertex3f(0, 0, 3);//R-atas
    glVertex3f(-1, 0, 3);//L-atas
    glEnd();

    //lubang kt depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-0.8, -0.5, 3.01);//L-bawah
    glVertex3f(-0.2, -0.5, 3.01);//R-bawh
    glVertex3f(-0.2, -0.2, 3.01);//R-atas
    glVertex3f(-0.8, -0.2, 3.01);//L-atas
    glEnd();

}
void nozel(void) {
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0.17, 0.0); glVertex3f(-0.2, -1.45, 2.49);//L-bawah
    glTexCoord2d(0.99, 0.0); glVertex3f(-0.8, -1.45, 2.49);//R-bawh
    glTexCoord2d(0.99, 1.0); glVertex3f(-0.8, -0.7, 2.49);//R-atas
    glTexCoord2d(0.19, 1.0); glVertex3f(-0.2, -0.7, 2.49);//L-atas
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0.17, 0.0); glVertex3f(1.2, -1.45, 2.49);//L-bawah
    glTexCoord2d(0.99, 0.0); glVertex3f(1.8, -1.45, 2.49);//R-bawh
    glTexCoord2d(0.99, 1.0); glVertex3f(1.8, -0.7, 2.49);//R-atas
    glTexCoord2d(0.19, 1.0); glVertex3f(1.2, -0.7, 2.49);//L-atas
    glEnd();

    //depan kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0.17, 0.0); glVertex3f(-0.8, -1.45, 3.01);//L-bawah
    glTexCoord2d(0.99, 0.0); glVertex3f(-0.2, -1.45, 3.01);//R-bawh
    glTexCoord2d(0.99, 1.0); glVertex3f(-0.2, -0.7, 3.01);//R-atas
    glTexCoord2d(0.19, 1.0); glVertex3f(-0.8, -0.7, 3.01);//L-atas
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0.17, 0.0); glVertex3f(1.8, -1.45, 3.01);//L-bawah
    glTexCoord2d(0.99, 0.0); glVertex3f(1.2, -1.45, 3.01);//R-bawh
    glTexCoord2d(0.99, 1.0); glVertex3f(1.2, -0.7, 3.01);//R-atas
    glTexCoord2d(0.19, 1.0); glVertex3f(1.8, -0.7, 3.01);//L-atas
    glEnd();



}
void nozel2b(void) {
     glBindTexture(GL_TEXTURE_2D, texture[1]);
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2d(0.17, 0.0); glVertex3f(1.8, -1.45, 6.01);//L-bawah
    glTexCoord2d(0.99, 0.0); glVertex3f(1.2, -1.45, 6.01);//R-bawh
    glTexCoord2d(0.99, 1.0); glVertex3f(1.2, -0.7, 6.01);//R-atas
    glTexCoord2d(0.19, 1.0); glVertex3f(1.8, -0.7, 6.01);//L-atas
    glEnd();

  //nozel2
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2d(0.18, 0.0); glVertex3f(-0.8, -1.45, 6.01);//L-bawah
    glTexCoord2d(1.0, 0.0); glVertex3f(-0.2, -1.45, 6.01);//R-bawh
    glTexCoord2d(1.0, 1.0); glVertex3f(-0.2, -0.7, 6.01);//R-atas
    glTexCoord2d(0.2, 1.0); glVertex3f(-0.8, -0.7, 6.01);//L-atas
    glEnd();

    //nozel2
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2d(0.18, 0.0); glVertex3f(-0.8, -1.45, 5.49);//L-bawah
    glTexCoord2d(1.0, 0.0); glVertex3f(-0.2, -1.45, 5.49);//R-bawh
    glTexCoord2d(1.0, 1.0); glVertex3f(-0.2, -0.7, 5.49);//R-atas
    glTexCoord2d(0.2, 1.0); glVertex3f(-0.8, -0.7, 5.49);//L-atas
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2d(0.17, 0.0); glVertex3f(1.8, -1.45, 5.49);//L-bawah
    glTexCoord2d(0.99, 0.0); glVertex3f(1.2, -1.45, 5.49);//R-bawh
    glTexCoord2d(0.99, 1.0); glVertex3f(1.2, -0.7, 5.49);//R-atas
    glTexCoord2d(0.19, 1.0); glVertex3f(1.8, -0.7, 5.49);//L-atas
    glEnd();
}
void stesen2B(void) {

  
    //back
    glBegin(GL_POLYGON);
    glColor3f(0.7,0,0);
    glVertex3f(1, -1.5, 5.5);//L-bawah
    glVertex3f(2, -1.5, 5.5);//R-bawh
    glVertex3f(2, 0, 5.5);//R-atas
    glVertex3f(1, 0, 5.5);//L-atas
    glEnd();

    //lubang kt blkg(mcm lcd )
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(1.8, -0.5, 5.49);//L-bawah
    glVertex3f(1.2, -0.5, 5.49);//R-bawh
    glVertex3f(1.2, -0.2, 5.49);//R-atas
    glVertex3f(1.8, -0.2, 5.49);//L-atas
    glEnd();

      //Left
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(2, -1.5, 6);//depanbawah
    glVertex3f(2, -1.5, 5.5);//bawah blkg
    glVertex3f(2, 0, 5.5);//atas blkg
    glVertex3f(2, 0, 6);
    glEnd();

    //Left
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(1, -1.5, 5.5);//blkg bawah
    glVertex3f(1, -1.5, 6);//depan bawah
    glVertex3f(1, 0, 6);//depan atas
    glVertex3f(1, 0, 5.5);
    glEnd();

    //front
    glBegin(GL_POLYGON);
    glColor3f(0.7,0,0);
    glVertex3f(2, -1.5, 6);//L-bawah
    glVertex3f(1, -1.5, 6);//R-bawh
    glVertex3f(1, 0, 6);//R-atas
    glVertex3f(2, 0, 6);//L-atas
    glEnd();

    //lubang kt depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(1.8, -0.5, 6.01);//L-bawah
    glVertex3f(1.2, -0.5, 6.01);//R-bawh
    glVertex3f(1.2, -0.2, 6.01);//R-atas
    glVertex3f(1.8, -0.2, 6.01);//L-atas
    glEnd();

    /*   //Isi minyak
       glBegin(GL_POLYGON);
       glColor3f(1, 1, 1);
       glVertex3f(-0.7, -0.95, 3.1);//R-atas
       glVertex3f(-0.8, -0.95, 3.1);//L-atas
       glVertex3f(-0.8, -1, 3.1);//L-bawah
       glVertex3f(-0.7, -1, 3.1);//R-bawh
       glEnd();*/

}
void stesen2(void) {
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(0.8,0,0);
    glVertex3f(-1, -1.5, 5.5);//belakang- L
    glVertex3f(2, -1.5, 5.5);//belakang-R
    glVertex3f(2, -1.5, 6);//depan-R
    glVertex3f(-1, -1.5, 6);//depan-L
    glEnd();

    //back
    glBegin(GL_POLYGON);
    glColor3f(0.7,0,0);
    glVertex3f(-1, -1.5, 5.5);//L-bawah
    glVertex3f(0, -1.5, 5.5);//R-bawh
    glVertex3f(0, 0, 5.5);//R-atas
    glVertex3f(-1, 0, 5.5);//L-atas
    glEnd();

    //lubang kt blkg(mcm lcd )
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-0.8, -0.5, 5.49);//L-bawah
    glVertex3f(-0.2, -0.5, 5.49);//R-bawh
    glVertex3f(-0.2, -0.2, 5.49);//R-atas
    glVertex3f(-0.8, -0.2, 5.49);//L-atas
    glEnd();



    /*  //is minyak
      glBegin(GL_POLYGON);
      glColor3f(1, 1, 1);
      glVertex3f(-0.8, -0.95, 1.99);//L-bawah
      glVertex3f(-0.7, -0.95, 1.99);//R-bawh
      glVertex3f(-0.7, -1, 1.99);//R-atas
      glVertex3f(-0.8, -1, 1.99);//L-atas
      glEnd();*/

      //Left
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(-1, -1.5, 6);//depanbawah
    glVertex3f(-1, -1.5, 5.5);//bawah blkg
    glVertex3f(-1, 0, 5.5);//atas blkg
    glVertex3f(-1, 0, 6);
    glEnd();

//kanan
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(0, -1.5, 5.5);//blkg bawah
    glVertex3f(0, -1.5, 6);//depan bawah
    glVertex3f(0, 0, 6);//depan atas
    glVertex3f(0, 0, 5.5);
    glEnd();

    //front
    glBegin(GL_POLYGON);
    glColor3f(0.7,0,0);
    glVertex3f(-1, -1.5, 6);//L-bawah
    glVertex3f(0, -1.5, 6);//R-bawh
    glVertex3f(0, 0, 6);//R-atas
    glVertex3f(-1, 0, 6);//L-atas
    glEnd();

    //lubang kt depan
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-0.8, -0.5, 6.01);//L-bawah
    glVertex3f(-0.2, -0.5, 6.01);//R-bawh
    glVertex3f(-0.2, -0.2, 6.01);//R-atas
    glVertex3f(-0.8, -0.2, 6.01);//L-atas
    glEnd();

    /*   //Isi minyak
       glBegin(GL_POLYGON);
       glColor3f(1, 1, 1);
       glVertex3f(-0.7, -0.95, 3.1);//R-atas
       glVertex3f(-0.8, -0.95, 3.1);//L-atas
       glVertex3f(-0.8, -1, 3.1);//L-bawah
       glVertex3f(-0.7, -1, 3.1);//R-bawh
       glEnd();*/




}
void tiang(void) {
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    //tapak
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(6, -1.5, 8);
    glVertex3f(6.3, -1.5, 8);
    glVertex3f(6.3, -1.5, 8.5);
    glVertex3f(6, -1.5, 8.5);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 1,1);
    glTexCoord2d(0.15, 0.0); glVertex3f(6.3,-1.5,8.51);
    glTexCoord2d(1.1, 0.0); glVertex3f(6.3, -1.5, 7.99);
    glTexCoord2d(1.0, 1.0); glVertex3f(6.3, 0.7, 7.99);
    glTexCoord2d(0.0, 1.0); glVertex3f(6.3, 0.7, 8.51);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glTexCoord2d(0.15, 0.0); glVertex3f(6, -1.5, 8.51);
    glTexCoord2d(1.1, 0.0);  glVertex3f(6, -1.5, 7.99);
    glTexCoord2d(1.0, 1.0); glVertex3f(6, 0.7, 7.99);
    glTexCoord2d(0.0, 1.0); glVertex3f(6, 0.7, 8.51);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0,0);
    glVertex3f(6.3, -1.5, 8);
    glVertex3f(6, -1.5, 8);
    glVertex3f(6, 0.7, 8);
    glVertex3f(6.3, 0.7, 8);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0,0);
    glVertex3f(6.3, -1.5, 8.5);
    glVertex3f(6, -1.5, 8.5);
    glVertex3f(6, 0.7, 8.5);
    glVertex3f(6.3, 0.7, 8.5);
    glEnd();

}
void logotiang(void) {
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //atas kanan logo
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glTexCoord2d(0.15, 0.0); glVertex3f(6.3, 0.7, 8.5);
    glTexCoord2d(1.1, 0.0); glVertex3f(6.3, 0.7, 8);
    glTexCoord2d(1.0, 1.0); glVertex3f(6.3, 1.2, 8);
    glTexCoord2d(0.0, 1.0); glVertex3f(6.3, 1.2, 8.5);
    glEnd();
    //atas kiri logo
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glTexCoord2d(0.15, 0.0); glVertex3f(6, 0.7, 8.5);
    glTexCoord2d(1.1, 0.0); glVertex3f(6, 0.7, 8);
    glTexCoord2d(1.0, 1.0); glVertex3f(6, 1.2, 8);
    glTexCoord2d(0.0, 1.0); glVertex3f(6, 1.2, 8.5);
    glEnd();

    //belakang atas logo
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    glVertex3f(6.3, 0.7,8);
    glVertex3f(6, 0.7, 8);
    glVertex3f(6, 1.2, 8);
    glVertex3f(6.3, 1.2,8);
    glEnd();
    //depan atas logo
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    glVertex3f(6.3, 0.7, 8.5);
    glVertex3f(6, 0.7,8.5);
    glVertex3f(6, 1.2, 8.5);
    glVertex3f(6.3, 1.2, 8.5);
    glEnd();
}
void surau(void){

    //jalan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.0f);    // 
    glVertex3f(3.5f, -1.5f, 1.0f);    // depan (R)
    glVertex3f(2.5f, -1.5f, 1.0f);    // depan (L)
    glVertex3f(2.5f, -1.5f, -1.0f);    // belakang (L)
    glVertex3f(3.5f, -1.5f, -1.0f);    // belakang (R)
    glEnd();
    //tapak belah kanan
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);    // 
    glVertex3f(5.5f, -1.5f, 1.0f);    // depan (R)
    glVertex3f(3.5f, -1.5f, 1.0f);    // depan (L)
    glVertex3f(3.5f, -1.5f, -1.0f);    // belakang (L)
    glVertex3f(5.5f, -1.5f, -1.0f);    // belakang (R)
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1, 0.0, 0); //putih
    glVertex3f(3.5f, -1.5f, -1.0f); //bawah (L)
    glVertex3f(5.5, -1.5f, -1.0f); //bawah (R)
    glVertex3f(5.5, 1.5f, -1.0f); //atas (R)
    glVertex3f(3.5f, 1.5f, -1.0f); //bawah (L)
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1,0,0); //putih
    glVertex3f(3.5f, -1.5f, 1.0f); //bawah (L)
    glVertex3f(5.5, -1.5f, 1.0f); //bawah (R)
    glVertex3f(5.5, 1.5f, 1.0f); //atas (R)
    glVertex3f(3.5f, 1.5f, 1.0f); //bawah (L)
    glEnd();
    //Left
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(3.5, -1.5, 1.0); //depan bawah
    glVertex3f(3.5, 1.5, 1);//dpn atas
    glVertex3f(3.5, 1.5, -1);//blkg atas
    glVertex3f(3.5, -1.5, -1);//blkg bawah
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.0f, 0.0f);    //merah 
    glVertex3f(5.5f, 1.5f, 1.0f);    // atas  dpn
    glVertex3f(5.5f, -1.5f, 1.0f);    // bawah dpn
    glVertex3f(5.5f, -1.5f, -1.0f);    // bawah belakang
    glVertex3f(5.5f, 1.5f, -1.0f);    // atas belakang
    glEnd();


    //pintu tepi bangunan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);    // Color Violet
    glVertex3f(3.49f, 1.3f, -0.8f);    // atas  dpn
    glVertex3f(3.49f, -1.5f, -0.8f);    // bawah dpn
    glVertex3f(3.49f, -1.5f, -0.1f);    // bawah belakang
    glVertex3f(3.49f, 1.3f, -0.1f);    // atas belakang
    glEnd();

    //pintu tepi bangunan
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);    // Color Violet
    glVertex3f(3.49f, 1.3f, 0.8f);    // atas  dpn
    glVertex3f(3.49f, -1.5f, 0.8f);    // bawah dpn
    glVertex3f(3.49f, -1.5f, 0.1f);    // bawah belakang
    glVertex3f(3.49f, 1.3f, 0.1f);    // atas belakang
    glEnd();

}
void logosurau(void){
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1); //putih
    glTexCoord2d(0.15, 0.0);  glVertex3f(3.5, 1.0f, 1.0f); //bawah (R)
    glTexCoord2d(0.2, 1.0);   glVertex3f(3.5, 1.5f, 1.0f);
    glTexCoord2d(1.0, 1.0);  glVertex3f(2.5f, 1.5f, 1.0f); //bawah (L)
    glTexCoord2d(1.1, 0.0);  glVertex3f(2.5f, 1.0f, 1.0f); //bawah (L)
    glEnd();
}
void bumbung(void) {
    //tapak bawah
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(-5, 1.5, -1.5);
    glVertex3f(6.5, 1.5, -1.5);
    glVertex3f(6.5, 1.5, 5.5);
    glVertex3f(-5, 1.5, 5.5);
    glEnd();
    //tapak bawah
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3f(-5, 2, -1.5);
    glVertex3f(6.5, 2, -1.5);
    glVertex3f(6.5, 2, 5.5);
    glVertex3f(-5, 2, 5.5);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3f(-5, 1.5, -1.5);
    glVertex3f(-5, 2, -1.5);
    glVertex3f(-5, 2, 5.5);
    glVertex3f(-5, 1.5, 5.5);
    glEnd();
    
  
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3f(6.5, 1.5, -1.5);
    glVertex3f(6.5, 2, -1.5);
    glVertex3f(6.5, 2, 5.5);
    glVertex3f(6.5, 1.5, 5.5);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3f(-5, 1.5, -1.5);
    glVertex3f(6.5, 2, -1.5);
    glVertex3f(6.5, 2, -1.5);
    glVertex3f(-5, 1.5, -1.5);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3f(-5, 1.5, 5.5);
    glVertex3f(6.5, 2, 5.5);
    glVertex3f(6.5, 2, 5.5);
    glVertex3f(-5, 1.5, 5.5);
    glEnd();
}
void tiangbesar(void) {
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    glVertex3f(-5, -1.5, 5.5);
    glVertex3f(-4.5, -1.5, 5.5);
    glVertex3f(-4.5, -1.5, 5);
    glVertex3f(-5, -1.5, 5);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(-5, -1.5, 5.5);
    glVertex3f(-5, -1.5, 5);
    glVertex3f(-5, 1.5, 5);
    glVertex3f(-5, 1.5, 5.5);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(-4.5, -1.5, 5.5);
    glVertex3f(-4.5, -1.5, 5);
    glVertex3f(-4.5, 1.5, 5);
    glVertex3f(-4.5, 1.5, 5.5);
    glEnd();

    //depam
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    glVertex3f(-5, -1.5, 5.5);
    glVertex3f(-5, 1.5, 5.5);
    glVertex3f(-4.5, 1.5, 5.5);
    glVertex3f(-4.5, -1.5, 5.5);
    glEnd();
    //blkg
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    glVertex3f(-5, -1.5, 5);
    glVertex3f(-5, 1.5, 5);
    glVertex3f(-4.5, 1.5, 5);
    glVertex3f(-4.5, -1.5, 5);
    glEnd();

    //tiang lgi stu belah kanan
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex3f(6.5, -1.5, 5.5);
    glVertex3f(6, -1.5, 5.5);
    glVertex3f(6, -1.5, 5);
    glVertex3f(6.5, -1.5, 5);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(6.5, -1.5, 5.5);
    glVertex3f(6.5, -1.5, 5);
    glVertex3f(6.5, 1.5, 5);
    glVertex3f(6.5, 1.5, 5.5);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex3f(6, -1.5, 5.5);
    glVertex3f(6, -1.5, 5);
    glVertex3f(6, 1.5, 5);
    glVertex3f(6, 1.5, 5.5);
    glEnd();

    //depam
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex3f(6.5, -1.5, 5.5);
    glVertex3f(6.5, 1.5, 5.5);
    glVertex3f(6.5, 1.5, 5.5);
    glVertex3f(6.5, -1.5, 5.5);
    glEnd();
    //blkg
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    glVertex3f(6.5, -1.5, 5);
    glVertex3f(6.5, 1.5, 5);
    glVertex3f(6, 1.5, 5);
    glVertex3f(6, -1.5, 5);
    glEnd();



}
void tapak(void) {
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-6,-1.51,-1.5);
    glVertex3f(7, -1.51, -1.5);
    glVertex3f(7, -1.51, 7.5);
    glVertex3f(-6, -1.51, 7.5);
    glEnd();

}
void pagar(void) {
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
  /* glTexCoord2d(0.15, 0.0); */ glVertex3f(1.0, -1.5, 9.5);
    /*glTexCoord2d(1.1, 0.0);*/ glVertex3f(1.0, -1.5, 9.3);
    /*glTexCoord2d(1.0, 1.0);*/ glVertex3f(1.0, -1, 9.3);
    /*glTexCoord2d(0.0, 1.0);*/ glVertex3f(1.0, -1, 9.5);
    glEnd();
    //tutup atas
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0, 0);
    glVertex3f(0, -1, 9.5);
    glVertex3f(0, -1, 9.3);
    glVertex3f(1.5, -1, 9.3);
    glVertex3f(1.5, -1, 9.5);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1, 0,0);
    /*glTexCoord2d(0.15, 0.0); */glVertex3f(0, -1.5, 9.5);
    /*glTexCoord2d(1.1, 0.0);  */glVertex3f(0, -1.5, 9.3);
    /*glTexCoord2d(1.0, 1.0); */glVertex3f(0, -1, 9.3);
    /*glTexCoord2d(0.0, 1.0);*/ glVertex3f(0, -1, 9.5);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0, 0);
      glVertex3f(1.0, -1.5, 9.3);
     glVertex3f(0, -1.5, 9.3);
     glVertex3f(0, -1, 9.3);
    glVertex3f(1.0, -1, 9.3);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0, 0);
         glTexCoord2d(0.15, 0.0); glVertex3f(1.0, -1.5, 9.5);
    glTexCoord2d(0.15, 1.0); glVertex3f(0, -1.5, 9.5);
        glTexCoord2d(1.0, 1.0); glVertex3f(0, -1, 9.5);
        glTexCoord2d(1.1, 0.0);    glVertex3f(1.0, -1, 9.5);
    glEnd();
}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0.0, 0.0, 18.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    // glTranslatef(rotate_x, 1.0, 0.0);
     //glTranslatef(rotate_y, 0.0, 1.0);
     //glRotatef(rotate_x, 1.0, 0.0, 0.0);
     //glRotatef(rotate_y, 0.0, 1.0, 0.0);
    camera();
    //enable();
 //   compound();
  
    glEnable(GL_TEXTURE_2D);
    logotiang();
    nozel2b();
    nozel();
    tandaslogo();
    logosurau();
    logotandas();
    tiang();
    pagar();
    glDisable(GL_TEXTURE_2D);
    
    surau();
    tapak();
    kedai();
    stesen2();
    stesen2B();
    stesenB();
    stesen();
    bumbung();
    tiangbesar();
    kiritandas();
   
    glutSwapBuffers();
    angle++;
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspectiv (angle of sight, width, height, , depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}
int main(int argc, char** argv) {

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
    // glutSpecialFunc(specialKeys);
    texture[0] = LoadTexture("ptr.bmp", 256, 256);
    texture[1] = LoadTexture("nozel.bmp", 256, 256);
    texture[2] = LoadTexture("tandas.bmp", 272, 279);
    texture[3] = LoadTexture("surau.bmp", 256, 252);
    texture[4] = LoadTexture("bank.bmp", 256, 252);
    texture[5] = LoadTexture("wc.bmp", 256, 252);

    glutMainLoop();
    FreeTexture(texture[0]);
    FreeTexture(texture[1]);
    FreeTexture(texture[2]);
    FreeTexture(texture[3]);
    FreeTexture(texture[4]);
    FreeTexture(texture[5]);
    return 0;
}
