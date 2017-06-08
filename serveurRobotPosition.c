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

int sock;
char PORTRobotSP[6] = "2048";

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
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(strtoul(PORTRobotSP,NULL,10));
    bind(sock,(struct sockaddr*)&sin, recsize);
    printf("\nConfig du serveur de position ok");

    /* Demarrage du listage (mode serveur) */
    listen(sock, 5);

    printf("\nServeur fonctionnel sur le port %s",PORTRobotSP);

    while(1) {
    /* Attente d'une connexion client */
        csock = accept(sock, (struct sockaddr*)&csin, &crecsize);     
        printf("\nUn client se connecte avec la socket %d de %s:%d",
            csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

        // Récupération de la requete du client
        char* requete = malloc(1024*sizeof(char));
        int res;
        recv(csock,requete,1024,0);

        printf("\nJe reçois la requete : %s",requete);

        // Découpage du message reçu        
        xSP = atoi(strtok(requete,","));
        ySP = atoi(strtok(NULL,","));
        diversSP = strtok(NULL,",");

        close(csock); 
    }
    return 0;
}