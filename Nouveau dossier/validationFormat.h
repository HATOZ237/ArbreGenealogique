/**
 * \file validationFormat.h
 * \brief Fichier qui contient l'interface des fonctions de validation de format.
 * \author Adrien Choinière
 * \version 1.0.1 avec contrat
 * \date 2020-04-09
 */


#ifndef VALIDATIONFORMAT_H_
#define VALIDATIONFORMAT_H_
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <sstream>

namespace util
{

bool validerTelephone(const std::string& p_telephone);

bool validerNumRAMQ(const std::string& p_numero, const std::string& p_nom, const std::string& p_prenom,
		            int p_jourNaissance, int p_moisNaissance, int p_anneeNaissance, char p_sex);

bool validerFormatNom(const std::string& p_nom);

bool validerFormatSexe(const char& p_sexe);

//bool validerPositionJoueur(const std::string& p_position);

} /* namespace util */

#endif /* VALIDATIONFORMAT_H_ */
