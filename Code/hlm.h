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
    char num[15];
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
    char nomDeFamille[31];
    char prenom[31];
    char nationalite[3];
    int nbNum;
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
    int numloca;
    char prenom[31];
    char nom[31];
    char nationalite[3];
    int plafond;
    float revenu;
    int numlogement;
    float prixLog;
    int nbNumTel;
    Tel *numTel;
    Date datedebutloca;
}Locataire;


typedef struct maillonloc {
    Locataire loc;
    struct maillonloc *suiv;
}MaillonLoc;

typedef MaillonLoc *Files;

/*Piles*/

typedef struct
{
    int numLogement;
    char typeLog[3];
    int nbChambre;
    float surfaceLog;
    float prixLog;
    char dispo[5];
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

void MenuLogement(Logement tLog[],int *nbLog);

void affichMenuLogement(void);

Files MenuLocataire(Files lc, int *nbL);

void affichMenuLocataire(void);

Files MenuChoixTrie (Files lc, int *nbL);

void affichChoixTrieLoca(void);

ListeDem MenuDemLog (ListeDem ld, int *nbD);

void affichMenuDemLog(void);

void sauvegardeTout(ListeDem ld, char *ficDem, int nbD, Files f, char *ficLoc);

/* Logement */

Logement lireLog(FILE *fe);

Logement* chargeLogement(FILE *fe, int *nbL);

void affichageLog(Logement tLog[], int nbLog);

int supprime(Logement *tLog, int nbLog);

int rechercheDico(Logement *tLog, int nbLog, int value);

int insertionLog(Logement *tLog, int nbLog);

Booleen numLogExiste(Logement *tLog, int value, int nbLog);

/* Locataire */

Locataire lireLocataire(FILE *fLoca);

Files chargementLoc (Files f, int *nbelem, char *fic2);

void AffichLocataire(Files f);

void AffichLocatairePrecis(Files f);

void AffichTab (Locataire *tloc[], int nbtl);

Files Enfillercharge (Files f, Locataire loc);

Files EnfilerLoca (Files f,int numloca, char prenom[], char nom[], char nationalite[], int plafond, float revenu, int numloge);

Files Defiler (Files f);

Files ViderFile (Files *pf);

Files FileVide(void);

Booleen EstVide (Files f);

void RechLoca (Files f, int numlocataire);

int TransfertTab (Files f, Locataire *tloc[], int tmax);

Locataire ViderTab (Locataire *tloc[], int nbtl);

Files TransfertFiles (Files f, Locataire *tloc[], int nbtl);

int RechMinPrixLoge (Locataire *tloc[], int nbtl, int i);

int RechMinNomLoca (Locataire *tloc[], int nbtl, int i);

int RechMinDate (Locataire *tloc[], int nbtl, int i);

int RechMinNumLoca (Locataire *tloc[], int nbtl, int i);

void Permute (Locataire *tloc[], int x, int y);

void TriePermuteLoge (Locataire *tloc[], int nbtl);

void TriePermuteDate (Locataire *tloc[], int nbtl);

void TriePermuteNumLoca (Locataire *tloc[], int nbtl);

void TriePermuteNomLoca (Locataire *tloc[], int nbtl);

void sauvegardeLoc(Files f, FILE *fLoc);

/* Demandeur */
ListeDem initliste(void);

ListeDem lireMenage(FILE *fDem, ListeDem l);

ListeDem chargementDem(ListeDem l, int *nbD, char *fic);

void affichageDem(ListeDem l);

Booleen numExiste(ListeDem l, int value);

ListeDem insertionEnTeteDem(ListeDem l, int numDemande, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite);

ListeDem insertionDem(ListeDem l, int numDemande, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite);

ListeDem rechercheUnDemandeur(ListeDem l, int value);

void afficherUnDemandeur(ListeDem l, int value);

ListeDem suppressionEnTete(ListeDem l, int *nbD);

ListeDem suppression(ListeDem l, int suppDem, int *nbD);

ListeDem modification(ListeDem l, int modif);

ListeDem expirationDemEnTete(ListeDem l, int *nbD);

ListeDem expirationDem(ListeDem l, int *nbD);

void suppressionAll(ListeDem l, int *nbD);

void sauvegardeDem(ListeDem l, FILE *fDem);