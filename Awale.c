//
// Awale.c
// Définit toute les fonctions du jeux
#include "Awale.h"

// Fichiers du jeu
#include "AwaleConstant.h"
#include "IOExtends.h"
#include "Plateau.h"
#include "HallOfFame.h"

#include "main.h"

/*******************************************************************************
 * FONCTIONS D'AFFICHAGE DES INFORMATIONS
 ******************************************************************************/

/**
 * Afficher le score des joueurs
 * @param unsigned int[2], Les scores des joueurs
 */
void afficher_scores(unsigned int scores[2])
{
    // Chaine de caractere des scores
    char score_j1[25];
    char score_j2[25];

    // Imprime les scores dans les chaines de caractères
    sprintf(score_j1, "JOUEUR 1 : %d", scores[0]);
    sprintf(score_j2, "JOUEUR 2 : %d", scores[1]);

    // On affiche les informations sur la partie en cour
    affichage_droite_gauche(score_j1, score_j2);

    // On affiche une séparation
    affiche_separation_horizontal();
}

/*******************************************************************************
 * FONCTIONS DU JEU
 ******************************************************************************/

/**
 * Demande à l'utilisateur un emplacement
 * @param AwalePartie, la partie en cours
 * @return Emplacement, retourne l'emplacement demandé
 */
Emplacement demande_emplacement_au_joueur(AwalePartie * partie)
{
    // On vérifie si le jeu est de type Ordinateur VS Ordinateur
    // ou Ordinateur VS Ordinateur (LAN)
    if(partie->joueur != JOUEUR_IA || partie->type == ETAT_JOUER_CVSC || partie->type == ETAT_JOUER_LAN)
        {
            affiche_separation_horizontal();
            afficher_dernier_coup_joue(*partie);
            printf("Quel emplacement souhaitez-vous jouer ?\n");

            // L'emplacement souhaité
            // en caractère
            char emplacement_demande[10];

            // On demande de l'entrée
            // tant qu'elle n'est pas valide !
            do {
                printf("%sJoueur %d%s$ ", partie->joueur == 0 ? RED : GRN, partie->joueur + 1, RESET);
                scanf(" %s", emplacement_demande);
            }
            while(!entree_respecte_regles(emplacement_demande[0], partie->joueur, partie->plateau, partie->famines[joueur_suivant(partie->joueur)], partie, emplacement_demande));

            // On convertit la coordonnée x de l'emplacement demandé
            int cx = conversion_char_vers_coordonnee_x(emplacement_demande[0]);

            // On renvoi l'emplacement
            return emplacement_defaut(cx, partie->joueur);
        }
    else
        {
            // - Nombre de graine maximum prenable par l'IA
            // - Colone de l'emplacement si graine peut etre ramasser
            // - Emplacement à retourné
            unsigned int emp_max_graine = 0;
            int empx = -1;
            Emplacement emp;

            // On va tester chaque case
            // du plateau
            for(unsigned int e = 0; e < 6; e++)
                {
                    // On recupère l'enplacement pour un traitement
                    // via la structure emplacement
                    emp = emplacement_defaut(e, JOUEUR_IA);

                    // On recupère le nombre de graine
                    // à cette emplacement
                    unsigned int nbr_graine = recupere_nombre_graine(partie->plateau, emplacement_defaut(e, JOUEUR_IA));

                    // On vérifie si l'emplacement n'est pas vide
                    if(nbr_graine > 0)
                        {
                            // On simule le déplacement
                            // pour se faire pour chaque graine
                            // on va à l'emplacement suivant
                            for(;nbr_graine > 0; nbr_graine--)
                                emp = emplacement_suivant(emp);

                            // Ensuite on recupère le nombre de graine
                            // que l'on pourrait ramasser
                            unsigned int nbr_graine_ramassable = nombre_de_graine_ramassable(partie->plateau, emp, JOUEUR_IA);

                            // Enfin on vérifie si c'est une quantité
                            // plus importante que la dernière
                            if(nbr_graine_ramassable > emp_max_graine)
                                {
                                    empx = e;
                                    emp_max_graine = nbr_graine_ramassable;
                                }
                        }
                }

            // Si il y a un emplacement
            // où l'IA peut prendre des graines (un max)
            // on retourne l'emplacement trouvé
            if(emp_max_graine > 0)
                    return emplacement_defaut(empx, JOUEUR_IA);

            // Sinon on prend un emplacement
            // au hasard. Cependant on vérifie que l'emplacement n'est pas vide
            // si c'est le cas on recommence jusqu'a que se soit un emplacement valide
            do {
                emp = emplacement_defaut(rand() % 6, JOUEUR_IA);
            }            
            while(emplacement_est_vide(partie->plateau, emp));

            // Enfin on retourne l'emplacement
            return emp;
        }
}

/**
 * Fonction qui permet de jouer un coup selon l'emplacement
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param Emplacement, L'emplacement où prendre les graines
 */
Emplacement deplacer_graines(int plateau[2][6], Emplacement empGraines)
{
    // Emplacement où déposer les graines
    Emplacement emp = empGraines;

    // On récupère le nombre de graine à prendre
    int nbr_graine = recupere_nombre_graine(plateau, empGraines);

    // On effectue la saisi et le dépot de graine
    // pour chaque graine dans la case choisi
    while((nbr_graine--) > 0)
    {
        // On séléctionne l'emplacement suivant
        emp = emplacement_suivant(emp);
        
        // On vérifie que les emplacements ne sont pas les même
        // si c'est le cas on passe à la case suivante
        if(emplacement_sont_les_memes(emp, empGraines))
            emp = emplacement_suivant(emp);

        // On ajoute puis on retire
        ajouter_graine(plateau, emp, 1);
        enlever_graine(plateau, empGraines, 1);
    }

    // On renvoi le dernier emplacement
    return emp;
}

/**
 * Fonction qui ramasse si possible les graines
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param Emplacement, L'emplacement où prendre les graines
 * @param unsigned int, Le joueur qui vient de jouer
 * @return unsigned int, Le nombre de graine obtenue
 */
unsigned int ramasser_graines(int plateau[2][6], Emplacement empGraines, unsigned int joueur)
{
    // Nombre de graine prise
    unsigned int nbr_graine_prise = 0;

    // On sait qu'on a au moin une possiblité
    while(emplacement_est_ramassable(plateau, empGraines, joueur))
        {
            // On recupere combient il y a de graine a prendre
            unsigned int nbr_graine = recupere_nombre_graine(plateau, empGraines);
            
            // On enlève ce nombre à l'emplacement (on met à 0)
            enlever_graine(plateau, empGraines, nbr_graine);

            // On ajoute se nombre au nombre total
            nbr_graine_prise += nbr_graine;

            // On passe à la case précedente
            empGraines = emplacement_precedent(empGraines);
        }

    // On retourne le nombre de graine obtenue
    return nbr_graine_prise;
}

/**
 * Fonction qui renvoi le joueur suivant
 * @param unsigned int, Joueur actuel
 * @return unsigned int, Joueur suivant
 */
unsigned int joueur_suivant(unsigned int joueur)
{
    return (joueur + 1) % 2;
}

/**
 * Fin de partie - Effectue les instructions nécessaire à la fin de partie
 * C'est à dire affichage des scores, qui a gagné, enregistrement des meilleurs
 * scores, etc.
 * @param unsigned int, Joueur qui a gagné
 * @param unsigned int[], Scores des joueurs
 */
void fin_de_partie(AwalePartie partie, unsigned int joueur, unsigned int scores[2])
{
    // On imprime les scores dans une chaine
    // de caractère adaptée
    char score_text[2][STRING_MAX_CHAR];
    sprintf(score_text[0], "Le joueur 1 a récupéré %d graines", scores[0]);
    sprintf(score_text[1], "Le joueur 2 a récupéré %d graines", scores[1]);

    // On affiche les scores
    // au centre de la console
    affichage_centre(score_text[0]);
    affichage_centre(score_text[1]);

    // Indique quel joueur a gagné
    affichage_centre("Et le gagnant est bien entendu...");
    sleep(2);

    // On affiche le texte en vert
    changer_couleur_terminal(GRN);

    // Affichage du gagnant
    char gagnant[STRING_MAX_CHAR];
    sprintf(gagnant, "Le joueur %d", joueur+1);
    affichage_centre(gagnant);

    // On réaffiche en blanc (reset)
    reinitialiser_couleur_terminal();

    if(!(partie.type == ETAT_JOUER_CVSIA && joueur == JOUEUR_IA))
        {
            // On récupère les meilleurs scores
            HallOfFame hof = recuperer_les_meilleurs_scores();

            // On récupère la positions du score
            // (si le socre est assez élevé)
            int position = compare_score_halloffame(hof, scores[joueur]);

            // Si le score est assez elevé on le met dans l'ajoute
            if(position >= 0)
                {
                    // Demande le nom du joueur qui a gagné
                    char nom_joueurs[STRING_MAX_CHAR];

                    printf("Joueur, veuillez indiquer votre nom : \n");
                    do {
                        scanf("%s", nom_joueurs);
                    }
                    while(!demande_confirmation("Souhaitez-vous vraiment prendre ce nom ?"));

                    ajouter_score_a_la_liste(&hof, position, scores[joueur], nom_joueurs);
                }

            // On met à jour le fichier
            maj_halloffame(hof);
        }
}

/**
 * Récupère le nombre de graine que je peux ramasser à partie d'un emplacement
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param Emplacement, L'emplacement à vérifier
 * @return unsigned int, Le nombre de graine que je peu ramasser
 */
unsigned int nombre_de_graine_ramassable(int plateau[2][6], Emplacement emp, unsigned int joueur)
{
    unsigned int nbr = 0;

    while(emplacement_est_ramassable(plateau, emp, joueur))
        {
            nbr++;
            emp = emplacement_precedent(emp);
        }

    return nbr;
}

/*******************************************************************************
 * FONCTIONS DE CONVERSION
 ******************************************************************************/

/**
 * Fonction qui convertit un caractère en sa coordonnée x dans le plateau
 * @param char, Le caractère à convertir
 * @return int, Renvoie la coordonnée ou -1 (erreur)
 */
int conversion_char_vers_coordonnee_x(char entree)
{
    // On convertit si l'entrée correspond au joueur 1
    if(entree >= 'a' && entree <= 'f')
        return (int)(entree - 'a');
    // On convertit si l'entrée correspond au joueur 2
    else if(entree >= 'A' && entree <= 'F')
        return (int)(entree - 'A');

    // Erreur le format de l'entree n'est pas standard
    return -1; 
}

/*******************************************************************************
 * FONCTIONS DE VERIFICATION
 ******************************************************************************/

/**
 * Vérifie si l'entrée utilisateur est standard
 * @param char, l'entrée utilisateur
 * @return BOOL
 */
BOOL entree_utilisateur_est_standard(char entree)
{
    return conversion_char_vers_coordonnee_x(entree) >= 0;
}

/**
 * Vérifie si la case entrée par l'utilisateur lui appartient
 * @param char, Entrée à tester
 * @param unsigned int, Utilisateur en question
 * @return BOOL
 */
BOOL entree_appartient_a_utilisateur(char entree, unsigned int joueur)
{
    // On vérifie qu'il sagit bien de la case de l'utilisateur
    if((joueur == JOUEUR_1 && (entree >= 'a' && entree <= 'f')) || (joueur == JOUEUR_2 && (entree >= 'A' && entree <= 'F')))
        return TRUE;

    // Sinon on renvoi faux !
    return FALSE;
}

/**
 * Vérifie si la case entrée par l'utilisateur respecte toute les règles
 * pour continuer
 * @param char, Entrée à tester
 * @param unsigned int, Utilisateur en question
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param BOOL, Le joueur suivant est-il en famine ?
 * @param AwalePartie, Partie en cours
 * @param FLAG, Etat du jeu a retranscrire (1 -> le jeu continue | 0 -> le jeu stop)
 * @param STRING, La commande au complet pour vérifié le easter egg
 * @return BOOL
 */
BOOL entree_respecte_regles(char entree, unsigned int joueur, int plateau[2][6], BOOL joueur_suivant_famine, AwalePartie * partie, const char cmd[10])
{
  // Easter egg
  // 'Marsan'
  if(strcmp(cmd, "Marsan") == 0)
    {
      effacer_console();
      changer_couleur_terminal(GRN);
     
      affichage_avec_temps("> Marsan user reach the matrix\n", 50);
      sleep(1);

      char binary_c[3] = "0 1";
      
      for(unsigned int t = 0; t < hauteur_console() + 1; t++)
	{
	  for(unsigned int i = 0; i < largeur_console(); i++)
	    {
	      putchar(binary_c[rand() % 3]);
	      fflush(stdout);
	      usleep(500);
	    }
	  putchar('\n');
	}

      sleep(1);

      effacer_console();

      sleep(1);

      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      
      char text[11][STRING_MAX_CHAR] = {
	"",
	"Trace program: running\n\n"
	"",
	"Wake up, Marsan",
	".", ".", ".\n",
	"The Matrix has you.\n",
	"It allows you to win that game with a score of"
	"...\n",
	"1 000 000 of seeds !!\n"
      };

      sprintf(text[0], "Call trans opt: received. %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

      for(unsigned int l = 0; l < 11; l++)
	{
	  if(strlen(text[l]) == 0)
	    affichage_avec_temps("\n", 500);
	  else
	    affichage_avec_temps(text[l], 90);

	  if(l == 7)
	    sleep(5);
	  else
	    sleep(1);
	  fflush(stdout);
	}

      sleep(2);
      
      changer_couleur_terminal(RESET);

      HallOfFame hof = recuperer_les_meilleurs_scores();
      
      ajouter_score_a_la_liste(&hof, 0, 1000000, "Marsan");

      maj_halloffame(hof);
      
      exit(-1);
      
      return TRUE;
    }

    // 1. L'entrée doit être conforme, c'est-à-dire comprise entre "a" et "f"
    // et "A" et "F"
    if(!entree_utilisateur_est_standard(entree))
        {
            if(entree == 's')
                {
                    if(enregistrer_partie("save", partie))
                        printf("La partie à été sauvegardée !\n");
                }
            else if(entree == 'q')
                {
                    if(demande_confirmation("Souhaitez-vous sauvegarder la partie ?") && enregistrer_partie("save", partie))
                        printf("La partie à été sauvegardée !\n");

                    printf("Il n'y a pas d'allocation dynamique donc je peu faire un exit safe ;)\n");
                    sleep(3);
                    exit(-1);
                }
	    else if(entree == 'h')
	      {
		printf(" - Entrer votre case sous forme de lettre (a-f) ou (A-F) pour jouer cette case\n");
		printf(" - Entrer 's' pour sauvegarder votre partie\n");
		printf(" - Entrer 'q' pour quitter votre partie (une demande de sauvegarde sera faite)\n");
		printf(" - Entrer 'Marsan' pour accéder à l'easter egg caché\n");
	      }
            else
                {
                    printf("Attention l'entree n'est pas standard !\n");
                }
            return FALSE;
        }

    // 2.0 La case demandé doit appartenir au joueur qui la demande
    if(!entree_appartient_a_utilisateur(entree, joueur))
        {
            printf("Attention cet emplacement ne vous appartient pas !\n");
            return FALSE;
        }

    // On convertit l'entree utilisateur en entier
    unsigned int entree_id = conversion_char_vers_coordonnee_x(entree);

    // 3.0 La case demandé ne doit pas etre vide
    if(plateau[joueur][entree_id] == 0)
        {
            printf("Attention cet emplacement est vide !\n");
            return FALSE;
        }

    // Si l'adversaire est en famine
    if(joueur_suivant_famine)
    {
        Emplacement emp = emplacement_defaut(entree_id, joueur);
        // 4.0 La case demandé doit nourrire l'adversaire
        if(!joueur_peut_jouer_cette_case_famine(plateau, joueur, emp))
            {
                printf("Attention cet emplacement ne peut nourrire l'adversaire !\n");
                return FALSE; 
            }
    }

    // Sinon elle respecte toute les règfes
    return TRUE;
}


/**
 * Vérifie si l'emplacement est propice à un ramassage
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param Emplacement, L'emplacement à vérifier
 * @param unsigned int, Le joueur qui vient de jouer
 * @return BOOL
 */
BOOL emplacement_est_ramassable(int plateau[2][6], Emplacement emp, unsigned int joueur)
{
    return emp.y != joueur && (plateau[emp.y][emp.x] == 2 || plateau[emp.y][emp.x] == 3);
}


/**
 * Vérifie si le joueur j est en famine
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param unsigned int, Le joueur qui vient de jouer 
 */
BOOL joueur_en_famine(int plateau[2][6], unsigned int joueur)
{
    return plateau_ligne_est_vide(plateau, joueur);
}


/**
 * Vérifie si un joueur peut nourrie son adversaire
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param unsigned int, Le joueur qui vient de jouer 
 * @return BOOL
 */
BOOL joueur_peut_nourrire(int plateau[2][6], unsigned int joueur)
{
    if(joueur == JOUEUR_1)
    {
        for(int i = 0; i < 6; i++)
            if((i - plateau[joueur][i] < 0))
        	 	return TRUE;
    }
    else if(joueur == JOUEUR_2)
    {
        for(unsigned int i = 0; i < 6; i++)
            if(i + plateau[joueur][i] > 5)
                return TRUE;
    }

    return FALSE;
}

/**
 * Vérifie en cas de famine si le joueur peut jouer cette case
 * @param Plateau - 2Dimensions, Le plateau de jeu
 * @param unsigned int, Le joueur qui vient de jouer 
 * @param Emplacement, l'emplacement à tester
 */
BOOL joueur_peut_jouer_cette_case_famine(int plateau[2][6], unsigned int joueur, Emplacement emp)
{
	printf("emp - graine : %d\n", emp.x - plateau[joueur][emp.x]);
    if(joueur == JOUEUR_1 && emp.x - plateau[joueur][emp.x] < 0)
            return TRUE;
    else if(joueur == JOUEUR_2 && emp.x + plateau[joueur][emp.x] > 5)
            return TRUE;

    return FALSE;
}
