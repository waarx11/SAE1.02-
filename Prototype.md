# Prototype des fonctions 

## Menu :

* void Logement (void)
    * Cette fonction aura pour but d'avoir un menu d'utilisation des diverse fonction appelé dans cette catégorie Logement

* void Locataire (void)
    * Cette fonction aura pour but d'avoir un menu d'utilisation des diverse fonction appelé dans cette catégorie Locataire 

* void DemandesLogement (void)
    * Cette fonction aura pour but d'avoir un menu d'utilisation des diverse fonction appelé dans cette catégorie DemandesLogement

* void Menu (void)
    * Cette fonction aura pour but de facilité la transition entre les fonctions menu précédement cité

## Structure :



## Logement :

* AjoutLogement()
    * Cette fonction aura pour but d'ajouter un logement dans un fichier

* SuppressionLogement()
    * Cette fonction aura pour objectif de supprimer un logement dans un fichier

* AffichLogeHLM()
    * Cette fonction affichera les logement que possède HLM63 (trié de manière ?)

* AffichLogeDispo()
    * Cette fonction affichera tout les logement disponible par type de logement (T1/T2/...)

* RechercheLoge()
    * Cette fonction permet de rechercher un logement dans un ficher

* ChargementLoge()
    * Cette fonction va chargé tout les logement dans un fichier


## Locataire :

* AffichLocataire() -> doit être triée
    * Cette fonction affichera l'ensemble des locataire avec sa nationalité ou carte de séjour, sous quel plafond il se trouve, nombre d'individu à charge et le nombre de points attribué

* RechLocataire()
    * Cette fonction aura pour but de rechercher un locataire dans le fichier / liste

* AffichUnLocataire()
    * Cette fonction affichera les informations d'une seul locataire

* AffichNationalité()
    * Cette fonction affichera la nationalité du d'un locataire

* AffichPlafond()
    * Cette fonction affichera le numéro du plafond que l'individu atteint

* AffichCharge()
    * Cette fonction affichera le nombre d'individu a la charge du locataire

* AffichPoint()
    * Cette fonction affichera le nombre de points attribué au locataire

* AffichRevenu()
    * Cette fonction affichera les revenu annuel/mensuel du locataire


## DemandeLogement

* SauvDemande()
    * Cette fonction nous permet d'enregitrer une demande de logement dans le fichier / liste

* SupDemande()
    * Cette fonction nous permet de supprimer une demande de logement dans le fichir / liste

* ModifDemande()
    * Cette fonction nous permet de modifier une demande de logement dans le ficher / liste

* AffichDemande()
    * Cette fonction nous permet d'afficher toute les demandes en cours pour un logement

* TraitementDemande()
    * Cette fonction nous permet de traiter les demande et d'affecter automatiquement un demandeurs de logement dans un logement disponible

