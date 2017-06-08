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
    fgets(chaine, TAILLE_MAX, fichier); 
	chaine[strlen(chaine)] = '\0';
	if(strlen(chaine) == 0)
	{
		return 0; //Cas de fichier vide
	}
	else
	{
		time_t times = time(NULL);
		int timeballon;
		char* idballon;
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
	printf("idball : %s\n", idBallon);
	time_t times = time(NULL);
	FILE* fichier = NULL;
    fichier = fopen("ballon.txt", "w+");
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    sprintf(chaine, "%s,%d",idBallon,times);
    fprintf(fichier, chaine);
    fclose(fichier);

    fichier = fopen("public/idball", "w+");
    char chaine2[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

    sprintf(chaine2, "%s", idBallon);
    fprintf(fichier, chaine2);
    fclose(fichier);
    
}


/*int main(int argc, char *argv[]){
	enleverBallon();
}*/