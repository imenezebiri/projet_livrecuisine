#include "afficher_recette_par_budget.h"

char liste_de_recette_budget[100][100];
int num_recettes_par_budget = 0;

void lire_fichier_budget(char nom[]) {
    FILE *file;
    char line[200];

    file = fopen(nom, "r");

    if (file == NULL) {
        printf("Error: Unable to open file!");
    }

    while (fgets(line, 200, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void Afficher_list_recette_par_budget(int budget) {
    memset(liste_de_recette_budget, 0, sizeof(liste_de_recette_budget));
    num_recettes_par_budget = 0;

    DIR *dir;
    struct dirent *ent;
    char path[100] = "data/recettes/";

    printf("Avec votre budget, vous pouvez utiliser une de ces recettes: \n");

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".txt")) {
                // recette_Buratta_1_10-20_buratta.txt
                // min_budget = 10 , max_budget = 20
                int min_budget, max_budget;
                sscanf(ent->d_name, "recette_%*[^_ ]_%*d_%d-%d", &min_budget, &max_budget);

                if (budget >= min_budget && budget <= max_budget) {
                    strcpy(liste_de_recette_budget[num_recettes_par_budget], ent->d_name);
                    num_recettes_par_budget++;

                    char name[100];
                    char *token, *saveptr;

                    token = strtok_r(ent->d_name, "_", &saveptr);
                    token = strtok_r(NULL, "_", &saveptr);
                    strcpy(name, token);

                    printf("%d-%s\n", num_recettes_par_budget, name);
                }

            }

        }
        closedir(dir);
    }
};

int num_de_recette_par_budget() {
    return num_recettes_par_budget;
}

void Afficher_recette_par_budget(int num) {
    char path[100] = "data/recettes/";

    char recette_path[100];
    sprintf(recette_path, "%s%s", path, liste_de_recette_budget[num - 1]);

    lire_fichier_budget(recette_path);
}