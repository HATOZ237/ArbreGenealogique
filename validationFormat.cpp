/**
 * \file validationFormat.cpp
 * \brief Fichier qui contient des fonctions de validation de format.
 * \author Adrien Choinière
 * \version 1.0.1 avec contrat
 * \date 2020-04-09
 */


#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <sstream>
#include "validationFormat.h"

using namespace std;

namespace util
{

const int MAX_LIGNES_REGIONAUX = 30;
const int MAX_COLONNES_REGIONAUX = 3;
const int NB_NOMBRE_CODES_REGIONAUX = 3;
const int NUM_TROIS_PREMIERES_LETTRES = 3;
const int NB_CARACTERES_NUM_MAX = 12;
const int MAX_LIGNES_CODE_SANS_FRAIS = 5;
const int TAILLE_NUMEROS_RAMQ = 14;

const int listeCodesRegionaux[MAX_LIGNES_REGIONAUX][MAX_COLONNES_REGIONAUX] = {{4, 0, 3},
																			   {7, 8, 0},
																			   {6, 0, 4},
																			   {2, 3, 6},
																			   {2, 5, 0},
																			   {7, 7, 8},
																			   {9, 0, 2},
																			   {2, 0, 4},
																			   {5, 0, 6},
																			   {9, 0, 2},
																			   {9, 0, 5},
																			   {5, 1, 9},
																			   {2, 8, 9},
																			   {7, 0, 5},
																			   {6, 1, 3},
																			   {8, 0, 7},
																			   {4, 1, 6},
																			   {6, 4, 7},
																			   {4, 3, 8},
																			   {5, 1, 4},
																			   {4, 5, 0},
																			   {5, 7, 9},
																			   {4, 1, 8},
																			   {5, 8, 1},
																			   {8, 1, 9},
																			   {8, 7, 3},
																			   {3, 0, 6},
																			   {7, 0, 9},
																			   {8, 6, 7},
																			   {8, 6, 7}};

const int listeCodesSansFrais[MAX_LIGNES_CODE_SANS_FRAIS][MAX_COLONNES_REGIONAUX] = {{8, 0, 0}, {8, 6, 6}, {8, 7, 7}, {8, 8, 8}, {8, 5, 5}};

bool verificationCodeRegionaux(int p_numTelephone[NB_NOMBRE_CODES_REGIONAUX]);
bool verifierCodeSansFrais(int p_numTelephone[NB_NOMBRE_CODES_REGIONAUX]);

/**
 * \fn bool validerTelephone(const std::string& p_telephone)
 * \brief validerTelephone permet de valider un numéro de
 *        téléphone canadien en format national.
 *
 * \param[in] p_telephone est une chaine de caractère (string)
 *            représentant un numéro de téléphone.
 *
 * \return un booléen, vrai si le numéro de télépnone est valide, faux autrement.
 */
bool validerTelephone(const std::string& p_telephone)
{
	//cout << " ------------------------------------------ " << endl;
	//cout << p_telephone << endl;

	bool validerNumTelephone = true;
	char numTelephone[p_telephone.length()]; //Déclaration d'un tableau de caractères.

	for (int i = 0; i < sizeof(numTelephone); i++)
	{
		numTelephone[i] = p_telephone[i];
	}

	if (numTelephone[3] != ' ' || numTelephone[7] != '-')
	{
//		cout << "LIGNE 89 -- VERIFIER ESPACE ou TRAIT-UNION" << endl;
//		cout << "numTelephone[3] = " << numTelephone[3] << " || " << "numTelephone[7] = " << numTelephone[7] << endl;
		validerNumTelephone = false;
	}
	else if (sizeof(numTelephone) != NB_CARACTERES_NUM_MAX) //longueur = 12
	{
//		cout << "LIGNE 95 -- LONGUEUR INVALIDE" << endl;
//		cout << "Longueur actuelle : " << sizeof(numTelephone) << endl;
		validerNumTelephone = false;
	}
	else
	{
		int nb;
		//Verifier les chiffres + question sur les XXX dans XXX CCC-CCCC.
		// sizeof(numTelephone) - 1: On fait -1, car la longueur est de 13 avec le "\n" ajouter ppar le langage.
		//                           La vrai longueur est de 12.
		// On commence à la position 4, car la position 3 correspond à un espace.
		for (int i = 0; i < sizeof(numTelephone); i++)
		{
			//cout << numTelephone[i] << endl;
			//Position 7, trait union (-) qui n'est pas un chiffre.  On ne veut pas le vérifier ici.
			// Si position 7 == '-', passe fait rien.
			// Si position 3 == ' ', passe fait rien.
			if (i != 7)
			{
				if (i != 3)
				{
					nb = static_cast<int>(numTelephone[i]);
					// Vérification table ASCII
					if (nb - 48 < 0 || nb - 59 > 0)
					{
//						cout << "LIGNE 120 -- VALEUR HORS BORNES!" << endl;
//						cout << "Pos: " << i << endl;
//						cout << "nb = " << nb << "  nb - 48 = " << nb - 48
//							 << "  nb - 59 = " << nb - 59 << endl;
						validerNumTelephone = false;
					}
				}
			}
		}
	}

	if (validerNumTelephone)
	{
		// 48 = zero dans ASCII.
		int codeRegionauxTelephone[NB_NOMBRE_CODES_REGIONAUX] = {numTelephone[0] - 48, numTelephone[1] - 48, numTelephone[2] - 48};

		// Si commence par un 9, c'est nméro privé (payant).  Tant que les caractères suivant le 9 sont des chiffres,
		// le numéro est valide.
		if (codeRegionauxTelephone[0] != 9)
		{
			if (!verificationCodeRegionaux(codeRegionauxTelephone))
			{
				if (!verifierCodeSansFrais(codeRegionauxTelephone))
				{
					validerNumTelephone = false;
				}
			}
		}
	}
	return validerNumTelephone;
}

/**
 * \fn bool verificationCodeRegionaux(int p_numTelephone[NB_NOMBRE_CODES_REGIONAUX])
 * \brief Vérifie si un numéro de téléphone contient
 *        un indicatif régional valide.
 *
 * \param[in] p_numTelephone est un tableau d'entier (int) contenant 3 nombres entiers.
 *
 * \return un booléen retourne vrai si le numéro de téléphone content un indicatif régional,
 *         faux autrement.
 */
bool verificationCodeRegionaux(int p_numTelephone[NB_NOMBRE_CODES_REGIONAUX])
{
	bool condition = false;
	for (int i = 0; i < MAX_LIGNES_REGIONAUX; i++)
	{
		//cout << listeCodesRegionaux[i][0] << " == " << numTelephone[0] << endl;
		if (listeCodesRegionaux[i][0] == p_numTelephone[0])
		{
			//cout << listeCodesRegionaux[i][0] << " == " << numTelephone[0] << endl;
			//cout << listeCodesRegionaux[i][1] << " == " << numTelephone[1] << endl;
			if (listeCodesRegionaux[i][1] == p_numTelephone[1])
			{
				//cout << listeCodesRegionaux[i][1] << " == " << numTelephone[1] << endl;
				//cout << listeCodesRegionaux[i][2] << " == " << numTelephone[2] << endl;
				if (listeCodesRegionaux[i][2] == p_numTelephone[2])
				{
					condition = true;
				}
			}
		}
	}
	return condition;
}

/**
 * \fn bool verifierCodeSansFrais(int p_numTelephone[NB_NOMBRE_CODES_REGIONAUX])
 * \brief Vérifie si un numéro de téléphone contient
 *        un indicatif sans frais valide.
 *
 * \param[in] p_numTelephone est un tableau d'entier (int) contenant 3 nombres entiers.
 *
 * \return un booléen retourne vrai si le numéro de téléphone content
 *         un indicatif sans frais valide, faux autrement.
 */
bool verifierCodeSansFrais(int p_numTelephone[NB_NOMBRE_CODES_REGIONAUX])
{
	bool condition = false;
	for (int i = 0; i < MAX_LIGNES_CODE_SANS_FRAIS; i++)
	{
		//cout << listeCodesSansFrais[i][0] << " == " << numTelephone[0] << endl;
		if (listeCodesSansFrais[i][0] == p_numTelephone[0])
		{
			//cout << listeCodesSansFrais[i][0] << " == " << numTelephone[0] << endl;
			//cout << listeCodesSansFrais[i][1] << " == " << numTelephone[1] << endl;
			if (listeCodesSansFrais[i][1] == p_numTelephone[1])
			{
				//cout << listeCodesSansFrais[i][1] << " == " << numTelephone[1] << endl;
				//cout << listeCodesSansFrais[i][2] << " == " << numTelephone[2] << endl;
				if (listeCodesSansFrais[i][2] == p_numTelephone[2])
				{
					condition = true;
				}
			}
		}
	}
	return condition;
}

/**
 * \fn string toUpper(string p_unString)
 * \brief Retourne une chaîne de caractère en MAJUSCULE.
 *
 * \param[in] p_unString est une chaîne de caractère (string).
 *
 * \return une chaîne de caractère (string) en MAJUSCULE.
 */
string toUpper(string p_unString)
{
	transform(p_unString.begin(), p_unString.end(), p_unString.begin(), ::toupper);
	return p_unString;
}

/**
 * \fn char* conversionIntEnTableauDeChar(int p_nombre)
 * \brief convertie un nombre entier (int) en un tableau de caractère (char[]).
 *
 * \param[in] p_nombre est un nombre entier.
 *
 * \return un tableau de caractère (char[]).
 */
char* conversionIntEnTableauDeChar(int p_nombre)
{
	std::string outString;
	std::stringstream ss;
	ss << p_nombre;
	outString = ss.str();
	char const* pchar = outString.c_str();
	//cout << "out_string: " << outString << endl;
	//cout << "pchar: " << pchar << endl;

	char* nbChar = new char[outString.length()];
	strcpy(nbChar, outString.c_str());
	//cout << "nbChar: " << nbChar << endl;
	//cout << "nbChar[0], [1], etc: " << nbChar[0] << nbChar[1] << nbChar[2] << nbChar[3] << endl;
	return nbChar;
}

/**
 * \fn char* conversionStringEnTableauDeChar(string p_unString)
 * \brief convertie une chaîne de caractère (string) en un tableau de caractère (char[]).
 *
 * \param[in] p_unString est une chaîne de caractère (string).
 *
 * \return un tableau de caractère (char[])
 */
char* conversionStringEnTableauDeChar(string p_unString)
{
	char* monChar = new char[p_unString.length()];
	strcpy(monChar, p_unString.c_str());
	return monChar;
}

/**
 * \fn bool validerMoisNaissance(char p_numRamq[TAILLE_NUMEROS_RAMQ], int p_moisNaissance, char p_sexe)
 * \brief Vérifie si le mois de naissance du numéro de ramq est valide.
 *
 * \param[in] p_numRamq est un tableau de caractère (char[]) de taille 14 contenant le numéro de ramq.
 * \param[in] p_moisNaissance est un entier contenant le mois de naissance.
 * \param[in] p_sexe est un caractère (char) contenant un préfixe le préfixe 'h' pour homme et 'f' pour femme.
 *
 * \return un booléen, vrai si le mois de naissance du numéro de rmq est valide, faux autrement.
 */
bool validerMoisNaissance(char p_numRamq[TAILLE_NUMEROS_RAMQ], int p_moisNaissance, char p_sexe)
{
	bool condition = true;
	if (1 <= p_moisNaissance && p_moisNaissance <= 12)
	{
		if (p_sexe == 'F' || p_sexe == 'f')
		{
			p_moisNaissance += 50;
			//cout << "p_moisNaissance si F = " << p_moisNaissance << endl;
		}
		char* nb = conversionIntEnTableauDeChar(p_moisNaissance);
		// Validation des chiffres correspondant au mois de naissance.
		if (p_moisNaissance >= 10)
		{
			if ((p_numRamq[7] != nb[0]) || (p_numRamq[8] != nb[1]))
			{
					condition = false;
//					cout << "Ligne 295: Chiffre du mois ne correspond pas au moi de naissance." << endl;
//					cout << "p_numRamq[7] != nb[0]: " << p_numRamq[7] << " != " << nb[0] << " OU "
//						 << "p_numRamq[8] != nb[1]: " << p_numRamq[8] << " != " << nb[1] << endl;
			}
		}
		else
		{
			char zero = '0';
			if ((p_numRamq[7] != zero) || (p_numRamq[8] != nb[0]))
			{
				condition = false;
//				cout << "Ligne 306: Chiffre du mois ne correspond pas au moi de naissance." << endl;
//				cout << "p_numRamq[7] != 0: " << p_numRamq[7] << " != " << zero << " OU "
//					 << "p_numRamq[8] != nb[0]: " << p_numRamq[8] << " != " << nb[0] << endl;
			}
		}
	}
	else
	{
		condition = false;
		//cout << "Ligne 315: Moi de naissance invalide: " << p_moisNaissance << endl;
	}
	return condition;
}

/**
 * \fn bool validerJourNaissance(char p_numRamq[TAILLE_NUMEROS_RAMQ], int p_jourNaissance)
 * \brief Vérifie si le jour de naissance du numéro de ramq est valide.
 *
 * \param[in] p_numRamq est un tableau de caractère (char[]) de taille 14 contenant le numéro de ramq.
 * \param[in] p_jourNaissance est un entier contenant le jour de naissance.
 *
 * \return Un booléen, vrai si le mois de naissance du numéro de ramq est valide, faux autrement.
 */
bool validerJourNaissance(char p_numRamq[TAILLE_NUMEROS_RAMQ], int p_jourNaissance)
{
	bool condition = true;
	if (1 <= p_jourNaissance &&  p_jourNaissance <= 31)
	{
		char* nb = conversionIntEnTableauDeChar(p_jourNaissance);
		// Validation des chiffres correspondant au jour de naissance.
		if (p_jourNaissance >= 10)
		{
			if (p_numRamq[10] != nb[0] || p_numRamq[11] != nb[1])
			{
				condition = false;
//				cout << "Ligne 340: Chiffre de la journée de naissance ne correspond pas à la journée de naissance." << endl;
//				cout << "p_numRamq[10] != nb[0]: " << p_numRamq[10] << " != " << nb[0] << " OU "
//				 << "p_numRamq[11] != nb[1]: " << p_numRamq[11] << " != " << nb[1] << endl;
			}
		}
		else
		{
			char zero = '0';
			if (p_numRamq[10] != zero || p_numRamq[11] != nb[0])
			{
				condition = false;
//				cout << "Ligne 351: Chiffre de la journée de naissance ne correspond pas à la journée de naissance." << endl;
//				cout << "p_numRamq[10] != 0: " << p_numRamq[10] << " != " << zero << " OU "
//					 << "p_numRamq[11] != nb[1]: " << p_numRamq[11] << " != " << nb[0] << endl;
			}
		}
	}
	else
	{
		condition = false;
		//cout << "Ligne 360: Jour de naissance invalide: " << p_jourNaissance << endl;
	}
	return condition;
}

/**
 * \fn bool validerNumRAMQ(const std::string& p_numero, const std::string& p_nom, const std::string& p_prenom,
		            int p_jourNaissance, int p_moisNaissance, int p_anneeNaissance, char p_sex)
 * \brief Vérifie si le numéro de ramq est valide.
 *
 * \param[in] p_numero est une chaîne de caractère constante (const string) qui contient le numéro de ramq à valider.
 * \param[in] p_nom est une chaîne de caractère constante (const string) qui contient le nom.
 * \param[in] p_prenom est une chaîne de caractère constante (const string) qui contient le prénom.
 * \param[in] p_jourNaissance est un entier contenant le jour de naissance.
 * \param[in] p_moisNaissance est un entier contenant le mois de naissance.
 * \param[in] p_anneeNaissance est un entier contenant l'annéer de naissance.
 * \param[in] p_sex est un caractère identifiant le sexe.
 *
 * \return un booléen, vrai si le du numéro de ramq est valide, faux autrement.
 */
bool validerNumRAMQ(const std::string& p_numero, const std::string& p_nom, const std::string& p_prenom,
		            int p_jourNaissance, int p_moisNaissance, int p_anneeNaissance, char p_sex)
{

	bool validerNumRamq = true;

	char* anneeNaissance = conversionIntEnTableauDeChar(p_anneeNaissance);
	char* numRamq = conversionStringEnTableauDeChar(p_numero);
	char* nom = conversionStringEnTableauDeChar(toUpper(p_nom));
	char* prenom = conversionStringEnTableauDeChar(toUpper(p_prenom));


	if (p_numero.length() == TAILLE_NUMEROS_RAMQ)
	{
		for (int i = 0; i < TAILLE_NUMEROS_RAMQ; i++)
		{
			if (validerNumRamq)
			{
				if (i == 0)
				{
					// Validation des 3 premiers caractères du numéréro.
					// Les 3 premiers caractères correspondent au 3 premières lettres du nom (de famille).
					if (numRamq[i] != nom[i] || numRamq[i + 1] != nom[i + 1] || numRamq[i + 2] != nom[i + 2])
					{
						validerNumRamq = false;
//						cout << "Les 3 premières lettres du numéroRAMQ ne correspondent pas "
//								"au 3 premières lettres nom de famille." << endl
//							 << "Ligne 405" << endl
//							 << "numRamq: " << numRamq[i] << numRamq[i + 1] << numRamq[i + 2] << endl
//							 << "nom: " << nom << endl;
					}
				}

				if (i == 3)
				{
					//Validation du 4e caractère qui correspond à la première lettre du prénom.
					if (numRamq[i] != prenom[0])
					{
						validerNumRamq = false;
//						cout << "4e caractère numRAMQ ne correspond à la 1 lettre du prénom." << endl
//							 << "Ligne 418" << endl
//							 << "numRamq[3]: " << numRamq[i] << endl
//							 << "nom[0]: " << nom[0] << endl;
					}
				}

				// Vérification des 2 espaces (4 et 9)
				if (i == 4)
				{
					// Vérification des espaces du numéro.
					if (numRamq[i] != ' ' || numRamq[9] != ' ')
					{
						validerNumRamq = false;
//						cout << "Vérification des espaces du numéro.  Ligne 431" << endl
//							 << "numRamq[4] = '" << numRamq[i] << "' OU " << "numRamq[9] = '" <<  numRamq[9] << "'" << endl;
					}
				}

				if (i == 5)
				{
					// Validation des 2 derniers chiffres de l'année de naissance.
					// (pos 5 et 6)
					if ((numRamq[i] != anneeNaissance[2] || numRamq[i + 1] != anneeNaissance[3]))
					{
							validerNumRamq = false;
//							cout << "Validation des 2 derniers chiffres de l'année de naissance.  Ligne 443" << endl
//								 << "    " << numRamq[i] << " != " << anneeNaissance[2] << endl
//								 << "OU  " << numRamq[6] << " != " <<  anneeNaissance[3] << endl;
					}
				}

				if (i == 7)
				{
					// Validation des chiffres correspondant au mois de naissance.
					if (!validerMoisNaissance(numRamq, p_moisNaissance, p_sex))
					{
						validerNumRamq = false;
					}
				}

				if (i == 10)
				{
					// Validation des chiffres correspondant au jour de naissance.
					if (!validerJourNaissance(numRamq, p_jourNaissance))
					{
						validerNumRamq = false;
					}
				}

				if (i >= 12)
				{
					int nb = static_cast<int>(numRamq[i]);
					// Vérification nombre dans la table ASCII
					if (nb - 48 < 0 || nb - 59 > 0)
					{
//						cout << "LIGNE 473 -- VALEUR HORS BORNES!" << endl;
//						cout << "Pos: " << i << endl;
//						cout << "nb = " << nb << "  nb - 48 = " << nb - 48
//							 << "  nb - 59 = " << nb - 59 << endl;
						validerNumRamq = false;
					}
				}
			}
		}
	}
	else
	{
		validerNumRamq = false;
		//cout << "Ligne 486: Longueur invalide: " << p_numero.length() << "!= 14" << endl;
	}

	return validerNumRamq;
}

/**
 * \fn bool validerFormatNom(const std::string& p_nom)
 * \brief Vérifie si une chaîne de caractère contient uniquement des lettres. Ne prend pas en charge les accents.
 *
 * \param[in] p_nom est une chaîne de caractère constante (const string) contenant un nom.
 *
 * \return un booléen, vrai si le nom valide, faux autrement.
 */
bool validerFormatNom(const std::string& p_nom)
{
	bool validation = true;

	if (p_nom == "" || p_nom.length() < 3)
	{
		validation = false;
	}
	else
	{
		char* nomAValider = conversionStringEnTableauDeChar(toUpper(p_nom));
		for (int i = 0; i < p_nom.length(); i++)
		{
			if (static_cast<int>(nomAValider[i]) - 65 < 0 || static_cast<int>(nomAValider[i]) - 90 > 0)
			{
				validation = false;
				//cout << "NomInvalide : " << nomAValider[i] << endl;
			}
		}
	}
	return validation;
}


/**
 * \fn bool validerFormatSexe(const char& p_sexe)
 * \brief Vérifie si le caractère (MAJUSCULE) représentant le sexe est valide.
 *
 * \param[in] p_sexe est un caractère (MAJUSCULE) constante (const char) représentant un sexe.
 *
 * \return un booléen, vrai si le sexe valide, faux autrement.
 */
bool validerFormatSexe(const char& p_sexe)
{
	return ((p_sexe == 'F') || (p_sexe == 'H'));
}


/**
 * \fn bool validerPositionJoueur(const std::string& p_position)
 * \brief validerPositionJoueur permet de valider que la
 *        position d'un joueur est valide.
 *
 * \param[in] p_position est une chaine de caractère (string)
 *            représentant la position du joueur .
 *
 * \return un booléen, vrai si la position est valide, faux autrement.
 */
//bool validerPositionJoueur(const std::string& p_position)
//{
//	return false;//((p_position == hockey::Joueur::POSITION_JOUEUR_AILIER) || (p_position == POSITION_JOUEUR_CENTRE) || (p_position == POSITION_JOUEUR_DEFENSEUR) || (p_position == POSITION_JOUEUR_GARDIEN));
//}



} /* namespace util */








