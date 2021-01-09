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

void Enfant::retirerFrere(const std::string &p_nas) {
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
}

Personne *Enfant::clone() const {
    return new Enfant(*this);
}

Enfant &Enfant::operator=(const Enfant &enfant) {
    if (this != & enfant) {
        m_dateNaissance = enfant.m_dateNaissance;
        m_nom = enfant.m_nom;
        m_Nas = enfant.m_Nas;
        m_groupeSanguin = enfant.m_groupeSanguin;
        statut = enfant.isStatut();
        m_dateNaissance = enfant.m_dateNaissance;
        m_dateDeces = enfant.m_dateDeces;
        sexe = enfant.sexe;
        for(auto iter:m_vFreres)
        {
            delete iter;
        }
        for(const auto iter : enfant.m_vFreres)
        {
            m_vFreres.push_back(iter->clone());
        }
    }
    return *this;
}

/*Enfant::Enfant(const Enfant &enfant) : Personne(enfant.getMNom(), enfant.getMPrenom(),enfant.getMVilleNaissance(), enfant.getMDateNaissance(),
                                                enfant.getSexe(), enfant.getMNas(), enfant.getMGroupeSanguin(),
                                                enfant.getMDateDeces(), enfant.isStatut()) {
    for (const auto it:enfant.m_vFreres){
        this->AjouterFrere(*it);
    }

}*/

bool Enfant::EstDejaFrere(const Personne& enfant) {
    for(const auto enf:m_vFreres)
    {
        if(*enf == enfant) return true;
    }
    return false;
}

std::string Enfant::reqPersonneFormate() const {
    return Personne::reqPersonneFormate();
}
