#include "afficher_recette_par_mot_cle.h"

char liste_de_mot_cle[100][100];
int num_mot_cle = 0;

void lire_fichier_mot_cle(char nom[]) {
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


void Afficher_list_mot_cle() {
    memset(liste_de_mot_cle, 0, sizeof(liste_de_mot_cle));
    num_mot_cle = 0;

    DIR *dir;
    struct dirent *ent;
    char path[100] = "data/recettes/";

    printf("Entrer l'ingrédient principale de votre recette parmis cette liste: \n");

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".txt")) {

                // recette_Carbonara_2_0-10_crème => crème
                char mot_cle[100];
                char *ptr = strrchr(ent->d_name, '_');
                strcpy(mot_cle, ptr + 1);
                strtok(mot_cle, ".");
                if (!recette_existe(mot_cle)) {
                    strcpy(liste_de_mot_cle[num_mot_cle], mot_cle);
                    num_mot_cle++;

                    printf("-%s \n", mot_cle);
                }

            }
        }
        closedir(dir);
    }
};

bool recette_existe(char mot_cle_saisir[]) {
    bool ver = false;

    for (int i = 0; i < num_mot_cle; i++) {
        if (strcmp(mot_cle_saisir, liste_de_mot_cle[i]) == 0) {
            ver = true;
            break;
        }
    }
    return ver;
}


void Afficher_recette_par_mot_cle(char mot_cle_saisir[]) {

    DIR *dir;
    struct dirent *ent;
    char path[100] = "data/recettes/";

    char liste_de_recette[100][100];
    int num_recette = 0;

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".txt")) {

                char mot_cle[100];
                char *ptr = strrchr(ent->d_name, '_');
                strcpy(mot_cle, ptr + 1);
                strtok(mot_cle, ".");

                char *result = strstr(mot_cle, mot_cle_saisir);

                if (result != NULL) {
                    strcpy(liste_de_recette[num_recette], ent->d_name);
                    num_recette++;
                }

            }
        }
        closedir(dir);
    }

    printf("Il y a %d recette(s) avec cet ingrediant (%s) , Veuillez choisir une recette : \n", num_recette,
           mot_cle_saisir);

    for (int i = 0; i < num_recette; i++) {
        char *token, *saveptr;
        char name[100];
        char recette[100];
        strcpy(recette, liste_de_recette[i]);

        token = strtok_r(recette, "_", &saveptr);
        token = strtok_r(NULL, "_", &saveptr);
        strcpy(name, token);

        printf("%d-%s \n", i + 1, name);
    }

    int num;
    do {
        printf("\nEntrer le numéro de la recette\n");
        scanf("%d", &num);
    } while ((num < 1) || (num > num_recette));


    char recette_path[100];
    sprintf(recette_path, "%s%s", path, liste_de_recette[num - 1]);

    lire_fichier_mot_cle(recette_path);

}