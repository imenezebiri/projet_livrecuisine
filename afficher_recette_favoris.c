#include "afficher_recette_favoris.h"

char liste_de_recette_favoris[100][100];
int num_recettes_favoris = 0;


void lire_fichier_recette(char nom[]) {
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

void remplir_favoris() {
    num_recettes_favoris = 0;
    memset(liste_de_recette_favoris, 0, sizeof(liste_de_recette_favoris));

    FILE *fp;
    fp = fopen("data/favoris/recette_favoris.txt", "r");
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp)) {  // Read file line by line
        strcpy(liste_de_recette_favoris[num_recettes_favoris], buffer);
        num_recettes_favoris++;
    }
    fclose(fp);
}

bool check_favoris(char *mot) {

    for (int i = 0; i < num_recettes_favoris; ++i) {
        if (strcmp(mot, liste_de_recette_favoris[i]) == 0) {
            return true;
        }
    }

    return false;
}

void Choisir_list_recette_favoris() {
    remplir_favoris();

    DIR *dir;
    struct dirent *ent;
    char path[100] = "data/recettes/";
    int numfav = 0;

    char liste[100][100];
    int counter = 0;

    printf("Voici la liste de toutes les recettes disponible : \n");

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".txt")) {
                char name[100];
                char name_avec_new_line[100];
                char *token, *saveptr;

                token = strtok_r(ent->d_name, "_", &saveptr);
                token = strtok_r(NULL, "_", &saveptr);
                strcpy(name, token);
                strcpy(name_avec_new_line, token);
                strcat(name_avec_new_line, "\n");

                if (check_favoris(name_avec_new_line) == false) {
                    strcpy(liste[counter], name);
                    counter++;
                    printf("%d. %s\n", counter, name);
                }
            }
        }
        closedir(dir);
    }

    do {
        printf("\nEnter le numéro de la recette que vous souhaiter inclure dans vos favoris: \n");
        scanf("%d", &numfav);
    } while ((numfav < 1) || (numfav > counter));


    FILE *fp;
    fp = fopen("data/favoris/recette_favoris.txt", "a");
    fprintf(fp, "%s\n", liste[numfav - 1]);
    fclose(fp);

}

int Afficher_list_recette_favoris(bool delete) {
    remplir_favoris();

    if (num_recettes_favoris == 0) return 0;

    printf("Voici la liste de voter recettes favoris : \n");
    for (int i = 0; i < num_recettes_favoris; ++i) {
        printf("%d-%s", i + 1, liste_de_recette_favoris[i]);
    }

    int numfav = 0;
    do {
        if (delete) {
            printf("\nEntrez le numéro de recette que vous souhaitez supprimer: \n");
        } else {
            printf("\nEntrez le numéro de la recette pour la voir en détail : \n");
        }
        scanf("%d", &numfav);
    } while ((numfav < 1) || (numfav > num_recettes_favoris));

    return numfav;

}

void Afficher_recette_details(int index) {
    char *recette_choisi = liste_de_recette_favoris[index - 1];

    int newline_pos = strcspn(recette_choisi, "\n");
    strcpy(&recette_choisi[newline_pos], "");


    DIR *dir;
    struct dirent *ent;
    char path[100] = "data/recettes/";

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".txt")) {
                if (strstr(ent->d_name, recette_choisi) != NULL) {
                    char recette_path[100];
                    sprintf(recette_path, "%s%s", path, ent->d_name);

                    lire_fichier_recette(recette_path);
                }
            }
        }
        closedir(dir);
    }
}

void supprimer_recette_favoris(int index) {
    char *favoris_path = "data/favoris/recette_favoris.txt";

    FILE *fp = fopen(favoris_path, "w");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", favoris_path);
    }

    for (int i = 0; i < num_recettes_favoris; i++) {
        if (index - 1 != i) {
            fprintf(fp, "%s", liste_de_recette_favoris[i]);
        }
    }

    fclose(fp);
}