#include "gopigo.h"
#include <math.h>
#include <stdio.h>
#include "pos.c"
#define TAILLE_CASE 20

void avancer(dist){
	int enc_right = 0;

    int enc_init_right = enc_read(1);
    bwd();
    while(enc_right < dist){
    	enc_right = enc_read(1) - enc_init_right;
    	printf("right : %i\n",enc_right);
    }
    stop();
}

void turnRight(rot){
    int enc = 0;
    int enc_init = enc_read(0);
    int enc_rot = 15*rot/90;
    right();
    while(enc < enc_rot){
        enc = enc_read(0) - enc_init;
    }
    stop();
}

void turnLeft(rot){
    int enc = 0;
    int enc_init = enc_read(1);
    int enc_rot = 15*rot/90;
    left();
    while(enc < enc_rot){
        enc = enc_read(1) - enc_init;
    }
    stop();
}

void makeRot(rot, newRot){
    if(newRot - rot > 0){
        turnRight(newRot - rot);
    }
    else{
        turnLeft(rot - newRot);
    }
}

void deplacementDis(int xCible, int yCible){

    int* pos = recup_pos(); //on recupere la pos dans le ficher pos.txt
    int x = pos[0];
    int y = pos[1];
    int rot = pos[2];

	int xdist = xCible - x;
	int ydist = yCible - y;
	int xdist_enc = TAILLE_CASE*xdist*11/12;
	int ydist_enc = TAILLE_CASE*ydist*11/12;
	

    //verifier la rotation
    if(rot != 0 && rot != 90 && rot != 180 && rot != 270){
        if(ydist > 0){
            makeRot(rot, 0);
            rot = 0;
        }
        else if(ydist < 0){
            makeRot(rot, 0);
            rot = 180;
        }
        else if(xdist > 0){
            makeRot(rot, 0);
            rot = 90;
        }
        else{
            makeRot(rot, 0);
            rot = 270;
        }
    }

    //Se dépalcer
    if(fabs(ydist) == 1 && xdist != 0){ //Si il reste une case verticale
        if(rot == 0){
            avancer(TAILLE_CASE*11/12);
            if(xdist > 0){
                turnRight(90);
                rot = (rot+90)%360;
            }
            else if(xdist < 0){
                turnLeft(90);
                rot = (rot+270)%360;
            }
        }
        else if(rot == 180){
            avancer(TAILLE_CASE*11/12);
            if(xdist < 0){
                turnRight(90);
                rot = (rot+90)%360;
            }
            else if(xdist > 0){
                turnLeft(90);
                rot = (rot+270)%360;
            }
        }
        ecrire_pos(x,0,rot,0);
        return 3;
    }
    else if(fabs(ydist) > 1){ //S'il reste plusieurs de case verticale
        if(rot == 0){
            avancer(TAILLE_CASE*11/12);
            ecrire_pos(x,y+1,70,0);
        }
        else if(rot == 180){
            avancer(TAILLE_CASE*11/12);
            ecrire_pos(x,y-1,70,0);
        }
        return 3;
    }
    else if(ydist == 0 && xdist != 0){ //S'il n'y a plus de case verticale mais il y a des cases horizontales
        if(rot == 90){
            avancer(TAILLE_CASE*11/12);
            ecrire_pos(x+1,y,70,0);
        }
        else if(rot == 270){
            avancer(TAILLE_CASE*11/12);
            ecrire_pos(x-1,y-1,70,0);
        }
        return 3;
    }
    else{
        return 4;
    }
}

void deplacementCage(int yCible){

    int* pos = recup_pos(); //on recupere la pos dans le ficher pos.txt
    int x = pos[0];
    int y = pos[1];
    int rot = pos[2];

    int xdist = xCible - x;
    int ydist = yCible - y;
    int xdist_enc = TAILLE_CASE*xdist*11/12;
    int ydist_enc = TAILLE_CASE*ydist*11/12;
    

    //verifier la rotation
    if(rot != 0 && rot != 180){
        if(ydist > 0){
            makeRot(rot, 0);
            rot = 0;
        }
        else if(ydist < 0){
            makeRot(rot, 0);
            rot = 180;
        }
    }

    //Se dépalcer
    if(fabs(ydist) > 0){ //S'il reste des cases verticales
        if(rot == 0){
            avancer(TAILLE_CASE*11/12);
            ecrire_pos(x,y+1,70,0);
        }
        else if(rot == 180){
            avancer(TAILLE_CASE*11/12);
            ecrire_pos(x,y-1,70,0);
        }
        return 5;
    }
    
    else{
        return 55;
    }
}