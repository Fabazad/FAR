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

void deplacementDis(int xCible, int yCible){
	int x = 0;
	int y = 0;
	int xdist = xCible - x;
	int ydist = yCible - y;
	int xdist_enc = TAILLE_CASE*xdist*11/12;
	int ydist_enc = TAILLE_CASE*ydist*11/12;
	
    
    avancer(ydist_enc);

    /*while(enc_left < 10 ){ //tourner
    	enc_left = enc_read(0) - enc_init_left;
    	left();
    	printf("left : %i\n",enc_left);
    }*/
    left();
    pi_sleep(333);	
    stop();
    
    avancer(xdist_enc);	
}


int main(void)
{
	//deplacementDis(7,7);
	 if(init()==-1)
        exit(1);
    led_on(1);

    pi_sleep(4000);
    int enc = 0;
    int enc_init = enc_read(0);
    right();
    while(enc < 15){
        enc = enc_read(0) - enc_init;
    }
    stop();
    //deplacementDis(3,3);

	return 0;
}