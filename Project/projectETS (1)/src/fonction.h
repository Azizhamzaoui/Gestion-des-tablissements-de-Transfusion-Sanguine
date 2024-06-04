#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>
#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdbool.h>

typedef struct {
        char ETS[50];
        int jour;
        int mois;
        int annee;    
} RDV;

typedef struct 
{
int j;
int m;
int a;
}date;

typedef struct
{
char nom[20];
char prenom[20];
char cin[20];
char n_telephone[20];
char lieu[20];
date date_naissance;
char sexe[20];
char enceinte[20];
char tatouage[20];
char maladies[20];
char traitement[20];

}donneur;

void MT_ajouter(donneur u, char *fname);
void MT_afficher(GtkWidget *liste, char *fname);
void MT_supprimer(donneur d, char *fname);
void MT_modifier(donneur u, char *fname);
donneur MT_chercher(char *cin, char *fname);


int MT_listeRDV(char nomFichier[], char ETS[], int jour, int mois, int annee);
int MT_nbETS(char nomFichier[]);
float MT_moyRDV_ETS(char nomFichier[], int jour, int mois, int annee);

#endif
