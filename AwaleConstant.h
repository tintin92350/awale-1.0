//
// AwaleConstant.h
// Définit tout les constantes utilisés par le jeu
#ifndef __AWALE_CONSTANT_HEADERFILE__
#define __AWALE_CONSTANT_HEADERFILE__

// Définit les joueurs (ID)
#define JOUEUR_1 0
#define JOUEUR_2 1
#define JOUEUR_IA JOUEUR_1

// Etat du jeu possibles
#define ETAT_JOUER_CVSC 1
#define ETAT_JOUER_CVSIA 2
#define ETAT_JOUER_PARTIEENR 3
#define ETAT_JOUER_LAN 4
#define ETAT_HALLOFFAME 5
#define ETAT_QUITTER 6

// Maximum constantes
#define STRING_MAX_CHAR 250

// Couleurs du terminale disponibles
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#endif