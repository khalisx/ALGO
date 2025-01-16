#ifndef VOITURE_H
#define VOITURE_H

#define MAX_MODEL_LENGTH 50

// Structure représentant une voiture
typedef struct {
    char supprime; // Indicateur de suppression
    char marque[50]; // Marque de la voiture
    char modele[50]; // Modèle de la voiture
    char immatriculation[20]; // Immatriculation de la voiture
    int statut; // Statut de la voiture (disponible, réservée, etc.)
} Voiture;

// Sauvegarder les voitures dans un fichier binaire
int sauvegarderVoitures(const char *filename, Voiture voitures[], int car_count);

// Réserver une voiture
void reserverVoiture(const char *filename);

// Ajouter une nouvelle voiture
void ajouterVoiture(const char *filename);

// Arrêter une réservation
void arreterReservation(const char *filename);

// Afficher le menu principal
void afficherMenuPrincipal();

// Afficher le menu admin
void afficherMenuAdmin();

// Lister les modèles de voitures disponibles
void listCarModels(const char *filePath);

// Lister les réservations
int listereserv();

// Convertir un caractère en minuscule
char convertirEnMinuscule(char c);

// Normaliser une chaîne de caractères (exemple : convertir en minuscules)
void normaliserChaine(const char *chaineOrigine, char *chaineNormalisee);


// Lire un fichier et remplir un tableau de voitures (surcharge)
void LireFichier(const char *nomFichier, Voiture voitures[], int *nbVoitures);

void RemplirTableau(const char *nomFichier, Voiture **voitures, int *nbVoitures, int *tailleTableau);

// Afficher un tableau de voitures
void afficherTableau(Voiture voitures[], int nbVoitures);

// Afficher un tableau de voitures
void AfficherTableau(Voiture *voitures, int nbVoitures);

// Trier un tableau de voitures
void trierTableau(Voiture *voitures, int nbVoitures);

// Recherche dichotomique dans un tableau de voitures
int rechercheDichotomique(Voiture *voitures, int nbVoitures, const char *marque, const char *modele);

// Lire le dernier ID enregistré
int lireDernierId();

// Mettre à jour le dernier ID
void mettreAJourDernierId(int nouvelId);

// Vider le tampon de saisie
void viderTampon();

// Recherche de voiture
int recherche();

// Supprimer une voiture
void supprimerVoiture(const char *filename);

#endif // VOITURE_H
