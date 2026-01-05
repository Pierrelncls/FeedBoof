#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifo.h"
#include "fonctions.h"


//MAIN
int main() {

    //LECTURE CSV
    Restaurant restaurants[4];

    // Définir la liste des commandes
    Queue Commandes; 
    initqueue(&Commandes);
    int commandes_servies = 0;

    int nb_restos = 0;

    FILE *file = fopen("restaurants.csv", "r");
    if (file == NULL) {
        printf("Echec de l'ouverture du fichier.\n");
        exit(1);
    }

    char ligne[200];

    //Lecture ligne par ligne
    while (fgets(ligne, 200, file) != NULL) {
        
        ligne[strcspn(ligne, "\n")] = 0;

        //Si pas virgule, c'est un resto
        if (strchr(ligne, ',') == NULL) {
            strcpy(restaurants[nb_restos].nom, ligne);
            restaurants[nb_restos].count = 0; //Initialisation du compteur de plats
            nb_restos++; 
        } 
        else {
            //Si virgule, c'est un plat
            int index_resto = nb_restos - 1; //Le resto actuel est le dernier
            int index_plat = restaurants[index_resto].count;

            //Coupe la ligne aux virgules
            char *morceau = strtok(ligne, ","); 
            strcpy(restaurants[index_resto].items[index_plat].type, morceau);

            morceau = strtok(NULL, ",");
            if(morceau[0] == ' ') morceau++; 
            strcpy(restaurants[index_resto].items[index_plat].nom, morceau);

            morceau = strtok(NULL, ",");
            //convertion de chaine en float
            restaurants[index_resto].items[index_plat].prix = atof(morceau); 

            morceau = strtok(NULL, ",");
            //convertion de chaine en int
            restaurants[index_resto].items[index_plat].stock = atoi(morceau);

            restaurants[index_resto].count++;
        }
    }

    fclose(file);

    //INTERFACE
    int choixMenu = -1;
    char mdp[20];

    while (choixMenu != 0) {
        printf("\n=== GESTION RESTAURANT ===\n");
        printf("1 - Mode CLIENT\n");
        printf("2 - Mode ADMIN\n");
        printf("0 - QUITTER\n");
        printf("Votre choix : ");
        scanf("%d", &choixMenu);


        switch (choixMenu) {
            case 0: //Quitter
                printf("Au revoir !\n");
                break;
            case 1: //compte client
                menuClient(restaurants, 4, &Commandes);
                break;
            case 2: //compte admin
                printf("\nMot de passe : ");
                scanf("%s", &mdp);
                if (strcmp(mdp, "admin") == 0) {
                menuAdmin(&Commandes, commandes_servies, restaurants, 4);
                }
                else {
                    printf("Mauvais mot de passe, retour au menu principal");
                }
                break;
            default: //saisie inconnue
                printf("Choix invalide.\n");
        }
    }

    return 0;
}


