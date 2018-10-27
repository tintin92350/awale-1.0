//
// AwalePartie.c
// Définis les fonctions relatives à une partie
#include "AwalePartie.h"
#include "Plateau.h"
#include "IOExtends.h"

/**
 * Charger une partie sauvegardée
 * @return AwalePartie, la partie sauvegardée OU une nouvelle partie si inexistante
 */
AwalePartie charger_partie()
{
    AwalePartie awale;
    if(recuperer_partie("save", &awale))
        remove("save");
    return awale;
}
/**
 * Créer une nouvelle partie
 * @return AwalePartie, renvoi la partie crée
 */
AwalePartie creer_partie(unsigned int type)
{
    // Créer une structure temporaire
    AwalePartie partie;

    // Initialise le plateau à ses valeurs par défaut
    plateau_defaut(partie.plateau);

    // Le joueur 1 commence
    partie.joueur = JOUEUR_1;

    // Initialise les scores à 0
    partie.scores[0] = partie.scores[1] = 0;

    // Initialise le premier coup
    partie.premier_coup = TRUE;

    // Les joueurs ne sont pas en famine ! (pas encore...)
    partie.famines[0] = partie.famines[1] = FALSE;

    // Indique le type de partie
    partie.type = type;
    
    // Retourne la structure crée
    return partie;
}

/**
 * Affiche le dernier coup joué par un joueur
 * @param AwalePartie, Partie en cours
 */
void afficher_dernier_coup_joue(AwalePartie partie)
{
    // On quit si c'est le premier coup
    if(partie.premier_coup)
        return;

    // On convertit le numéro en caractere
    char emp_alpha = partie.dernier_emplacement.y == 0 ? partie.dernier_emplacement.x + 'a' : partie.dernier_emplacement.x + 'A';

    // Affiche sur la console
    printf("Le dernier coup à été joué par le joueur %d : %c\n", partie.dernier_emplacement.y + 1, emp_alpha);
}

/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 ******************************************************************************/

/**
 * Vérifie si le joueur n est en famine
 * @param AwalePartie, Partie en cours
 * @param unsigned int, Le joueur
 * @return BOOL
 */
BOOL joueur_est_en_famine(AwalePartie partie, unsigned int joueur)
{
    return partie.famines[joueur];
}