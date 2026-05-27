#include "movieReader.h"
#include "SORT/quicksort.h"


// std::vector <movie> filmy...


// vector<int> v;

// v.push_back(5);     // dodaj na koniec
// v.pop_back();       // usuń ostatni
// v.size();           // liczba elementów
// v.empty();          // czy pusty
// v[0];               // dostęp po indeksie (bez sprawdzania zakresu)
// v.at(0);            // dostęp po indeksie (z wyjątkiem gdy poza zakresem)
// v.clear();          // usuń wszystkie elementy
// v.front();          // pierwszy element
// v.back();           // ostatni element

listaFilmow::listaFilmow(){}

listaFilmow::listaFilmow(std::string plik, int ile){
    /*problem resize+aloc pamieci */
    ListaFilmow.reserve(ile);//na ilosc objektow
    indeksy.reserve(ile);
    for(int i =0; i<ile; i++) {
        // indeksy.back();//do dodawania od indeksu koncowego
        indeksy.push_back(i);
    }

    this->addFromFile(plik, ile);
}

//~listaFilmow(){}

void listaFilmow::addToList(const movie& arg) {
        ListaFilmow.push_back(arg);
}

void listaFilmow::addFromFile(std::string nazwa, int ile) {
    //filestream
    std::ifstream file(nazwa);
    if (!file.is_open()) {
        throw std::runtime_error("Nie mozna otworzyc pliku");
    }

    std::string line;

    // Pomiń header
    std::getline(file, line);

    //pass args
    std::string tmp;
    int tconst;
    double rating = 0.0;
    int numVotes = 0;

    int counter = 0;
    while (std::getline(file, line) && counter < ile) {
        std::stringstream ss(line);

        std::getline(ss, tmp, '\t');   // tconst do tab
        // rzutowanie na logn
        long tconst = std::stol(tmp.substr(2));  // "0000001"  =1 (long)

        std::getline(ss, tmp, '\t');      // rating
        rating = std::stod(tmp);
        std::getline(ss, tmp, '\t');      // numVotes
        numVotes = std::stoi(tmp);

        ListaFilmow.push_back(movie(tconst, rating, numVotes));

        counter++;
    }
}

void listaFilmow::addTitles(std::string nazwa) {
    std::ifstream file(nazwa);
    if (!file.is_open())
        throw std::runtime_error("Nie mozna otworzyc pliku: " + nazwa);

    std::string line, tmp, title;
    int tconst;
    // pomiń header
    std::getline(file, line); 

    //counter
    int counter=this->ListaFilmow.size();
    while (std::getline(file, line) && counter > 1) {
        std::stringstream ss(line);

        std::getline(ss, tmp, '\t');  // tconst
        tconst = std::stol(tmp.substr(2));

        std::getline(ss, tmp, '\t');  // titleType (pomijamy)

        std::getline(ss, tmp, '\t');  // primaryTitle
        title = tmp;
        // std::string title = tmp;

        titleTree.insert(title, tconst);
        counter--;
    }

    // Uzupełnij tytuły w wektorze
    for (movie& m : ListaFilmow) {
        m.setTitle(titleTree.getValueById(m.getTconst()));
    }
}


void listaFilmow::usunPuste() {
    int licznik = 0;
    for (int m : indeksy) {
        if (ListaFilmow[m].getTitle().empty()) {  // twój warunek
            licznik++;
        }
    }
    std::cout<<"liczna filmow bez tyt: " <<licznik<<std::endl;
}

/*gettery i settery*/

    int listaFilmow::getSize() const{
        return ListaFilmow.size();
    }

/*gettery i settery*/

void listaFilmow::sortowanie(const int arg){
    switch (arg)
    {
    case 1:
        std::cout<<"Merge sort"<<std::endl;
        mergeSort(this->ListaFilmow, this->indeksy, 0, this->indeksy.size() - 1);
        break;
    
    case 2:
        std::cout<<"quick sort"<<std::endl;
        quickSort(ListaFilmow, indeksy);
        break;
    
    default:
        std::cout<<"Merge sort"<<std::endl;
        mergeSort(this->ListaFilmow, this->indeksy, 0, this->indeksy.size() - 1);
        break;
    }
}

void listaFilmow::testSortowania(const int arg) {
    auto start = std::chrono::high_resolution_clock::now();
    
    sortowanie(arg);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Czas sortowania: " << czas.count() << " ms" << std::endl;
}


void listaFilmow::PrintBrief() {
    for (const movie m : ListaFilmow) {
        std::cout << m.printBrief() << std::endl;
    }
}

void listaFilmow::PrintLast10() {
    for (int i = 0; i < 10; i++)
        std::cout << ListaFilmow[indeksy[i]].printBrief() << std::endl;
}

void listaFilmow::PrintTop10() {
    for (int i = 0; i < 10; i++)
        std::cout << ListaFilmow[indeksy[indeksy.size()-i-1]].printBrief() << std::endl;
}

void listaFilmow::top3Cat(const int arg, int typ) {}

