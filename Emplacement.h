//
// Emplacement.h
// Définit ce qu'est un emplacement
// et les fonctions permettent le déplacement et la récupération
// d'informations dans un tableau d'emplacement (plateau)
#ifndef __EMPLACEMENT_HEADERFILE__
#define __EMPLACEMENT_HEADERFILE__

// En-têtes nécessaire
#include "AwaleTypes.h"

// Structure d'un emplacement
// Contient juste les coordonnée sur un plateau
typedef struct structEmplacement
{
    int x;
    int y;
} Emplacement;

/**
 * Initialise un emplacement définit
 * @param int, Coordonnée en x
 * @param int, Coordonnée en y
 * @return Emplacement, l'emplacement à créer
 */
Emplacement emplacement_defaut(const int x, const int y);

/**
 * Donne l'emplacement suivant dans un plateau standard AWALE
 * @param Emplacement, L'emplacement actuel
 * @return Emplacement, L'emplacement suivant
 */
Emplacement emplacement_suivant(Emplacement emp_actuel);

/**
 * Donne l'emplacement précédent dans un plateau standard AWALE
 * @param Emplacement, L'emplacement actuel
 * @return Emplacement, L'emplacement précédent
 */
Emplacement emplacement_precedent(Emplacement emp_actuel);

/**
 * Donne la direction à suivre selon la coordonnée Y de 
 * l'emplacement donnée
 * @param Emplacement, l'emplacement actuel
 * @return int, La direction (-1 | 1)
 */
int direction(const Emplacement emp_actuel);

/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 ******************************************************************************/

/**
 * Fonction qui teste si deux emplacement sont les mêmes
 * @param Emplacement, l'enmplacement numéro 1
 * @param Emplacement, l'enmplacement numéro 2
 * @return BOOL
 */
BOOL emplacement_sont_les_memes(const Emplacement emp1, const Emplacement emp2);

#endif