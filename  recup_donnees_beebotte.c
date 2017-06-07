#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int sock;

void getData(char host[], int port, char file[], char recup[])
{
  /* Saisie des infos de connexion */
  
  
  /* Calcul de l'IP de l'hote */
  struct hostent *hostinfo;
  hostinfo = gethostbyname(host); 
  if (hostinfo) {
    struct in_addr  **pptr;
    pptr = (struct in_addr **)hostinfo->h_addr_list;
    printf("Adresse IP de l'hote : %s\n",inet_ntoa(**(pptr)));
  } 

/*  if (hostinfo) {
    struct in_addr  **pptr;
    pptr = (struct in_addr **)hostinfo->h_addr;
    printf("Adresse IP de l'hote : %s\n",inet_ntoa(**(pptr)));
  }*/

  /* if ( hostinfo = gethostbyname(host) )
    memcpy((void*)&sin.sin_addr,(void*)hostinfo->h_addr,hostinfo->h_length);
  else if( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
    Error("unknown host");
  */

  /* Creation de la socket */
  if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) <0 )
    printf("can't create socket");
 
  /* Configuration de la connexion */

  struct sockaddr_in sin;
 
  sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
  sin.sin_family = AF_INET;
  if ( (sin.sin_port = htons(port)) == 0)
    printf("unknown service");

  /* Tentative de connexion au serveur */
  if (connect(sock, (struct sockaddr*)&sin,sizeof(sin))<0)
    printf("can't connect");
  else printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));

  
    //Envoi de donnees au serveur
  char buffer[1024] = "GET ";
  strcat(buffer, file);
  strcat(buffer, " HTTP/1.0\r\n");
  strcat(buffer, "Host: ");
  strcat(buffer, host);
  strcat(buffer, "\r\n\r\n");
  printf("Requete : \n%s", buffer);

  // TO DO : test whether this suceeds or Erorr("write error on socket")
   send(sock, buffer, strlen(buffer), 0);
  
   


  /* Reception de donnees du serveur */
  char buffer2[1024];
  FILE *f = fopen(recup, "w");

    int res = recv(sock, buffer2, sizeof(buffer2)-1, 0);
    //printf(" res =%i \n", res);
    char * s;
    if(s = strstr(buffer2,"\r\n\r\n")){
       // memmove(s, s+strlen("\r\n\r\n"),1+strlen(s+strlen("\r\n\r\n")));
       fprintf(f,"%s",s+4 );
    }
    else if (res > 0) {
      buffer2[res] = '\0';
      printf("%s", buffer2);
      fprintf(f,"%s",buffer2 );
      fflush(stdout);
    }//if


  /* Fermeture de la socket client */
  fclose(f);
  close(sock);

}

void recup_pos_db(void)
{
	char *host="api.beebotte.com";
	int port = 80;
	char file[100] = "/v1/public/data/read/vberry/DBpartie0/msg?limit=2 ";
	char recup[10] = "dist.txt";

	getData(host, port, file, recup);

}

void recup_deb_partie(void)
{
	char *host="api.beebotte.com";
	int port = 80;
	char file[100] = "/v1/public/data/read/vberry/TESTVB_MONITORING/msg?limit=1 ";
	char recup[20] = "deb_partie.txt";

	getData(host, port, file, recup);

}

int main(void)
{

	recup_pos_db();
	recup_deb_partie();
	return 1;

}






