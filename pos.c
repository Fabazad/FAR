#include "gopigo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 1000

/*
Fonction qui récupère la position sous forme de tableau à deux éléments, ce sont les coordonnées du robot.
*/
int* recup_pos () {
	int pos[4];
	FILE* fichier = NULL;
    fichier = fopen("pos.txt", "r");
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

    if (fichier != NULL) //cas de fichier non vide
    {
        // On récupère les coordonnées présentes dans le fichier
    	fgets(chaine, TAILLE_MAX, fichier); 
        chaine[strlen(chaine)] = '\0';
        printf(strcat(chaine,"\n"));
    	char *tok = strtok(chaine, ",");
    	pos[0] = atoi(tok);
		tok = strtok(NULL, " ");
		pos[1] = atoi(tok);
        tok = strtok(NULL, " ");
        pos[3] = atoi(tok);
        tok = strtok(NULL, " ");
        pos[4] = atoi(tok);
        fclose(fichier);
    }
    else // cas de fichier vide
    {
        printf("null"); // On renvoie null
    }
    return pos;
}

void ecrire_pos(int x, int y, int rot, int new) {
    FILE* fichier = NULL;
    fichier = fopen("pos.txt", "w+");
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    sprintf(chaine, "%d,%d,%d,%d",x,y,rot,new);
    fprintf(fichier, chaine);
    fclose(fichier);

    int possedeBallon = ballonOK();
    if(new){
        fichier = fopen("monitoring/dataPosition/verifiedPosition.txt", "w+");
        char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
        sprintf(chaine, "%d_%d_0",x,y,possedeBallon);
        fprintf(fichier, chaine);
        fclose(fichier);
    }
    else{
        fichier = fopen("monitoring/dataPosition/position.txt", "w+");
        char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
        sprintf(chaine, "%d_%d_0",x,y,possedeBallon);
        fprintf(fichier, chaine);
        fclose(fichier);
    }
}

int nouvellePos(){
    int* pos = recup_pos();
    return pos[3];
}


/*int main(int argc, char *argv[])
{
    //int* pos = recup_pos();
    //printf("%d,%d,%d,%d\n",pos[0],pos[1],pos[2],pos[3]);
    ecrire_pos(7,3,70,0);
}*/