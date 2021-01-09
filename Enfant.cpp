//
// Created by Duroy on 08/01/2021.
//

#include "Enfant.h"


Enfant::Enfant(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
               const std::tuple<int, int, int> &mDateNaissance, char sexe, const std::string &mNas,
               const std::string &mGroupeSanguin, const std::tuple<int, int, int> &mDateDeces, bool statut) : Personne(
        mNom, mPrenom, mVilleNaissance, mDateNaissance, sexe, mNas, mGroupeSanguin, mDateDeces, statut) {}

Enfant::~Enfant() {

}


void Enfant::AjouterFrere(const Personne &enfant) {
    if(!EstDejaFrere(enfant))
    {
        m_vFreres.push_back(enfant.clone());
    } else throw PersonneDejaPresenteException(enfant.reqPersonneFormate());

}

/*void Enfant::retirerFrere(const std::string &p_nas) {
    std::vector<Personne*>::iterator iter;
    bool trouve = false;
    for(iter = m_vFreres.begin(); iter != m_vFreres.end(); iter++)
    {
        if ((*iter)->getMNas() == p_nas)
        {
            trouve = true;
            m_vFreres.erase(iter);
        }
    }
}*/

Personne *Enfant::clone() const {
    return new Enfant(*this);
}

/*Enfant &Enfant::operator=(const Enfant &enfant) {
    if (this != & enfant) {
        std::vector<Personne*>::iterator iter;
        for(iter = m_vFreres.begin(); iter != m_vFreres.end(); iter++)
        {
            delete (*iter);
        }

        m_vFreres.clear();

        //std::vector<Personne*>:: const_iterator it;
        for (const auto it:enfant.m_vFreres){
            m_vFreres.push_back(it->clone());
        }


    }
    return *this;
}*/

/*Enfant::Enfant(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
               const std::tuple<int, int, int> &mDateNaissance, char sexe, const std::string &mNas,
               const std::string &mGroupeSanguin, const std::tuple<int, int, int> &mDateDeces, bool statut,
               const Enfant &enfant) : Personne(mNom, mPrenom, mVilleNaissance, mDateNaissance, sexe, mNas, mGroupeSanguin, mDateDeces, statut) {
    for (const auto it:enfant.m_vFreres){
        this->AjouterFrere((*it));
    }

}*/

/*bool Enfant::EstDejaFrere(const Personne& enfant) {
    for(const auto enf:m_vFreres)
    {
        if(*enf == enfant) return true;
    }
    return false;
}*/

std::string Enfant::reqPersonneFormate() const {
    return Personne::reqPersonneFormate();
}
