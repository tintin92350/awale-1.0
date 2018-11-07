# READ ME - JEU AWALE
Le jeu que nous avons codé est un "awalé", jeu de réflexion d'origine africaine.

# Fichiers du jeu

## Les constantes du jeu (AwaleConstante.h)

Ce fichier contient toutes les constantes du jeu telles que le joueur, la couleur du terminal, ...

## Le plateau de jeu (Plateau.h et Plateau.c)

### Plateau.h
Déclare les prototypes des fonctions de "Plateau.c"

### Plateau.c
Définit les fonctions propres au plateau de jeu (et aux graines) telles que affichage du plateau, recupere graines, ...

## Le jeu (Awale.h et Awale.c)

### Awale.h
Déclare les prototypes des fonctions de "Awale.c"

### Awale.c
Définit les fonctions propres au deroulement d'une partie telles que demander l'emplacement où prendre les graines, les deplacer, ...

## Une partie de jeu (AwalePartie.h et AwalePartie.c)

### AwalePartie.h
Déclare les prototypes des fonctions de "AwalePartie.c"

### AwalePartie.c
Définit les fonctions propres à la partie telles que charger une partie, lancer une nouvelle partie, ...

## Emplacement dans le plateau (Emplacement.h et Emplacement.c)

### Emplacement.h
Déclare les prototypes des fonctions de "Emplacement.c"

### Emplacement.c
Définit les fonctions propres à chaque emplacement telles que emplacement suivant, ou precedent

## Le "BEAU" et l'utile (IOExtends.h et IOExtends.c)

### IOExtends.h
Déclare les prototypes des fonctions de "IOExtends.c"

### IOExtends.c
Définit les fonctions propres à l'affichage d'un BEAU terminal et également les fonctions propres aux fichiers utilisés pour charger une partie préexistante

## Hall of Fame (HallOfFame.h et HallOfFame.c)

### HallOfFame.h 
Déclare les prototypes des fonctions de "HallOfFame.c"

### HallOfFame.c
Définit les fonctions relatives à notre Hall of Fame : l'afficher, enregistrer un nouveau score, ...

## Un main digne de ce nom (main.h et main.c)

### main.h
Contient toutes les bibliothèques standard et UNIX utilisées.

### main.c
Fonction principale qui regroupe les appels aux fonctions du jeu pour son fonctionnement logique.

