//
// HallOfFame.c
// Définit toutes les fonctions relative à l'option HOF
#include "HallOfFame.h"

// Fichiers du jeu
#include "IOExtends.h"

/**
 * Créer une structure vide
 * @return HallOfFame
 */
HallOfFame hof_vide()
{
    HallOfFame hof;

    for(unsigned int i = 0; i < 10; i++)
        strcpy(hof.noms[i], "");
    for(unsigned int i = 0; i < 10; i++)
        hof.scores[i] = 0;

    return hof;
}

/**
 * Récupère dans une structure HallOfFames
 * les meilleurs scores depuis le fichier
 */
HallOfFame recuperer_les_meilleurs_scores()
{
    // Ouvre le fichier en lecture seul
    FILE * fichier_hof = fopen("HallOfFame", "r");

    // On renvoie une structure vide
    // si le fichier n'existe pas (pas de meilleur score)
    if(!fichier_hof)
        return hof_vide();

    // Hall Of Fame
    HallOfFame hof = hof_vide();

    // Nom et score (buffer)
    char nom[STRING_MAX_CHAR];
    unsigned int score;
    unsigned int score_index = 0;

    // Sinon on lit le fichier
    while(fscanf(fichier_hof, "%s : %d", nom, &score) > 0 && score_index < 10)
        {
            // On l'ajoute à l'HOF
            strcpy(hof.noms[score_index], nom);
            hof.scores[score_index] = score;

            score_index++;
        }

    // On ferme le fichier
    fclose(fichier_hof);

    // On renvoi la structure
    return hof;
}

/**
 * Fonction qui renvoie la position du score par rapport
 * aux autres de la liste sinon -1
 * @param HallOfFame, Liste des meilleurs scores
 * @param unsigned int, Score du joueur
 * @return int, Renvoi la position sinon -1
 */
int compare_score_halloffame(HallOfFame hof, unsigned int score)
{
    for(unsigned int pos = 0; pos < 10; pos++)
            if(score >= hof.scores[pos])
                return pos;
    return -1;
}

/**
 * Ajoute le score et nom du joueur à la position demandée, puis effectue
 * les changements nécessaires
 * @param HallOfFame*, La structure à modifier
 * @param unsigned int, La position
 * @param unsigned int, Le score
 * @param string, Le nom du joueur
 */
void ajouter_score_a_la_liste(HallOfFame * hof, unsigned int pos, unsigned int score, string name)
{
    int pos_courante = 9;

    while((pos_courante--) > pos)
        {
            if(pos_courante + 1 < 10)
                {
                    hof->scores[pos_courante+1] = hof->scores[pos_courante];
                    strcpy(hof->noms[pos_courante+1], hof->noms[pos_courante]);
                }
        }

    hof->scores[pos] = score;
    strcpy(hof->noms[pos], name);

    afficher_hof(*hof);
}

/**
 * Affiche le Hall Of Fame au centre !
 * @param HallOfFame
 */
void afficher_hof(HallOfFame hof)
{
    unsigned int i;
    // On affiche chaque meilleur score
    for(i = 0; i < 10; i++)
        {
            if(hof.scores[i] == 0)
                break;

            char texte[STRING_MAX_CHAR];
            sprintf(texte, "%i. Le joueur %s a récupéré %d graine !", i+1, hof.noms[i], hof.scores[i]);
            affichage_centre(texte);
        }
    
    if(i==0)
        printf("Il n'y a pas encore de best score !\n");
}

/**
 * Met à jour le contenue du fichier du Hall Of Fame
 * @param HallOfFame, Les meilleurs scores
 * @return BOOL, La fonction a t-elle echoué ?
 */
BOOL maj_halloffame(HallOfFame hof)
{
    // Ouvre le fichier en écriture (efface le dernier contenue)
    FILE * fichier_hof = fopen("HallOfFame", "w+");

    if(!fichier_hof) return FALSE;

    // On écrit dans le fichier pour chaque meilleur score
    for(unsigned int i = 0; i < 10; i++)
        {
            // On arrete au dernier
            if(hof.scores[i] == 0)
                break;
            fprintf(fichier_hof, "%s : %d\n", hof.noms[i], hof.scores[i]);
        }
    
    // Ferme le fichier
    fclose(fichier_hof);
    
    return TRUE;
}