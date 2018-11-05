//
// Main.c
// Fichier principale du programme
// concentrent les diffèrenes fonctins et contenue
// du jeu pour son fonctionnement logique

// En-tête obligatoires
#include "main.h"
#include <ctype.h>

// Fichiers du jeu
#include "Awale.h"
#include "Plateau.h"
#include "AwalePartie.h"
#include "Emplacement.h"
#include "IOExtends.h"
#include "HallOfFame.h"

/**
 * Introduction du jeu
 */
void introduire_le_jeu();

/**
 * Demande au joueur ce qu'il souhaite faire au début du programme
 * @return unsigned int, Etat du jeu demandé
 */
unsigned int selection_menu();

// Entree principale du programme
int main(void)
{ 
    // Initialisation des informations sur la console
    // nécessaire au bon fonctionnement des fonctions
    // d'entrée / sortie étendu
    initialise_informations_console();

    // Créer une partie
    AwalePartie awale;

    // Etat du jeu
    FLAG etat_du_jeu;

    do {   
        // On efface la console
        effacer_console();
        // Introduction du jeu
        introduire_le_jeu();
        // Demande au joueur ce qu'il souhaite
        etat_du_jeu = selection_menu();
    }
    while(!demande_confirmation("Souhaitez-vous vraiment faire cela ?"));

    // Si l'utilisateur demande de rejouer une partie
    // sauvegarder on la charge
    if(etat_du_jeu == ETAT_JOUER_PARTIEENR)
        awale = charger_partie();
    // Charger un fichier
    else if(etat_du_jeu == ETAT_JOUER_FICHIER)
        {
            char buffer[STRING_MAX_CHAR];
            printf("entrez un nom de fichier : \n");
            scanf("%s", buffer);
            awale = charger_partie_depuis_fichier(buffer);
        }
    // Sinon on créer la partie
    else
        awale = creer_partie(etat_du_jeu);

    // Tant que le jeu est en cour d'execution
    // on continue de jouer :)
    while(etat_du_jeu != ETAT_QUITTER)
        {
            // Initialisation des informations sur la console
            // nécessaire au bon fonctionnement des fonctions
            // d'entrée / sortie étendu (encore une fois en cas
            // de changement de la taille de la fenêtre)
            initialise_informations_console();
            
            // On teste si le joueur (en cour) est en famine
            // si c'est le cas il a perdu
            if(joueur_est_en_famine(awale, awale.joueur))
                {
                    fin_de_partie(awale, joueur_suivant(awale.joueur), awale.scores);
                    break;
                }
            // On test si l'adversaire est en famine
            // si c'est le case on test si on peut le nourrire
            // si ce n'est pas possible il a gagné
            else if(joueur_est_en_famine(awale, joueur_suivant(awale.joueur)) && !joueur_peut_nourrire(awale.plateau, awale.joueur))
                {
                    fin_de_partie(awale, awale.joueur, awale.scores);
                    break;
                }

            // On efface l'écran
            // uniquement en release pas en mode debug
            #ifndef DEBUG
                effacer_console();
            #endif

            // On affiche les scores des joueurs
            afficher_scores(awale.scores);

            // On affiche la plateau de facon centré
            afficher_plateau(awale.plateau);

            // Demande au joueur la case qu'il souhaite jouée            
            // On récupère l'emplacement demandé par le joueur
            awale.emplacement = demande_emplacement_au_joueur(&awale);

            // Met à jour le dernier coup joué
            awale.dernier_emplacement = awale.emplacement;

            // On jou le coup demandé puis on récupère la
            // dernière case du atteinte
            awale.emplacement = deplacer_graines(awale.plateau, awale.emplacement);

            // On teste si le joueur (en cours) est en famine (après avoir jouer)
            // si c'est le cas on l'indique
            awale.famines[awale.joueur] = joueur_en_famine(awale.plateau, awale.joueur);

            // On vérifie si on peut ramasser
            // si c'est le cas on ramasse ainsi de suite
            // et on récupère le score du joueur
            awale.scores[awale.joueur] = awale.scores[awale.joueur] + ramasser_graines(awale.plateau, awale.emplacement, awale.joueur);

            // On teste si le joueur (suivant) est en famine (après avoir pris les graines)
            // si c'est le cas on l'indique
            awale.famines[joueur_suivant(awale.joueur)] = joueur_en_famine(awale.plateau, joueur_suivant(awale.joueur));

            // On teste si le joueur a gagner
            if(awale.scores[awale.joueur] > 24)
                {
                    fin_de_partie(awale, awale.joueur, awale.scores);
                    etat_du_jeu = ETAT_QUITTER;
                }

            // Si le joueur suivant est l'IA on attend
            // un peu...
            // sinon c'est trop rapide on voi rien...
            if(awale.type == ETAT_JOUER_CVSIA && awale.joueur == JOUEUR_IA)
                sleep(2);

            // On passe au joueur suivant
            awale.joueur = joueur_suivant(awale.joueur);

            // Met le premier coup à false
            if(awale.premier_coup)
                awale.premier_coup = FALSE;
        }

    // Retourne un code
    // d'erreur succés (aucune erreur)
    return EXIT_SUCCESS;
}

/**
 * Introduction du jeu
 */
void introduire_le_jeu()
{
    effacer_console();
    // Affichage des informations relatives.. a nous !
    affichage_centre("*********************************");
    affichage_centre("** CODE PAR QUENTIN ET COLLINE **");
    affichage_centre("*********************************");
    printf("\n");
}

/**
 * Demande au joueur ce qu'il souhaite faire au début du programme
 * @return unsigned int, Etat du jeu demandé
 */
unsigned int selection_menu()
{
    // Affiche au joueur la demande
    printf("Que souhaitez-vous faire ?\n");
    affichage_centre("[1] Joueur VS Joueur");
    affichage_centre("[2] Joueur VS IA");
    affichage_centre("[3] Partie sauvgardée");
        changer_couleur_terminal(RED);
        affichage_centre("[4] Joueur VS Joueur (LAN)");
        reinitialiser_couleur_terminal();
    affichage_centre("[5] Voire la Hall Of Fame");
    affichage_centre("[6] Quitter");

    // String buffer
    char buffer_choix_utilisateur[STRING_MAX_CHAR];
    unsigned int choix = 0;

    // Une boucle pour vérifier ce que l'utilisateur
    // rentre comme donnée
    // certaines fonctionnalités ne sont pas encore disponible (LAN)
    do {
        // Demande à l'utilisateur de faire son choix
        // on attend une chaine de caractère pour ensuite pouvoir
        // faire des teste de vérificaiton sur l'entrée
        scanf("%s", buffer_choix_utilisateur);

        // On convertit cette entrée en un nombre
        choix = atoi(buffer_choix_utilisateur);
        
        // La fonctionnalités LAN n'étant pas disponible
        // on informe l'utilisateur que son choix est impossible
        if(choix == ETAT_JOUER_LAN)
            {
                printf("Attention cette option est non fonctionelle\n");
                continue;
            }
        // Si l'utilisateur souhaite continuer une partie
        else if(choix == ETAT_JOUER_PARTIEENR)
            {
                // On vérifie si une sauvegarde existe !
                if(!fichier_exist("save"))
                    {
                        printf("Il n'y a aucune partie enregistrée !\n");
                        continue;
                    }
            }
        // Si l'utilisateur demande le Hall Of Fame
        // on l'affiche
        else if(choix == ETAT_HALLOFFAME)
                afficher_hof(recuperer_les_meilleurs_scores());
    }
    // Tant que le choix n'est pas standard (i.e. > 6 donc pas une fonction proposé)
    // l'état HallOfFame aussi rejour la boucle car après affichage on redemande à l'utilisateur de faire un choix
    // et enfin on vérifie si le fichier existe si on a demandé de rejouer une partie (si il n'existe pas on refais un tour !)
    while(choix > 7 || (choix == ETAT_HALLOFFAME) || (choix==ETAT_JOUER_LAN) || (choix==ETAT_JOUER_PARTIEENR && !fichier_exist("save")) || !isdigit(buffer_choix_utilisateur[0]));

    // On retourne le choix de l'utilisateur
    // qui sera traiter
    return choix;
}