#include "gopigo.h"
#include <math.h>
#include <stdio.h>
#define TAILLE_CASE 20
#define PI 3.14159265

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
	int x = 0;
	int y = 0;
    int rot = 0;
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
    if(ydist == 1 && xdist != 0){
        if(rot == 0){
            avancer(TAILLE_CASE*11/12);
            if(xdist > 0){
                turnRight(90);
                rot = (rot+90)%360;
            }
            else if(xdist < 0){
                rot = turnLeft(90);
                rot = (rot+270)%360;
            }
        }
        else if(rot == 180){
            avancer(TAILLE_CASE*11/12);
            if(xdist < 0){
                rot = turnRight(90);
                rot = (rot+90)%360;
            }
            else if(xdist > 0){
                rot = turnLeft(90);
                rot = (rot+270)%360;
            }
        }
        return 3;
    }
    else if(ydist > 1){
        if(rot == 0 || rot == 180){
            avancer(TAILLE_CASE*11/12);
        }
        return 3;
    }
    else if(ydist == 0 && xdist != 0){
        if(rot == 90 || rot == 270){
            avancer(TAILLE_CASE*11/12);
        }
        return 3;
    }
    else{
        return 4;
    }
}


int main(void)
{
	//deplacementDis(7,7);
	 if(init()==-1)
        exit(1);
    led_on(1);

    pi_sleep(4000);
    
    //deplacementDis(3,3);

	return 0;
}