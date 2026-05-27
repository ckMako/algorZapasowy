#pragma once

#include <chrono>

#include "movie.h"
#include "SORT/merge.h"
#include "SORT/algorytmySortowania.h"
#include "BST/rebl.h"

//iterowanie vector
// for (int x : v)        // kopia każdego elementu
// for (int& x : v)       // referencja, można modyfikować element
// for (const int& x : v) // referencja tylko do odczytu (najwydajniejsze)

//swap


/**
 * @brief kontener na filmy
 * @param ListaFilmow wektor filmow
 * @param indeksy indeksy filmow
 */
class listaFilmow {
    /**
     * co boedzie szybsze
     * std::vector<int> sortujemy indeksy
     * std::vector<movie*> sortujemy wskaznik
     */

    std::vector<movie> ListaFilmow;
    std::vector<int> indeksy; //to srtujemy; ListaFilmow[indeksy].setTitle
    // std::vector<movie*> ptrMovie //wiszace wskazniki przy relokacji(vector to dyn array)


    //do sortowania titles
    reblBTS<std::string> titleTree;

    public:

    listaFilmow();

    /**
     * @brief construc czytajacy juz dane, pamiec na filmy nalezy allocowac
     * 1 raz - na poczatku(alloc wazy duzo, kod wolny) - definiuje ilosc filmow
     * @param string nazwa pliku(titles)
     * @param int ile filmow
     */
    listaFilmow(std::string,int);

    /**
     * @brief niepotrzebne przy braku dyn mem alloc
     */
    ~listaFilmow(){}

    /**
     * @brief pushbackElem
     * @param movie film do dodania do vec
     */
    void addToList(const movie&);

    /**
     * @brief dodaje z pliku
     * @param string nazwa pliku(titles)
     * @param int ile filmow
     */
    void addFromFile(std::string, int);

    /**
     * @param fileName nazwa pliku z titles
     */
    void addTitles(std::string nazwa);  

    void usunPuste();

    /*gettery i settery */

    int getSize() const;

    /*end - gettery i settery */

    /** 
     * @brief sortuje dane na liscie
     * @param int typ sortowania
     */
    void sortowanie(const int);

    /**
     * @brief mierzy czas sortowania
     * @param int typ sortowania
     */
    void testSortowania(const int);

    void PrintBrief();

    void PrintTop10();

    void PrintLast10();

    void PrintMedian();

    /**
     * @brief top 3 w danej kat
     * @param int w jakiej kategorii
     */
    void top3Cat(const int, int typ);


    /**
     * @brief wyswietl mediane danych
     */
    void Mediana();
    
};




    // std::ifstream plik("DATA/title.basics.tsv/data.tsv");
    // std::string linia;

    // int limiter=0;
    // while (std::getline(plik, linia) && limiter<1000) {        // czyta do \n
    //     std::istringstream ss(linia);
    //     std::string pole;

    //     while (std::getline(ss, pole, ' ')) { // czyta do \t
    //         std::cout << pole << " | ";
    //     }
    //     std::cout << "\n";

    //     limiter++;
    // }

