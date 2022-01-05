#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum
{
    Faux,
    Vrai
} Booleen;

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
    int numTel;
    DateDem dateDemande;
} Menage;

typedef struct listeDem
{
    Menage demandeurs;
    struct listeDem *suivant;
}MaillonDem, *ListeDem;

/*Files*/

typedef struct{
    char prenom[31];
    char nom[31];
    char nationalité[3];
    int plafond;
    float revenu;
    int numlogement;
} Locataire;

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

void afficheMenu(void);

void afficheMenuLogement(void);

void afficheMenuLocataire(void);

void afficheMenuLocatairePrecis(void);

void afficheMenuDemLog(void);

void menu(void);

/* Demandeur */
ListeDem initliste(void);

ListeDem lireMenage(FILE *fDem, ListeDem l);

void chargementDem(ListeDem l, FILE *fDem, int *nbD);

void affichage(ListeDem l);

ListeDem insertionEnTeteDem(ListeDem l, int nbPoint, int nbPersonne, float ressourceAnnuel, char *nomDeFamille, int numTel);

ListeDem insertionDem(ListeDem l, int nbPoint, int nbPersonne, float ressourceAnnuel, char *nomDeFamille, int numTel);
