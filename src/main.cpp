#include "movieReader.h"

#include <cmath>

#define PRINTL(arg) std::cout<<arg<<std::endl //printLine

// void nextNonspace (std::string) {
//     for 
// }

int main(int argc, const char *argv[]) {
    long ilosc;
    std::cout<<"ile rek?"<<std::endl;
    std::cin>>ilosc;


    ilosc= std::pow(10, ilosc);  // 7-wszyskie
    std::cout<<"l rekordow: "<<ilosc<<std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    listaFilmow obj("/home/vboxuser/Desktop/Alg_Struct/algorSort/DATA/title.ratings.tsv/data.tsv",
        ilosc);
    obj.addTitles("/home/vboxuser/Desktop/Alg_Struct/algorSort/DATA/title.basics.tsv/data.tsv");
    std::cout<<"liczba filmow w struct "<<obj.getSize()<<std::endl;

    
    auto end = std::chrono::high_resolution_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout<<"czas zapisu: "<<czas.count()<<"ms"<<std::endl;
    obj.testSortowania(1);
    std::cout<<"Top 10: "<<std::endl;
    obj.PrintTop10();
    std::cout<<std::endl<<"Last 10: "<<std::endl;
    obj.PrintLast10();

    obj.usunPuste();

    obj.PrintBrief();

}

/*
https://eduinf.waw.pl/inf/alg/001_search/0117.php
https://eduinf.waw.pl/inf/alg/001_search/0121.php
wczytywanie + sortowanie ok 2 min
*/