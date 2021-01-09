//
// Created by Duroy on 08/01/2021.
//

#ifndef ARBREGENEALOGIQUE_PERSONNE_H
#define ARBREGENEALOGIQUE_PERSONNE_H

#include <string>
#include <ostream>
//#include "Date.h"
#include <tuple>
#include "ContratException.h"
#include "PersonneException.h"
#include <vector>

typedef std::tuple<int, int, int> Tuple;

class Personne {
protected:
    std::vector<Personne *> m_vFreres;
    std::string m_nom;
    std::string m_prenom;
    std::string m_villeNaissance;
    std::tuple<int, int, int> m_dateNaissance;
    char sexe;
    std::string m_Nas;
    std::string m_groupeSanguin;
    std::tuple<int, int, int> m_dateDeces;
    bool statut;
public:
    static Tuple dateDeces = std::make_tuple(31, 12, 9999);
    virtual ~Personne();

    virtual std::string reqPersonneFormate() const;

    virtual Personne *clone() const ;

    void setMNas(const std::string &mNas);

    //void setMDateDeces(const util::Date &mDateDeces);

    void setStatut(bool statut);

    void setMGroupeSanguin(const std::string &mGroupeSanguin);

    /*bool operator<(const Personne &rhs) const;

    bool operator>(const Personne &rhs) const;

    bool operator<=(const Personne &rhs) const;

    bool operator>=(const Personne &rhs) const;*/

    bool operator==(const Personne &rhs) const;

    bool operator!=(const Personne &rhs) const;

    const std::string &getMNom() const;

    const std::string &getMPrenom() const;

    const std::string &getMVilleNaissance() const;

    //const util::Date &getMDateNaissance() const;

    char getSexe() const;

    const std::string &getMNas() const;

    //const util::Date &getMDateDeces() const;

    bool isStatut() const;

    const std::string &getMGroupeSanguin() const;

    Personne(const std::string &mNom, const std::string &mPrenom, const std::string &mVilleNaissance,
             const std::tuple<int, int, int> &mDateNaissance, char sexe, const std::string &mNas,
             const std::string &mGroupeSanguin, const std::tuple<int, int, int> &mDateDeces, bool statut);

    const Tuple &getMDateDeces() const;

    void setMDateDeces(const std::tuple<int, int, int> &mDateDeces);

    const std::tuple<int, int, int> &getMDateNaissance() const;

    Personne &operator=(const Personne & personne);

    void setMNom(const std::string &mNom);

    void setMPrenom(const std::string &mPrenom);

    void setMVilleNaissance(const std::string &mVilleNaissance);

    void setMDateNaissance(const std::tuple<int, int, int> &mDateNaissance);

    void setSexe(char sexe);

};


#endif //ARBREGENEALOGIQUE_PERSONNE_H
