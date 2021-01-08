//
// Created by Duroy on 08/01/2021.
//

#include "Enfant.h"


Enfant::Enfant(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
               const util::Date &mDateNaissance, char sexe, const std::string &mNas, const util::Date &mDateDeces,
               bool statut, const std::string &mGroupeSanguin) : Personne(mNom, mPrenom, mVilleNaissance,
                                                                          mDateNaissance, sexe, mNas, mDateDeces,
                                                                          statut, mGroupeSanguin) {

}
