//
// Main.c
// Fichier principale du programme
// concentrent les diffèrenes fonctins et contenue
// du jeu pour son fonctionnement logique

// En-tête obligatoires
#include "main.h"

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
    // On efface la console
    effacer_console();
    
    // Initialisation des informations sur la console
    // nécessaire au bon fonctionnement des fonctions
    // d'entrée / sortie étendu
    initialise_informations_console();

    // Introduction du jeu
    introduire_le_jeu();

    // Créer une partie
    AwalePartie awale;

    // Etat du jeu
    FLAG etat_du_jeu;
    do {   
        // On efface la console
        effacer_console();
        // Demande au joueur ce qu'il souhaite
        etat_du_jeu = selection_menu();
    }
    while(!demande_confirmation());

        switch (etat_du_jeu)
        {
            case ETAT_JOUER_PARTIEENR:
                awale = charger_partie();
                break;
            case ETAT_JOUER_CVSC:
                awale = creer_partie(ETAT_JOUER_CVSC);
                break;
            case ETAT_JOUER_CVSIA:
                awale = creer_partie(ETAT_JOUER_CVSIA);
                break;
            case ETAT_JOUER_LAN:
                awale = creer_partie(ETAT_JOUER_LAN);
                break;
            default:
                break;
        }

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
                    etat_du_jeu = ETAT_QUITTER;
                }
            // On test si l'adversaire est en famine
            // si c'est le case on test si on peut le nourrire
            // si ce n'est pas possible il a gagné
            else if(joueur_est_en_famine(awale, joueur_suivant(awale.joueur)))
                if(!joueur_peut_nourrire(awale.plateau, awale.joueur))
                    {
                        fin_de_partie(awale, awale.joueur, awale.scores);
                        etat_du_jeu = ETAT_QUITTER;
                    }

            // On efface l'écran
            #ifndef DEBUG
                    effacer_console();
            #endif

            // On affiche les scores des joueurs
            afficher_scores(awale.scores);

            // On affiche la plateau de facon centré
            afficher_plateau(awale.plateau);

            // Demande au joueur la case qu'il souhaite jouée
            affiche_separation_horizontal();
            afficher_dernier_coup_joue(awale);
            printf("Quel emplacement souhaitez-vous jouer ?\n");
            
            // On récupère l'emplacement demandé par le joueur
            awale.emplacement = demande_emplacement_au_joueur(&awale);

            // Met à jour le dernier coup joué
            awale.dernier_emplacement = awale.emplacement;

            // On jou le coup demandé puis on récupère la
            // dernière case du coup
            awale.emplacement = deplacer_graines(awale.plateau, awale.emplacement);

            // On teste si le joueur (en cours) est en famine
            // si c'est le cas on l'indique
            awale.famines[awale.joueur] = joueur_en_famine(awale.plateau, awale.joueur);

            // On vérifie si on peut ramasser
            // si c'est le cas on ramasse ainsi de suite
            // et on récupère le score du joueur
            awale.scores[awale.joueur] = awale.scores[awale.joueur] + ramasser_graines(awale.plateau, awale.emplacement, awale.joueur);

            // On teste si le joueur (suivant) est en famine
            // si c'est le cas on l'indique
            awale.famines[awale.joueur] = joueur_en_famine(awale.plateau, joueur_suivant(awale.joueur));

            // On teste si le joueur a gagner
            if(awale.scores[awale.joueur] > 24)
                {
                    fin_de_partie(awale, awale.joueur, awale.scores);
                    etat_du_jeu = ETAT_QUITTER;
                }

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
    // Légendes à afficher
    char * legendes_text[7] = {
        "Ils ont marché longtemps, très longtemps à travers le désert...",
        "jusqu'à ce qu'ils arrivent au bord de la mer...",
        "Ils ont fait des provisions de coquillages..",
        "puis sont repartis dans leur village",
        "En chemin, ils ont fait des trous dans le sable",
        "pour stocker les coquillages.",
        "C'est ainsi qu'est né le jeu : des coquillages dans des trous"
    };

    // On afficher au centre chaque légende
    for(unsigned int legende = 0;legende < 7; legende++)
    {
        // On affiche sa valeur au entre de la console
        affichage_centre((char*)legendes_text[legende]);
        
        // Puis on attend 1s
        #ifndef DEBUG
        sleep(1);
        #else
        sleep(0);
        #endif
    }

    // Retour à la ligne
    printf("\n");

    // On affiche 3 tirets
    // avec une animation
    for(unsigned int compteur = 0; compteur < 3; compteur++)
    {
        // On affiche le tiret
        affichage_centre("-");
        // Attend 1 second
        #ifndef DEBUG
        sleep(1);
        #else
        sleep(0);
        #endif
    }

    // Retour à la ligne
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
    affichage_centre("[1] Ordinateur VS Ordinateur");
    affichage_centre("[2] Ordinateur VS IA");
    affichage_centre("[3] Partie sauvgardée");
        changer_couleur_terminal(RED);
        affichage_centre("[4] Ordinateur VS Ordinateur (LAN)");
        reinitialiser_couleur_terminal();
    affichage_centre("[5] Voire la Hall Of Fame");
    affichage_centre("[6] Quitter");

    // String buffer
    char buffer_choix_utilisateur[STRING_MAX_CHAR];
    unsigned int choix = 0;

    do {
        scanf("%s", buffer_choix_utilisateur);

        if(strcmp(buffer_choix_utilisateur, "") == 0)
            continue;

        choix = atoi(buffer_choix_utilisateur);
        
        if(choix == ETAT_JOUER_LAN)
                printf("Attention cette option est non fonctionelle\n");
        else if(choix == ETAT_JOUER_PARTIEENR)
            {
                if(!fichier_exist("save"))
                    printf("Il n'y a aucune partie enregistrée !\n");
            }
        else if(choix == ETAT_HALLOFFAME)
            {
                afficher_hof(recuperer_les_meilleurs_scores());                
            }
    }
    while(choix > 6 || (choix == ETAT_HALLOFFAME) || (choix==ETAT_JOUER_LAN) || (choix==ETAT_JOUER_PARTIEENR && !fichier_exist("save")));

    return choix;
}