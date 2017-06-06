#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
#define PORT 80

int main(void) {

  int sock;

  char hostname[32] = "www.beebotte.com";
  struct sockaddr_in sin;
  struct hostent *hostinfo;

  /* Configuration de la connexion */
  sin.sin_port = htons(PORT);
  hostinfo = gethostbyname(hostname);

  sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
  sin.sin_family = AF_INET;


  /* Creation de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));


  while(1)
  {
      /* Creation de la requête */
      char request[256];
      int x = random()%200;
      int y = random()%200;
      sprintf   (request, "GET /dweet/for/Robot5?x=%d&y=%d HTTP/1.1\r\nHost:%s\r\n\r\n", x, y, hostname);
      printf("REQUETE : \n%s\n",request);
      printf("Valeur de x : %d\n",x);
      printf("Valeur de y : %d\n\n",y);
      /* Envoie du message au serveur */
      send(sock, request, strlen(request),0);
      
      sleep(1);
  }
  close(sock);
  return(EXIT_SUCCESS);


}//main