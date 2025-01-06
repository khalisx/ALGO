#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_MODEL_LENGTH 50

void listCarModels(char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char model[MAX_MODEL_LENGTH];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        char *delimiter = strchr(line, ':');
        if (delimiter != NULL) {
            size_t modelLength = delimiter - line;
            strncpy(model, line, modelLength);
            model[modelLength] = '\0';  // Ajouter le caractère nul de fin
            printf("%s\n", model);
        }
    }

    fclose(file);
}

int main() {
    const char *filePath = "voiture.txt";
    listCarModels(filePath);
    return 0;
}
