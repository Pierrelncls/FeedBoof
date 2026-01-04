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
    MenuItem items[15];
} Restaurant;

typedef struct Commande {
    char nomResto[100];
    int ncommande;
    float total;
    struct Commande *next;
} Commande;

void menuClient(Restaurant restaurants[], int nb_restos);

void menuAdmin(void);

#endif