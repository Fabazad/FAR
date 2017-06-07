#include <ballon.c>
#include <pos.c>
#include <beebotte.c>
#include <deplacement.c>
#include "serveurRobotPosition.c"
#include "serveur_robot.c"
#define X_TERRAIN 8
#define Y_TERRAIN 12


void envoyerInfoJoueur(){
	return 1;
}
int partieFinie(){
	return 0;
}
int* recupInfoPartie(){
	return 1;
}
int debPartie(){
	return 1;
}
int boutonDeclenche(){}
int butValide(){}

void reinitialiserDonnees(){
	ecrire_pos(1, 1, 0, 0);
	enleverBallon();
}

int main(int argc, char *argv[])
{	
	ecrire_pos(1, 1, 0, 0);
	enleverBallon();
	int etat = 0;
	while(partieFinie() == 0){

		int pid = fork();
		if(pid == 0){
			switch(etat){
				case 0: //Envoie des données joueur
					if(envoyerInfoJoueur() == 1){ // Envoie des info joueur sur dweet ou autre
						printf("Données envoyées !\n");
						etat = 1;
					}
					break;

				case 1: //Recupération des informations de parties
					if (recupInfoPartie() == NULL){
						printf("En attente d'information de partie\n");
					}
					else{
						int xCible = recupInfoPartie().distributeur[1].x; // Récupèration des coordonnées du distributeur
						int yCible = recupInfoPartie().distributeur[1].y;
						etat = 2;
					}
					break;

				case 2: //En attente de début de partie
					if(debPartie() == 1){
						etat = 3;
					}
					else{
						printf("En attente de debut de partie\n");	
					}
					break;

				case 3: //Se déplacer jusqu'au distributeur
					etat = deplacementDist(xCible,yCible);
					if(etat == 4){
						int pid = fork();
						if(pid != 0){
							char* idBallon = server();
							entrerBallon(idBallon);
						}
					}
					break;

				case 4: // Attendre de recevoir un ballon

					if(ballonOK() == 1){
						etat = 5;
					}
					else if(nouvellePos() == 1){
						etat = 3;
					}
					break;

				case 5: // Se deplacer jusqu'aux cages
					etat = deplacementCage(Y_TERRAIN);
					if(ballonOK() == 0){
						enleverBallon();
						etat = 3;
					}
					break;

				case 55: // Attente aux cages
					if(ballonOK() == 0){
						enleverBallon();
						etat = 3;
					}
					else if(boutonDeclenche() == 1){
						etat = 6;
					}
					else if(nouvellePos() == 1){
						etat = 5;
					}
					break;
				
				case 6: //Bouton declenché, Verification du but
					if(butValide() == 1){
						etat = 7;
					}
					else
					{
						enleverBallon();
						etat = 3;
					}
					break;

				case 7: //But validé ! Retour au depart
					if(boutonDeclenche() == 1){
						reinitialiserDonnees();
						etat = 3;
					}
					break;
			}
		}
		else{
			lancerServeurPosition();
		}

	}
}

