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
    fscanf(fDem, "%d %d %d %f %s %s %s %d %d %d %d %d %d", &m->demandeurs.numDemande, &m->demandeurs.nbPoint, &m->demandeurs.nbPersonne, &m->demandeurs.revenueBrut, m->demandeurs.nomDeFamille, m->demandeurs.prenom, m->demandeurs.nationalite, &m->demandeurs.dateDemande.jours, &m->demandeurs.dateDemande.mois, &m->demandeurs.dateDemande.annee, &m->demandeurs.dateDemande.heure, &m->demandeurs.dateDemande.minute, &m->demandeurs.dateDemande.seconde);
    fscanf(fDem, "%d ", &m->demandeurs.nbNum);
    m->demandeurs.numTel=(Tel *)malloc(sizeof(Tel)*m->demandeurs.nbNum);
    for (int i=0; i<m->demandeurs.nbNum; i++) 
    {
        fscanf(fDem, "%s %s", m->demandeurs.numTel[i].libelle, m->demandeurs.numTel[i].num);
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
    affichageDem(l->suivant);
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Numero de dossier : %d\n\n", l->demandeurs.numDemande);
    printf("Point : %d \nPersonne a charge : %d \nRevenue brut : %.2f \nNom : %s %s\nNationaliter : %s\n\n", l->demandeurs.nbPoint, l->demandeurs.nbPersonne, l->demandeurs.revenueBrut, l->demandeurs.nomDeFamille, l->demandeurs.prenom, l->demandeurs.nationalite);
    for (int i=0;i<l->demandeurs.nbNum;i++) 
    {
        printf("%s :\n%s\n\n", l->demandeurs.numTel[i].libelle, l->demandeurs.numTel[i].num);
    }
    printf("Fait le : %d/%d/%d a %d:%d:%d\n", l->demandeurs.dateDemande.jours, l->demandeurs.dateDemande.mois, l->demandeurs.dateDemande.annee, l->demandeurs.dateDemande.heure, l->demandeurs.dateDemande.minute, l->demandeurs.dateDemande.seconde);
    printf("-----------------------------------------------------------------------------------------------------\n\n");
}

void affichageUnDem(ListeDem l)
{
    if (l==NULL)
        return;
    affichageDem(l->suivant);
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Numero de dossier : %d\n\n", l->demandeurs.numDemande);
    printf("Point : %d \nPersonne a charge : %d \nRevenue brut : %.2f \nNom : %s %s\n Nationaliter : %s \n\n", l->demandeurs.nbPoint, l->demandeurs.nbPersonne, l->demandeurs.revenueBrut, l->demandeurs.nomDeFamille, l->demandeurs.prenom, l->demandeurs.nationalite);
    for (int i=0;i<l->demandeurs.nbNum;i++) 
    {
        printf("%s :\n%s\n\n", l->demandeurs.numTel[i].libelle, l->demandeurs.numTel[i].num);
    }
    printf("Fait le : %02d/%02d/%02d a %02d:%02d:%d\n", l->demandeurs.dateDemande.jours, l->demandeurs.dateDemande.mois, l->demandeurs.dateDemande.annee, l->demandeurs.dateDemande.heure, l->demandeurs.dateDemande.minute, l->demandeurs.dateDemande.seconde);
    printf("-----------------------------------------------------------------------------------------------------\n\n");
}

// int rechercheDem(ListeDem t, int n, int val)
// {
//     int i;
//     for(i=0;i<t->demandeurs.numDemande;i++)
//     {
//         if(t[i]>val)
//             return i;
//     }
//     return i;
// }

// void insertion(int *t, int r, int k)
// {
//     int temp=t[k];
//     for(int i=k;i>r;i--)
//     {
//         t[i]=t[i--];
//     }
//     t[r]=temp;
// }

// void tri(int t, int n)
// {
//     int k;
//     for(k=1;k<n;k++)
//     {
//         n=RechPos(t,k,t[h]);
//         Insertion(t,r,k);
//     }
// }

ListeDem insertionEnTeteDem(ListeDem l, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite)
{
    int jours, mois, an, h, min, s, numDemande, nbNum;
    char libelle[32], numTel[16];
    MaillonDem *m;
    ListeDem existe;
    m=(MaillonDem *)malloc(sizeof(MaillonDem));
    if(m==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    //Valeur aléatoire compris entre 0 et 5000
    srand(time(NULL));
    numDemande=rand() %5000;
    existe=rechercheUnDemandeur(l, numDemande);
    while (existe!=NULL) 
    {
        numDemande=rand() %5000;
        existe=rechercheUnDemandeur(l, numDemande);
    }
    //date courant
    time_t now;
    time(&now);
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
    printf("Combien de numero de telephone posseder vous : ");
    scanf("%d%*c", &nbNum);
    m->demandeurs.nbNum=nbNum;
    m->demandeurs.numTel=(Tel*)malloc(sizeof(Tel)*nbNum);
    for (int i=0, s=1; i<nbNum; i++, s++) 
    {
        printf("Ecrit le libelle du %d numero\n", s);
        fgets(libelle, 32, stdin);
        libelle[strlen(libelle)-1]='\0';
        strcpy(m->demandeurs.numTel[i].libelle,libelle);
        printf("Ecrit le %d numero\n", s);
        fgets(numTel, 16, stdin);
        numTel[strlen(numTel)-1]='\0';
        strcpy(m->demandeurs.numTel[i].num,numTel);
    }
    m->suivant=l;
    return m;
}

ListeDem rechercheUnDemandeur(ListeDem l, int value)
{
    if(l==NULL)
        return l;//comme faire return NULL parsque l==NULL actuellement
    if(value==l->demandeurs.numDemande)
        return l;
    return rechercheUnDemandeur(l->suivant, value);
}

ListeDem insertionDem(ListeDem l, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite)
{
    if(l==NULL)
        return insertionEnTeteDem(l, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    if (l->demandeurs.nbPoint>nbPoint) 
        return insertionEnTeteDem(l, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    l->suivant=insertionDem(l->suivant, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    return l;
}

void afficherUnDemandeur(ListeDem l, int value)
{
    if (l==NULL)
        return;
    afficherUnDemandeur(l->suivant,value);
    if (l->demandeurs.numDemande==value) 
    {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("Numero de dossier : %d\n\n", l->demandeurs.numDemande);
        printf("Point : %d \nPersonne a charge : %d \nRevenue brut : %.2f \nNom : %s %s\n", l->demandeurs.nbPoint, l->demandeurs.nbPersonne, l->demandeurs.revenueBrut, l->demandeurs.nomDeFamille, l->demandeurs.prenom);
        for (int i=0;i<l->demandeurs.nbNum;i++) 
        {
            printf("%s :\n%s\n", l->demandeurs.numTel[i].libelle, l->demandeurs.numTel[i].num);
        }
        printf("Fait le : %d/%d/%d a %d:%d:%d\n", l->demandeurs.dateDemande.jours, l->demandeurs.dateDemande.mois, l->demandeurs.dateDemande.annee, l->demandeurs.dateDemande.heure, l->demandeurs.dateDemande.minute, l->demandeurs.dateDemande.seconde);
        printf("-----------------------------------------------------------------------------------------------------\n\n");

    }
}

ListeDem suppressionEnTete(ListeDem l)
{
    ListeDem t;
    t=l->suivant;
    for(int i=0; i<l->demandeurs.nbNum;i++)
        free(l->demandeurs.numTel+i);
    free(l);
    return t;
}

ListeDem suppression(ListeDem l, int suppDem)
{
    if(l==NULL)
        return l;//équivaux a null
    if (suppDem<l->demandeurs.numDemande)
        return l;//équivaux a null
    if (l->demandeurs.numDemande==suppDem)
        return suppressionEnTete(l);
    l->suivant=suppression(l->suivant, suppDem);
    return l;
}

ListeDem modificationEnTete(ListeDem l)
{
    int nbPoint, nbPersonne, revenueBrut, nbNum;
    char choixNum, libelle[32], numTel[16];
    printf("Combien de point avez-vous ?");
    printf("Pour rappel : \n");
    printf("Les personnes handicapees : 30 points\nLes personnes victimes de violences au sein du couple :15 points\nLes personnes hébergées ou logées temporairement : 15 points\nLes personnes sans aucun logement ou menacées dexpulsion sans relogement : 10 points\nLes personnes logées dans un logement insalubre ou dangereux : 8 points\n");
    printf("Combien de point avez-vous : ");
    scanf("%d",&nbPoint);
    printf("Combien de personne avez-vous a charge : ");
    scanf("%d",&nbPersonne);
    printf("Qu'elle sont vos revenue : ");
    scanf("%d%*c",&revenueBrut);
    l->demandeurs.nbPoint=nbPoint;
    l->demandeurs.nbPersonne=nbPersonne;
    l->demandeurs.revenueBrut=revenueBrut;
    printf("Voulez changer vos numero de telephones (O pour oui) : ");
    scanf("%c%*c",&choixNum);
    if (choixNum=='O'||choixNum=='o') 
    {
        for(int i=0; i<l->demandeurs.nbNum;i++)
            free(l->demandeurs.numTel+i);
        printf("Combien de numero de telephone posseder vous : ");
        scanf("%d%*c", &nbNum);
        l->demandeurs.nbNum=nbNum;
        l->demandeurs.numTel=(Tel*)malloc(sizeof(Tel)*nbNum);
        for (int i=0, s=1; i<nbNum; i++, s++) 
        {
            printf("Ecrit le libelle du %d numero\n", s);
            fgets(libelle, 32, stdin);
            libelle[strlen(libelle)-1]='\0';
            strcpy(l->demandeurs.numTel[i].libelle,libelle);
            printf("Ecrit le %d numero\n", s);
            fgets(numTel, 16, stdin);
            numTel[strlen(numTel)-1]='\0';
            strcpy(l->demandeurs.numTel[i].num,numTel);
        }
        //la modification du nbPoint nous oblige a replacer le maillon au bon endroit. Faire un trie et adapter son changement de point pour avoir un bon emplacement
    }
    return l;
}

ListeDem modification(ListeDem l, int modif)
{
    if(l==NULL)
        return l;//équivaux a null
    if (modif<l->demandeurs.numDemande)
        return l;//équivaux a null
    if (l->demandeurs.numDemande==modif)
        return modificationEnTete(l);
    l->suivant=modification(l->suivant, modif);
    return l;
}