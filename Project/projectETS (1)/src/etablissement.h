#ifndef ETABLISSEMENT_H_INCLUDED
#define ETABLISSEMENT_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>
#include<stdbool.h>
//youssef 
typedef struct
{
    char id[50];
    char responsable[50];
    char region[50];
    char adresse[50];
    char capacite[50];
    char temps_travail[50];
}etablissement;

char YRajouter(char *, etablissement );
char YRmodifier( char *, etablissement );
char YRsupprimer(char *, etablissement );
etablissement YRchercher(char *, char);
void YRETSParRegion(const char *search_role, GtkWidget *treeview);
void YRETSTrieCapacite(char *);

void YRafficher_etablissement(GtkWidget *liste);
  //ETABLISSEMENT_H_INCLUDED
/////////////////////////////////////////////////////////////////

//aziz
typedef struct
{
char cin [100];
char nom[100];
char prenom[100];
char role[100];
char sexe[100];
char age[100];
}user;
void AHajouter_user(user u);
void AHafficher_user(GtkWidget *liste);
void AHsupprimer_user(user u);
void calculate_male_percentage(int *totalUsers, float *malePercentage);
void calculate_female_percentage(int *totalUsers, float *femalePercentage);
void rechercher_user(const char *search_term, GtkWidget *treeview);
void rechercher_par_role(const char *search_role, GtkWidget *treeview);

///////////////////////////////////////(hna tzid les fonction mteek elli fl .h o structure )








//hadhemi

#define EIDD 0
#define ENOMCOMPLET 1
#define ETYPE 2
#define ENATURE 3
#define EQUANTITE 4
#define EJOUR 5
#define EMOIS 6
#define EANNEE 7

typedef struct {
    char idd[30];
    char nomcomplet[30];
    char type[30];  
    char nature[20];
    float quantite;
    int jour;
    int mois;
    int annee;
} don;

int ajouter(don d);
void afficher(GtkWidget *liste);
void modifier(char *filename, char *idd, don d2);
void vider(GtkWidget *liste);
void supprimer_par_id(char *filename, char *idd);
void supprimer(don d);
don rechercher(char *filename, int idd_rechercher);
float quantite_type(char *filename, char type[30]);




//oumayma
typedef struct
{
	
	char heure_RDV[50];
	char lieu[50];
	char id[50];
	int jours;
	int moiis;
	char anneee[50];
}rdv;

int OGajouter(char *, rdv );
int OGsupprimer(char *, rdv );
void Gafficher(GtkWidget *liste);



#endif

























































































































