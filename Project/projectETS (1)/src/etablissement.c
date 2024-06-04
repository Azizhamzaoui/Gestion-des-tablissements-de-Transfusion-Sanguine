#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etablissement.h"
#include <gtk/gtk.h> 
//youssef

char YRajouter(char *filename, etablissement e) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s %s %s\n", e.id, e.responsable, e.region, e.adresse, e.capacite, e.temps_travail);
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char YRmodifier(char *filename, etablissement e) {
    int tr = 0;
    etablissement nouv;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %s %s\n", nouv.id, nouv.responsable, nouv.region, nouv.adresse, nouv.capacite, nouv.temps_travail) != EOF) {
            if (strcmp(e.id , nouv.id) != 0 || strcmp(e.responsable , nouv.responsable) != 0 || strcmp(e.region , nouv.region) != 0 || strcmp(e.adresse , nouv.adresse) != 0 || strcmp(e.capacite , nouv.capacite) != 0 || strcmp(e.temps_travail , nouv.temps_travail) != 0  ) {
                fprintf(f2, "%s %s %s %s %s %s\n", nouv.id, nouv.responsable, nouv.region, nouv.adresse, nouv.capacite, nouv.temps_travail);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %s %s\n", nouv.id, nouv.responsable, nouv.region, nouv.adresse, nouv.capacite , nouv.temps_travail);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char YRsupprimer(char *filename, etablissement e) {

etablissement nouv;
  FILE *f, *g;
  f = fopen(filename, "r");
  g = fopen("nouv.txt", "w");

  if (f == NULL || g == NULL)
  {
    perror("Error opening file for reading or writing");
    return;
  }
  int tr = 0;
  while (fscanf(f, "%s %s %s %s %s %s\n", nouv.id, nouv.responsable, nouv.region, nouv.adresse, nouv.capacite, nouv.temps_travail) ==6)
  {
    if (strcmp(e.id , nouv.id) != 0 || strcmp(e.responsable , nouv.responsable) != 0 || strcmp(e.region , nouv.region) != 0 || strcmp(e.adresse , nouv.adresse) != 0 || strcmp(e.capacite , nouv.capacite) != 0 || strcmp(e.temps_travail , nouv.temps_travail) != 0)
    {
      tr = 1;
    }
    else
    {
      
fprintf(g, "%s %s %s %s %s %s\n", nouv.id, nouv.responsable, nouv.region, nouv.adresse, nouv.capacite , nouv.temps_travail);
    }
  }

  fclose(f);
  fclose(g);

  if (!tr)
  {
    printf("ETS not found for deletion.\n");
    remove("nouv.txt");
  }
  else
  {

    remove(filename);
    rename("nouv.txt", filename);
  }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
etablissement YRchercher(char *filename, char reg) {
    etablissement e;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (tr == 0 && fscanf(f, "%s %s %s %s %s %s\n", e.id, e.responsable, e.region, e.adresse, e.capacite, e.temps_travail) != EOF) {
            if (strcmp(e.region , reg) == 0) {
                printf("%s %s %s %s %s %s\n", e.id, e.responsable, e.region, e.adresse, e.capacite, e.temps_travail);
                tr = 1;
            }
        }
    }
    fclose(f);
    //if (tr == 0) {
    //    e.id = -1;
    //}
    return e;
}
//***************************************************************************************************************************************************************************************************
enum
{
	EID,
	ERESPONSABLE,
	EREGION,
	EADRESSE,
	ECAPACITE,
	ETEMPSTRAVAIL,
	COLUMNS
};

void YRETSParRegion(const char *search_region, GtkWidget *treeview) {

    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    gboolean valid;
    gchar *id, *responsable, *region, *adresse, *capacite, *temps_travail;
    GList *selected_rows = NULL; 

    valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid)
    {
        gtk_tree_model_get(model, &iter, EID, &id, ERESPONSABLE, &responsable, EREGION, &region, EADRESSE, &adresse, ECAPACITE, &capacite, ETEMPSTRAVAIL, &temps_travail, -1);

	
        if (strcmp(region, search_region) == 0)
        {
            
            GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
            selected_rows = g_list_append(selected_rows, path);
        }

       
        g_free(id);
        g_free(responsable);
        g_free(region);
        g_free(adresse);
        g_free(capacite);
        g_free(temps_travail);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    // Select all rows stored in the list
    gtk_tree_selection_unselect_all(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)));
    GList *iter_list = selected_rows;
    while (iter_list != NULL)
    {
        GtkTreePath *path = iter_list->data;
        gtk_tree_selection_select_path(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)), path);
        iter_list = g_list_next(iter_list);
    }

    // Free allocated memory for the list
    g_list_free_full(selected_rows, (GDestroyNotify)gtk_tree_path_free);
}
//**********************************************************************************************************************************************************************************

void YRtrierParCapacite(etablissement tab[], int taille) {
    int i, j;
    etablissement temp;

    for (i = 0; i < taille - 1; i++) {
        for (j = 0; j < taille - i - 1; j++) {
            int capacite1 = atoi(tab[j].capacite);
            int capacite2 = atoi(tab[j + 1].capacite);

            if (capacite1 > capacite2) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void YRETSTrieCapacite(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    etablissement tabETS[100];
    int nombreETS = 0;

    while (fscanf(f, "%s %s %s %s %s %s\n",tabETS[nombreETS].id,tabETS[nombreETS].responsable,tabETS[nombreETS].region,tabETS[nombreETS].adresse, tabETS[nombreETS].capacite,tabETS[nombreETS].temps_travail) != EOF) {
        nombreETS++;
    }

    fclose(f);

    YRtrierParCapacite(tabETS, nombreETS);

    FILE *fResultat = fopen("resultat_tri_capacite.txt", "w");
    if (fResultat == NULL) {
        printf("Erreur lors de l'ouverture du fichier de resultat.\n");
        return;
    }

    for (int i=0;i<nombreETS;i++) {
        fprintf(fResultat, "%s %s %s %s %s %s\n",tabETS[i].id,tabETS[i].responsable,tabETS[i].region,tabETS[i].adresse,tabETS[i].capacite, tabETS[i].temps_travail);
    }

    fclose(fResultat);

    printf("Fichier trie par capacite sauvegarde avec succes.\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YRafficher_etablissement(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	
	etablissement e;

	 char id[50];
    char responsable[50];
    char region[50];
    char adresse[50];
    char capacite;
    char temps_travail[50];

	if (store==NULL)
	{

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID, NULL); 
	gtk_tree_view_append_column (GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("responsable", renderer, "text",ERESPONSABLE, NULL); 
	gtk_tree_view_append_column (GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("region", renderer, "text",EREGION, NULL); 
	gtk_tree_view_append_column (GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text",EADRESSE, NULL); 
	gtk_tree_view_append_column (GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("capacite", renderer, "text",ECAPACITE, NULL); 
	gtk_tree_view_append_column (GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("temps_travail", renderer, "text",ETEMPSTRAVAIL, NULL); 
	gtk_tree_view_append_column (GTK_TREE_VIEW(liste), column); 
 	}
	store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);

	FILE *f = fopen("etablissement.txt", "r");
	if(f==NULL)
	{
	    printf("Error opening file for reading.\n");
	    return;
	}
	while(fscanf(f, "%s %s %s %s %s %s\n", e.id, e.responsable, e.region, e.adresse, e.capacite, e.temps_travail) == 6)
	{
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, EID, e.id, ERESPONSABLE, e.responsable, EREGION, e.region, EADRESSE, e.adresse, ECAPACITE, e.capacite, ETEMPSTRAVAIL, e.temps_travail, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);

	}

	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//aziz

enum
{
  ECIN,
  ENOM,
  EPRENOM,
  EROLE,
  ESEXE,
  EAGE,
  //COLUMNS(hedhy aamloha commentaire khtr mawjuda lfog)
};

void AHajouter_user(user u)
{GtkWidget *pQuestion;
gpointer user_data;

  FILE *f;
  f = fopen("users.txt", "a+");
  if (f != NULL)
  {
    fprintf(f, "%s %s %s %s %s %s\n", u.cin, u.nom, u.prenom, u.role, u.sexe, u.age);
    fclose(f);
pQuestion=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"User ajouté avec succès !");
switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
{
case GTK_RESPONSE_OK:
gtk_widget_destroy(pQuestion);
break;
}
  }

 
}

void AHafficher_user(GtkWidget *liste)
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
  user u;

  if (store == NULL)
  {
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", ECIN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", EPRENOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("role", renderer, "text", EROLE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", ESEXE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("age", renderer, "text", EAGE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
  }

  store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING);
  FILE *f = fopen("users.txt", "r");

  if (f == NULL)
  {
    
    printf("Error opening file for reading.\n");
    return;
  }

  while (fscanf(f, "%s %s %s %s %s %s\n", u.cin, u.nom, u.prenom, u.role, u.sexe, u.age) == 6)
  {
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, ECIN, u.cin, ENOM, u.nom, EPRENOM, u.prenom, EROLE, u.role, ESEXE, u.sexe, EAGE, u.age, -1);
  }

  fclose(f);
  gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
  g_object_unref(store);
}

void AHsupprimer_user(user u)
{
  user u2;
  FILE *f, *g;
  f = fopen("users.txt", "r");
  g = fopen("users2.txt", "w");

  if (f == NULL || g == NULL)
  {
    perror("Error opening file for reading or writing");
    return;
  }

  int userFound = 0;

  while (fscanf(f, "%s %s %s %s %s %s\n", u2.cin, u2.nom, u2.prenom, u2.role, u2.sexe, u2.age) == 6)
  {
    if (strcmp(u.cin, u2.cin) != 0 || strcmp(u.nom, u2.nom) != 0 || strcmp(u.prenom, u2.prenom) != 0 || strcmp(u.role, u2.role) != 0 || strcmp(u.sexe, u2.sexe) != 0 || strcmp(u.age, u2.age) != 0)
    {
      fprintf(g, "%s %s %s %s %s %s\n", u2.cin, u2.nom, u2.prenom, u2.role, u2.sexe, u2.age);
    }
    else
    {
      userFound = 1; 
    }
  }

  fclose(f);
  fclose(g);

  if (!userFound)
  {
    printf("User not found for deletion.\n");
    remove("users2.txt"); 
  }
  else
  {
    remove("users.txt");
    rename("users2.txt", "users.txt");
  }
}


static const char *roles[] = {"Responsable ETS", "Infirmier", "Médecin biologiste","Donneur"};

int get_role_index(const char *role) {
    for (int i = 0; i < sizeof(roles) / sizeof(roles[0]); ++i) {
        if (strcmp(roles[i], role) == 0) {
            return i;
        }
    }
    return -1;
}
void calculate_male_percentage(int *totalUsers, float *malePercentage)
{
 user u3;
    FILE *f = fopen("users.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    *totalUsers = 0;
    int maleCount = 0;
   

    while (fscanf(f, "%*s %*s %*s %*s %s %*s", u3.sexe) == 1)
    {
        (*totalUsers)++;
        if (strcmp(u3.sexe, "H") == 0)
        {
            maleCount++;
        }
    }

    fclose(f);

    if (*totalUsers > 0)
    {
        *malePercentage = (float)maleCount / *totalUsers * 100.0;
    }
    else
    {
        *malePercentage = 0.0;
    }
}
void calculate_female_percentage(int *totalUsers, float *femalePercentage)
{
 user u4;
    FILE *f = fopen("users.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    *totalUsers = 0;
    int femaleCount = 0;
   

    while (fscanf(f, "%*s %*s %*s %*s %s %*s", u4.sexe) == 1)
    {
        (*totalUsers)++;
        if (strcmp(u4.sexe, "F") == 0)
        {
            femaleCount++;
        }
    }

    fclose(f);

    if (*totalUsers > 0)
    {
        *femalePercentage = (float)femaleCount / *totalUsers * 100.0;
    }
    else
    {
        *femalePercentage = 0.0;
    }
}
void rechercher_user(const char *search_term, GtkWidget *treeview)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    gboolean valid;
    gchar *cin, *nom, *prenom, *role, *sexe, *age;

    valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid)
    {
        gtk_tree_model_get(model, &iter, ECIN, &cin, ENOM, &nom, EPRENOM, &prenom, EROLE, &role, ESEXE, &sexe, EAGE, &age, -1);

       
        if (strstr(cin, search_term) != NULL ||
            strstr(nom, search_term) != NULL ||
            strstr(prenom, search_term) != NULL ||
            strstr(role, search_term) != NULL ||
            strstr(sexe, search_term) != NULL ||
            strstr(age, search_term) != NULL)
        {
          
            gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)), &iter);

            
            GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
            gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(treeview), path, NULL, FALSE, 0.5, 0.0);

            
            g_free(cin);
            g_free(nom);
            g_free(prenom);
            g_free(role);
            g_free(sexe);
            g_free(age);

            return; 
        }

        
        g_free(cin);
        g_free(nom);
        g_free(prenom);
        g_free(role);
        g_free(sexe);
        g_free(age);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

   
    g_print("No matching user found.\n");
}
void rechercher_par_role(const char *search_role, GtkWidget *treeview)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    gboolean valid;
    gchar *cin, *nom, *prenom, *role, *sexe, *age;
    GList *selected_rows = NULL; 

    valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid)
    {
        gtk_tree_model_get(model, &iter, ECIN, &cin, ENOM, &nom, EPRENOM, &prenom, EROLE, &role, ESEXE, &sexe, EAGE, &age, -1);

        
        if (strcmp(role, search_role) == 0)
        {
            
            GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
            selected_rows = g_list_append(selected_rows, path);
        }

       
        g_free(cin);
        g_free(nom);
        g_free(prenom);
        g_free(role);
        g_free(sexe);
        g_free(age);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    // Select all rows stored in the list
    gtk_tree_selection_unselect_all(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)));
    GList *iter_list = selected_rows;
    while (iter_list != NULL)
    {
        GtkTreePath *path = iter_list->data;
        gtk_tree_selection_select_path(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)), path);
        iter_list = g_list_next(iter_list);
    }

    // Free allocated memory for the list
    g_list_free_full(selected_rows, (GDestroyNotify)gtk_tree_path_free);
}
///////////////////////////////////////////////////////////////
//(hna thotou l.c mteekokom)


//oumayma

int OGajouter(char *oumayma ,rdv r)
{
int tr = 0;
    FILE * f =fopen("r.txt", "a+");

    if(f!=NULL)
    {

        fprintf(f,"%s %s %s {%d %d %s}\n",r.heure_RDV,r.lieu,r.id,r.jours,r.moiis,r.anneee);
           tr = 1;
        fclose(f); 

    }
return tr;
}

int OGsupprimer(char *oumayma, rdv r)
{
 	rdv nouv;
        int tr = 0;
    
    FILE *f = fopen(oumayma, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %d %d %s\n", nouv.id, nouv.heure_RDV, nouv.lieu, &nouv.jours, &nouv.moiis, nouv.anneee) == 6) {
            if (strcmp(r.id , r.id) != 0 || strcmp(r.heure_RDV , nouv.heure_RDV) != 0 || strcmp(r.lieu , nouv.lieu) != 0 || r.jours != nouv.jours || r.moiis != nouv.moiis || strcmp(r.anneee , nouv.anneee) != 0  ) {
                tr = 1;
            } else { fprintf(f2, "%s %s %s %d %d %s\n", nouv.id, nouv.heure_RDV, nouv.lieu, nouv.jours, nouv.moiis, nouv.anneee);
            	}
        }
    }
    fclose(f);
    fclose(f2);
    remove(oumayma);
    rename("nouv.txt", oumayma);
    return tr;
}

enum
{
	EHEURE_RDV,
	ELIEU,
	EIDENTIFIANT,
	EJOURS,
	EMOIIS,
	EANNEEE,
	//COLUMNS,
};

void Gafficher(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
rdv r;

	char heure_RDV[50];
	char lieu[50];
	char id[50];
	int jours;
	int moiis;
	char anneee[50];
	

	

	if(store==NULL)
	{

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("heure_r", renderer, "text" ,EHEURE_RDV, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("lieu", renderer, "text" ,ELIEU, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text" ,EIDENTIFIANT, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text" ,EJOURS, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text" ,EMOIIS, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text" ,EANNEEE, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column); }
	
	store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_POINTER, G_TYPE_STRING); 
	
	FILE *f=fopen("oumayma.txt", "r");
	if(f==NULL)
	{
		printf("Error opening file for reading.\n");
		return;
	}
	

		while(fscanf(f,"%s %s %s %d %d %s \n",r.heure_RDV,r.lieu,r.id,&r.jours,&r.moiis,r.anneee)!=6)
		{
			gtk_list_store_append (store, &iter);
			gtk_list_store_set (store, &iter, EHEURE_RDV, r.heure_RDV, ELIEU, r.lieu, EIDENTIFIANT, r.id, EJOURS, r.jours, EMOIIS, r.moiis, EANNEEE, r.anneee, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
//hadhemi
int id_existe_deja(const char *idd) {
    FILE *f;
    f = fopen("don.txt", "r");
    
    if (f != NULL) {
        don d;

        while (fscanf(f, "%s %s %s %s %.2f %d %d %d \n", d.idd, d.nomcomplet, d.type, d.nature, &d.jour, &d.mois, &d.annee) != EOF) {
            if (strcmp(idd, d.idd) == 0) {
                fclose(f);
                return 1;  // ID already exists
            }
        }

        fclose(f);
    }

    return 0;  // ID does not exist
}

int ajouter(don d) {
    if (strlen(d.idd) > 0 && strlen(d.nomcomplet) > 0 && strlen(d.type) > 0 && strlen(d.nature) > 0) {
     if (id_existe_deja(d.idd)) {
            return 2;  // ID already exists
        }

        FILE *f;
        f = fopen("don.txt", "a");
        if (f != NULL) {
            fprintf(f, "%s %s %s %s %.2f %d %d %d\n", d.idd, d.nomcomplet, d.type, d.nature, d.quantite, d.jour, d.mois, d.annee);
            fclose(f);
            return 1; // Succès
        } else {
            return -1; // Erreur lors de l'ajout
        }
    } else {
        return 0; // Veuillez remplir tous les champs
    }
}


// Fonction pour afficher les demandes dans un TreeView
void afficher(GtkWidget *liste) {
    don d;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    const int COLUMNS = 8;

    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);

    f = fopen("don.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %f %d %d %d", d.idd, d.nomcomplet, d.type, d.nature, &d.quantite, &d.jour, &d.mois, &d.annee) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDD, d.idd, ENOMCOMPLET, d.nomcomplet, ETYPE, d.type, ENATURE, d.nature, EQUANTITE, d.quantite, EJOUR, d.jour, EMOIS, d.mois, EANNEE, d.annee, -1);
        }
        fclose(f);
    }

    // Affichage des colonnes dans le TreeView
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("IDD", renderer, "text", EIDD, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nomcomplet", renderer, "text", ENOMCOMPLET, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", ETYPE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nature", renderer, "text", ENATURE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Quantite", renderer, "text", EQUANTITE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", EJOUR, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", EMOIS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", EANNEE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    // Affichage du modèle dans le TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

void vider(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    const int COLUMNS = 8;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL) {
        store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("IDD", renderer, "text", EIDD, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nomcomplet", renderer, "text", ENOMCOMPLET, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", ETYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nature", renderer, "text", ENATURE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Quantite", renderer, "text", EQUANTITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", EJOUR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", EMOIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", EANNEE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    }

    gtk_list_store_clear(store);
}

void modifier(char *filename, char *idd, don d2) {
    don d;
    FILE *f = fopen("don.txt", "r");
    FILE *f2 = fopen("don2.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, " %s %s %s %s %f %d %d %d ", d.idd, d.nomcomplet, d.type, d.nature, &d.quantite, &d.jour, &d.mois, &d.annee) != EOF) {
            if (strcmp(d.idd, idd) == 0) {
                fprintf(f2, " %s %s %s %s %.2f %d %d %d \n", d2.idd, d2.nomcomplet, d2.type, d2.nature, d2.quantite, d2.jour, d2.mois, d2.annee);
            } else {
                fprintf(f2, " %s %s %s %s %.2f %d %d %d \n", d.idd, d.nomcomplet, d.type, d.nature, d.quantite, d.jour, d.mois, d.annee);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("don2.txt", filename);
}


    
// Fonction pour supprimer une demande par son ID du fichier
void supprimer_par_id(char *filename, char *idd) {
    don d;
    FILE *f = fopen("don.txt", "r");
    FILE *f2 = fopen("don2.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, " %s %s %s %s %f %d %d %d ", d.idd, d.nomcomplet, d.type, d.nature, &d.quantite, &d.jour, &d.mois, &d.annee) != EOF) {
            if (strcmp(d.idd, idd) != 0) {
                fprintf(f2, " %s %s %s %s %f %d %d %d \n", d.idd, d.nomcomplet, d.type, d.nature, d.quantite, d.jour, d.mois, d.annee);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("don2.txt", filename);
}




void supprimer(don d) {
    char idd[30];
    char nomcomplet[30];
    char type[30];
    char nature[20];
    float quantite;
    int jour;
    int mois;
    int annee;

    FILE *f, *g;
    f = fopen("don.txt", "r");
    g = fopen("don2.txt", "w");

    if (f == NULL || g == NULL) {
        return;
    } else {
        while (fscanf(f, "%s %s %s %s %f %d %d %d", idd, nomcomplet, type, nature, &quantite, &jour, &mois, &annee) != EOF) {
            if (strcmp(d.idd, idd) != 0 || strcmp(d.nomcomplet, nomcomplet) != 0 || strcmp(d.type, type) != 0 || strcmp(d.nature, nature) != 0 ||
                d.quantite != quantite || d.jour != jour || d.mois != mois || d.annee != annee) {
                fprintf(g, "%s %s %s %s %f %d %d %d\n", idd, nomcomplet, type, nature, quantite, jour, mois, annee);
            }
        }
        fclose(f);
        fclose(g);
        remove("don.txt");
        rename("don2.txt", "don.txt");
    }
}




don rechercher(char *filename, int idd_rechercher) {
    don d;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fscanf(f, " %s %s %s %s %f %d %d %d ", d.idd, d.nomcomplet, d.type, d.nature, &d.quantite, &d.jour, &d.mois, &d.annee) != EOF) {
            if (atoi(d.idd) == idd_rechercher) {
                tr = 1;
                break; // On a trouvé, on peut sortir de la boucle
            }
        }
        fclose(f);
    } else {
        // Gestion d'erreur si le fichier ne peut pas être ouvert
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        exit(EXIT_FAILURE);  // Terminer le programme avec un code d'erreur
    }

    if (tr == 0) {
        // Marqueur d'absence, l'ID n'a pas été trouvé
        d.idd[0] = '\0';
        strcpy(d.nomcomplet, "");
        strcpy(d.type, "");
        strcpy(d.nature, "");
        d.quantite = 0.0;
        d.jour = 0;
        d.mois = 0;
        d.annee = 0;
    }
    return d;
}

 /*float quantite_type(char *filename , char type[30]) {
      FILE *f = fopen(filename, "r");
    float quantites = 0.0;
    don d;

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %f %d %d %d\n", d.idd, d.nomcomplet, d.type, d.nature, &d.quantite, &d.jour, &d.mois, &d.annee) != EOF) {
            if (strcmp(d.type, type) == 0 ) {
                quantites += d.quantite;
            }
        }
        fclose(f);
    }

    return quantites;
}*/

float quantite_type(char *filename, char type[30]) {
    FILE *f = fopen(filename, "r");
    float quantites = 0.0;
    don d;

    if (f != NULL) {
        while (fscanf(f, "%29s %29s %29s %19s %f %d %d %d\n", d.idd, d.nomcomplet, d.type, d.nature, &d.quantite, &d.jour, &d.mois, &d.annee) != EOF) {
            if (strcmp(d.type, type) == 0) {
                quantites += d.quantite;
            }
        }
        fclose(f);
    }

    return quantites;
}

    /*char type[4][3] = {"A", "B", "AB", "O"};
    float FLT_max = FLT_MAX;
    float min_quantite = FLT_max;
    char type_min_quantite[4];

    for (int i = 0; i < 4; i++) {
        float quantite = quantite_type(filename, type[i]);
        if (quantite > 0 && quantite< min_quantite) {
            min_quantite = quantite;
            strcpy(type_min_quantite, type[i]);
        }
    }

    if (min_quantite < FLT_max) {
        printf("Le type de sang le plus rare est : '%s' avec une quantité de %.2f ml \n", type_min_quantite, min_quantite);
    } else {
        printf("Aucune demande trouvée.\n");
    }
}*/














