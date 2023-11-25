#include <stdio.h>
#include <string.h>
#include "user.h"

int main()
{
int totalUsers, nbHomme, nbFemme;
    user u1 = {12709784, "hamzaoui", "aziz", "medecin", "homme", 22}, u2 = {18057489, "taleb", "mansour", "infirmier", "H", 23}, u3;
    int x = ajouter("user.txt", u1);

   /* int y = modifier("user.txt", 12709784, u2);

    if (y == 1)
        printf("\nModification de l'utilisateur avec succès");
    else
        printf("\nÉchec Modification");

    int z = supprimer("user.txt", 12709784);

    if (z == 1)
        printf("\nSuppression de l'utilisateur avec succès");
    else
        printf("\nÉchec Suppression");

    u3 = chercher("user.txt", 12100548);

    if (u3.id == -1)
        printf("introuvable");*/
 userRole("user.txt","infirmier");
 
    chercherPourcentage("user.txt", &totalUsers, &nbHomme, &nbFemme);
    printf("Pourcentage d'hommes: %.2f%%\n", (float)nbHomme / totalUsers * 100);
    printf("Pourcentage de femmes: %.2f%%\n", (float)nbFemme / totalUsers * 100);


    return 0;
}

