#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50
#define MAX_CARS 100

void sortModelsAlphabetically(char models[][MAX_MODEL_LENGTH], int count) {
    char temp[MAX_MODEL_LENGTH];
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(models[i], models[j]) > 0) {
                strcpy(temp, models[i]);
                strcpy(models[i], models[j]);
                strcpy(models[j], temp);
            }
        }
    }
}

void listCarModels(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char models[MAX_CARS][MAX_MODEL_LENGTH];
    int modelCount = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        char *delimiter = strchr(line, ':');
        if (delimiter != NULL) {
            size_t modelLength = delimiter - line;
            strncpy(models[modelCount], line, modelLength);
            models[modelCount][modelLength] = '\0';  // Ajouter le caractère nul de fin
            modelCount++;
        }
    }

    fclose(file);

    // Trier les modèles par ordre alphabétique
    sortModelsAlphabetically(models, modelCount);

    // Afficher les modèles triés
    for (int i = 0; i < modelCount; i++) {
        printf("%s\n", models[i]);
    }
}

int main() {
    const char *filePath = "voiture.txt";
    listCarModels(filePath);
    return 0;
}
