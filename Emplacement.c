//
// Emplacement.c
// Définit les fonctions relatives aux emplacements
#include "Emplacement.h"

/**
 * Initialise un emplacement définit
 * @param int, Coordonnée en x
 * @param int, Coordonnée en y
 * @return Emplacement, l'emplacement à créer
 */
Emplacement emplacement_defaut(int x, int y)
{
    return (Emplacement) {x, y};
}

/**
 * Donne l'emplacement suivant dans un plateau standard AWALE
 * @param Emplacement, L'emplacement actuel
 * @return Emplacement, L'emplacement suivant
 */
Emplacement emplacement_suivant(Emplacement emp_actuel)
{
    // Ajoute ou diminue la coordonnée en X de l'emplacement actuelle
    // possibilité d'un dépassement prévut pour (c'est à dire x < 0 et x > 5)
    emp_actuel.x += direction(emp_actuel);

    // Si on dépasse du plateau par la gauche
    // Alors on passe au joueur suivant
    // et on remet à 0 la coordoonée x
    if(emp_actuel.x < 0)
    {
        emp_actuel.y = 1;
        emp_actuel.x = 0;
    }
    // Sinon si on dépasse du plateau par la droite
    // Alors on passe au joueur suivant
    // et on remet à 5 la coordonnée x
    else if(emp_actuel.x > 5)
    {
        emp_actuel.y = 0;
        emp_actuel.x = 5;
    }

    // Retourne le nouvel emplacement
    return emp_actuel;
}

/**
 * Donne l'emplacement précédent dans un plateau standard AWALE
 * @param Emplacement, L'emplacement actuel
 * @return Emplacement, L'emplacement précédent
 */
Emplacement emplacement_precedent(Emplacement emp_actuel)
{
    // Ajoute ou diminue la coordonnée en X de l'emplacement actuelle
    // possibilité d'un dépassement prévut pour (c'est à dire x < 0 et x > 5)
    emp_actuel.x += -1 * direction(emp_actuel);

    // Si on dépasse du plateau par la gauche
    // Alors on passe au joueur suivant
    // et on remet à 0 la coordoonée x
    if(emp_actuel.x < 0)
    {
        emp_actuel.y = 0;
        emp_actuel.x = 0;
    }
    // Sinon si on dépasse du plateau par la droite
    // Alors on passe au joueur suivant
    // et on remet à 5 la coordonnée x
    else if(emp_actuel.x > 5)
    {
        emp_actuel.y = 1;
        emp_actuel.x = 5;
    }

    // Retourne le nouvel emplacement
    return emp_actuel;

}

/**
 * Donne la direction à suivre selon la coordonnée Y de 
 * l'emplacement donnée
 * @param Emplacement, l'emplacement actuel
 * @return int, La direction (-1 | 1)
 */
int direction(Emplacement emp_actuel)
{
    return emp_actuel.y == 0 ? -1 : 1;
}

/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 ******************************************************************************/

/**
 * Fonction qui teste si deux emplacement sont les mêmes
 * @param Emplacement, l'enmplacement numéro 1
 * @param Emplacement, l'enmplacement numéro 2
 * @return BOOL
 */
BOOL emplacement_sont_les_memes(Emplacement emp1, Emplacement emp2)
{
    return (emp1.x == emp2.x) && (emp1.y == emp2.y);
}