#include "movie.h"

movie::movie(int arg1, double arg2, int arg3){
    tconst=arg1;
    averageRating=arg2;
    numVotes=arg3;
}

movie::movie() {

}


double movie::getAverageRating () const{
    return averageRating;
}

int movie::getTconst () const {
    return tconst;
}

std::string movie::getTitle () const {
    return title;
}

void movie::setTitle(std::string Title) {
    title=Title;
}

std::string movie::printBrief()const{
    std::string ret=std::to_string(this->averageRating);
    ret+=" tytul: ";
    ret+=this->title;
    ret+=" tconst: ";
    ret+=std::to_string(this->tconst);
    return ret;
}


bool operator<(const movie& a, const movie& b) {
    return a.getAverageRating() < b.getAverageRating();
}
bool operator>(const movie& a, const movie& b) {
    return a.getAverageRating() > b.getAverageRating();
}
