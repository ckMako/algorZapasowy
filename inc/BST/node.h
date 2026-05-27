#pragma once

#include <iostream>


/**
 * @brief node drzewa AVL
 */
template <class T>
struct avlNode {
    T data;//data to store
    int key;//tconst, moze byc jako string ew

    avlNode<T>* parent;
    avlNode<T>* left;
    avlNode<T>* right;

    int balans;//left<0<right
    int height;

    avlNode() {

    }

    avlNode(T k, const std::string& t) : key(k), left(nullptr), right(nullptr), height(1) {}

    avlNode(T argDat, int argKey) {
        data=argDat;
        //potencjalnie wolne
        key=data.getPriority();
    }
};


/**
 * @brief enum class do obsługi koloru nodea
 * @param true kolor czarny
 * @param false kolor czerw
 * @comm nie wiem co z tym : bool
 */
enum class Kolor : bool{
    black = true,
    red = false,
};


/**
 * @brief node drzewa red-black
 */
template <class T>
struct reblNode {
    T data; //pole data
    int key; //kopia elementu z data

    Kolor color=Kolor::red; //inicjalizujemy val, zeby uniknac bledow
    reblNode<T>* parent;
    reblNode<T>* left;
    reblNode<T>* right;

    reblNode() {}
    reblNode(T argDat, int argKey) : data(argDat), key(argKey) {}
    // reblNode(T argDat, int argKey) : data(argDat, argKey, 0), key(argKey) {} //zakładamy że argDat obsłuży 3 elem, ryzykowne
};