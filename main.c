#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTURES

typedef struct MenuItem {
    char type[15];
    char nom[100];
    float prix;
    int stock;
} MenuItem;

typedef struct Restaurant {
    char nom[100];
    int count;
    MenuItem items[15];
} Restaurant;

typedef struct Commande {
    char nomResto[100];
    int ncommande;
    float total;
    struct Commande *next;
} Commande;

void menuClient(Restaurant restaurants[], int nb_restos) {

}

void menuAdmin() {
    
    int choix = -1;

    while (choix != 0) {
        printf("\n--- PANEL ADMINISTRATEUR ---\n");
        printf("1 - Servir la prochaine commande\n");
        printf("2 - Voir le nombre total de commande servies\n");
        printf("3 - Voir le montant total des ventes\n");
        printf("0 - Retour menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            //mettre la fonction qui sert la commande
            printf("Service)\n");
        }
        //Mettre les fonctions pour voir le nombre de commande
        else if (choix == 2) {
            printf("Affichage des commandes\n");
        }
        //Mettre les fonctions pour voir le nombre de vente
        else if (choix == 3) {
            printf("Affichage du montant total des ventes\n");
        }
        else if (choix != 0) {
            printf("Mauvaise saisie\n");
        }
    }
}


//MAIN
int main() {


    //LECTURE CSV
    Restaurant restaurants[4];
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

        if (choixMenu == 1) {
            menuClient(restaurants, nb_restos);
        }
        else if (choixMenu == 2) {
            printf("\nMot de passe :");
            scanf("%s", &mdp);
            if (strcmp(mdp, "admin") == 0) {
            menuAdmin();
            }
            else {
                printf("Mauvais mot de passe, retour au menu principal");
            }
        }
        else if (choixMenu == 0) {
            printf("Au revoir !\n");
        }
        else {
            printf("Choix invalide.\n");
        }
    }

    return 0;
}


