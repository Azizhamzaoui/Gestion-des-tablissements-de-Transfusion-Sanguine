#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <stdio.h>
#include <string.h>
typedef struct
{
 int id;
char nom[20];
char prenom[20];
char role[20];
char sexe[20];
int age;
}user;
int ajouter(char *filename, user u);
int modifier(char *filename, int id, user nouv);
int supprimer(char *filename, int id);
user chercher(char *filename, int id);
void userRole(char *filename,char role[20]);
void chercherPourcentage(char *filename, int *totalUsers, int *nbHomme, int *nbFemme);
#endif
