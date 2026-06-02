#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream> 


enum class infoFilm {
    tconst,
    typTytulu,
    tytul,
    orygTytul,
    isAdult, 
    startYear,
    endYear,
    runTime,
    genres
};

//tsv->tab separated values
//ss rozdzieli tez tytuly

/**
 * @brief klasa ma duzo pol, nalezy posortowac po ptr*
 */
class movie {

    //tconst-wart ID IMBD
    // std::string tconst;
    long tconst;

    double averageRating=0.0;
    int	numVotes=0;

    //dodawane pozniej
    std::string title="noT";

    // std::string titleType; //short, short movie
    // std::string genres;

    public:

    /**
     * @brief konstruktor domyslnie uzywany
     * @param int l porzadkowa(tconst)/key
     * @param double rating
     * @param int l glosow
     */
    movie(int, double, int);
    movie();

    // ~movie();

    //gettery i settery

    double getAverageRating () const;

    int getTconst () const;

    std::string getTitle () const;

    /**
     * @param string title
     */
    void setTitle(std::string);

    //gettery i settery


    std::string printBrief()const;    
};


/**
 * @brief overload < dla Ratingow
 * @param   movie 2 filmy do porównania
 * @return wynik < dla AverageRaing
 */
bool operator<(const movie& a, const movie& b);

/**
 * @brief overload > dla Ratingow
 * @param   movie 2 filmy do porównania
 * @return wynik > dla AverageRaing
 */
bool operator>(const movie& a, const movie& b);
