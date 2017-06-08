=======================================================================
| Module de réception des positions envoyées par le Serveur de Position |
| Auteurs : Clément ROIG & Hugo LECLER                                  |
=======================================================================

Pour faire fonctionner le serveur :
- ajoute simplement la ligne #include "serveurRobotPosition.c" à votre programme
- lancer la fonction lancerServeurPosition() dans un processus parallèle à votre programme principal
	=> car ce programme est bloquant (vous êtes un serveur, vous attendez qu'un client vous écrive).

A tout moment, vous pouvez lire les dernières informations reçues dans xSP, ySP et diversSP (vous pourrez envoyer ce que vous voulez dans divers, un angle par exemple ou votre note en projet FAR :p).
