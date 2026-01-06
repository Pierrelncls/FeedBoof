#ifndef FONCTIONS
#define FONCTIONS

typedef struct MenuItem {
    char type[15];
    char nom[100];
    float prix;
    int stock;
} MenuItem;

typedef struct Restaurant {
    char nom[100];
    int count;
    float recettes;
    MenuItem items[15];
} Restaurant;

void menuClient(Restaurant restaurants[], int nb_restos, Queue *Commandes);

void menuAdmin(Queue *Commandes, int commandes_servies, Restaurant restaurants[], int nb_restos);

#endif