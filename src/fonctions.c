#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifo.h"

typedef struct MenuItem {
    char type[15];
    char nom[100];
    float prix;
    int stock;
} MenuItem;

typedef struct Restaurant {
    char nom[100];
    int count;
    int recettes; //somme d'argent gagnées par les ventes
    MenuItem items[15];
} Restaurant;


//FONCTIONS PROFILS
void menuClient(Restaurant restaurants[], int nb_restos, Queue *Commandes) {
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
        printf("DEBUG : indexR=%d, count=%d\n", indexR, restaurants[indexR].count);
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
                //Ajouter la commande à la liste totale

                totalCommande = totalCommande + restaurants[indexR].items[indexP].prix;
                
                //baisse le stock sauf -1
                if (restaurants[indexR].items[indexP].stock > 0) {
                    restaurants[indexR].items[indexP].stock = restaurants[indexR].items[indexP].stock - 1;
                }
                printf("=> %s ajoute - Total provisoire : %.2f €\n", restaurants[indexR].items[indexP].nom, totalCommande);
            }
        }
        enqueue(Commandes, indexR,totalCommande );
    }

    // Validation finale
    if (totalCommande > 0) {
        printf("\nCommande validee pour le restaurant %s - Montant total : %.2f €\n", nomRestoChoisi, totalCommande);
        //ajouter la fontion de l'ajout de commande
    }
}



void menuAdmin(Queue *Commandes, int *commandes_servies, Restaurant restaurants[]) {
    
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
                dequeue(Commandes);
                commandes_servies+=1;

                printf("Service)\n");
                break;
            case 2:
                printf("Affichage des commandes\n");
                break;
            case 3:
                printf("Affichage du montant total des ventes\n");
                break;
            default:
                printf("Mauvaise saisie\n");
        }
    }
}