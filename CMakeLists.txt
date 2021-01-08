cmake_minimum_required(VERSION 3.17)
project(ArbreGenealogique)

set(CMAKE_CXX_STANDARD 14)

add_library(ArbreGenealogique Personne.cpp Personne.h Enfant.cpp Enfant.h Famille.cpp Famille.h Clan.cpp Clan.h)