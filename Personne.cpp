//
// Created by Duroy on 08/01/2021.
//

#include "Personne.h"
#include <sstream>


const std::string &Personne::getMNom() const {
    return m_nom;
}

const std::string &Personne::getMPrenom() const {
    return m_prenom;
}

const std::string &Personne::getMVilleNaissance() const {
    return m_villeNaissance;
}

/*const util::Date &Personne::getMDateNaissance() const {
    return m_dateNaissance;
}*/

char Personne::getSexe() const {
    return sexe;
}

const std::string &Personne::getMNas() const {
    return m_Nas;
}

/*const util::Date &Personne::getMDateDeces() const {
    return m_dateDeces;
}*/

bool Personne::isStatut() const {
    return statut;
}

const std::string &Personne::getMGroupeSanguin() const {
    return m_groupeSanguin;
}

void Personne::setMNas(const std::string &mNas) {
    m_Nas = mNas;
}

/*void Personne::setMDateDeces(const util::Date &mDateDeces) {
    m_dateDeces = mDateDeces;
}*/

void Personne::setStatut(bool statut) {
    Personne::statut = statut;
}

void Personne::setMGroupeSanguin(const std::string &mGroupeSanguin) {
    m_groupeSanguin = mGroupeSanguin;
}

Personne::~Personne() {
    for (auto iter = m_vFreres.begin(); iter != m_vFreres.end(); iter++) delete *iter;

}

std::string Personne::reqPersonneFormate() const {
    std::ostringstream os;

    return os.str();
}

/*bool Personne::operator<(const Personne &rhs) const {
    return m_dateNaissance < rhs.m_dateNaissance;
}

bool Personne::operator>(const Personne &rhs) const {
    return rhs < *this;
}

bool Personne::operator<=(const Personne &rhs) const {
    return !(rhs < *this) || m_dateNaissance == rhs.m_dateNaissance;
}

bool Personne::operator>=(const Personne &rhs) const {
    return !(*this < rhs) || m_dateNaissance == rhs.m_dateNaissance;
}*/

bool Personne::operator==(const Personne &rhs) const {
    return m_nom == rhs.m_nom &&
           m_prenom == rhs.m_prenom &&
           sexe == rhs.sexe &&
           m_Nas == rhs.m_Nas;
}

bool Personne::operator!=(const Personne &rhs) const {
    return !(rhs == *this);
}

Personne::Personne(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
                   const Tuple &mDateNaissance, char sexe, const std::string &mNas,
                   const std::string &mGroupeSanguin, const Tuple &mDateDeces, bool statut) : m_nom(
        mNom), m_prenom(mPrenom), m_villeNaissance(mVilleNaissance), m_dateNaissance(mDateNaissance), sexe(sexe),
                                                                                              m_Nas(mNas),
                                                                                              m_groupeSanguin(
                                                                                                      mGroupeSanguin),
                                                                                              m_dateDeces(
                                                                                                      mDateDeces),
                                                                                              statut(statut) {

}

const std::tuple<int, int, int> &Personne::getMDateDeces() const {
    return m_dateDeces;
}

void Personne::setMDateDeces(const std::tuple<int, int, int> &mDateDeces) {
    m_dateDeces = mDateDeces;
}

const std::tuple<int, int, int> &Personne::getMDateNaissance() const {
    return m_dateNaissance;
}

Personne *Personne::clone() const {
    return new Personne(*this);
}

Personne &Personne::operator=(const Personne &personne) {
    if(this == &personne)
    {
        m_dateNaissance = personne.m_dateNaissance;
        m_nom = personne.m_nom;
        m_Nas = personne.m_Nas;
        m_groupeSanguin = personne.m_groupeSanguin;
        statut = personne.isStatut();
        m_dateNaissance = personne.m_dateNaissance;
        m_dateDeces = personne.m_dateDeces;
        sexe = personne.sexe;
        for(auto iter:m_vFreres)
        {
            delete iter;
        }
        for(const auto iter : personne.m_vFreres)
        {
            m_vFreres.push_back(iter->clone());
        }
    }
    return *this;
}

void Personne::setMNom(const std::string &mNom) {
    m_nom = mNom;
}

void Personne::setMPrenom(const std::string &mPrenom) {
    m_prenom = mPrenom;
}

void Personne::setMVilleNaissance(const std::string &mVilleNaissance) {
    m_villeNaissance = mVilleNaissance;
}

void Personne::setMDateNaissance(const std::tuple<int, int, int> &mDateNaissance) {
    m_dateNaissance = mDateNaissance;
}

void Personne::setSexe(char sexe) {
    Personne::sexe = sexe;
}
