#include "hlm.h"


void affichMenu(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Information sur Locataire \t\t\t |\n");
	printf("| 2. Logement \t\t\t\t\t |\n");
	printf("| 3. Demande de logement \t\t\t |\n");
	printf("| 9. Quitter \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuLogement(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Ajouter un logement  \t \t \t |\n");
	printf("| 2. Supprimer un logement \t\t\t |\n");
	printf("| 3. Afficher posséder par des HLM63 \t\t |\n");
	printf("| 4. Afficher les types de logement \t\t |\n");
	printf("| 5. Afficher les types de logement disponuble   |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichChoixTrieLoca(void)
{
	printf("\t Comment souhaitez vous triez la liste : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Le nom par ordre alphabétique \t |\n");
	printf("| 2. Par numéro de logement\t\t |\n");
	printf("| 3. En fonction du prix du logement\t |\n");
	printf("| 4. Ordre croissant d'arrivée au logement\t|\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuLocataire(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Afficher la liste des locataires \t\t |\n");
	printf("| 2. Recherche d'un locataire \t\t\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void affichMenuDemLog(void)
{
	printf("\t Que voulez vous faire : \n");
	printf("+------------------------------------------------+\n");
	printf("| 1. Enregistrer une demande \t\t\t |\n");
	printf("| 2. Modifier une demande\t\t\t |\n");
	printf("| 3. Supprimer une demande\t\t\t |\n");
	printf("| 4. Afficher toute les demandes\t\t |\n");
	printf("| 5. Traité les demandes en attente\t\t |\n");
	printf("| 9. Retour \t\t\t\t\t |\n");
	printf("+------------------------------------------------+\n");
}

void menu(void)
{
	int nbD, choix;
	char ficDem[30]="FichierDemLoge.txt"
	ListeDem ld;
	// FilesLoc lc;
	// ListeLoge lg;

	chargementDem(ld, &nbD, ficDem);

	// FILE *fLoca;
	// lireLocataire(fLoca, lc);

	// FILE *fLoge;
	// chargementLoge();

	affichMenu();
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
				MenuLogement();
			break;

			case 2:
				MenuLocataire();
			break;

			case 3:
				MenuDemLog();
			break;
		}

		affichMenu();
		scanf("%d%*c", &choix);

		while (choix != 1 && choix != 2 && choix != 3 && choix != 9)
		{
			printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
			scanf("%d%*c", &choix);
		}
	 }
	
}

void MenuLocataire(void)
{
	int choixLoca, locataire;

	affichMenuLocataire();
	scanf("%d%*c", &choixLoca);

	while (choixLoca != 1 && choixLoca != 2 && choixLoca != 3 && choixLoca != 9)
	{
		printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
		scanf("%d%*c", &choixLoca);
	}

	 while (choixLoca != 9)
	 {
		switch (choixLoca)
		{
			case 1:
				MenuChoixTrie();
			break;

			case 2:
				// Fonction recherche locataire
				// scanf("%d", &locataire);
			break;
		}
		affichMenuLocataire();
		scanf("%d%*c", &choixLoca);

		while (choixLoca != 1 && choixLoca != 2 && choixLoca != 3 && choixLoca != 9)
		{
			printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
			scanf("%d%*c", &choixLoca);
		}
	 }
}

void MenuChoixTrie (void)
{
	int choixTrie;

	affichMenuLocataire();
	scanf("%d%*c", &choixTrie);

	while (choixTrie != 1 && choixTrie != 2 && choixTrie != 3 && choixTrie !=4 && choixTrie != 9)
	{
		printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
		scanf("%d%*c", &choixTrie);
	}

	 while (choixTrie != 9)
	 {
		switch (choixTrie)
		{
			case 1:
				// Afficher en fonction du nom
			break;

			case 2:
				// Afficher en fonction du numéro de logement
			break;

			case 3:
				// Afficher en fonction du prix du logement
			break;

			case 4:
				// Afficher en fonction de la date d'arrivée au logement
			break;
		}
		affichMenuLocataire();
		scanf("%d%*c", &choixTrie);

		while (choixTrie != 1 && choixTrie != 2 && choixTrie != 3 && choixTrie != 9)
		{
			printf("Choix doit être égale à 1, 2, 3 ou 9. Retapez : ");
			scanf("%d%*c", &choixTrie);
		}
	 }
}

void MenuLogement (void)
{
	int choixLoge;

	affichMenuLogement();
	scanf("%d%*c", &choixLoge);

	while (choixLoge != 1 && choixLoge != 2 && choixLoge != 3 && choixLoge != 4 && choixLoge != 5 && choixLoge != 9)
	{
		printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
		scanf("%d%*c", &choixLoge);
	}

	while (choixLoge != 9)
	{
		switch (choixLoge)
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
		affichMenuLogement();
		scanf("%d%*c", &choixLoge);

		while (choixLoge != 1 && choixLoge != 2 && choixLoge != 3 && choixLoge != 4 && choixLoge != 5 && choixLoge != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
			scanf("%d%*c", &choixLoge);
		}
	}
}

void MenuDemLog (void)
{
	int choixDemLoge;

	affichMenuDemLog();
	scanf("%d%*c", &choixDemLoge);

	while (choixDemLoge != 1 && choixDemLoge != 2 && choixDemLoge != 3 && choixDemLoge != 4 && choixDemLoge != 5 && choixDemLoge != 9)
	{
		printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
		scanf("%d%*c", &choixDemLoge);
	}

	while (choixDemLoge != 9)
	{
		switch (choixDemLoge)
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
		affichMenuDemLog();
		scanf("%d%*c", &choixDemLoge);

		while (choixDemLoge != 1 && choixDemLoge != 2 && choixDemLoge != 3 && choixDemLoge != 4 && choixDemLoge != 5 && choixDemLoge != 9)
		{
			printf("Choix doit être égale à 1, 2, 3, 4, 5 ou 9. Retapez : ");
			scanf("%d%*c", &choixDemLoge);
		}
	}
}


