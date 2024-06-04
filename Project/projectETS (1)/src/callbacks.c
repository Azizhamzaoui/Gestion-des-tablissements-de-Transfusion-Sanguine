#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include <string.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "etablissement.h"
#include "fonction.h"
#include <stdbool.h>

void on_YRradiobuttonlunven_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    
}

void on_YRradiobutton7_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
   
}

void on_YRcheckbuttonconfirmer_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
  
}

void on_YRbuttoncreer_clicked(GtkWidget *objet, gpointer user_data) {
    etablissement e;
    GtkWidget *YRentryid, *YRentryresponsable, *YRcomboboxregion, *YRentryadresse, *YRspinbuttoncapacite, *YRradiobuttonlunven, *YRradiobutton7, *YRcheckbuttonconfirmer;
    GtkWidget *YRwindowajouterETS;
    GtkWidget *YRtreeviewETS;
    YRwindowajouterETS = lookup_widget(objet, "YRwindowajouterETS");

    YRentryid = lookup_widget(objet, "YRentryid");
    YRentryresponsable = lookup_widget(objet, "YRentryresponsable");
    YRcomboboxregion = lookup_widget(objet, "YRcomboboxregion");
    YRentryadresse = lookup_widget(objet, "YRentryadresse");
    YRspinbuttoncapacite = lookup_widget(objet, "YRspinbuttoncapacite");
    YRradiobuttonlunven = lookup_widget(objet, "YRradiobuttonlunven");

    strcpy(e.id, gtk_entry_get_text(GTK_ENTRY(YRentryid)));
    strcpy(e.responsable, gtk_entry_get_text(GTK_ENTRY(YRentryresponsable)));
    strcpy(e.adresse, gtk_entry_get_text(GTK_ENTRY(YRentryadresse)));
    // combobox
    strcpy(e.region, gtk_combo_box_get_active_text(GTK_COMBO_BOX(YRcomboboxregion)));
    // spinbutton
    int capacite_value = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(YRspinbuttoncapacite));
    sprintf(e.capacite, "%d", capacite_value);
    // radiobutton
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(YRradiobuttonlunven))) {
        strcpy(e.temps_travail, "lundi_vendredi");
    } else {
        strcpy(e.temps_travail, "7_jours");
    }

    YRajouter("etablissement.txt", e);

    //YRtreeviewETS = lookup_widget(YRtreeviewETS, "YRtreeviewETS");
}

void on_YRbuttonafficher_clicked(GtkWidget *objet, gpointer user_data) {
    
    GtkWidget *YRwindowajouterETS;
    GtkWidget *YRwindowtreeview;
    GtkWidget *YRtreeviewETS;

    YRwindowajouterETS = lookup_widget(objet, "YRwindowajouterETS");

    gtk_widget_destroy(YRwindowajouterETS);
    YRwindowtreeview = lookup_widget(objet, "YRwindowtreeview");
    YRwindowtreeview = create_YRwindowtreeview();

    gtk_widget_show(YRwindowtreeview);

    YRtreeviewETS = lookup_widget(YRwindowtreeview, "YRtreeviewETS");
    YRafficher_etablissement(YRtreeviewETS);
}


void on_YRtreeviewETS_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeIter iter;
    gchar *id;
    gchar *responsable;
    gchar *region;
    gchar *adresse;
    gchar *capacite;
    gchar *temps_travail;
    etablissement e;
    GtkWidget *YRtreeviewETS;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &id, 1, &responsable, 2, &region, 3, &adresse, 4, &capacite, 5, &temps_travail, -1);
        strcpy(e.id, id);
        strcpy(e.responsable, responsable);
        strcpy(e.region, region);
        strcpy(e.adresse, adresse);
        strcpy(e.capacite, capacite);
        strcpy(e.temps_travail, temps_travail);

        YRafficher_etablissement(YRtreeviewETS);
    }
}

void on_YRbuttondeconnexion_clicked(GtkWidget       *objet, gpointer user_data) {
    GtkWidget *Acceuil, *YRwindowtreeview;
	
	YRwindowtreeview=lookup_widget(objet,"YRwindowtreeview");
	gtk_widget_destroy(YRwindowtreeview);
	Acceuil=create_Acceuil();
	gtk_widget_show(Acceuil);
}

void on_YRbuttonsupprimer_clicked (GtkWidget       *objet, gpointer user_data) {
    
    GtkWidget *YRtreeviewETS;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id;
    etablissement e;

    
    YRtreeviewETS = lookup_widget(objet, "YRtreeviewETS");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(YRtreeviewETS));

    
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        strcpy(e.id, id);

        
        GtkListStore *liststore = GTK_LIST_STORE(model);
        gtk_list_store_remove(liststore, &iter);
	

	YRsupprimer("etablissement.txt", e);
	//YRafficher_etablissement(YRtreeviewETS);
    }
}

void on_YRbuttonmodifier_clicked(GtkWidget       *objet, gpointer user_data) {
    
GtkWidget *YRentryid, *YRentryresponsable, *YRcomboboxregion, *YRentryadresse, *YRspinbuttoncapacite, *YRradiobuttonlunven, *YRradiobutton7, *YRcheckbuttonconfirmer;
    GtkWidget *YRwindowajouterETS;
    GtkWidget *YRtreeviewETS;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id;
    gchar *responsable;
    gchar *region;
    gchar *adresse;
    gchar *capacite;
    gchar *temps_travail;
    YRtreeviewETS = lookup_widget(GTK_WIDGET(objet), "YRtreeviewETS");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(YRtreeviewETS));

    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        return;
    }

    gtk_tree_model_get(model, &iter, 0, &id, 1, &responsable, 2, &region, 3, &adresse, 4, &capacite, 5, &temps_travail, -1);
    YRwindowajouterETS = lookup_widget(GTK_WIDGET(objet), "YRwindowajouterETS");
    gtk_widget_destroy(YRwindowajouterETS);
    YRwindowajouterETS = create_YRwindowajouterETS();
    gtk_widget_show(YRwindowajouterETS);
    YRentryid =          lookup_widget(YRwindowajouterETS, "YRentryid");
    YRentryresponsable = lookup_widget(YRwindowajouterETS, "YRentryresponsable");
    YRcomboboxregion =   lookup_widget(YRwindowajouterETS, "YRcomboboxregion");
    YRentryadresse =     lookup_widget(YRwindowajouterETS, "YRentryadresse");
    YRspinbuttoncapacite=lookup_widget(YRwindowajouterETS, "YRspinbuttoncapacite");
    YRradiobuttonlunven= lookup_widget(YRwindowajouterETS, "YRradiobuttonlunven");
    YRradiobutton7     = lookup_widget(YRwindowajouterETS, "YRradiobutton7");

    gtk_entry_set_text(GTK_ENTRY(YRentryid), id);
    gtk_entry_set_text(GTK_ENTRY(YRentryresponsable), responsable);
    gtk_entry_set_text(GTK_ENTRY(YRentryadresse), adresse);
    gtk_combo_box_set_active(GTK_COMBO_BOX(YRcomboboxregion),(region));

    if (strcmp(temps_travail, "lundi_vendredi") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(YRradiobuttonlunven), TRUE);
    else
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(YRradiobutton7), TRUE);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(YRspinbuttoncapacite), atoi(capacite));
}

void on_YRbuttonajouter_clicked(GtkWidget *objet, gpointer user_data) {
    GtkWidget *YRwindowajouterETS;
    GtkWidget *YRwindowtreeview;

    YRwindowtreeview = lookup_widget(objet, "YRwindowtreeview");
    gtk_widget_destroy(YRwindowtreeview);
    YRwindowajouterETS = create_YRwindowajouterETS();
    gtk_widget_show(YRwindowajouterETS);
    
}

//**********************************************************************************************************************************************************************************
void on_YRbuttonchercher_clicked(GtkWidget       *objet, gpointer user_data) {
    GtkWidget *YRcomboboxetsregion, *YRtreeviewETS;
    const gchar *search_region;

   
    YRcomboboxetsregion = lookup_widget(objet, "YRcomboboxetsregion");
    YRtreeviewETS = lookup_widget(objet, "YRtreeviewETS");

    search_region = gtk_combo_box_get_active_text(GTK_COMBO_BOX(YRcomboboxetsregion));
    if (search_region != NULL)
    {
        YRETSParRegion(search_region, YRtreeviewETS);
        g_free(search_region);
    }
    else
    {
        g_print("Please select a region to search.\n");
    }
}
//**********************************************************************************************************************************************************************************

void on_YRbuttontrier_clicked(GtkWidget       *objet, gpointer user_data) {
	GtkWidget *YRtreeviewETS;
	YRtreeviewETS = lookup_widget(objet, "YRtreeviewETS");

	YRETSTrieCapacite("etablissement.txt");

	YRafficher_etablissement(YRtreeviewETS);
}


























void
on_MT_ajouter_formulaire_clicked       (GtkWidget      *objet,
                                        gpointer         user_data)
{
 GtkWidget *MT_w_acceuil;
  GtkWidget *MT_w_formulaire;
  MT_w_acceuil = lookup_widget(objet, "MT_w_acceuil");
  gtk_widget_hide (MT_w_acceuil);
  MT_w_formulaire = create_MT_w_formulaire ();
  gtk_widget_show (MT_w_formulaire);
}


void
on_MT_afficher_rdv_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *MT_w_acceuil;
  GtkWidget *MT_w_rdv;
  MT_w_acceuil=lookup_widget(objet,"MT_w_acceuil");
  gtk_widget_hide (MT_w_acceuil);
  MT_w_rdv=create_MT_w_rdv();
  gtk_widget_show (MT_w_rdv);
}


void
on_MT_afficher_liste_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
  GtkWidget *MT_w_acceuil;
  GtkWidget *MT_w_liste;
  MT_w_acceuil = lookup_widget(objet,"MT_w_acceuil");
  gtk_widget_hide (MT_w_acceuil);
  MT_w_liste = create_MT_w_liste ();
  gtk_widget_show (MT_w_liste);
}


void
on_MT_deconnexion_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_MT_oui_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MT_non_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MT_tatouage_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MT_afficher_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_w_formulaire,*MT_treeview1;
  GtkWidget *MT_w_liste;
  MT_w_formulaire=lookup_widget(objet,"MT_w_formulaire");
  gtk_widget_destroy(MT_w_formulaire);
  MT_w_liste=lookup_widget(objet,"MT_w_liste");
  MT_w_liste=create_MT_w_liste();
  gtk_widget_show(MT_w_liste);
  MT_treeview1=lookup_widget(MT_w_liste,"MT_treeview1");
  MT_afficher(MT_treeview1,"donneur.txt");
}


void
on_MT_ajouter_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
donneur d;
	GtkWidget *MT_nom,*MT_prenom,*MT_cin,*MT_telephone,*MT_lieu,*MT_jour,*MT_mois,*MT_annee,*MT_sexe,*MT_oui,*MT_non,*MT_tatouage,*MT_maladies,*MT_traitement,*pInfo;
	GtkWidget *MT_w_formulaire;

        MT_w_formulaire=lookup_widget(objet,"MT_w_formulaire");
	MT_nom=lookup_widget(objet,"MT_nom");
	MT_prenom=lookup_widget(objet,"MT_prenom");
	MT_cin=lookup_widget(objet,"MT_cin");
	MT_telephone=lookup_widget(objet,"MT_telephone");
	MT_lieu=lookup_widget(objet,"MT_lieu");
	MT_jour=lookup_widget(objet,"MT_jour");
	MT_mois=lookup_widget(objet,"MT_mois");
	MT_annee=lookup_widget(objet,"MT_annee");
	MT_sexe=lookup_widget(objet,"MT_sexe");
	MT_oui=lookup_widget(objet,"MT_oui");
	MT_non=lookup_widget(objet,"MT_non");
	MT_tatouage=lookup_widget(objet,"MT_tatouage");	
	MT_maladies=lookup_widget(objet,"MT_maladies");
	MT_traitement=lookup_widget(objet,"MT_traitement");
	
	strcpy(d.nom,gtk_entry_get_text(GTK_ENTRY(MT_nom)));
	strcpy(d.prenom,gtk_entry_get_text(GTK_ENTRY(MT_prenom)));
	strcpy(d.cin,gtk_entry_get_text(GTK_ENTRY(MT_cin)));
	strcpy(d.n_telephone,gtk_entry_get_text(GTK_ENTRY(MT_telephone)));
	strcpy(d.lieu,gtk_entry_get_text(GTK_ENTRY(MT_lieu)));	
	strcpy(d.maladies,gtk_entry_get_text(GTK_ENTRY(MT_maladies)));
	strcpy(d.traitement,gtk_entry_get_text(GTK_ENTRY(MT_traitement)));
	
	d.date_naissance.j=gtk_spin_button_get_value(GTK_SPIN_BUTTON(MT_jour));
	d.date_naissance.m=gtk_spin_button_get_value(GTK_SPIN_BUTTON(MT_mois));
	d.date_naissance.a=gtk_spin_button_get_value(GTK_SPIN_BUTTON(MT_annee));


	strcpy(d.sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(MT_sexe)));


	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MT_oui)))
	strcpy(d.enceinte,"MT_oui");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MT_non)))
	strcpy(d.enceinte,"MT_non");


	if(gtk_toggle_button_get_active(GTK_CHECK_BUTTON(MT_tatouage)))
	strcpy(d.tatouage,"MT_oui");
	else
	strcpy(d.tatouage,"MT_non");
	


	MT_ajouter(d,"donneur.txt");

}


void
on_MT_acceuil1_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
  GtkWidget *MT_w_formulaire;
  GtkWidget *MT_w_acceuil;
  MT_w_formulaire = lookup_widget(objet, "MT_w_formulaire");
  gtk_widget_hide (MT_w_formulaire);
  MT_w_acceuil = create_MT_w_acceuil ();
  gtk_widget_show (MT_w_acceuil);
}


void
on_MT_treeview1_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gchar* MT_nom;	
	gchar* MT_prenom;
	gchar* MT_cin;
	gchar* MT_n_telephone;
	gchar* MT_lieu;
	gchar* MT_date_naissance;
	gchar* MT_sexe;
	gchar* MT_enceinte;
	gchar* MT_oui;
	gchar* MT_non;
	gchar* MT_tatouage;
	gchar* MT_maladies;
	gchar* MT_traitement;
	char date[20];	
	donneur d;
	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path))
	{
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&MT_nom,1,&MT_prenom,2,&MT_cin,3,&MT_n_telephone,4,&MT_lieu,5,&MT_date_naissance,6,&MT_sexe,7,&MT_enceinte,8,&MT_tatouage,9,&MT_maladies,10,&MT_traitement,-1);
	strcpy(d.nom,MT_nom);
	strcpy(d.prenom,MT_prenom);
	strcpy(d.cin,MT_cin);
	strcpy(d.n_telephone,MT_n_telephone);
	strcpy(d.lieu,MT_lieu);
	strcpy(d.sexe,MT_sexe);
	strcpy(d.tatouage,MT_tatouage);
	strcpy(d.maladies,MT_maladies);
	strcpy(d.traitement,MT_traitement);
	sprintf(date,"%d/%d/%d",d.date_naissance.j,d.date_naissance.m,d.date_naissance.a);
	strcpy(date,MT_date_naissance);
	strcpy(d.enceinte,MT_oui);
	
	MT_afficher(treeview,"donneur.txt");
	
	}
}


void
on_MT_chercher_liste_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_MT_acceuil2_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
  GtkWidget *MT_w_liste;
  GtkWidget *MT_w_acceuil;
  MT_w_liste = lookup_widget(objet, "MT_w_liste");
  gtk_widget_hide (MT_w_liste);
  MT_w_acceuil = create_MT_w_acceuil ();
  gtk_widget_show (MT_w_acceuil);

}


void
on_MT_actualiser_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
 GtkWidget *MT_treeview1;
  GtkWidget *MT_w_liste;
 
  MT_w_liste=lookup_widget(objet,"MT_w_liste");
  MT_w_liste=create_MT_w_liste();
  gtk_widget_show(MT_w_liste);
  MT_treeview1=lookup_widget(MT_w_liste,"MT_treeview1");
  MT_afficher(MT_treeview1,"donneur.txt");
}


void
on_MT_modifier_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_w_formulaire,*MT_recherche_modif;	
	GtkWidget *MT_treeview1;
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *MT_cin;
   	GtkWidget *MT_button1;
	donneur d;

	MT_w_formulaire=lookup_widget(objet, "MT_w_formulaire");
	
	MT_treeview1=lookup_widget(objet,"MT_treeview1");
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(MT_treeview1));

	if(gtk_tree_selection_get_selected(selection,&model,&iter))
	{
	gtk_tree_model_get(model,&iter,0,&MT_cin,-1);
	strcpy(d.cin,MT_cin);
	GtkListStore *liststore=GTK_LIST_STORE(model);
	
		
	MT_recherche_modif=lookup_widget(objet,"MT_recherche_modif");
	gtk_entry_set_text(GTK_ENTRY(MT_recherche_modif),MT_cin);
	
 		
	}
}


void
on_MT_supprimer_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_treeview1,*check,*pInfo;
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *MT_cin;
	donneur d;
	//check=lookup_widget(objet,"checkbutton1");

	MT_treeview1=lookup_widget(objet,"MT_treeview1");
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(MT_treeview1));
	if(gtk_tree_selection_get_selected(selection,&model,&iter))
	{
	//if(gtk_toggle_button_get_active(GTK_CHECK_BUTTON(check)))	
	//{
	
	gtk_tree_model_get(model,&iter,0,&MT_cin,-1);
	strcpy(d.cin,MT_cin);
	GtkListStore *liststore=GTK_LIST_STORE(model);
	gtk_list_store_remove(liststore,&iter);
	MT_supprimer(d,"donneur.txt");
	//}
	}
	else
	{
		pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Confirmé!");
		switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
		{
		case GTK_RESPONSE_OK:
		gtk_widget_destroy(pInfo);
		break;
		}
	

}

}


void
on_MT_treeview2_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_MT_acceuil3_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_w_rdv;
  GtkWidget *MT_w_acceuil;
  MT_w_rdv = lookup_widget(objet, "MT_w_rdv");
  gtk_widget_hide (MT_w_rdv);
  MT_w_acceuil = create_MT_w_acceuil ();
  gtk_widget_show (MT_w_acceuil);
}


void
on_MT_chercher_rdv_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_MT_moyenne_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_MT_m_button_rechercher_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_MT_modif_oui_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MT_modif_non_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MT_m_button_modifier_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
donneur u;   	
    	GtkWidget 	*MT_recherche_modif,*MT_modif_nom,*MT_modif_etablissement,*MT_modif_prenom,*MT_modif_lieu_naissance,*MT_modif_n_telephone,*MT_modif_maladie,*MT_modif_traitements,*MT_modif_jour,*MT_modif_mois,*MT_modif_annee,*MT_modif_tatouage,*MT_modif_non,*MT_modif_oui,*MT_modif_sexe, *pInfo;
	

	MT_recherche_modif=lookup_widget(objet,"MT_recherche_modif");
	
        MT_modif_nom=lookup_widget(objet,"MT_modif_nom");
	MT_modif_prenom=lookup_widget(objet,"MT_modif_prenom");
	MT_modif_lieu_naissance=lookup_widget(objet,"MT_modif_lieu");
	MT_modif_n_telephone=lookup_widget(objet,"MT_modif_n_telephpone");
	MT_modif_maladie=lookup_widget(objet,"MT_modif_maladie");
	MT_modif_traitements=lookup_widget(objet,"MT_modif_traitement");
	MT_modif_oui=lookup_widget(objet,"MT_modif_oui");
	MT_modif_non=lookup_widget(objet,"MT_modif_non");
	MT_modif_sexe=lookup_widget(objet,"MT_modif_sexe");
	MT_modif_tatouage=lookup_widget(objet,"MT_modif_tatouage");
	MT_modif_jour=lookup_widget(objet,"MT_modif_jour");	
	MT_modif_mois=lookup_widget(objet,"MT_modif_mois");
	MT_modif_annee=lookup_widget(objet,"MT_modif_annee");	
	

	strcpy(u.cin,gtk_entry_get_text(GTK_ENTRY(MT_recherche_modif)));
	strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(MT_modif_nom)));
	strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(MT_modif_prenom)));
	strcpy(u.lieu,gtk_entry_get_text(GTK_ENTRY(MT_modif_lieu_naissance)));
	strcpy(u.cin,gtk_entry_get_text(GTK_ENTRY(MT_recherche_modif)));
	strcpy(u.n_telephone,gtk_entry_get_text(GTK_ENTRY(MT_modif_n_telephone)));	
	strcpy(u.maladies,gtk_entry_get_text(GTK_ENTRY(MT_modif_maladie)));
	strcpy(u.traitement,gtk_entry_get_text(GTK_ENTRY(MT_modif_traitements)));
	u.date_naissance.j=gtk_spin_button_get_value(GTK_SPIN_BUTTON(MT_modif_jour));
	u.date_naissance.m=gtk_spin_button_get_value(GTK_SPIN_BUTTON(MT_modif_mois));
	u.date_naissance.a=gtk_spin_button_get_value(GTK_SPIN_BUTTON(MT_modif_annee));
		
	strcpy(u.sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(MT_modif_sexe)));
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MT_modif_oui)))
	strcpy(u.enceinte,"MT_oui");
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(MT_modif_non)))
	strcpy(u.enceinte,"MT_non");
	if(gtk_toggle_button_get_active(GTK_CHECK_BUTTON(MT_modif_tatouage)))
	strcpy(u.tatouage,"MT_oui");
	else
	strcpy(u.tatouage,"MT_non");
		
	
	MT_modifier(u,"donneur.txt");
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Donneur modifié avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
		{
		case GTK_RESPONSE_OK:
		gtk_widget_destroy(pInfo);
		break;
		}
	
}


void
on_MT_m_button_afficher_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_w_m_formulaire,*MT_treeview1;
  GtkWidget *MT_w_liste;
  MT_w_m_formulaire=lookup_widget(objet,"MT_w_m_formulaire");
  gtk_widget_destroy(MT_w_m_formulaire);
  MT_w_liste=lookup_widget(objet,"MT_w_liste");
  MT_w_liste=create_MT_w_liste();
  gtk_widget_show(MT_w_liste);
  MT_treeview1=lookup_widget(MT_w_liste,"MT_treeview1");
  MT_afficher(MT_treeview1,"donneur.txt");
}


void
on_MT_m_button_acceuil_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_w_m_formulaire;
  GtkWidget *MT_w_acceuil;
  MT_w_m_formulaire = lookup_widget(objet, "MT_w_m_formulaire");
  gtk_widget_hide (MT_w_m_formulaire);
  MT_w_acceuil = create_MT_w_acceuil ();
  gtk_widget_show (MT_w_acceuil);
}


void
on_radiobuttonH_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobuttonF_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbuttonconfirmer_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_buttonafficher_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *AHwindowajouter;
	GtkWidget *AHwindowtreeview;
	GtkWidget *treeview1;
	
	AHwindowajouter=lookup_widget(objet,"AHwindowajouter");

	gtk_widget_destroy(AHwindowajouter);
	AHwindowtreeview=lookup_widget(objet,"AHwindowtreeview");
	AHwindowtreeview=create_AHwindowtreeview();

	gtk_widget_show(AHwindowtreeview);

	treeview1=lookup_widget(AHwindowtreeview,"treeview1");
	
	AHafficher_user(treeview1);
}


void
on_buttoncreer_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{

     user u;
    GtkWidget *entrycin, *entrynom, *entryprenom, *comboboxrole, *radiobuttonH,   *spinbuttonage ;
    GtkWidget *AHwindowajouter,*radiobuttonF;
    GtkWidget *treeview1;

    AHwindowajouter = lookup_widget(objet, "AHwindowajouter");
    entrycin = lookup_widget(objet, "entrycin");
    entrynom = lookup_widget(objet, "entrynom");
    entryprenom = lookup_widget(objet, "entryprenom");
    comboboxrole = lookup_widget(objet, "comboboxrole");
    radiobuttonH = lookup_widget(objet, "radiobuttonH");
    spinbuttonage = lookup_widget(objet, "spinbuttonage");
    radiobuttonF = lookup_widget(objet, "radiobuttonF");
    strcpy(u.cin, gtk_entry_get_text(GTK_ENTRY(entrycin)));
    strcpy(u.nom, gtk_entry_get_text(GTK_ENTRY(entrynom)));
    strcpy(u.prenom, gtk_entry_get_text(GTK_ENTRY(entryprenom)));
    strcpy(u.role, gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxrole)));
    
    sprintf(u.age, "%d", (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spinbuttonage)));

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonH)))
{
   strcpy(u.sexe, "H");
}
else  
{
    strcpy(u.sexe, "F");
}
        AHajouter_user(u);

    //treeview1 = lookup_widget(AHwindowajouter, "AHwindowtreeview");
    
}


void
on_treeview1_row_activated (GtkTreeView *treeview, GtkTreePath *path,GtkTreeViewColumn *column,gpointer user_data)
    
{                                   


    GtkTreeSelection *selection;

GtkTreeIter iter;
	gchar* cin;	
	gchar* nom;
	gchar* prenom;
	gchar* role;
	gchar* sexe;
        gchar* age;
	user u;
	GtkWidget *treeview1;
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path))
	{
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&cin,1,&nom,2,&prenom,3,&role,4,&sexe,5,&age,-1);
	strcpy(u.cin,cin);
	strcpy(u.nom,nom);
	strcpy(u.prenom,prenom);
	strcpy(u.role,role);
	strcpy(u.sexe,sexe);
        strcpy(u.age,age);
	//supprimer_user(u);
	AHafficher_user(treeview1);}
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        
        gtk_tree_model_get(model, &iter, 0, &cin, -1);
        strcpy(u.cin, cin);

        
        GtkListStore *liststore = GTK_LIST_STORE(model);
        gtk_list_store_remove(liststore, &iter);

        AHsupprimer_user(u);}                                   


}


void
on_buttonback_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *AHwindowajouter, *AHwindowtreeview;
	AHwindowtreeview=lookup_widget(objet,"AHwindowtreeview");

	gtk_widget_destroy(AHwindowtreeview);
	AHwindowajouter=create_AHwindowajouter();
	gtk_widget_show(AHwindowajouter);

}


void
on_buttonsupprimer_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkWidget *treeview1;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *cin;
    user u;

    
    treeview1 = lookup_widget(objet, "treeview1");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1));

    
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        
        gtk_tree_model_get(model, &iter, 0, &cin, -1);
        strcpy(u.cin, cin);

        
        GtkListStore *liststore = GTK_LIST_STORE(model);
        gtk_list_store_remove(liststore, &iter);

        AHsupprimer_user(u);
    }
}


void
on_buttonmodifier_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *AHwindowajouter, *treeview1, *entrycin, *entrynom, *entryprenom, *comboboxrole, *radiobuttonH, *radiobuttonF, *spinbuttonage;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *cin, *nom, *prenom, *role, *sexe, *age;
    treeview1 = lookup_widget(GTK_WIDGET(objet), "treeview1");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1));

    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
       
        return;
    }

    gtk_tree_model_get(model, &iter, 0, &cin, 1, &nom, 2, &prenom, 3, &role, 4, &sexe, 5, &age, -1);
    AHwindowajouter = lookup_widget(GTK_WIDGET(objet), "AHwindowajouter");
    gtk_widget_destroy(AHwindowajouter);
    AHwindowajouter = create_AHwindowajouter();
    gtk_widget_show(AHwindowajouter);
    entrycin = lookup_widget(AHwindowajouter, "entrycin");
    entrynom = lookup_widget(AHwindowajouter, "entrynom");
    entryprenom = lookup_widget(AHwindowajouter, "entryprenom");
    comboboxrole = lookup_widget(AHwindowajouter, "comboboxrole");
    radiobuttonH = lookup_widget(AHwindowajouter, "radiobuttonH");
    radiobuttonF = lookup_widget(AHwindowajouter, "radiobuttonF");
    spinbuttonage = lookup_widget(AHwindowajouter, "spinbuttonage");

    gtk_entry_set_text(GTK_ENTRY(entrycin), cin);
    gtk_entry_set_text(GTK_ENTRY(entrynom), nom);
    gtk_entry_set_text(GTK_ENTRY(entryprenom), prenom);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboboxrole), (role));

    if (strcmp(sexe, "H") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonH), TRUE);
    else
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonF), TRUE);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonage), atoi(age));
     
     }


void
on_buttonfemme_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
user u4;

GtkWidget *AHwindowtreeview ,*labelfemme  ; 

  AHwindowtreeview = lookup_widget(objet, "AHwindowtreeview");
  labelfemme = lookup_widget(objet, "labelfemme");

    int totalUsers;
    float femalePercentage;
    
   calculate_female_percentage(&totalUsers, &femalePercentage) ;
      char femalePer[20];
      sprintf(femalePer, "%.2f %%", femalePercentage);
    
    gtk_label_set_text(GTK_LABEL(labelfemme), femalePer);
}


void
on_buttonhomme_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
user u3;

 	GtkWidget *AHwindowtreeview,*labelhomme ; 

   	AHwindowtreeview = lookup_widget(objet, "AHwindowtreeview");
  	labelhomme = lookup_widget(objet, "labelhomme");

    	int totalUsers;
    	float malePercentage;
    
    	calculate_male_percentage(&totalUsers, &malePercentage);
      	char malePer[20];
      	sprintf(malePer, "%.2f %%", malePercentage);
    
    	gtk_label_set_text(GTK_LABEL(labelhomme), malePer);
   
}


void
on_buttonrechercherole_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *comboboxrole1, *treeview1;
    const gchar *search_role;

   
    comboboxrole1 = lookup_widget(objet, "comboboxrole1");
    treeview1 = lookup_widget(objet, "treeview1");

   
    search_role = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxrole1));

    
    if (search_role != NULL)
    {
        
        rechercher_par_role(search_role, treeview1);

      
        g_free(search_role);
    }
    else
    {
        g_print("Please select a role to search.\n");
    }
}





void
on_buttonajouter_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *AHwindowajouter, *AHwindowtreeview;
	AHwindowtreeview=lookup_widget(objet,"AHwindowtreeview");

	gtk_widget_destroy(AHwindowtreeview);
	AHwindowajouter=create_AHwindowajouter();
	gtk_widget_show(AHwindowajouter);
}


void
on_buttonrechercher_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *entryrechercher, *treeview1;
    const char *search_term;

    
    entryrechercher = lookup_widget(objet, "entryrechercher");
    treeview1 = lookup_widget(objet, "treeview1");

    
    search_term = gtk_entry_get_text(GTK_ENTRY(entryrechercher));

   
    rechercher_user(search_term, treeview1);
}
///////////////////////////////////(hna baad ma tzidou les interface o tsamou taamel build yetzedou les boutons mteekom o tcopi l callbacks mteek bl kaaba bl kaaba )


void
on_gestionets_clicked                  (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *YRwindowajouterETS, *YRwindowtreeview;
	YRwindowtreeview=lookup_widget(objet,"YRwindowtreeview");

	gtk_widget_destroy(YRwindowtreeview);
	YRwindowajouterETS=create_YRwindowajouterETS();
	gtk_widget_show(YRwindowajouterETS);
}


void
on_gestionuser_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *AHwindowajouter, *AHwindowtreeview;
	AHwindowtreeview=lookup_widget(objet,"AHwindowtreeview");

	gtk_widget_destroy(AHwindowtreeview);
	AHwindowajouter=create_AHwindowajouter();
	gtk_widget_show(AHwindowajouter);
}


void
on_fichedonneur_clicked                (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *MT_w_acceuil;

	MT_w_acceuil=create_MT_w_acceuil();
	gtk_widget_show(MT_w_acceuil);
}


void
on_gestionrendezvous_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *OGajout;

	OGajout=create_OGajout();
	gtk_widget_show(OGajout);
}


void
on_gestiondons_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *fenetre_ajout;

	fenetre_ajout=create_fenetre_ajout();
	gtk_widget_show(fenetre_ajout);
}


void
on_loginbutton_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *usernameentry,*mot_de_passeentry,*pInfo;
 GtkWidget *login,*Acceuil;
char username[20],password[20];

login=lookup_widget(objet,"login");
usernameentry=lookup_widget(objet,"usernameentry");
mot_de_passeentry=lookup_widget(objet,"mot_de_passeentry");
strcpy(username,gtk_entry_get_text(GTK_ENTRY(usernameentry)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(mot_de_passeentry)));

if(strcmp(username,"enneslkol")==0 && strcmp(password,"enneslkol")==0)
  {
  gtk_widget_hide (login);
  Acceuil = create_Acceuil ();
  gtk_widget_show (Acceuil);
}
else
{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"USERNAME incorrect");
switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
{
case GTK_RESPONSE_OK:
gtk_widget_destroy(pInfo);
break;
}
}
}


void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

rdv rdv;

GtkWidget *jour = lookup_widget(button, "OGspinjour");
rdv.jours = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(jour));

GtkWidget *mois = lookup_widget(button, "OGspinmois");
rdv.moiis = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(mois));

GtkWidget *annee = lookup_widget(button, "OGcomboheure");
strcpy(rdv.anneee,gtk_combo_box_get_active_text(GTK_COMBO_BOX(annee)));

GtkWidget *lieu = lookup_widget(button, "OGcombolieu");
strcpy(rdv.lieu,gtk_combo_box_get_active_text(GTK_COMBO_BOX(lieu)));

GtkWidget *heure_RDV = lookup_widget(button, "OGcomboheure");
strcpy(rdv.heure_RDV,gtk_combo_box_get_active_text(GTK_COMBO_BOX(heure_RDV)));

GtkWidget *Identifiant = lookup_widget(button, "OGentryid");
strcpy(rdv.id, gtk_entry_get_text(GTK_ENTRY(Identifiant)));

OGajouter("rdv.txt", rdv);

GtkWidget *rdvs, *OGajout;
	
	OGajout=lookup_widget(button,"OGajout");
	gtk_widget_destroy(OGajout);
	rdvs=create_rdvs();
	gtk_widget_show(rdvs);

}


void
on_treeview2_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

GtkTreeIter iter;
gchar* heure_RDV;
gchar* id;
gchar* jours;
gchar* moiis;
gchar* anneee;
gchar* lieu;
rdv rdv;

GtkWidget *OGtreeview;
GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get (GTK_LIST_STORE(model),&iter,0,&heure_RDV,1,&lieu,2,&jours,3,&moiis,4,&anneee,5,&id,-1);

strcpy(rdv.heure_RDV,heure_RDV);
strcpy(rdv.lieu,lieu);
strcpy(rdv.jours,jours);
strcpy(rdv.moiis,moiis);
strcpy(rdv.anneee,anneee);
strcpy(rdv.id,id);

Gafficher(OGtreeview);

	}

}


void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *OGtreeview;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id;
    rdv rdv;

    
    OGtreeview = lookup_widget(button, "OGtreeview");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(OGtreeview));

    
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        strcpy(rdv.id, id);

        
        GtkListStore *liststore = GTK_LIST_STORE(model);
        gtk_list_store_remove(liststore, &iter);
	

	OGsupprimer("rdv.txt", rdv);
	Gafficher(OGtreeview);
}

}


void
on_button5_clicked                     (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *OGajout;
    GtkWidget *OGtreeview;

    OGtreeview = lookup_widget(objet, "OGtreeview");
    gtk_widget_destroy(OGtreeview);
    OGajout = create_OGajout();
    gtk_widget_show(OGajout);

}


void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OGbuttonretour1_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OGbuttonaffiche_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *OGajout;
GtkWidget *OGafficher;
GtkWidget *OGtreeview;

    OGajout = lookup_widget(button,"OGajout");

   gtk_widget_destroy(OGajout);
   OGafficher=lookup_widget(button,"OGafficher");
   OGafficher=create_OGaffiche();

    gtk_widget_show(OGafficher);

    OGtreeview=lookup_widget(OGafficher,"OGtreeview");
    Gafficher(OGtreeview);

}
//hadhemi

void on_ajouter_clicked   (GtkWidget *objet, gpointer user_data) {
    don d;
    GtkWidget *idd, *nomcomplet, *type, *quantite, *jour, *mois, *annee;
    GtkWidget *positive_radio, *negative_radio;
    GtkWidget *text_view2;
    GtkWidget *confirmera_checkbox;
    // Récupération des widgets
    idd = lookup_widget(objet, "idd");
    nomcomplet = lookup_widget(objet, "nomcomplet");
    type = lookup_widget(objet, "type");
    quantite = lookup_widget(objet, "quantite");
    jour = lookup_widget(objet, "jour");
    mois = lookup_widget(objet, "mois");
    annee = lookup_widget(objet, "annee");
    positive_radio = lookup_widget(objet, "positive_radio");
    negative_radio = lookup_widget(objet, "negative_radio");
    text_view2 = lookup_widget(objet, "text_view2");
    confirmera_checkbox = lookup_widget(objet, "confirmera_checkbox");

// Vérification que tous les champs sont remplis
    if (gtk_entry_get_text(GTK_ENTRY(idd))[0] == '\0' ||
        gtk_entry_get_text(GTK_ENTRY(nomcomplet))[0] == '\0' ||
        gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)) == NULL) 
      {
        afficher_message(text_view2, "Veuillez remplir tous les champs.");
        return; // Sortie de la fonction si un champ est vide
      }

   if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(confirmera_checkbox))) {
    afficher_message(text_view2, "Je confirme !");
    return; // Sortir de la fonction si la case n'est pas cochée
}

    // Remplissage de la structure demande avec les données des widgets
    strcpy(d.idd, gtk_entry_get_text(GTK_ENTRY(idd)));
    strcpy(d.nomcomplet, gtk_entry_get_text(GTK_ENTRY(nomcomplet)));
    strcpy(d.type, gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)));
    d.quantite = atof(gtk_entry_get_text(GTK_ENTRY(quantite)));
    d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    d.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
    d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
    strcpy(d.nature, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(positive_radio)) ? "positive" : "negative");

    // Appel de la fonction ajouter
     int result = ajouter(d);

    // Affichage du message dans le GtkTextView
    if (result == 1) {
        afficher_message(text_view2, "L'ajout a été effectué avec succès.");
    } else if (result == 2) {
    afficher_message(text_view2, "Erreur : L'ID existe déjà.");
    } else if (result == -1) {
        afficher_message(text_view2, "Erreur lors de l'ajout.");
    } else {
        afficher_message(text_view2, "Veuillez remplir tous les champs.");
    }
}




void
on_retour2_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_ajout,*fenetre_afficher ;
    fenetre_afficher=lookup_widget(objet, "fenetre_afficher");
    gtk_widget_destroy(fenetre_afficher);
   
    fenetre_ajout = create_fenetre_ajout();
    gtk_widget_show(fenetre_ajout);

}


void sang_rare(GtkWidget *objet, char *filename) {
    GtkWidget *textviewsr;
    textviewsr = lookup_widget(objet, "textviewsr");

    float a = quantite_type("don.txt", "A");
    float b = quantite_type("don.txt", "B");
    float ab = quantite_type("don.txt", "AB");
    float o = quantite_type("don.txt", "O");

    float min_quantity = FLT_MAX;  // Use FLT_MAX for initialization
    char min_type;

    // Compare each quantity and update min_quantity and min_type accordingly
    if (a < min_quantity) {
        min_quantity = a;
        min_type = 'A';
    }

    if (b < min_quantity) {
        min_quantity = b;
        min_type = 'B';
    }

    if (ab < min_quantity) {
        min_quantity = ab;
        min_type = 'AB';  // Change to a character literal
    }

    if (o < min_quantity) {
        min_quantity = o;
        min_type = 'O';
    }

    char message[100];
    snprintf(message, sizeof(message), "Le type de sang le plus rare est : %c avec une quantité de %.2f ml \n", min_type, min_quantity);
    afficher_message(textviewsr, message);
}

void on_actualiser_clicked(GtkWidget *objet, gpointer user_data) {
    GtkWidget *entrytype;
    GtkWidget *textviewq;
    GtkWidget *textviewsr;
    GtkWidget *typeq;  // Assuming typeq is declared somewhere in your code

    entrytype = lookup_widget(objet, "entrytype");
    textviewq = lookup_widget(objet, "textviewq");
    textviewsr = lookup_widget(objet, "textviewsr");

    const gchar *type_saisi = gtk_entry_get_text(GTK_ENTRY(entrytype));

    char type[20];
    strncpy(type, type_saisi, sizeof(type));

    float quantite_result = quantite_type("don.txt", type);

    if (quantite_result >= 0) {
        char message[100];
        snprintf(message, sizeof(message), "%.2f", quantite_result);
        afficher_message(textviewq, message);
    } else {
        afficher_message(textviewq, "Erreur lors du calcul du quantite.\n");
    }

    // Déclaration et initialisation du tableau types_sang
    char type_sang[4][3] = {"A", "B", "AB", "O"};

    // Update the function call to include 'objet' in 'sang_rare'
    sang_rare(objet, "don.txt");
}



void
on_modifier1_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{  GtkWidget *fenetre_ajout;
    GtkWidget *fenetre_modifier;
   

    // Destruction de la fenêtre actuelle
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    gtk_widget_destroy(fenetre_ajout);

    // Création et affichage de la nouvelle fenêtre
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    fenetre_modifier = create_fenetre_modifier();
    gtk_widget_show(fenetre_modifier); 


}







void
on_retour1_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{  GtkWidget *Acceuil,*fenetre_ajout ;
 GtkWidget *treeview1h;
    fenetre_ajout=lookup_widget(objet, "fenetre_ajout");
    gtk_widget_destroy(fenetre_ajout);
   
   Acceuil = lookup_widget(objet, "Acceuil");
    Acceuil = create_Acceuil();
    gtk_widget_show(Acceuil);

   treeview1h = lookup_widget(fenetre_ajout, "treeview1h");
    afficher(treeview1h);


}






void
on_ajouter2_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
   GtkWidget *fenetre_ajout;
    GtkWidget *fenetre_afficher;
    

    // Destruction de la fenêtre actuelle
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    gtk_widget_destroy(fenetre_afficher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    fenetre_ajout = create_fenetre_ajout();
    gtk_widget_show(fenetre_ajout);
}






void
on_modifier2_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data)
{ GtkWidget *fenetre_modifier;
    GtkWidget *fenetre_afficher;
    

    // Destruction de la fenêtre actuelle
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    gtk_widget_destroy(fenetre_afficher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    fenetre_modifier = create_fenetre_modifier();
    gtk_widget_show(fenetre_modifier);

}




void
on_afficher3_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{ GtkWidget *fenetre_modifier;
    GtkWidget *fenetre_afficher;
    GtkWidget *treeview1h;

    // Destruction de la fenêtre actuelle
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    gtk_widget_destroy(fenetre_modifier);

    // Création et affichage de la nouvelle fenêtre
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

    // Récupération du treeview et appel de la fonction afficher
    treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);  // Passer le treeview1 directement à la fonction afficher
 

}


void
on_ajouter3_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{  GtkWidget *fenetre_modifier;
    GtkWidget *fenetre_ajout;
    

    // Destruction de la fenêtre actuelle
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    gtk_widget_destroy(fenetre_modifier);

    // Création et affichage de la nouvelle fenêtre
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    fenetre_ajout = create_fenetre_ajout();
    gtk_widget_show(fenetre_ajout);

}





void
on_retour3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
    GtkWidget *fenetre_afficher,*fenetre_modifier ;
    GtkWidget *treeview1h;
    fenetre_modifier=lookup_widget(objet, "fenetre_modifier");
    gtk_widget_destroy(fenetre_modifier);
   
     fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

   treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);


}
bool charger_donnees_don_par_id(char *filename, char *idd, don *resultat) {
    FILE *f = fopen(filename, "r");
    resultat->idd[0] = '\0';  // Initialisation à une chaîne vide au cas où l'ID ne serait pas trouvé
    bool id_trouve = false;

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %f %d %d %d  \n", resultat->idd, resultat->nomcomplet, resultat->type,  resultat->nature, &resultat->quantite , &resultat->jour, &resultat->mois, &resultat->annee) != EOF) {
            if (strcmp(resultat->idd, idd) == 0) {
id_trouve = true;
                break;  // Sortir de la boucle une fois que l'ID est trouvé
            }
        }
        fclose(f);
    }
    return id_trouve;
}

int etat_modifier = 0; 


void on_modifier_clicked(GtkWidget *objet, gpointer user_data) {
    don d;
    GtkWidget *idd, *nomcomplet, *type, *quantite, *jour, *mois, *annee;
    GtkWidget *positive_radio, *negative_radio;
  
    GtkWidget *treeview1h;
    GtkWidget *text_view3;
    GtkWidget *confirmerm;
    confirmerm= lookup_widget(objet, "confirmerm");
    // Récupération des widgets
    idd = lookup_widget(objet, "iddm");
    nomcomplet = lookup_widget(objet, "nomcompletm");
    type = lookup_widget(objet, "typem");
    quantite = lookup_widget(objet, "quantitem");
    jour = lookup_widget(objet, "jourm");
    mois = lookup_widget(objet, "moism");
    annee = lookup_widget(objet, "anneem");
    positive_radio = lookup_widget(objet, "positive_radiom");
    negative_radio = lookup_widget(objet, "negative_radiom");
    text_view3 = lookup_widget(objet, "text_view3");

    // Remplissage de la structure demande avec les données des widgets
    strcpy(d.idd, gtk_entry_get_text(GTK_ENTRY(idd)));

    if (etat_modifier == 0) {
        // Charger les données de l'ETS dans les champs correspondants
       don donnees_don ;
       bool id_trouve = charger_donnees_don_par_id("don.txt", d.idd , &donnees_don);
	       if (!id_trouve) {
afficher_message(text_view3, "L'ID n'est pas disponible.");
}
	else{
        gtk_entry_set_text(GTK_ENTRY(nomcomplet), donnees_don.nomcomplet);
        
        gtk_combo_box_set_active(GTK_COMBO_BOX(type), g_strcmp0(donnees_don.type, "") ? 0 : -1); 
	if (strcmp(donnees_don.nature, "positive") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(positive_radio), TRUE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(negative_radio), FALSE);
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(positive_radio), FALSE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(negative_radio), TRUE);
        }
        gchar *quantite_text = g_strdup_printf("%.2f", donnees_don.quantite);
	gtk_entry_set_text(GTK_ENTRY(quantite), quantite_text);
	g_free(quantite_text);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour), donnees_don.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois), donnees_don.mois);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee), donnees_don.annee);

        // Mettre à jour l'état pour indiquer que nous sommes prêts à modifier
        etat_modifier = 1;

        // Afficher un message dans le textview pour informer l'utilisateur
        afficher_message(text_view3, "Modifiez les champs et cliquez à nouveau sur Modifier.");
}
    } else if (etat_modifier == 1) {
        // Remplir la structure demande avec les données modifiées
        strcpy(d.nomcomplet, gtk_entry_get_text(GTK_ENTRY(nomcomplet)));
        
        strcpy(d.type, gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)));
	strcpy(d.nature, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(negative_radio)) ? "positive" : "negative");
	d.quantite = atof(gtk_entry_get_text(GTK_ENTRY(quantite)));
        d.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
        d.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois)); 
        d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
 if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(confirmerm)))
               {
                 afficher_message(text_view3, "Veuillez cocher la case de confirmation. ");
        return; // Exit the function if the checkbox is not checked
          }
if (strlen(d.nomcomplet) == 0 || strlen(d.idd) == 0 || strlen(d.type) == 0 ) {
      afficher_message(text_view3, "Les champs ne sont pas tous remplis.");
} 
else {
        // Appel de la fonction modifier
        modifier("don.txt", d.idd, d);
        afficher(treeview1h);
        afficher_message(text_view3, "La modification a été effectuée avec succès.");
        etat_modifier = 0;
    }
  }
}







void
on_modifier4_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *fenetre_modifier;
    GtkWidget *fenetre_supprimer;
    

    // Destruction de la fenêtre actuelle
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    gtk_widget_destroy(fenetre_supprimer);

    // Création et affichage de la nouvelle fenêtre
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    fenetre_modifier = create_fenetre_modifier();
    gtk_widget_show(fenetre_modifier);

}


void
on_afficher4_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_afficher;
    GtkWidget *treeview1h;
    
    // Destruction de la fenêtre actuelle
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    gtk_widget_destroy(fenetre_supprimer);

    // Création et affichage de la nouvelle fenêtre
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

    // Récupération du treeview et appel de la fonction afficher
    treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);  // Passer le treeview1 directement à la fonction afficher

}


void
on_retour4_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
  GtkWidget *fenetre_afficher,*fenetre_supprimer ;
    GtkWidget *treeview1h;
    fenetre_supprimer=lookup_widget(objet, "fenetre_supprimer");
    gtk_widget_destroy(fenetre_supprimer);
   
     fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

   treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);

}


void on_supprimer_clicked(GtkWidget *objet, gpointer user_data) {
    
    

     don d;
    GtkWidget *idd_entry, *treeview1h;
    GtkWidget *text_view4;
     GtkWidget *confirmers;
    // Récupération des widgets
    idd_entry = lookup_widget(objet, "idd_entry");
    treeview1h = lookup_widget(objet, "treeview1h");
     text_view4 = lookup_widget(objet, "text_view4"); 
    confirmers= lookup_widget(objet, "confirmers");  // Remplacez "confirmer_checkbox" par le vrai nom de votre case à cocher
    // Récupération de l'ID à supprimer
    strcpy(d.idd, gtk_entry_get_text(GTK_ENTRY(idd_entry)));
    // Vérification de l'état de la case à cocher "confirmer"
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(confirmers))) {
    // Appel de la fonction supprimer_par_id avec le treeview1
    supprimer_par_id("don.txt", d.idd);
    afficher_message(text_view4, "La suppression a été effectuée avec succès.");

    } else {
        // La case à cocher n'est pas cochée, afficher un message dans le text_view4w
        afficher_message(text_view4, "Veuillez cocher la case 'confirmer' avant de supprimer.");
    }


    // Affichage mis à jour dans le treeview
  
    afficher(treeview1h);

supprimer_par_id("don.txt", d.idd);
    
}






void
on_ajouter4_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_ajout;
    

    // Destruction de la fenêtre actuelle
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    gtk_widget_destroy(fenetre_supprimer);

    // Création et affichage de la nouvelle fenêtre
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    fenetre_ajout = create_fenetre_ajout();
    gtk_widget_show(fenetre_ajout);
}


void
on_supprimer1_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_ajout;
    

    // Destruction de la fenêtre actuelle
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    gtk_widget_destroy(fenetre_ajout);

    // Création et affichage de la nouvelle fenêtre
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    fenetre_supprimer = create_fenetre_supprimer();
    gtk_widget_show(fenetre_supprimer);
}


void
on_supprimer2_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
    GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_afficher;
    

    // Destruction de la fenêtre actuelle
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    gtk_widget_destroy(fenetre_afficher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    fenetre_supprimer = create_fenetre_supprimer();
    gtk_widget_show(fenetre_supprimer);

}


void
on_supprimer3_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
   GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_modifier;
    

    // Destruction de la fenêtre actuelle
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    gtk_widget_destroy(fenetre_modifier);

    // Création et affichage de la nouvelle fenêtre
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    fenetre_supprimer = create_fenetre_supprimer();
    gtk_widget_show(fenetre_supprimer);

}


void
on_ajouter5_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_rechercher;
    GtkWidget *fenetre_ajout;
    

    // Destruction de la fenêtre actuelle
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    gtk_widget_destroy(fenetre_rechercher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    fenetre_ajout = create_fenetre_ajout();
    gtk_widget_show(fenetre_ajout);
}



void
on_afficher5_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_rechercher;
    GtkWidget *fenetre_afficher;
    GtkWidget *treeview1h;
    
    // Destruction de la fenêtre actuelle
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    gtk_widget_destroy(fenetre_rechercher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

    // Récupération du treeview et appel de la fonction afficher
    treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);  // Passer le treeview1 directement à la fonction afficher

}


void
on_modifier5_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *fenetre_modifier;
    GtkWidget *fenetre_rechercher;
    

    // Destruction de la fenêtre actuelle
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    gtk_widget_destroy(fenetre_rechercher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    fenetre_modifier = create_fenetre_modifier();
    gtk_widget_show(fenetre_modifier);

}

void
on_supprimer5_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
   GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_rechercher;
    

    // Destruction de la fenêtre actuelle
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    gtk_widget_destroy(fenetre_rechercher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    fenetre_supprimer = create_fenetre_supprimer();
    gtk_widget_show(fenetre_supprimer);

}


void
on_retour5_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
  GtkWidget *fenetre_afficher,*fenetre_rechercher ;
    GtkWidget *treeview1h;
    fenetre_rechercher=lookup_widget(objet, "fenetre_rechercher");
    gtk_widget_destroy(fenetre_rechercher);
   
     fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

   treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);

}


void afficher_message(GtkWidget *text_view, const char *message) {
    GtkTextBuffer *buffer;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, message, -1);
}

void on_rechercher_clicked(GtkWidget *objet, gpointer user_data) {
    GtkWidget *idd_rechercher, *text_view5;
    idd_rechercher = lookup_widget(GTK_WIDGET(objet), "idd_rechercher");
    text_view5 = lookup_widget(GTK_WIDGET(objet), "textview5");

    // Récupérer l'ID à rechercher depuis l'entry
    int idd_recherche = atoi(gtk_entry_get_text(GTK_ENTRY(idd_rechercher)));

    // Appeler la fonction de recherche
    don resultat = rechercher("don.txt", idd_recherche);

    // Affichage du résultat dans le GtkTextView
    if (resultat.idd[0] != '\0') {
        // La demande a été trouvée, afficher ses caractéristiques
        char message[256];
        snprintf(message, sizeof(message), "ID de donneur :  %s\n\nNomcomplet :  %s\n\nType de sang :  %s\n\nNature de sang :  %s\n\nQuantité (L) :  %f\n\nDate de la don  %d / %d / %d ",
                 resultat.idd, resultat.nomcomplet, resultat.type, resultat.nature, resultat.quantite, resultat.jour, resultat.mois, resultat.annee);
        afficher_message(text_view5, message);
    } else {
        // L'ID n'a pas été trouvé, afficher un message spécifique
        char message[256];
        snprintf(message, sizeof(message), "IDD %d non trouvé.", idd_recherche);
        afficher_message(text_view5, message);
    }
}






void
on_rechercher1_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_ajout;
    GtkWidget *fenetre_rechercher;
    

    // Destruction de la fenêtre actuelle
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    gtk_widget_destroy(fenetre_ajout);

    // Création et affichage de la nouvelle fenêtre
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    fenetre_rechercher = create_fenetre_rechercher();
    gtk_widget_show(fenetre_rechercher);
}


void
on_rechercher2_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_afficher;
    GtkWidget *fenetre_rechercher;
    

    // Destruction de la fenêtre actuelle
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    gtk_widget_destroy(fenetre_afficher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    fenetre_rechercher = create_fenetre_rechercher();
    gtk_widget_show(fenetre_rechercher);

}


void
on_rechercher3_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_modifier;
    GtkWidget *fenetre_rechercher;
    

    // Destruction de la fenêtre actuelle
    fenetre_modifier = lookup_widget(objet, "fenetre_modifier");
    gtk_widget_destroy(fenetre_modifier);

    // Création et affichage de la nouvelle fenêtre
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    fenetre_rechercher = create_fenetre_rechercher();
    gtk_widget_show(fenetre_rechercher);
}


void
on_rechercher4_clicked                 (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_supprimer;
    GtkWidget *fenetre_rechercher;
    

    // Destruction de la fenêtre actuelle
    fenetre_supprimer = lookup_widget(objet, "fenetre_supprimer");
    gtk_widget_destroy(fenetre_supprimer);

    // Création et affichage de la nouvelle fenêtre
    fenetre_rechercher = lookup_widget(objet, "fenetre_rechercher");
    fenetre_rechercher = create_fenetre_rechercher();
    gtk_widget_show(fenetre_rechercher);
}










void
on_qts_clicked                         (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_calcul;
    GtkWidget *fenetre_afficher;
    

    // Destruction de la fenêtre actuelle
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    gtk_widget_destroy(fenetre_afficher);

    // Création et affichage de la nouvelle fenêtre
    fenetre_calcul = lookup_widget(objet, "fenetre_calcul");
    fenetre_calcul = create_fenetre_calcul();
    gtk_widget_show(fenetre_calcul);
}



void on_calculq_clicked(GtkWidget *objet, gpointer user_data) {
    GtkWidget *textview6qs, *typeq;

    const gchar *type_sang ;
    strcpy(type_sang, gtk_combo_box_get_active_text(GTK_COMBO_BOX(typeq)));
    float resultat;

    // Call your quantite_type function
    resultat = quantite_type("don.txt", type_sang);

    if (resultat >= 0) {
        char message[100];
        snprintf(message, sizeof(message), "%.2f", resultat);
        afficher_message(textview6qs, message);  // Use the correct function here
    } else {
        afficher_message(textview6qs, "Erreur lors du calcul\n");  // Use the correct function here
    }
}
/*void
on_calculq_clicked                     (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *typeq = GTK_WIDGET(gtk_builder_get_object(builder, "typeq"));
    GtkWidget *textview6qs;
    const gchar *type_sang = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(typeq));  // "typeq" est le nom du ComboBox
    float resultat;

    // Appeler votre fonction quantite_type
    resultat = quantite_type("don.txt", type_sang);

    // Mettre à jour le TextView avec le résultat
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview6qs));  // "textview6qs" est le nom du TextView
    gchar *resultat_str = g_strdup_printf("Quantité pour le type %s : %.2f", type_sang, resultat);
    gtk_text_buffer_set_text(buffer, resultat_str, -1);
    g_free(resultat_str);
}  */




void
on_retourq_clicked                     (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *fenetre_calcul;
    GtkWidget *fenetre_afficher;
    

    // Destruction de la fenêtre actuelle
    fenetre_calcul = lookup_widget(objet, "fenetre_calcul");
    gtk_widget_destroy(fenetre_calcul);

    // Création et affichage de la nouvelle fenêtre
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);
}



void
on_treeview1h_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

    GtkTreeSelection *selection;

GtkTreeIter iter;
	gchar* cin;	
	gchar* nom;
	gchar* prenom;
	gchar* role;
	gchar* sexe;
        gchar* age;
	user u;
	GtkWidget *treeview1h;
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path))
	{
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&cin,1,&nom,2,&prenom,3,&role,4,&sexe,5,&age,-1);
	strcpy(u.cin,cin);
	strcpy(u.nom,nom);
	strcpy(u.prenom,prenom);
	strcpy(u.role,role);
	strcpy(u.sexe,sexe);
        strcpy(u.age,age);
	//supprimer_user(u);
	AHafficher_user(treeview1h);}
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        
        gtk_tree_model_get(model, &iter, 0, &cin, -1);
        strcpy(u.cin, cin);

        
        GtkListStore *liststore = GTK_LIST_STORE(model);
        gtk_list_store_remove(liststore, &iter);

        AHsupprimer_user(u);}    
}


void
on_positive_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_negative_radio_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_afficher1_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data)
{
   GtkWidget *fenetre_ajout;
    GtkWidget *fenetre_afficher;
    GtkWidget *treeview1h;

    // Destruction de la fenêtre actuelle
    fenetre_ajout = lookup_widget(objet, "fenetre_ajout");
    gtk_widget_destroy(fenetre_ajout);

    // Création et affichage de la nouvelle fenêtre
    fenetre_afficher = lookup_widget(objet, "fenetre_afficher");
    fenetre_afficher = create_fenetre_afficher();
    gtk_widget_show(fenetre_afficher);

   treeview1h = lookup_widget(fenetre_afficher, "treeview1h");
    afficher(treeview1h);
}



void
on_OGtreeview_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_OGbuttonretour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OGbuttonmodifier_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OGbuttonsupprimer_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_OGbuttonrechercher_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}

