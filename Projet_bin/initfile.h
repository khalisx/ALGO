#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_VOITURES 100


#ifndef INITFILE_H
#define INITFILE_H


typedef struct {
   short jour;
   short mois;
   short annee;
   int NbRecord;       // Nombre total d'enregistrements dans le fichier
   int LengthHeader;   // Taille de l'entête
   int LengthRecord;   // Taille des enregistrements
} Header;



// Fonction pour initialiser le fichier Voiture.dat
void initialiserFichierVoiture(const char *nomFichier);
void placerCurseurApresHeader(FILE *fichier);


#endif
