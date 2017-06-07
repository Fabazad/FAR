#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define TAILLE_MAX 1000

/*
Fonction qui verifie si le robot possède un ballon en regardant dans le fichier ballon.txt
Renvoie un booléen (0 ou 1)
*/
int ballonOK () {
	FILE* fichier = NULL;
    fichier = fopen("ballon.txt", "r");
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    fseek(fichier,0, SEEK_END);
	int taillef = ftell(fichier);
	if(taillef == 0)
	{
		return 0; //Cas de fichier vide
	}
	else
	{
		time_t times = time(NULL);
		int timeballon;
		char* idballon;
		memset (chaine, 0, sizeof (chaine));
		fgets(chaine, TAILLE_MAX, fichier); 
		chaine[strlen(chaine)] = '\0';

    	char *tok = strtok(chaine, ",");
    	idballon = tok;
		tok = strtok(NULL, " ");
		timeballon = atoi(tok);
		if(timeballon + 120 < times)
		{
			return 0; // Si le ballon est périmé
		}
		else
		{
			return 1; // Ballon valide
		}
	}
}

void enleverBallon(){
	FILE* fichier = NULL;
    fichier = fopen("ballon.txt", "w+");
    fclose(fichier);
}

void entrerBallon(char* idBallon){
	time_t times = time(NULL);
	FILE* fichier = NULL;
    fichier = fopen("ballon.txt", "w+");
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    sprintf(chaine, "%s,%d",idBallon,times);
    fprintf(fichier, chaine);
    fclose(fichier);
}


/*int main(int argc, char *argv[]){
	enleverBallon();
}*/