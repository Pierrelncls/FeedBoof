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

//FONCTIONS PROFILS
void menuClient(Restaurant restaurants[], int nb_restos) {
    int choixResto = -1;
    
    //Choix du resto
    printf("\n--- CHOIX DU RESTAURANT ---\n");
    for (int i = 0; i < nb_restos; i++) {
        printf("%d. %s\n", i + 1, restaurants[i].nom);
    }
    printf("Votre choix (0 pour annuler) : ");
    scanf("%d", &choixResto);

    //sortie si mauvaise saisie
    if (choixResto <= 0 || choixResto > nb_restos) {
        return; 
    }

    int indexR = choixResto - 1;
    char nomRestoChoisi[100];
    strcpy(nomRestoChoisi, restaurants[indexR].nom);

    //Boucle pour commander des plats
    int choixPlat = -1;
    float totalCommande = 0.0;

    while (choixPlat != 0) {
        printf("\n--- MENU : %s ---\n", restaurants[indexR].nom);
        
        // Affichage des plats
        for (int i = 0; i < restaurants[indexR].count; i++) {
            printf("%d. %s (%.2f €) - Stock: %d\n", 
                   i + 1, 
                   restaurants[indexR].items[i].nom, 
                   restaurants[indexR].items[i].prix,
                   restaurants[indexR].items[i].stock);
        }
        printf("0 - Valider et terminer la commande\n");
        printf("Choix du plat : ");
        scanf("%d", &choixPlat);

        //traitement du choix
        if (choixPlat > 0 && choixPlat <= restaurants[indexR].count) {
            int indexP = choixPlat - 1;
            
            // Verif stock
            if (restaurants[indexR].items[indexP].stock == 0) {
                printf("=> Plus de stocks\n");
            } 
            else {
                totalCommande = totalCommande + restaurants[indexR].items[indexP].prix;
                
                //baisse le stock sauf -1
                if (restaurants[indexR].items[indexP].stock > 0) {
                    restaurants[indexR].items[indexP].stock = restaurants[indexR].items[indexP].stock - 1;
                }
                printf("=> %s ajoute - Total provisoire : %.2f €\n", restaurants[indexR].items[indexP].nom, totalCommande);
            }
        }
    }

    // Validation finale
    if (totalCommande > 0) {
        printf("\nCommande validee pour le restaurant %s - Montant total : %.2f €\n", nomRestoChoisi, totalCommande);
        //ajouter la fontion de l'ajout de commande
    }
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

        switch (choix) {
            case 1:
                //mettre la fonction qui sert la commande
                printf("Service)\n");
                break;
            case 2:
                printf("Affichage des commandes\n");
                break;
            case 3:
                printf("Affichage du montant total des ventes\n");
                break;
            default:
                printf("Mauvaise saisie\n");;
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


