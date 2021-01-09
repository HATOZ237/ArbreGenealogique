//
// Created by Duroy on 08/01/2021.
//

#ifndef ARBREGENEALOGIQUE_ENFANT_H
#define ARBREGENEALOGIQUE_ENFANT_H

#include "Personne.h"
#include <vector>
#include <ostream>

class Enfant: public Personne{
public:
    /**
     * @brief
     * @param mNom
     * @param mPrenom
     * @param mVilleNaissance
     * @param mDateNaissance
     * @param sexe
     * @param mNas
     * @param mDateDeces
     * @param statut
     * @param mGroupeSanguin
     */

    virtual ~Enfant();

    //friend std::ostream &operator<<(std::ostream &os, const Enfant &enfant);

    void AjouterFrere(const Personne& enfant);

    void retirerFrere(const std::string& p_nas);

    //bool EstFrere();

    bool EstDejaFrere(const Personne& enfant);

    Personne* clone() const;

    Enfant &operator=(const Enfant& enfant );

    /*Enfant(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
           const std::tuple<int, int, int> &mDateNaissance, char sexe, const std::string &mNas,
           const std::string &mGroupeSanguin, const std::tuple<int, int, int> &mDateDeces, bool statut,
           const Enfant &enfant);*/

    std::string reqPersonneFormate() const;

    Enfant(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
           const std::tuple<int, int, int> &mDateNaissance, char sexe, const std::string &mNas,
           const std::string &mGroupeSanguin, const std::tuple<int, int, int> &mDateDeces, bool statut);


};


#endif //ARBREGENEALOGIQUE_ENFANT_H
