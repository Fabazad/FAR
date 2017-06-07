=======================================================================
| Module de réception des positions envoyées par le Serveur de Position |
| Auteurs : Clément ROIG & Hugo LECLER                                  |
=======================================================================

Pour faire fonctionner le serveur :
- ajoute simplement la ligne #include "serveurRobotPosition.c" à votre programme
- compiler le .c
- lancer la fonction lancerServeurPosition() dans un processus parallèle à votre programme principal
	=> car ce programme est bloquant (vous êtes un serveur, vous attendez qu'un client vous écrive).

A tout moment, vous pouvez lire les dernières coordonnées reçues dans xSP, ySP et diversSP.