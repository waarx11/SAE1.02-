#include "hlm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ce fichier s'occupe des demandes

ListeDem initliste(void)
{
    return NULL;
}

ListeDem lireMenage(FILE *fDem, ListeDem l)
{
    MaillonDem *m;
    m=(MaillonDem *)malloc(sizeof(MaillonDem));
    if(m==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    fscanf(fDem, "%d %d %d %f %s %s %s %d %d %d %d %d %d ", &m->demandeurs.numDemande, &m->demandeurs.nbPoint, &m->demandeurs.nbPersonne, &m->demandeurs.revenueBrut, m->demandeurs.nomDeFamille, m->demandeurs.prenom, m->demandeurs.nationalite, &m->demandeurs.dateDemande.jours, &m->demandeurs.dateDemande.mois, &m->demandeurs.dateDemande.annee, &m->demandeurs.dateDemande.heure, &m->demandeurs.dateDemande.minute, &m->demandeurs.dateDemande.seconde);
    fscanf(fDem, "%d ", &m->demandeurs.nbNum);
    for (int i=0; i<m->demandeurs.nbNum; i++) 
    {
        m->demandeurs.numTel=(Tel *)malloc(sizeof(Tel));
        fscanf(fDem, "%s %s", m->demandeurs.numTel->libelle, m->demandeurs.numTel->num);
    }
    m->suivant=l;
    return m;
}

ListeDem chargementDem(ListeDem l, int *nbD, char *fic)
{
    FILE *fDem;
    fDem=fopen(fic,"r");
    if (fDem == NULL)
    {
        printf("Problème ouverture fichier Dem");
        return NULL;
    }
    fscanf(fDem, "%d", nbD);
    for(int i=0;i<*nbD;i++)
        l=lireMenage(fDem,l);
    fclose(fDem);
    return l;
}

void affichageDem(ListeDem l)
{
    if (l==NULL)
        return;
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Numero de dossier : %d\n\n", l->demandeurs.numDemande);
    printf("%d %d %f %s\n", l->demandeurs.nbPoint, l->demandeurs.nbPersonne, l->demandeurs.revenueBrut, l->demandeurs.nomDeFamille);
    for (int i=0; i<l->demandeurs.nbNum; i++) 
    {
        printf("%s :\n%s\n", l->demandeurs.numTel->libelle, l->demandeurs.numTel->num);
    }
    printf("Le %d/%d/%d a %d:%d:%d\n", l->demandeurs.dateDemande.jours, l->demandeurs.dateDemande.mois, l->demandeurs.dateDemande.annee, l->demandeurs.dateDemande.heure, l->demandeurs.dateDemande.minute, l->demandeurs.dateDemande.seconde);
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    affichageDem(l->suivant);
}

ListeDem insertionEnTeteDem(ListeDem l, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite)
{
    int jours, mois, an, h, min, s, numDemande, nbNum;
    char libelle[31], numTel[16];
    MaillonDem *m;
    m=(MaillonDem *)malloc(sizeof(MaillonDem));
    if(m==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    //Valeur aléatoire compris entre 0 et 5000
    srand(time(NULL));
    numDemande=rand() %5000;
    //date courant
    time_t now;
    struct tm *local = localtime(&now);
    h=local->tm_hour;
    min=local->tm_min;
    s=local->tm_sec;
    jours=local->tm_mday;
    mois=local->tm_mon+1;
    an=local->tm_year+1900;
    m->demandeurs.numDemande=numDemande+1;
    m->demandeurs.nbPoint=nbPoint;
    m->demandeurs.nbPersonne=nbPersonne;
    m->demandeurs.revenueBrut=revenueBrut;
    strcpy(m->demandeurs.nomDeFamille,nomDeFamille);
    strcpy(m->demandeurs.prenom,prenom);
    strcpy(m->demandeurs.nationalite,nationalite);
    m->demandeurs.dateDemande.jours=jours;
    m->demandeurs.dateDemande.mois=mois;
    m->demandeurs.dateDemande.annee=an;
    m->demandeurs.dateDemande.heure=h;
    m->demandeurs.dateDemande.minute=min;
    m->demandeurs.dateDemande.seconde=s;
    printf("Combien de numero de telephone posseder vous?");
    scanf("%d", &nbNum);
    m->demandeurs.nbNum=nbNum;
    for (int i=0; i<nbNum; i++) 
    {
        m->demandeurs.numTel=(Tel*)malloc(sizeof(Tel));
        fgets(libelle, 30, stdin);
        libelle[strlen(libelle)-1]='\0';
        strcpy(m->demandeurs.numTel->libelle,libelle);
        fgets(numTel, 15, stdin);
        numTel[strlen(numTel)-1]='\0';
        strcpy(m->demandeurs.numTel->num,numTel);
    }
    m->suivant=l;
    return m;
}

ListeDem insertionDem(ListeDem l, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite)
{
    if(l==NULL)
        return insertionEnTeteDem(l, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    if (l->demandeurs.nbPoint<nbPoint) 
        return insertionEnTeteDem(l, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    l->suivant=insertionDem(l->suivant, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    return l;
}

