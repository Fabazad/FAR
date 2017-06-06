#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 1000

/*
Fonction qui récupère la position sous forme de tableau à deux éléments, ce sont les coordonnées du robot.
*/
int* recup_pos () {
	int pos[2];
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
        fclose(fichier);
    }
    else // cas de fichier vide
    {
        printf("null"); // On renvoie null
    }
    return pos;
}

