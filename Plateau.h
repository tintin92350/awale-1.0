//
// Plateau.h
// Définit toute les fonctions relatives
// au fonctionnement et à la description du plateau
#ifndef __PLATEAU_HEADERFILE__
#define __PLATEAU_HEADERFILE__

// En-têtes requis
#include "main.h"

// Fichiers du jeu
#include "AwaleTypes.h"
#include "Emplacement.h"

/**
 * Fonction qui initialise un plateau
 * @param Plateau - 2Dimensions, La plateau à initialisé
 */
void plateau_defaut(int plateau[2][6]);

/**
 * Fonction qui dessiner dans la console un plateau
 * @param Plateau - 2Dimensions, Le plateau à dessiner
 */
void afficher_plateau(int plateau[2][6]);

/**
 * Fonction qui renvoie le nombre de graine dans une case (valide)
 * @param Plateau - 2Dimensions, Le plateau où récupèrer les informations
 * @param Emplacement, Emplacement où chercher
 * @return int, Le nombre de graine (-1 si l'emplacement est non-valide)
 */
int recupere_nombre_graine(int plateau[2][6], Emplacement emp);

/**
 * Fonction qui ajoute une graine à un emplacement
 * @param Plateau - 2Dimensions, Le plateau où insérer les informations
 * @param Emplacement, Emplacement où insérer
 * @param unsigned int, Nombre de graine a ajouter
 * @return BOOL, Renvoie faux si la fonction échoue sinon vraie
 */
BOOL ajouter_graine(int plateau[2][6], Emplacement emp, unsigned int n);


/**
 * Fonction qui enlève une graine à un emplacement
 * @param Plateau - 2Dimensions, Le plateau où insérer les informations
 * @param Emplacement, Emplacement où prendre
 * @param unsigned int, Nombre de graine a enlever
 * @return BOOL, Renvoie faux si la fonction échoue sinon vraie
 */
BOOL enlever_graine(int plateau[2][6], Emplacement emp, unsigned int n);


/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 *******************************************************************************/

/**
 * Teste si un emplacement est valide
 * @param Emplacement, L'emplacement a tester
 * @return BOOL
 */
BOOL emplacement_est_valide(Emplacement emp);

/**
 * Teste si un emplacement est vide
 * @param Plateau - 2Dimensions, Plateau de jeu
 * @param Emplacement, L'emplacement a tester
 * @return BOOL
 */
BOOL emplacement_est_vide(int plateau[2][6], Emplacement emp);

/**
 * Teste si la ligne n est vide
 * @param Plateau - 2Dimensions, Plateau de jeu
 * @param unsigned int, Ligne en question
 * @return BOOL
 */
BOOL plateau_ligne_est_vide(int plateau[2][6], unsigned int ligne);

#endif