#ifndef VOITURE_H
#define VOITURE_H

#define MAX_MODEL_LENGTH 50

typedef struct {
    char marque[50];
    char modele[50];
    char immatriculation[20];
    int statut;
    char supprime; 
} Voiture;


int sauvegarderVoitures(const char *filename, Voiture voitures[], int car_count);
void reserverVoiture(const char *filename);
void ajouterVoiture(const char *filename);
void arreterReservation(const char *filename);
void afficherMenuPrincipal();
void afficherMenuAdmin();
void listCarModels(const char *filePath);
int listereserv();
char convertirEnMinuscule(char c);
void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee);
void lireFichierEtRemplirTableau(const char *nomFichier, Voiture **voitures, int *nbVoitures, int *tailleTableau);
void LireFichierEtRemplirTableau(const char *nomFichier, Voiture voitures[], int *nbVoitures);
void afficherTableau(Voiture voitures[], int nbVoitures);
void AfficherTableau(Voiture *voitures, int nbVoitures);
void trierTableau(Voiture *voitures, int nbVoitures);
int rechercheDichotomique(Voiture *voitures, int nbVoitures, const char *marque, const char *modele);
int lireDernierId();
void mettreAJourDernierId(int nouvelId);
void viderTampon();
int recherche(); 
void supprimerVoiture(const char *filename); 
void case2(); 
void case3(); 
void case4(); 



#endif
