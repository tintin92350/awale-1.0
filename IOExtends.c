//
// IOExtends.c
// Définit les fonctions d'entrée / sortie étendues
#include "IOExtends.h"

// Structure récuperant des informations sur la console
static struct winsize CONSOLE_SIZE;

/**
 * Initialise la structure d'information sur la console
 */
void initialise_informations_console()
{
    // Fonction permettant la récuperation
    // des informations sur la taille
    // de la console
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &CONSOLE_SIZE);
}

/**
 *  Donne la lergeur de la console
 * @return unsigned int, la largeur de la console
 */
unsigned int largeur_console()
{
    return CONSOLE_SIZE.ws_col;
}

/**
 * Affiche un text brut de facon centré sur la console
 * @param string, la chaine de caractère à afficher
 */
void affichage_centre(string str)
{
    // Récupère le nombre de caractere de la chaine
    unsigned int chaine_taille = strlen(str);
    // Récupère la taille de la console en largeur
    unsigned int console_largeur = largeur_console();

    // On vérifie que la taille de la chaine n'est
    // pas supérieur à la taille de la console
    if(chaine_taille > console_largeur)
        {
            printf("%s\n", str);
            return;
        }

    // On affiche des espaces
    // pour l'alignement    
    for(unsigned int space = 0;space < console_largeur / 2 - chaine_taille / 2; space++)
        printf(" ");

    // Enfin on affiche la chaine de caractères
    printf("%s\n", str);    
}

/**
 * Affiche 2 textes opposé (droite - gauche)
 * @param string, première chaine de caractère (gauche)
 * @param string, deuxième chaine de caractère (droite)
 */
void affichage_droite_gauche(string str1, string str2)
{
    // On vérifie si la taille additionné
    // des deux chaines ne dépasse pas
    // la longueur de la console
    // si c'est la cas on affiche les deux par saut de ligne (défautt)
    if(strlen(str1) + strlen(str2) > largeur_console())
        {
            printf("%s\n%s", str1, str2);
        }
    else
        {
            // On affiche la première chaine de caractère
            printf("%s", str1);

            // On récupère l'espace entre les deux
            unsigned int espace_max = largeur_console() - strlen(str2) - strlen(str1);

            // On affiche les espaces souhaités
            unsigned int espace;
            for(espace = 0; espace < espace_max; espace++)
            printf(" ");

            // On affiche le deuxième text
            printf("%s\n", str2);
        }
}

/**
 *  Affiche une bar de séparation
 */
void affiche_separation_horizontal()
{
    for(unsigned int i = 0;i<largeur_console(); i++)
        printf("-");
    printf("\n");    
}

/**
 * Efface la console
 */
void effacer_console()
{
    system("clear");
}


/**
 * Change le text de couleur
 * @param string, Couleur à mettre
 */
void changer_couleur_terminal(const string c)
{
    printf("%s", c);
}

/**
 * Réinitialisation de la couleur du terminal
 */
void reinitialiser_couleur_terminal()
{
    printf("\x1B[0m");
}

/**
 * Demande de certitude
 * @return BOOL
 */
BOOL demande_confirmation()
{
    printf("Voulez-vous vraiment faire cela ?\n");
    char confirmation[STRING_MAX_CHAR] = "";

    do {
        scanf("%s", confirmation);
    }
    while(strlen(confirmation) == 0 && confirmation[0] != 'o' && confirmation[0] != 'y');

    return confirmation[0] == 'o';
}

/*******************************************************************************
 * FONCTIONS SUR FICHIERS
 ******************************************************************************/

/**
 * Enregistre la partie dans un fichier
 * @param string, Nom du fichier
 * @param AwalePartie, Partie à enregistrer
 * @return BOOL, La fonction a t-elle bien enregistrer la partie
 */
BOOL enregistrer_partie(string name, AwalePartie * partie)
{
    // Create the file in binary mode
    FILE * fichier_partie = fopen(name, "wb");

    // On retourne faux si le fichier
    // n'est pas ouvert en ecriture
    if(!fichier_partie)
        return FALSE;

    // On écrit la partie
    // dans le fichier
    fwrite(partie, sizeof(AwalePartie), 1, fichier_partie);

    // Ferme le fichier
    fclose(fichier_partie);

    return TRUE;
}


/**
 * Récupère la partie à partie d'un fichier
 * @param string, Nom du fichier
 * @param AwalePartie, Partie à enregistrer
 * @return BOOL, La fonction a t-elle bien enregistrer la partie
 */
BOOL recuperer_partie(string name, AwalePartie * partie)
{
    // Create the file in binary mode
    FILE * fichier_partie = fopen(name, "rb");

    // On retourne faux si le fichier
    // n'est pas ouvert en ecriture
    if(!fichier_partie)
        return FALSE;

    // On écrit la partie
    // dans le fichier
    fread(partie, sizeof(AwalePartie), 1, fichier_partie);

    // Ferme le fichier
    fclose(fichier_partie);

    return TRUE;
}

/**
 * Enregistre le score dans le Hall of fame
 * @param string, Nom du fichier
 * @param unsigned int, Joueur
 * @param unsigned int, Score
 * @return BOOL
 */
BOOL enregistre_score(string name, unsigned int joueur, unsigned int score)
{
    // Create the file in binary mode
    FILE * fichier_score = fopen(name, "w");

    // On retourne faux si le fichier
    // n'est pas ouvert en ecriture
    if(!fichier_score)
        return FALSE;

    // Créer la chine
    char chaine[100];
    sprintf(chaine, "Le joueur %d à obtenue un score de %d graine !\n", joueur, score);

    // On écrit la partie
    // dans le fichier
    fputs(chaine, fichier_score);

    // Ferme le fichier
    fclose(fichier_score);

    return TRUE;
}

/**
 * Vérifie si un fichier existe
 * @param string, Nom du fichier
 * @return BOOL
 */
BOOL fichier_exist(string name)
{    
    // Ouvre le fichier
    FILE * fichier = fopen(name, "r");
    
    // Si le fichier est ouvert
    if(fichier)
        {
            fclose(fichier);
            return TRUE;
        }

    return FALSE;
}