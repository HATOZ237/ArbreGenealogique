//
// Created by Duroy on 08/01/2021.
//

#ifndef ARBREGENEALOGIQUE_PERSONNE_H
#define ARBREGENEALOGIQUE_PERSONNE_H

#include <string>
#include <ostream>
#include "Date.h"

class Personne {
private:
    std::string m_nom;
    std::string m_prenom;
    std::string m_villeNaissance;
    util::Date m_dateNaissance;
    char sexe;
    std::string m_Nas;
    util::Date m_dateDeces;
    bool statut;
    std::string m_groupeSanguin;
public:
    virtual ~Personne();
    virtual Personne* clone() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Personne &personne);

    void setMNas(const std::string &mNas);

    void setMDateDeces(const util::Date &mDateDeces);

    void setStatut(bool statut);

    void setMGroupeSanguin(const std::string &mGroupeSanguin);

    bool operator<(const Personne &rhs) const;

    bool operator>(const Personne &rhs) const;

    bool operator<=(const Personne &rhs) const;

    bool operator>=(const Personne &rhs) const;

    bool operator==(const Personne &rhs) const;

    bool operator!=(const Personne &rhs) const;

    const std::string &getMNom() const;

    const std::string &getMPrenom() const;

    const std::string &getMVilleNaissance() const;

    const util::Date &getMDateNaissance() const;

    char getSexe() const;

    const std::string &getMNas() const;

    const util::Date &getMDateDeces() const;

    bool isStatut() const;

    const std::string &getMGroupeSanguin() const;


    Personne(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
             const util::Date &mDateNaissance, char sexe, const std::string &mNas, const util::Date &mDateDeces,
             bool statut, const std::string &mGroupeSanguin);


};


#endif //ARBREGENEALOGIQUE_PERSONNE_H
