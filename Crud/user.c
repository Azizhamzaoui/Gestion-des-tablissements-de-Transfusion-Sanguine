#include "user.h"

int ajouter(char *filename, user u)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %s %s %d\n", u.id, u.nom, u.prenom, u.role, u.sexe, u.age);
        fclose(f);
        return 1;
    }
    else
        return 0;
}

int modifier(char *filename, int id, user nouv)
{
    int tr = 0;
    user u;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("user2.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %s %s %d\n", &u.id, u.nom, u.prenom, u.role, u.sexe, &u.age) != EOF)
        {
            if (u.id == id)
            {
                fprintf(f2, "%d %s %s %s %s %d\n", u.id, u.nom, u.prenom, u.role, u.sexe, u.age);
                tr = 1;
            }
            else
                fprintf(f2, "%d %s %s %s %s %d\n", u.id, u.nom, u.prenom, u.role, u.sexe, u.age);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("user2.txt", filename);
    return tr;
}

int supprimer(char *filename, int id)
{
    int tr = 0;
    user u;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("user2.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %s %s %d\n", &u.id, u.nom, u.prenom, u.role, u.sexe, &u.age) != EOF)
        {
            if (u.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %s %d\n", u.id, u.nom, u.prenom, u.role, u.sexe, u.age);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("user2.txt", filename);
    return tr;
}

user chercher(char *filename, int id)
{
    user u;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (tr == 0 && fscanf(f, "%d %s %s %s %s %d\n", &u.id, u.nom, u.prenom, u.role, u.sexe, &u.age) != EOF)
        {
            if (u.id == id)
                tr = 1;
        }
    }
    fclose(f);
    if (tr == 0)
        u.id = -1;
    return u;
}
void userRole(char *filename,char role[])
{
    user u;
    FILE *f = fopen(filename,"r");
    FILE *f2 = fopen("userROLE.txt" , "w");
    if (f == NULL || f2 == NULL)
      {printf("Erreur de l'ouverture du fichier");}
while (fscanf(f,"%d %s %s %s %s%d\n",&u.id,u.nom,u.prenom,u.role,u.sexe,&u.age)!=EOF) {
     if (strcmp(role,u.role)== 0)
   {fprintf(f2,"%d %s %s %s %s %d\n",u.id,u.nom,u.prenom,u.role,u.sexe,u.age);
         }
     }

        fclose(f);
        fclose(f2);
       }
void chercherPourcentage(char *filename, int *totalUsers, int *nbHomme, int *nbFemme) {

    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printf("Erreur de l'ouverture du fichier");
        return;
    }


    *totalUsers = 0;
    *nbHomme = 0;
    *nbFemme = 0;


    user u;
    while (fscanf(f, "%d %s %s %s %s %d", &u.id, u.nom, u.prenom, u.role, u.sexe, &u.age) != EOF) {
        (*totalUsers)++;
        if (strcmp(u.sexe, "homme") == 0) {
            (*nbHomme)++;
        } else if (strcmp(u.sexe, "femme") == 0) {
            (*nbFemme)++;
        }
    }


    fclose(f);
}
