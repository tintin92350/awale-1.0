#! /bin/bash

# Fichiers à compiler
fichiers="main.c Emplacement.c IOExtends.c Plateau.c Awale.c AwalePartie.c HallOfFame.c"

# Nom de l'executable à générer
exec="Awale"

# Options
opts="-Wall -g"

# Compile le programme
gcc $fichiers -o $exec $opts