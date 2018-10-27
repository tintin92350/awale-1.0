//
// Plateau.c
// Définit les fonctions relatives au plateau
#include "Plateau.h"

// Fichiers du jeu
#include "IOExtends.h"

/**
 * Fonction qui initialise un plateau
 * @param Plateau - 2Dimensions, La plateau à initialisé
 */
void plateau_defaut(int plateau[2][6])
{
    // Pour chaque élément du plateau
    // on initialise le nombre de graine à 4
    for(short unsigned int y = 0; y < 2; y++)
        for(short unsigned int x = 0; x < 6; x++)
            plateau[y][x] = 4;
}

/**
 * Fonction qui dessiner dans la console un plateau
 * @param Plateau - 2Dimensions, Le plateau à dessiner
 */
void afficher_plateau(int plateau[2][6])
{
    // Saute 3 lignes
    printf("\n\n\n");
    
    // Affiche les cases du joueur 1
    affichage_centre("[a] [b] [c] [d] [e] [f]");

    // Les differents cases du joueur (avec séprations verticales)
    char joueur_1_cases[26];
    char joueur_2_cases[26];

    // Créer les chaines de caractère souhaités à l'aide
    // des informations contenue dans le plateau
    sprintf(joueur_1_cases, "| %d | %d | %d | %d | %d | %d |", plateau[0][0], plateau[0][1], plateau[0][2], plateau[0][3], plateau[0][4], plateau[0][5]);
    sprintf(joueur_2_cases, "| %d | %d | %d | %d | %d | %d |", plateau[1][0], plateau[1][1], plateau[1][2], plateau[1][3], plateau[1][4], plateau[1][5]);

    // Séparation
    affichage_centre("-------------------------");

    // On l'affiche
    affichage_centre(joueur_1_cases);

    // On affiche la séparation horizontal
    affichage_centre("-------------------------");

    // On l'affiche
    affichage_centre(joueur_2_cases);

    // On affiche la séparation horizontal
    affichage_centre("-------------------------");

    // Affiche les cases du joueur 2
    affichage_centre("[A] [B] [C] [D] [E] [F]");

    // Saute 3 lignes
    printf("\n\n\n");
}

/**
 * Fonction qui renvoie le nombre de graine dans une case (valide)
 * @param Plateau - 2Dimensions, Le plateau où récupèrer les informations
 * @param Emplacement, Emplacement où chercher
 * @return int, Le nombre de graine (-1 si l'emplacement est non-valide)
 */
int recupere_nombre_graine(int plateau[2][6], Emplacement emp)
{
    // Deja on teste si l'emplacement n'est pas valide
    // (pas de dépassement de mémoire)
    // si c'est la cas on renvoi un code d'erreur
    if(!emplacement_est_valide(emp))
        return -1;

    // L'emplacement est valide
    // on renvoi donc la valeur de l'emplacement
    return plateau[emp.y][emp.x];
}

/**
 * Fonction qui ajoute une graine à un emplacement
 * @param Plateau - 2Dimensions, Le plateau où insérer les informations
 * @param Emplacement, Emplacement où insérer
 * @return BOOL, Renvoie faux si la fonction échoue sinon vraie
 */
BOOL ajouter_graine(int plateau[2][6], Emplacement emp, unsigned int n)
{
    // Deja on teste si l'emplacement n'est pas valide
    // (pas de dépassement de mémoire)
    // si c'est la cas on renvoi un code d'erreur
    if(!emplacement_est_valide(emp))
        return FALSE;

    // L'emplacement est valide
    // On ajoute alors une graine
    plateau[emp.y][emp.x]+=n;

    // Enfin on renvoi vrai
    return TRUE;
}

/**
 * Fonction qui enlève une graine à un emplacement
 * @param Plateau - 2Dimensions, Le plateau où insérer les informations
 * @param Emplacement, Emplacement où prendre
 * @return BOOL, Renvoie faux si la fonction échoue sinon vraie
 */
BOOL enlever_graine(int plateau[2][6], Emplacement emp, unsigned int n)
{
    // Deja on teste si l'emplacement n'est pas valide
    // (pas de dépassement de mémoire)
    // si c'est la cas on renvoi un code d'erreur
    if(!emplacement_est_valide(emp))
        return FALSE;
        
    // On test si enlever une graine est
    // possible c'est a dire > 0
    if(plateau[emp.y][emp.x] < n)
        return FALSE;

    // L'emplacement est valide
    // On enleve alors une graine
    plateau[emp.y][emp.x]-=n;
    
    // Enfin on renvoi vrai
    return TRUE;
}


/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 *******************************************************************************/

/**
 * Teste si un emplacement est valide
 * @param Emplacement, L'emplacement a tester
 * @return BOOL
 */
BOOL emplacement_est_valide(Emplacement emp)
{
    return (emp.x >= 0 && emp.x <= 5) && (emp.y >= 0 && emp.y <= 1);
}

/**
 * Teste si un emplacement est vide
 * @param Emplacement, L'emplacement a tester
 * @return BOOL
 */
BOOL emplacement_est_vide(int plateau[2][6], Emplacement emp)
{
    return emplacement_est_valide(emp) && (plateau[emp.y][emp.x] == 0);
}

/**
 * Teste si la ligne n est vide
 * @param Plateau - 2Dimensions, Plateau de jeu
 * @param unsigned int, Ligne en question
 * @return BOOL
 */
BOOL plateau_ligne_est_vide(int plateau[2][6], unsigned int ligne)
{
    return plateau[ligne][0] == 0 && plateau[ligne][1] == 0 && plateau[ligne][2] == 0 && plateau[ligne][3] == 0 && plateau[ligne][4] == 0 && plateau[ligne][5] == 0;
}