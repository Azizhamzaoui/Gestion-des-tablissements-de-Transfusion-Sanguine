#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include <gtk/gtk.h>
#include <stdbool.h>


////////////////////////////////


enum
{
	NOM,	
	PRENOM,
	CIN,
	N_TELEPHONE,
	LIEU,
	DATE_NAISSANCE,
	SEXE,
	ENCEINTE,
	TATOUAGE,
	MALADIES,
	TRAITEMENT,
	COLUMNS
};



///////////////////////////////




///////////////Ajouuuuuutttttt///////////

void MT_ajouter(donneur u, char *fname){
GtkWidget *pQuestion, *pInfo;
FILE *f;
int b=0;
gpointer user_data;
donneur d;
f=fopen(fname,"a+");
if(f!=NULL)
{	while(fscanf(f,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,&(d.date_naissance.j),&(d.date_naissance.m),&(d.date_naissance.a),d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement)!=EOF)
	{	
		if(strcmp(u.cin,d.cin)==0)
		b++;
	}
	if(b==0){
	fprintf(f,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",u.nom,u.prenom,u.cin,u.n_telephone,u.lieu,u.date_naissance.j,u.date_naissance.m,u.date_naissance.a,u.sexe,u.enceinte,u.tatouage,u.maladies,u.traitement);
	pQuestion=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"donneur ajouté avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pQuestion);
	break;
	}
	}
	if(b!=0){
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"CIN doit etre unique !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	}
	fclose(f); 
}
}


///////////////Afficheerr//////////




void MT_afficher(GtkWidget *liste, char *fname)
{
	donneur d;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	gchar date[30];
	FILE *f;

	store=gtk_tree_view_get_model(liste);
	if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("nom", renderer,"text",NOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" prenom", renderer,"text",PRENOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" cin", renderer,"text",CIN, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_resizable(column,TRUE);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" n_telephone", renderer,"text",N_TELEPHONE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" lieu", renderer,"text",LIEU, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("date_naissance", renderer,"text",DATE_NAISSANCE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("sexe", renderer,"text",SEXE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);
 	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("enceinte", renderer,"text",ENCEINTE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);


	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("tatouage", renderer,"text",TATOUAGE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("maladies", renderer,"text",MALADIES, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("traitement", renderer,"text",TRAITEMENT, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
f=fopen(fname,"r");
if(f!=NULL)

{ f = fopen(fname,"a+");
		while(fscanf(f,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,&d.date_naissance.j,&d.date_naissance.m,&d.date_naissance.a,d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement)!=EOF)
	{

sprintf(date,"%d/%d/%d",d.date_naissance.j,d.date_naissance.m,d.date_naissance.a);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,NOM,d.nom,PRENOM,d.prenom,CIN,d.cin,N_TELEPHONE,d.n_telephone,LIEU,d.lieu,DATE_NAISSANCE,date,SEXE,d.sexe,ENCEINTE,d.enceinte,TATOUAGE,d.tatouage,MALADIES,d.maladies,TRAITEMENT,d.traitement,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}

}






void MT_supprimer(donneur u, char *fname)
{
donneur d;
int a=0;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f!=NULL&&g!=NULL){
	while(fscanf(f,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,&(d.date_naissance.j),&     (d.date_naissance.m),&(d.date_naissance.a),d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement)!=EOF)
	{
		if(strcmp(d.cin,u.cin)!=0)
			fprintf(g,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,d.date_naissance.j,d.date_naissance.m,d.date_naissance.a,d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement);
		else
			a=1;
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,a==1?"donneur supprimé avec succès":"donneur introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}


void MT_modifier(donneur u, char *fname){
donneur d;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,&(d.date_naissance.j),&     (d.date_naissance.m),&(d.date_naissance.a),d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement)!=EOF)
	{
		if(strcmp(d.cin,u.cin)!=0)
			fprintf(g,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,d.date_naissance.j,d.date_naissance.m,d.date_naissance.a,d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement);
		else
			fprintf(g,"%s %s %s %s %s %d %d %d %s %s %s %s %s   \n",u.nom,u.prenom,d.cin,u.n_telephone,u.lieu,u.date_naissance.j,u.date_naissance.m,u.date_naissance.a,u.sexe,u.enceinte,u.tatouage,u.maladies,u.traitement);
		}
	
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}



donneur MT_chercher(char *cin, char *fname){
donneur d, e;
FILE *f;
f=fopen(fname,"r");
if(f!=NULL){
	while(fscanf(f,"%s %s %s %s %s %d %d %d %s %s %s %s %s  \n",d.nom,d.prenom,d.cin,d.n_telephone,d.lieu,&(d.date_naissance.j),&     (d.date_naissance.m),&(d.date_naissance.a),d.sexe,d.enceinte,d.tatouage,d.maladies,d.traitement)!=EOF){
		if(strcmp(d.cin,cin)==0)
			return d;
	}
	fclose(f);
}
strcpy(e.cin,"");
return e;
}





























