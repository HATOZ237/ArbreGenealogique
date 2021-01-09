/**
 * \file PersonneException.h
 * \brief Fichier contenant la déclaration de la classe PersonneException et de ses héritiers
 * \date 2020-11-29
 * \author Danny Lavallée et Sylviane Chedjoun Guiatchuing
 */

#ifndef PERSONNEEXCEPTION_H_
#define PERSONNEEXCEPTION_H_

#include <string>
#include <stdexcept>

/**
 * \classe PersonneException
 * \brief Classe de base des exceptions de Personne
 */
class PersonneException: public std::runtime_error
{
public:
	PersonneException(const std::string& p_raison);
};

/**
 * \classe PersonneDejaPresenteException
 * \brief Classe pour la gestion des erreurs d'une personne qui est déjà présente lors d'une inscription
 */
class PersonneDejaPresenteException: public PersonneException
{
public:
	PersonneDejaPresenteException(const std::string& p_raison);
};

/**
 * \classe PersonneAbsenteException
 * \brief Classe pour la gestion des erreurs d'une personne qui est absente lors d'une désinscription
 */
class PersonneAbsenteException: public PersonneException
{
public:
	PersonneAbsenteException(const std::string& p_raison);
};

#endif /* PERSONNEEXCEPTION_H_ */
