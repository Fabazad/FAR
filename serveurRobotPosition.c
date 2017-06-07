// Fichier serveurRobotPosition.c

// Sockets / HTTP / IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

// Erreurs
#include <errno.h>

// Base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---- VARIABLES ---- //

// Variables qui stockent en permanence les dernières données reçues.
int xSP = -1;
int ySP = -1;
char* diversSP;

/* !! TODO remplacer 'testVB' par le canal dans lequel publier (ex: partie12)
    (ici msg est la "ressource" que ce canal attend */
char* canal = "testVB";

    /* Par convention dans FAR on parle sur ressource "msg"
      sur laquelle on envoie une chaine contenant les couples clef:valeur separes par des virgules */
char* ressource = "msg";
char* ressource2 = "msg?limit=15&time-range=1hour";

    // !! TO DO : mettre ci-dessous le token du canal !!
    // canal partie0 : 1494793564147_KNl54g97mG89kQSZ
    // canal testVB : 1494771555601_5SGQdxJaJ8O1HBj4
char* clefCanal = "1494771555601_5SGQdxJaJ8O1HBj4";

int sock;
char[6] PORTRobotSP = 2048;


// ======= FONCTIONS  ======= //

int checkFinPartie() {
    return 0;
}

// =========================================== //

int lancerServeurPosition() {
    /* Socket et contexte d'adressage du serveur */
    struct sockaddr_in sin;
    int sock;
    socklen_t recsize = sizeof(sin);

    /* Socket et contexte d'adressage du client */
    struct sockaddr_in csin;
    int csock;
    socklen_t crecsize = sizeof(csin);

    /* Creation d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* Configuration */
    char port[6] = PORTRobotSP;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(strtoul(port,NULL,10));
    bind(sock,(struct sockaddr*)&sin, recsize);
    printf("\nconfig ok");

    /* Demarrage du listage (mode serveur) */
    listen(sock, 5);

    printf("\nServeur fonctionnel sur le port %s",port);

    while(1) {
    /* Attente d'une connexion client */
        csock = accept(sock, (struct sockaddr*)&csin, &crecsize);     
        printf("\nUn client se connecte avec la socket %d de %s:%d",
            csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

        // Récupération de la requete du client
        char requete[1024];
        int res;
        recv(csock,requete,sizeof(requete)-1,0);

        char* copy;
        copy = malloc(50*sizeof(char));
        strcpy(copy,requete);

        // Découpage du message reçu        
        xSP = atoi(strtok(copy,","));
        ySP = atoi(strtok(NULL,","));
        diversSP = strtok(NULL,",");    

        //Mon code

        ecrire_pos(xSP, int ySP, diversSP, 1)
        
        close(csock); 
    }
	return 0;
}
