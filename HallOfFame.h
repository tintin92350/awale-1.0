//
// HallOfFame.h
// Définit toutes les fonctions relatives à l'option Hall Of Fame
#ifndef __HALLOFFAME_HEADERFILE__
#define __HALLOFFAME_HEADERFILE__

// Fichiers du jeu
#include "AwaleConstant.h"
#include "AwaleTypes.h"

// Hall_of_fame
// Définis une deux tableaux
// -> Le "nom" du joueur
// -> Le "score" du joueur
// Ces deux parametres sont lié !
typedef struct HallOfFame_t
{
    char noms[10][STRING_MAX_CHAR];
    unsigned int scores[10];
} HallOfFame;

/**
 * Créer une structure vide
 * @return HallOfFame
 */
HallOfFame hof_vide();

/**
 * Récupère dans une structure HallOfFames
 * les meilleurs scores depuis le fichier
 */
HallOfFame recuperer_les_meilleurs_scores();

/**
 * Fonction qui renvoie la position du score par rapport
 * aux autres de la liste sinon -1
 * @param HallOfFame, Liste des meilleurs scores
 * @param unsigned int, Score du joueur
 * @return int, Renvoi la position sinon -1
 */
int compare_score_halloffame(HallOfFame, unsigned int);

/**
 * Ajoute le score et nom du joueur à la position demandée, puis effectue
 * les changements nécessaires
 * @param HallOfFame*, La structure à modifier
 * @param unsigned int, La position
 * @param unsigned int, Le score
 * @param string, Le nom du joueur
 */
void ajouter_score_a_la_liste(HallOfFame *, unsigned int, unsigned int, string);

/**
 * Affiche le Hall Of Fame au centre !
 * @param HallOfFame
 */
void afficher_hof(HallOfFame);

/**
 * Met à jour le contenue du fichier du Hall Of Fame
 * @param HallOfFame, Les meilleurs scores
 * @return BOOL, La fonction a t-elle echoué ?
 */
BOOL maj_halloffame(HallOfFame);

#endif