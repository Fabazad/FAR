#include "ballon.c"
#include "pos.c"
#include "deplacement.c"
#include "serveurRobotPosition.c"
#include "serveur_robot.c"
#include "beebotte.c"
#define X_TERRAIN 8
#define Y_TERRAIN 12


int envoyerInfoJoueur(){
	return 1;
}
int partieFinie(){
	return 0;
}
int * recupDist(){
	int posDist[2];
	posDist[0] = 5;
	posDist[1] = 5;
	return posDist;
}
int debPartie(){
	return 1;
}
int boutonDeclenche(){
	return 1;
}
int butValide(){
	return 1;
}

void reinitialiserDonnees(){
	ecrire_pos(1, 1, 0, 0);
	enleverBallon();
	//char* ballon = "47584d84e8d4e";
	//entrerBallon(ballon);
}

int main(int argc, char *argv[])
{	
	int status = system("cd monitoring/bin && ./monitoringServer.farm &");
	status = system("gcc joueur.c -o valBut && sudo ./valBut &");
	sendData();

	int pid = fork();
	if(pid != 0){

	    if(init()==-1)
	        exit(1);
	    led_on(1);
	    set_speed(250);

	    reinitialiserDonnees();

		int etat = 0;
		int *xCible;
		int *yCible;

		while(partieFinie() == 0){
			switch(etat){
				case 0: //Envoie des données joueur
				if(envoyerInfoJoueur() == 1){ // Envoie des info joueur sur dweet ou autre
					printf("Données envoyées !\n");
					etat = 1;
				}
				break;

				case 1: //Recupération des informations de parties
				if (!recupDist()){
					printf("En attente d'information de partie\n");
				}
				else{
					printf("Information récupérée !\n");
					xCible = recupDist()[0]; // Récupèration des coordonnées du distributeur
					yCible = recupDist()[1];
					etat = 2;
				}
				break;

				case 2: //En attente de début de partie
				if(debPartie() == 1){
					printf("Début de la partie\n");
					etat = 3;
				}
				else{
					printf("En attente de debut de partie\n");	
				}
				break;

				case 3: //Se déplacer jusqu'au distributeur
				printf("Se deplace vers le distributeur\n");
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
				printf("Attendre un ballon\n");
				if(ballonOK() == 1){
					etat = 5;
				}
				else if(nouvellePos() == 1){
					etat = 3;
				}
				else{
					pi_sleep(300);
				}
				break;

				case 5: // Se deplacer jusqu'aux cages
				printf("Se deplace vers les cages\n");
				etat = deplacementCage(Y_TERRAIN);
				if(ballonOK() == 0){
					enleverBallon();
					etat = 3;
				}
				break;

				case 55: // Attente aux cages
				printf("Attente aux cages\n");
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
				printf("Verification du but\n");
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
				printf("But validé\n");
				if(boutonDeclenche() == 1){
					reinitialiserDonnees();
					etat = 3;
				}
				break;
			}

		}
		return 0;
	}
	else{
		lancerServeurPosition();
	}
}

