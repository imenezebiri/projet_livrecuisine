#include <stdio.h>
#include <stdbool.h>
#include "afficher_recette_par_type.h"
#include "afficher_recette_par_mot_cle.h"
#include "afficher_recette_par_budget.h"
#include "afficher_recette_favoris.h"


/*Fonction retour au menu*/
bool Retour_menu() {
    char r = 'X';
    while ((r != 'O') & (r != 'N')) {
        printf("\nVoulez-vous continuer? 0/N\n");
        scanf(" %c", &r);
    };
    return r == 'N';
}


int main() {
    char Mot_cle[20];
    int choix = -1, num, type, budget, numfav;
    bool is_retour_menu;

    do {
        /* Présentation du menu principale*/
        printf("\n************ Livre de Cuisine Numérique ***********\n");
        printf("\t1.Liste des noms de recettes \n");
        printf("\t2.Liste trié par mots clés  \n");
        printf("\t3.Liste trié par budget\n");
        printf("\t4.Ajouter une recette en favoris\n");
        printf("\t5.Afficher les recettes en favoris\n");
        printf("\t6.Supprimer une recette de la liste des favoris \n");
        printf("\t0.Quitter");
        printf("\n***************************************************\n");
        printf("\nEntrer votre choix : \n");
        scanf("%d", &choix);

        if (choix == 1) {
            do {
                printf("Quelle type de recette recherchez-vous ? \n"
                       "1.Recette gatronomique\n"
                       "2.Recette bon marché\n"
                       "3.Rectte de grand-mère\n");

                scanf("%d", &type);
            } while (type > 3 || type <1);

            Afficher_recette_list_par_type(type);
            is_retour_menu = Retour_menu();

            if (is_retour_menu== false) {
                int max_num_recette = num_de_recette_par_type();
                do {
                    printf("\nEntrer le numéro de la recette\n");
                    scanf("%d", &num);
                } while ((num < 1) || (num > max_num_recette));

                Afficher_recette_par_type(num);
            }
        }

        if (choix == 2) {
            Afficher_list_mot_cle();

            do {
                scanf("%s", Mot_cle);
                if (!recette_existe(Mot_cle)) {
                    printf("Vous n'avez pas saisi um ingrédiant dans la liste. Recommmencez !\n");
                }
            } while (!recette_existe(Mot_cle));

            is_retour_menu = Retour_menu();
            Afficher_recette_par_mot_cle(Mot_cle);
        }
        if (choix == 3) {
            printf("Quel est votre budget ?\n");
            scanf("%d", &budget);

            Afficher_list_recette_par_budget(budget);

            int max_num_recette = num_de_recette_par_budget();

            if (max_num_recette > 0) {
                do {
                    printf("\nEntrer le numéro de la recette\n");
                    scanf("%d", &num);
                } while ((num < 1) || (num > max_num_recette));

                is_retour_menu = Retour_menu();

                Afficher_recette_par_budget(num);
            } else {
                printf("il n'y a pas de recette disponible avec votre budget\n");
            }
        }
        if (choix == 4) {
            Choisir_list_recette_favoris();
        }
        if (choix == 5) {
            int favoris_num = Afficher_list_recette_favoris(false);

            if (favoris_num == 0) {
                printf("Il n'y a pas de recette enregistrée dans la liste des favoris \n");
            } else {
                is_retour_menu = Retour_menu();
                Afficher_recette_details(favoris_num);
            }

        }
        if (choix == 6) {
            int favoris_num = Afficher_list_recette_favoris(true);
            if (favoris_num == 0) {
                printf("Il n'y a pas de recette enregistrée dans la liste des favoris \n");
            } else {
                is_retour_menu = Retour_menu();
                supprimer_recette_favoris(favoris_num);
            }
        }
    } while (choix != 0);

    return 0;
}