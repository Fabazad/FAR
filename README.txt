=======================================================================
| Module de réception des positions envoyées par le Serveur de Position |
| Auteurs : Clément ROIG & Hugo LECLER                                  |
=======================================================================

Pour faire fonctionner le serveur :
- ajoute simplement la ligne #include "serveurRobotPosition.c" à votre programme
- lancer la fonction lancerServeurPosition() dans un processus parallèle à votre programme principal

A tout moment, vous pouvez lire les dernières coordonnées reçues dans xSP, ySP et diversSP.
