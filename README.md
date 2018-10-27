# My AWALE
Il s'agit d'un jeu basé sur le "Awalé", un jeu d'origine africaine.

# Fichiers du jeu

## Constantes du jeu (AwaleConstantes.h)

Fichier rassemblent uniquement les diffèrentes constantes du jeu.

## Types (AwaleTypes.h)

Fichier rassemblent uniquement les types spécialisé, créer spécialement pour le jeu

## Print Interface (PrintInterface.h | PrintInterface.c)

Fichier contentant les diffèrentes fonctions "outils" pour l'affichage
dans le Terminal (text)

## Introduction Jeu (IntroductionJeu.h | IntroductionJeu.c)

L'en-tête "h" contient la déclaration de la fonction utilisée pour introduire le jeu
avec les légendes

Le fichier source "c" en contient la définition de cette fonction

## Jeu (Jeu.h | Jeu.c)

L'en-tête contient la déclaration de la structure de donnée "JEU"
ainsi que toutes les fonctions en rapport avec le jeu, c-a-d : 
- Création / Initialisation du jeu et de la partie
- Méthodes pour le comportements du jeu
- Méthode de test des diffèrents variables

Le fichier source "c" en contient les définitions

## Main (main.h | main.c)

Cette en-tête contient les inclusions générales de tout les en-têtes nécessaire
au programme en générale et au jeu

Le fichier source contient la fonction main() qui va permettre :
- l'initialisation du jeu
- Son introduction
- Le regroupement des fonctionnalités du jeu
