#include "gopigo.h"
#include <stdio.h>
#include <math.h>
#define TAILLE_CASE 24

void avancer(int dist){
	int enc_right = 0;
    int enc_init_right = enc_read(1);
    bwd();
    while(enc_right < dist){
    	enc_right = enc_read(1) - enc_init_right;
    }
    stop();
}

void turnRight(int rot){
    set_speed(80);
    int enc = 0;
    int enc_init = enc_read(0);
    int enc_rot = 8*rot/90;
    right_rot();
    while(enc < enc_rot){
        enc = enc_read(0) - enc_init;
    }
    stop();
    set_speed(250);
}

void turnLeft(int rot){
    set_speed(80);
    int enc = 0;
    int enc_init = enc_read(1);
    int enc_rot = 8*rot/90;
    left_rot();
    while(enc < enc_rot){
        enc = enc_read(1) - enc_init;
    }
    stop();
    set_speed(250);
}

int makeRot(int rot, int newRot){
    if(newRot - rot > 0){
        turnRight(newRot - rot);
    }
    else if(newRot - rot < 0){
        turnLeft(rot - newRot);
    }
    return newRot;
}

int deplacementDist(int xCible, int yCible){   

    int* pos = recup_pos(); //on recupere la pos dans le ficher pos.txt
    int x = pos[0];
    int y = pos[1];
    int rot = pos[2];

	int xdist = xCible - x;
	int ydist = yCible - y;
	int xdist_enc = TAILLE_CASE*xdist*11/12;
	int ydist_enc = TAILLE_CASE*ydist*11/12;

    //verifier la rotation
    if(ydist > 0){
        rot = makeRot(rot, 0);
        y++;
    }
    else if(ydist < 0){
        rot = makeRot(rot, 180);
        y--;
    }
    else{
        if(xdist > 0){
            rot = makeRot(rot, 90);
            x++;
        }
        else if(xdist < 0){
            rot = makeRot(rot, 270);
            x--;
        }
    }
     
    //Se dépalcer
    if(xdist == 0 && ydist == 0){
        return 4;
    }
    else{
        avancer(TAILLE_CASE*11/12);
        //printf("test : %d_%d_%d\n",x,y,rot); 
        ecrire_pos(x,y,rot,0);

        return 3;
    }
}

int deplacementCage(int yCible){

    int* pos = recup_pos(); //on recupere la pos dans le ficher pos.txt
    int x = pos[0];
    int y = pos[1];
    int rot = pos[2];

    int ydist = yCible - y;
    int ydist_enc = TAILLE_CASE*ydist*11/12;
    


    //verifier la rotation
    if(ydist > 0){
        rot = makeRot(rot, 0);
        y++;
    }
    else if(ydist < 0){
        rot = makeRot(rot, 180);
        y--;
    }
    
    //Se dépalcer
    if(ydist == 0){
        return 55;
    }
    else{
        avancer(TAILLE_CASE*11/12);
        ecrire_pos(x,y,rot,0);
        return 5;
    }
}