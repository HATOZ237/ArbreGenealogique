//
// Created by Duroy on 08/01/2021.
//

#include <iostream>
#include "Enfant.h"

int main()
{
    std::tuple<int, int, int> date(13, 8, 1971);
    std::cout<<date<<std::endl;
    Enfant enfant("Toukam", "Zanjio","Douala", date, 'M');
    enfant.AjouterFrere(enfant);
    std::cout<<enfant;
    return 0;
}