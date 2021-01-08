cmake_minimum_required(VERSION 3.17)
project(ArbreGenealogique)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) #for the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) #for static library
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) #for shared library

#add_library(ArbreGenealogique STATIC Personne.cpp Personne.h Enfant.cpp Enfant.h Famille.cpp Famille.h Clan.cpp Clan.h)
add_library(ArbreGenealogique STATIC Personne.cpp Enfant.cpp Famille.cpp Clan.cpp ContratException.cpp
        validationFormat.cpp Date.cpp)
link_directories(${PROJECT_SOURCE_DIR})
add_executable(main main.cpp)
target_link_libraries(main ArbreGenealogique)