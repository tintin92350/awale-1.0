//
// AwalePartie.h
// Définit la structure d'une partie (données)
#ifndef __AWALE_PARTIE_HEADERFILE__
#define __AWALE_PARTIE_HEADERFILE__

// En-têtes
#include "main.h"

// Fichiers du jeu
#include "AwaleConstant.h"
#include "Emplacement.h"

// Structure partie
typedef struct s_AwalePartie
{
    // Plateau de jeu
    int plateau[2][6];

    // Scores des joueurs
    unsigned int scores[2];

    // Joueur qui est en train de jouer
    unsigned int joueur;

    // l'Emplacement demandé
    Emplacement emplacement;
    // Dernier emplacement joué
    Emplacement dernier_emplacement;

    // Permier coup ?
    BOOL premier_coup;

    // Stock l'etat famine des joueurs
    BOOL famines[2];

    // Type de partie (etat...)
    FLAG type;

} AwalePartie;

/*******************************************************************************
 * FONCTIONS POUR LA PARTIE
 ******************************************************************************/

/**
 * Charger une partie sauvegardée
 * @return AwalePartie, la partie sauvegardée OU une nouvelle partie si inexistante
 */
AwalePartie charger_partie();

/**
 * Créer une nouvelle partie
 * @param unsigned int, Le type de partie
 * @return AwalePartie, renvoi la partie crée
 */
AwalePartie creer_partie(unsigned int type);

/**
 * Affiche le dernier coup joué par un joueur
 * @param AwalePartie, Partie en cours
 */
void afficher_dernier_coup_joue(AwalePartie partie);

/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 ******************************************************************************/

/**
 * Vérifie si le joueur n est en famine
 * @param AwalePartie, Partie en cours
 * @param unsigned int, Le joueur
 * @return BOOL
 */
BOOL joueur_est_en_famine(AwalePartie partie, unsigned int joueur);

#endif