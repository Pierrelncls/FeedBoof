# FeedBoof (Projet NF06 UTT A25)
FeedBoof est un logiciel en ligne de commandes permettant de gérer des commandes de plusieurs articles dans plusieurs restaurants, pour plus d'informations consultez la [notice](notice.pdf).
## Instructions de compilation
Prérequis:
- shell unix
- gcc

Placez vous dans le dossier avec un terminal unix et lancez la commande suivante: <br>
`gcc -Isrc src/main.c src/fifo.c src/fonctions.c -o main` \
Puis lancez avec: \
`./main`
## Roadmap ([Consignes](consignes.pdf))
- [x] Créer les fichiers restau avec les menus
- [x] Structures
- [x] Profil Client
- [x] Profil Admin
- [x] File d’attente
- [x] Finalisation de l'interface en ligne de commande.
