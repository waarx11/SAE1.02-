#include "hlm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \file hlmDemandeur.c
 * \brief Emsemble des fonctions permettant de gérés la partit sur les demandes de logement
 * \autor VERDIER Nathan, MUZARD Thomas
 * \date 14 janvier 2020
 * 
 * Dans cette partie du programme, nous avons choisie d'utiliser les listes chainés pour exploité un peu toute les notions vu en cours.
 * De plus, les liste chainée permettent facillement d'inserer de façon trier, permettant de facilité la gestion de nos demandeurs
 *
 * Dans cette partit, nous utilisons pas spécialement de trie, nous inserons trier les demandeurs par rapport a leurs points
 */

/**
 * \brief initialisation de la liste
 * \return return une liste
 */
ListeDem initliste(void)
{
    return NULL;
}

/**
 * \brief 
 * \param *fDem : Fichier demandeurs
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur les demandeurs
 * \return Une liste
 */
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
    if(m->demandeurs.numTel==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    for (int i=0; i<m->demandeurs.nbNum; i++) 
    {
        fscanf(fDem, "%s %s", m->demandeurs.numTel[i].libelle, m->demandeurs.numTel[i].num);
    }
    m->suivant=l;
    return m;
}

/**
 * \brief chargement demandeurs
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur les demandeurs
 * \param *nbD nombre de demandeurs dans le fichier
 * \param *fic nom du fichier
 * \return Une liste
 */
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

/**
 * \brief Affichage liste demandeurs
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur un demandeurs
 */
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

/**
 * \brief Supprime un demandeurs ayant fait une demande dépassant les 1 an
 * \param ListeDem l: c'est un pointeur d'un maillon sur les demandeurs
 * \param *nbD nombre de demandeurs
 * \return Une liste
 */
ListeDem expirationDem(ListeDem l, int *nbD)
{
    if (l==NULL)
        return NULL;
    l->suivant=expirationDem(l->suivant, nbD);
    return expirationDemEnTete(l, nbD);
    return l;

}

/**
 * \brief Supprime un demandeurs en tête
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur les demandeurs
 * \param *nbD nombre de demandeurs
 * \return Une liste
 */
ListeDem expirationDemEnTete(ListeDem l, int *nbD)
{
    int jours, mois, an;
    srand(time(NULL));
    //date courant
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    jours=local->tm_mday;
    mois=local->tm_mon+1;
    an=local->tm_year+1900;
    if (an==l->demandeurs.dateDemande.annee) 
        return l;
    else if (an-1==l->demandeurs.dateDemande.annee) 
    {
        if (l->demandeurs.dateDemande.mois-mois>0) 
            return l;
        else 
        {
            if (jours<l->demandeurs.dateDemande.jours) 
                return l;
            else
                return suppressionEnTete(l, nbD);
        }
    }
    else
        return suppressionEnTete(l, nbD);
}

/** 
 * \brief Insère en tête de liste un demandeurs
 * \param Liste l : c'est un pointeur sur un maillon pointant sur un demandeurs
 * \param numDemande numéro demandeurs
 * \param nbPoint nombre de point
 * \param nbPersonne nombre de personne
 * \param revenueBrut revenu du demandeurs
 * \param *nomDeFamille nom de famille du demandeurs
 * \param *prenom prénom du demandeurs
 * \*nationalite nationalite du demandeurs
 * \return Une liste
 */
ListeDem insertionEnTeteDem(ListeDem l, int numDemande, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite)
{
    int jours, mois, an, h, min, s, nbNum;
    char libelle[32], numTel[16];
    MaillonDem *m;
    m=(MaillonDem *)malloc(sizeof(MaillonDem));
    if(m==NULL)
    {
        printf("Problème malloc\n");
        exit(1);
    }
    //Valeur aléatoire compris entre 0 et 5000
    srand(time(NULL));
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
    m->demandeurs.numDemande=numDemande;
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
    while (nbNum==0) 
    {   
        printf("Vous devez nous donner au moins un numero de telephone : ");
        scanf("%d%*c", &nbNum);
    }
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

/**
 * \brief Regarde si le numéro de demandeurs existe
 * \param ListeDem l : c'est un pointeur d'un maillon pointant sur les demandeurs
 * \param value : le futur numéro des demandeurs
 * \return Vrai ou Faux
 */
Booleen numExiste(ListeDem l, int value)
{
    if(l==NULL)
        return Faux;
    if(value==l->demandeurs.numDemande)
        return Vrai;
    return numExiste(l->suivant, value);
}

/**
 * \brief recherche un demandeurs dans la liste
 * \param ListeDem l : c'est un pointeur d'une maillon pointant sur un demandeurs
 * \param value numéro de demandeurs
 * \return Une liste
 */
ListeDem rechercheUnDemandeur(ListeDem l, int value)
{
    if(l==NULL)
    {
        printf("Demandeur introuvable");
        return l;//comme faire return NULL parsque l==NULL actuellement
    }
    if(value==l->demandeurs.numDemande)
        return l;
    return rechercheUnDemandeur(l->suivant, value);
}

/**
 * \brief insère dans la liste un demandeurs
 * \param ListeDem l : c'est un pointeur d'un maillon pointant sur un demandeurs
 * \param numDemande numéro demandeurs
 * \param nbPoint nombre de point
 * \param nbPersonne nombre de personne
 * \param revenueBrut revenu du demandeurs
 * \param *nomDeFamille nom de famille du demandeurs
 * \param *prenom prénom du demandeurs
 * \*nationalite nationalite du demandeurs
 * \return Une liste
 */
ListeDem insertionDem(ListeDem l, int numDemande, int nbPoint, int nbPersonne, float revenueBrut, char *nomDeFamille, char *prenom, char *nationalite)
{
    if(l==NULL)
        return insertionEnTeteDem(l, numDemande, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    if (l->demandeurs.nbPoint>nbPoint) 
        return insertionEnTeteDem(l, numDemande, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    l->suivant=insertionDem(l->suivant, numDemande, nbPoint, nbPersonne, revenueBrut, nomDeFamille, prenom, nationalite);
    return l;
}

/**
 * \brief Affiche un demandeur
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur un demandeurs
 * \param value numéro du demandeurs
 */
void afficherUnDemandeur(ListeDem l, int value)
{
    if (l==NULL)
    {
        printf("Demandeur introuvable !\n");
        return;
    }
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

/**
 * \brief Supprime un élément en tête de liste
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur les demandeurs
 * \param *nbD nombre de demandeur
 * \return Une liste
 */
ListeDem suppressionEnTete(ListeDem l, int *nbD)
{
    ListeDem t;
    t=l->suivant;
    free(l->demandeurs.numTel);
    free(l);
    (*nbD)--;
    return t;
}

/**
 * \brief Supprime un élément de la liste
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur un demandeurs
 * \param suppDem Supprime se numéro de demandeurs
 * \param *nbD Nombre de demandeurs
 * \return Une liste
 */
ListeDem suppression(ListeDem l, int suppDem, int *nbD)
{
    if(l==NULL)
    {
        printf("Demandeur introuvable\nsuppression annuler!\n");
        return l;//équivaux a null
    }
    if (l->demandeurs.numDemande==suppDem)
    {
		printf("Demandeur supprimer\n");
        return suppressionEnTete(l, nbD);
    }
    l->suivant=suppression(l->suivant, suppDem, nbD);
    return l;
}

/**
 * \brief Supprime tout les éléments du fichier
 * \param ListeDem l : c'est un pointeur sur maillon pointant sur les demandeurs
 * \param *nbD c'est le nombre d'élément dans le fichier
 */
void suppressionAll(ListeDem l, int *nbD)
{
    if(l==NULL)
        return;//équivaux a null
    suppressionAll(l->suivant, nbD);
    suppressionEnTete(l, nbD);
    return;
}

/**
 * \brief Modification d'une demande en tête de liste
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur les demandeurs
 * \return Une liste
 */
ListeDem modificationEnTete(ListeDem l)
{
    int nbPoint, nbPersonne, revenueBrut, nbNum;
    char choixNum, libelle[32], numTel[16];
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
        free(l->demandeurs.numTel);
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
/**
 * \brief Modifie les informations d'une demande de logement dans la liste
 * \param ListeDem l : c'est un pointeur sur un maillon pointant sur un demandeurs
 * \modif numéro de locataire a modifier
 * \return une Liste
 */
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

/**
 * \brief Sauvegarde dans le fichier l'ajout ou la modification d'une demandes de logement
 * \param ListeDem l :c'est un pointeur sur un maillon pointant sur un demandeurs
 * \param *fDem : ficher des demandeurs
 */
void sauvegardeDem(ListeDem l, FILE *fDem)
{
    if (l==NULL)
        return;
    sauvegardeDem(l->suivant, fDem);
    fprintf(fDem, "%d %d %d %.2f %s %s %s %d %d %d %d %d %d %d ", l->demandeurs.numDemande, l->demandeurs.nbPoint, l->demandeurs.nbPersonne, l->demandeurs.revenueBrut, l->demandeurs.nomDeFamille, l->demandeurs.prenom, l->demandeurs.nationalite, l->demandeurs.dateDemande.jours, l->demandeurs.dateDemande.mois, l->demandeurs.dateDemande.annee, l->demandeurs.dateDemande.heure, l->demandeurs.dateDemande.minute, l->demandeurs.dateDemande.seconde, l->demandeurs.nbNum);
    for (int i=0; i<l->demandeurs.nbNum; i++) 
    {
        fprintf(fDem, "%s %s ", l->demandeurs.numTel[i].libelle, l->demandeurs.numTel[i].num);
    }
    fprintf(fDem,"\n");
}