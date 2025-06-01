cmake_minimum_required(VERSION 3.23)
project(lyna_project C)
# Copy data files to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

set(CMAKE_C_STANDARD 99)

add_executable(lyna_project main.c
        afficher_recette_par_type.h afficher_recette_par_type.c
        afficher_recette_par_mot_cle.c afficher_recette_par_mot_cle.h
        afficher_recette_par_budget.c afficher_recette_par_budget.h
        afficher_recette_favoris.c afficher_recette_favoris.h)
