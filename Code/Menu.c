#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hlm.h"


void afficheMenu(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Information sur Locataire \t\t\t |\n");
	printf("| 2. Logement \t\t\t\t\t |\n");
	printf("| 3. Demande de logement \t\t\t |\n");
	printf("| 9. Quitter \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void afficheMenuLogement(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Ajouter un logement  \t \t \t |\n");
	printf("| 2. Supprimer un logement \t\t\t |\n");
	printf("| 3. Afficher posséder par des HLM63 \t\t |\n");
	printf("| 4. Afficher les types de logement \t\t |\n");
	printf("| 5. Afficher les types de logement disponuble   |\n");
	printf("| 9. Quitter \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void afficheMenuLocataire(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Afficher la liste des locataires \t\t |\n");
	printf("| 2. Recherche d'un locataire \t\t\t |\n");
	printf("| 9. Quitter \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void afficheMenuLocatairePrecis(void)
{
	printf("\t Que voulez vous savoir sur ce locataire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Afficher toutes les informations \t\t |\n");
	printf("| 2. Nationalité / Carte de séjour \t\t |\n");
	printf("| 3. Numéro plafond concerné \t\t\t |\n");
	printf("| 4. Nombre d'individu à charge\t\t\t |\n");
	printf("| 5. Nombre de points attribués\t\t\t |\n");
	printf("| 6. Revenu annuel du locataire\t\t\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void afficheMenuDemLog(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Enregistrer une demande \t\t\t |\n");
	printf("| 2. Modifier une demande\t\t\t |\n");
	printf("| 3. Supprimer une demande\t\t\t |\n");
	printf("| 4. Afficher toute les demandes\t\t |\n");
	printf("| 5. Traité les demandes en attente\t\t |\n");
	printf("| 9. Quitter \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void menu(void)
{
FILE *fe;
int choix, choix2, choix3, locataire;
afficheMenu();
scanf("%d%*c", &choix);

while (choix != 1 && choix != 2 && choix != 3 && choix != 9)
{
	printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
	scanf("%d%*c", &choix);
}

 while (choix != 9)
 {
	switch (choix)
	{
		case 1:
		afficheMenuLocataire();
		scanf("%d%*c", &choix2);

		while (choix2 != 1 && choix2 != 2 && choix2 != 9)
		{
			printf("Choix doit être égale à 1, 2 ou 9. Retapez : ");
			scanf("%d%*c", &choix2);
		}

		while (choix != 9)
		{
			switch (choix2)
			{
			case 1:
			// Affichage de la liste de locataire
			break;

			case 2:
			// Fonction recherche locataire
			//scanf("%d", &locataire);
			afficheMenuLocatairePrecis();
			scanf("%d%*c", &choix3);

			while (choix3 != 1 && choix3 != 2 && choix3 != 3 && choix3 != 4 && choix3 != 5 && choix3 != 6 && choix3 != 9)
			{
				printf("Choix doit être égale à 1, 2, 3, 4, 5, 6 ou 9. Retapez : ");
				scanf("%d%*c", &choix3);
			}

			while (choix3 != 9)
			{
				switch (choix3)
				{
					case 1:
					// Fonction d'affichage de toutes les informations du locataire
					break;

					case 2:
					// Fonction d'affichage de la nationnalité ou carnet visite
					break;

					case 3:
					// Fonction d'affichage n° plafond atteint par le locataire
					break;

					case 4:
					// Fonction d'affiche du nombre d'individu à la charge du locataire
					break;

					case 5:
					// Fonction d'affichage du nombre de points attribuer au locataire
					break;

					case 6:
					// Fonction d'affichage du revenu annuel du locataire
					break;
				}
			}
			break;
			}
		}
		break;

		case 2:
		afficheMenuLogement();
		scanf("%d%*c", &choix2);

		while (choix2 != 1 && choix2 != 2 && choix2 != 3 && choix2 != 4 && choix2 != 5 && choix2 != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
			scanf("%d%*c", &choix2);
		}

		while (choix2 != 9)
		{
			switch (choix2)
			{
				case 1:
				// Fonction d'ajout logement
				break;

				case 2:
				// Fonction suppression de logement
				break;

				case 3:
				// Fonction d'affichage des logement possédé par des HLM63
				break;

				case 4:
				// Fonction d'affichage des types des logements
				break;

				case 5:
				// Fonction d'affichage des logements disponiblent
				break;
			}
		}
		break;

		case 3:
		afficheMenuDemLog();
		scanf("%d%*c", &choix2);

		while (choix2 != 1 && choix2 != 2 && choix2 != 3 && choix2 != 4 && choix2 != 5 && choix2 != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
			scanf("%d%*c", &choix2);
		}

		while (choix2 != 9)
		{
			switch (choix2)
			{
				case 1:
				// Fonction d'enregistrer une demande
				break;

				case 2:
				// Fonction modification d'une demande
				break;

				case 3:
				// Fonction suppression d'une demande
				break;

				case 4:
				// Fonction d'affichage de toutes les demandes
				break;

				case 5:
				// Fonction de traitement des demandes en attente
				break;
			}
		}
		break;

	}
	afficheMenu();
	printf("Que voulez-vous faire : ");
	scanf("%d%*c", &choix);

	while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 9)
	{
		printf("Choix doit être egale à 1, 2, 3, 4, 5, 6 ou 9. Retapez : ");
		scanf("%d%*c", &choix);
	}
 }
}
