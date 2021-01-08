//
// Created by Duroy on 08/01/2021.
//

#include "Personne.h"

Personne::Personne(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
                   const util::Date &mDateNaissance, char sexe, const std::string &mNas = "", const util::Date &mDateDeces = util::Date(),
                   bool statut = true, const std::string &mGroupeSanguin= "O") : m_nom(mNom), m_prenom(mPrenom),
                                                                     m_villeNaissance(mVilleNaissance),
                                                                     m_dateNaissance(mDateNaissance), sexe(sexe),
                                                                     m_Nas(mNas), m_dateDeces(mDateDeces),
                                                                     statut(statut), m_groupeSanguin(mGroupeSanguin) {

}

const std::string &Personne::getMNom() const {
    return m_nom;
}

const std::string &Personne::getMPrenom() const {
    return m_prenom;
}

const std::string &Personne::getMVilleNaissance() const {
    return m_villeNaissance;
}

const util::Date &Personne::getMDateNaissance() const {
    return m_dateNaissance;
}

char Personne::getSexe() const {
    return sexe;
}

const std::string &Personne::getMNas() const {
    return m_Nas;
}

const util::Date &Personne::getMDateDeces() const {
    return m_dateDeces;
}

bool Personne::isStatut() const {
    return statut;
}

const std::string &Personne::getMGroupeSanguin() const {
    return m_groupeSanguin;
}

void Personne::setMNas(const std::string &mNas) {
    m_Nas = mNas;
}

void Personne::setMDateDeces(const util::Date &mDateDeces) {
    m_dateDeces = mDateDeces;
}

void Personne::setStatut(bool statut) {
    Personne::statut = statut;
}

void Personne::setMGroupeSanguin(const std::string &mGroupeSanguin) {
    m_groupeSanguin = mGroupeSanguin;
}

Personne::~Personne() {

}

std::ostream &operator<<(std::ostream &os, const Personne &personne) {
    os << "m_nom: " << personne.m_nom << " m_prenom: " << personne.m_prenom << " m_villeNaissance: "
       << personne.m_villeNaissance << " m_dateNaissance: " << personne.m_dateNaissance << " sexe: " << personne.sexe
       << " m_Nas: " << personne.m_Nas << " m_dateDeces: " << personne.m_dateDeces << " statut: " << personne.statut
       << " m_groupeSanguin: " << personne.m_groupeSanguin;
    return os;
}

bool Personne::operator<(const Personne &rhs) const {
    return m_dateNaissance < rhs.m_dateNaissance;
}

bool Personne::operator>(const Personne &rhs) const {
    return rhs < *this;
}

bool Personne::operator<=(const Personne &rhs) const {
    return !(rhs < *this) && m_dateNaissance == rhs.m_dateNaissance ;
}

bool Personne::operator>=(const Personne &rhs) const {
    return !(*this < rhs);
}

bool Personne::operator==(const Personne &rhs) const {
    return m_nom == rhs.m_nom &&
           m_prenom == rhs.m_prenom &&
           sexe == rhs.sexe &&
           m_Nas == rhs.m_Nas;
}

bool Personne::operator!=(const Personne &rhs) const {
    return !(rhs == *this);
}
