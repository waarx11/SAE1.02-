#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum
{
    Faux,
    Vrai
} Booleen;

typedef struct
{
    char libelle[30];
    int num;
} Tel;

typedef struct {int jours, mois, annee, heure, minute, seconde;} DateDem;

typedef struct {int jours, mois, annee;} Date;

/*Liste Chainer 
Seules les demandes de demandeurs ayant leur papier en règle et ne dépassant pas le plafond de ressources sont enregistrées*/

typedef struct
{
    int numDemande;
    int nbPoint;
    int nbPersonne;
    float revenueBrut;
    char nomDeFamille[50];
    Tel *numTel;
    DateDem dateDemande;
} Menage;

typedef struct listeDem
{
    Menage demandeurs;
    struct listeDem *suivant;
}MaillonDem, *ListeDem;

/*Files*/

typedef struct {
    char prenom[31];
    char nom[31];
    char nationalite[4];
    int plafond;
    float revenu;
    int numlogement;
    Tel *numTel;
    Date datedebutloca;
}Locataire;

typedef struct maillonloc {
    Locataire loc;
    struct maillonloc *suiv;
}MaillonLoc, *FilesLoc;

typedef MaillonLoc *Files;

/*Piles*/

typedef struct
{
    int numLogement;
    char typeLog[3];
    int nbChambre;
    float surfaceLog;
    float prixLog;
    Date dateAchat;
} Logement;

typedef struct maillonLog
{
    Logement logement;
    struct maillonLog *suivant;
} MaillonLog, *PileLog;


/* Menu */

void menu(void);

void affichMenu(void);

void MenuLogement(PileLog lg);

void affichMenuLogement(void);

void MenuLocataire(FilesLoc lc);

void affichMenuLocataire(void);

void MenuChoixTrie (void);

void affichChoixTrieLoca(void);

void MenuDemLog(ListeDem ld);

void affichMenuDemLog(void);

/* Locataire */

FilesLoc lireLocataire(FILE *fLoca, FilesLoc lc);

FilesLoc chargementLoc(FilesLoc lc, char *fic2, int *nbL);

FilesLoc AffichLocataire(Files f);

FilesLoc AffichLocatairePrecis(Files f);

FilesLoc Enfiler (Files f, char prenom[], char nom[], char nationalite[], int plafond, float revenu, int numloge, int annee, int mois, int jour);

FilesLoc Defiler (Files f);

Files FileVide(void);

void Vider (Files *f);

Booleen EstVide (Files f);

/* Demandeur */
ListeDem initliste(void);

ListeDem lireMenage(FILE *fDem, ListeDem l);

ListeDem chargementDem(ListeDem l, int *nbD, char *fic);

void affichageDem(ListeDem l);

ListeDem insertionEnTeteDem(ListeDem l, int nbPoint, int nbPersonne, float ressourceAnnuel, char *nomDeFamille, int numTel);

ListeDem insertionDem(ListeDem l, int nbPoint, int nbPersonne, float ressourceAnnuel, char *nomDeFamille, int numTel);
