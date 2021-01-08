//
// Created by Duroy on 08/01/2021.
//

#ifndef ARBREGENEALOGIQUE_ENFANT_H
#define ARBREGENEALOGIQUE_ENFANT_H

#include "Personne.h"
#include <vector>

class Enfant: public Personne{
private:
    std::vector<Enfant*> m_vFreres;
public:
    Enfant(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
           const util::Date &mDateNaissance, char sexe, const std::string &mNas, const util::Date &mDateDeces,
           bool statut, const std::string &mGroupeSanguin);


};


#endif //ARBREGENEALOGIQUE_ENFANT_H
