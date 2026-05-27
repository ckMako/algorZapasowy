#pragma once

#include "node.h"

/**
 * Red-black tree elems
 * rotate L/R -> fix Black height
 * fixColors
 * add new elem
 * remove elem by key
 * find elem by key
 * 
 */


/**
 * @brief drzewo BST red-black
 * @tparam typ danych na node
 */
template <class T>
class reblBTS {
    reblNode<T>* root;
    //sentinel node
    reblNode<T>* NIL;//jeden NIL na który wskazuja wszysktkie liscie
    int size=0;

    public:
    reblBTS() {
        NIL  = new reblNode<T>();
        NIL->color = Kolor::black; //NIL zawsze czarny
        NIL->left=NIL;
        NIL->right=NIL;
        NIL->parent=NIL;
        root = NIL;
    }

    ~reblBTS() {
        clearTree(root);
        delete NIL;
    }

    bool isNil(reblNode<T>* arg) {
        return arg == NIL;
    }

    /**
     * @brief odwraca col 
     * func moze nie byc optymalna z if condition
     */
    void changeCol (reblNode<T>* toChang) {
        // toChang->color = ~toChang->color //wlasnie tak nie mozna
        if(toChang->color==Kolor::black)
            toChang->color=Kolor::red;
        
        else
            toChang->color=Kolor::black;
    }

    /**
     * @brief insert Data oraz priority(key)
     * @param T film
     * @param int klucz
     */
    void insert(T argData, int argKey) {
        reblNode<T>* tmp=root;

        //sprawdzamy czy root to NIL
        if(isNil(tmp)) {
            root=new reblNode<T>(argData, argKey);
            root->color = Kolor::black;
            root->left=NIL;
            root->right=NIL;
            root->parent=tmp;
            size++;
            return;
        }
        while (!isNil(tmp))//chyba while moze miec po prostu warunek zawsze true
        {
            if (tmp->key > argKey) {
            //go left

            if(isNil(tmp->left)){ //insert w momencie znalezienia NIL
                reblNode<T> *toIns = new reblNode<T>(argData, argKey); //dyn mem alloc - slow
                toIns->color = Kolor::red; //default czerwony, 
                tmp->left=toIns;
                toIns->left=NIL;
                toIns->right=NIL;
                toIns->parent=tmp;
                fixInsert(toIns); //napraw kolory
                size++;
                break;
            } else {
                tmp=tmp->left; //idz dalej jesli nie NIL
            }
            }

            else {
            //go right
            //na prawo laduja tez warunki =, 

            if(isNil(tmp->right)){
                reblNode<T> *toIns = new reblNode<T>(argData, argKey);
                toIns->color = Kolor::red;
                tmp->right=toIns;
                toIns->left=NIL;
                toIns->right=NIL;
                toIns->parent=tmp;
                fixInsert(toIns);
                size++;
                break;
            }  else {
                tmp=tmp->right;
            }
        }
        
    }}



    /**
     * @brief func naprawia kolory po Insert
     * @param reblNode ptr* na node od którego zaczynamy naprawianie
     * red nie moze miec red child
     * root i NIL jest black
     * default insert to red
     */
    void fixInsert(reblNode<T>* toFix) {

        //ograniczamy dostawanie sie przez wskazniki podczas wyszukiwania func
        reblNode<T>* Dad = toFix->parent;
        reblNode<T>* wujek=NIL;

        // nowy node zawsze red, dopoki ojciec red-zmieniamy kolory(zatrzymuje sie na pierwszym black)
        while (toFix->parent->color == Kolor::red) {

            if(isRight(Dad)==99){
                //do nothing
                //parent to NIL
            }

            // czy ojciec to LEFT child
            else if (!isRight(Dad)) {
                wujek = Dad->parent->right;

                // VAR 1 : wujek jest RED, zmieniamy kolor na
                if (wujek->color == Kolor::red) {
                    toFix->parent->color          = Kolor::black;
                    wujek->color              = Kolor::black;
                    toFix->parent->parent->color  = Kolor::red;
                    toFix = toFix->parent->parent; // idź wyżej
                } 
                else {
                    // PRZYPADEK 2: z jest PRAWYM dzieckiem — rotacja w lewo
                    if (toFix == toFix->parent->right) {
                        toFix = toFix->parent;
                        rotateLEFT(toFix);
                    }
                    // PRZYPADEK 3: z jest LEWYM dzieckiem — rotacja w prawo
                    toFix->parent->color         = Kolor::black;
                    toFix->parent->parent->color = Kolor::red;
                    rotateRIGHT(toFix->parent->parent);
                }
            } 
            // czy ojciec to RIGHT child
            else {
                reblNode<T>* wujek = toFix->parent->parent->left;

                // PRZYPADEK 1: wujek czerwony — przekoloruj
                if (wujek->color == Kolor::red) {
                    toFix->parent->color         = Kolor::black;
                    wujek->color             = Kolor::black;
                    toFix->parent->parent->color = Kolor::red;
                    toFix = toFix->parent->parent;
                } 
                else {
                    // PRZYPADEK 2: z jest LEWYM dzieckiem — rotacja w prawo
                    if (toFix == toFix->parent->left) {
                        toFix = toFix->parent;
                        rotateRIGHT(toFix);
                    }
                    // PRZYPADEK 3: z jest PRAWYM dzieckiem — rotacja w lewo
                    toFix->parent->color         = Kolor::black;
                    toFix->parent->parent->color = Kolor::red;
                    rotateLEFT(toFix->parent->parent);
                }
            }
        }
        // korzeń zawsze czarny
        root->color = Kolor::black;
    }


    /**
     * @brief naprawia ilosc black node po usunieciu elem
     * @param reblNode node zajmujacy miejsce
     */
    void fixDelete(reblNode<T>* toFix) {
        //toFix 
        while (toFix != root && toFix->color == Kolor::black)
        
        {
            // toFix jest lewym child
            if (toFix == toFix->parent->left)
            {
                reblNode<T>* sibl = toFix->parent->right;

                // CASE 1:
                // sibling czerwony
                if (sibl->color == Kolor::red)
                {
                    sibl->color = Kolor::black;
                    toFix->parent->color = Kolor::red;

                    rotateLEFT(toFix->parent);

                    sibl = toFix->parent->right;
                }

                // CASE 2:
                // sibling black + oboje dzieci black
                if (sibl->left->color == Kolor::black &&
                    sibl->right->color == Kolor::black)
                {
                    sibl->color = Kolor::red;
                    toFix = toFix->parent;
                }
                else
                {
                    // CASE 3:
                    // right child black
                    if (sibl->right->color == Kolor::black)
                    {
                        sibl->left->color = Kolor::black;
                        sibl->color = Kolor::red;

                        rotateRIGHT(sibl);

                        sibl = toFix->parent->right;
                    }

                    // CASE 4:
                    sibl->color = toFix->parent->color;
                    toFix->parent->color = Kolor::black;
                    sibl->right->color = Kolor::black;

                    rotateLEFT(toFix->parent);

                    toFix = root;
                }
            }

            // SYMETRYCZNIE
            else
            {
                reblNode<T>* sibl = toFix->parent->left;

                // CASE 1
                if (sibl->color == Kolor::red)
                {
                    sibl->color = Kolor::black;
                    toFix->parent->color = Kolor::red;

                    rotateRIGHT(toFix->parent);

                    sibl = toFix->parent->left;
                }

                // CASE 2
                if (sibl->right->color == Kolor::black &&
                    sibl->left->color == Kolor::black)
                {
                    sibl->color = Kolor::red;
                    toFix = toFix->parent;
                }
                else
                {
                    // CASE 3
                    if (sibl->left->color == Kolor::black)
                    {
                        sibl->right->color = Kolor::black;
                        sibl->color = Kolor::red;

                        rotateLEFT(sibl);

                        sibl = toFix->parent->left;
                    }

                    // CASE 4
                    sibl->color = toFix->parent->color;
                    toFix->parent->color = Kolor::black;
                    sibl->left->color = Kolor::black;

                    rotateRIGHT(toFix->parent);

                    toFix = root;
                }
            }
            }

            toFix->color = Kolor::black;
        }


        /**
         * @brief find key val
         * @param klucz wartosc do wyszukania
         * @return prt* na wartosc wg klucza
         * OBSŁÓGA WARTOŚCI =,
         * teoretycznie mozna znalezc wartosci = wywolujac to samo na retVal->right znajdzKey
         */

        reblNode<T>* findKey(int klucz) {
            reblNode<T>* retVal=root;
            while(  retVal!=NIL &&  (retVal->key!=klucz)  ){

                if(  retVal->key  <  klucz  )
                    //go right
                    retVal = retVal->right;
                else
                    //go left
                    retVal = retVal->left;
            }
            return retVal;
        }

        /**
         * @brief obroc drzewo w lewo (RIGHT elem zostaje PARNET)
         * @param wskaznik na ex-parent
         */
        void rotateLEFT(reblNode<T>* argParent) {
            if(argParent->right==NIL){
                std::cout<<"nie wykonano rotacji lewej"<<std::endl;
                return;
            }

            // reblNode<T>* babyHolder[3];//lepiej sep variables
            reblNode<T>* parentsParent;
            reblNode<T>* parToBe;
            reblNode<T>* childsChild;
            
            parentsParent=argParent->parent;//ojciec ojca
            parToBe=argParent->right;//paretn to be
            childsChild=parToBe->left;//LEWE dziecko dziecka

            //ojciec ojca wskazuje na nowego syna (jesli nie NIL)
            if(argParent->parent!=NIL){                 
                if(parentsParent->left==argParent)
                    parentsParent->left=parToBe;
                else
                    parentsParent->right=parToBe;
                }

            //nowy root jesli to byl root
            else 
                root=parToBe;

            //nowy ojciec ustawia LEWE dziecko(ex-ojca) i PARENT
            parToBe->left=argParent;
            parToBe->parent=argParent->parent;


            //ex-ojciec ustawia nowe dziecko PRAWE i PARENT
            argParent->right=childsChild;
            argParent->parent=parToBe;

            //PRAWE dziecko ustawia ex-ojca
            if(childsChild!=NIL) {
                childsChild->parent=argParent;
            }

        }

        /**
         * @brief obroc drzewo w prawo (LEFT elem zostaje PARNET)
         * @param wskaznik na ex-parent
         */
        void rotateRIGHT(reblNode<T>* argParent) {
            if(argParent->left==NIL){
                std::cout<<"nie wykonano rotacji prawej"<<std::endl;
                return;
            }

            // reblNode<T>* babyHolder[3];//lepiej sep variables
            reblNode<T>* parentsParent;
            reblNode<T>* parToBe;
            reblNode<T>* childsChild;//zmiana array[3] na 3 wskazniki nic nie zmienia
            
            parentsParent=argParent->parent;//ojciec ojca
            parToBe=argParent->left;//paretn to be
            childsChild=parToBe->right;//LEWE dziecko dziecka

            //ojciec ojca wskazuje na nowego syna (jesli nie NIL)
            if(argParent->parent!=NIL){                 
                if(parentsParent->right==argParent)
                    parentsParent->right=parToBe;
                else
                    parentsParent->left=parToBe;
                }

            //nowy root jesli to byl root
            else 
                root=parToBe;

            //nowy ojciec ustawia LEWE dziecko(ex-ojca) i PARENT
            parToBe->right=argParent;
            parToBe->parent=argParent->parent;


            //ex-ojciec ustawia nowe dziecko PRAWE i PARENT
            argParent->left=childsChild;
            argParent->parent=parToBe;

            //PRAWE dziecko ustawia ex-ojca
            if(childsChild!=NIL) {
                childsChild->parent=argParent;
            }

        }

        /**
         * @brief sprawdza czy node jest prawym synem
         * @return int - 0 jeżeli jest left, 1 jeżeli jest right, 99 jeżeli paretn to NIL (nie zwroci err)
         */
        int isRight (reblNode<T>* toCheck) {
            reblNode<T>* Dad = toCheck->parent;
            if (Dad == NIL)
                // nie wywala programu.
                return 99;
            if (Dad->left==toCheck)
                return 0;

            if (Dad->right==toCheck)
                return 0;

        }

        /**
         * @brief znajdz wezel przech max wartosc
         * @zalozenie po prostu idz w prawo caly czas az trafisz na NIL lub nullptr
         */
        reblNode<T>* fMaxNode () {
            reblNode<T>* tmp=root;
            if(isNil(root))
                throw std::runtime_error("empty tree");
            while (tmp->right!=NIL) {
                tmp=tmp->right;
            }
            return tmp;
        }


        /**
         * @brief znajdz wezel przech min wartosc
         * @zalozenie po prostu idz w lewo caly czas az trafisz na NIL lub nullptr
         */
        reblNode<T>* fMinNode () {
            reblNode<T>* tmp=root;
            if(isNil(root))
                throw std::runtime_error("empty tree");
            while (tmp->left!=NIL) {
                tmp=tmp->left;
            }
            return tmp;
        }


        /**
         * @brief zwrócenie i usunięcie największego elementu 
         */
        T extract_max()  {
            reblNode<T>* maxNode = fMaxNode();//po prostu w prawo
            T ret = maxNode->data; //to extract

            reblNode<T>* child = maxNode->left;

            Kolor deletedColor = maxNode->color;

            if (maxNode->parent == NIL) //wstaw child jako root, jezeli usuwasz root
                root = child;
            else
                maxNode->parent->right = child;

            child->parent = maxNode->parent;

            delete maxNode;

            size--;

            if (deletedColor == Kolor::black)
                fixDelete(child);

            return ret;
        }


        /**
         * @brief zwrócenie największego elementu
         * wg key tj priority
         */
        T find_max()  {
            if(isNil(root))
                throw std::runtime_error("empty tree"); //warunke ponieważ jeżeli fMaxNode() wyrzuci Error to i tak ta func próbuje dotknąć pola data
            return fMaxNode()->data;
        }

        //usun ostatni
        void removeLast(){
            
        }

        //zmiana priorytetu elementu e na p
        /**
         * @brief zmien wartosc elementu o danym key na val
         * @param T wartosc do zmiany
         * @param int klucz
         */
        void modify_key(T argData, int argKey) {
            reblNode<T>* tmp = this->findKey(argKey); 
            tmp->data.setValue(argData);
        }

        /**
         * @brief policz wszystkie nodey(wolne, nie ma sensu bo jest juz int size)
         */
        int countNodes(reblNode<T>* node) {
            if(isNil(node)) return 0;
                return 1 + countNodes(static_cast<reblNode<T>*>(node->left))+ countNodes(static_cast<reblNode<T>*>(node->right));
        }
        /**
         * @brief zwrócenie liczby elementów w kolejce
         */
        int return_size()  {
            return size;
        }


        /**
         * @brief za pomocą rekurencji wyczysc nodey
         */
        void clearTree(reblNode<T>* node) {
            if(isNil(node)) return;
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
        //to samo co wyzej tylko obsl root i size
        void clear()  {
            clearTree(root);
            root = NIL;
            size = 0;
        }

        /**
         * @brief do testow
         */
        void printInOrder(reblNode<T>* node) {
            if(isNil(node)) return;
            printInOrder(node->left);
            std::cout << node->key << " ";
            printInOrder(node->right);
        }


        //wypisanie kolejki
        void print_queue()  {
            printInOrder(root);
            std::cout << std::endl;
        }

        //zwracanie wartości elementu w id(do testów)
        T getValueById(int id)  {
            reblNode<T>* result = findKey(id);
            if(isNil(result)) throw std::runtime_error("nie znaleziono");
            return result->data.getValue();
        }


        // gettery
        reblNode<T>* getRoot() { return root; }
        reblNode<T>* getNIL()  { return NIL;  }


        /**
         * @brief poprzednia wersja bledna
         * extract elem
         * change val(key)
         * insert
         */
        void modify_keyProper(int oldKey, int newKey) {
            reblNode<T>* node = findKey(oldKey);

            if (isNil(node))
                throw std::runtime_error("key not found");

            T value = node->data.getValue();

            // usuń stary, remove naprawi drzewo
            remove(oldKey);

            // dodaj nowy, zachowaj Data.value, jesli zmienimy value, to bez sensu jest cala ta operacja bo to po prostu insert
            insert(value, newKey);
        }

        /**
         * @brief rekurencyjny validator dla calego tree
         */
        bool validateRebl()
        {
            // puste drzewo jest poprawne
            if (root == NIL)
                return true;

            // ROOT musi byc black
            if (root->color != Kolor::black)
                return false;

            // NIL musi byc black
            if (NIL->color != Kolor::black)
                return false;

            int blackHeight = -1;

            return validateNode(root, 0, blackHeight);
        }

        /**
         * @brief validator dla 1 nde
         */
        bool validateNode(
            reblNode<T>* node,
            int blackCount,
            int& expectedBlackHeight) {
            // NIL = koniec sciezki
            if (node == NIL)
            {
                // pierwszy NIL ustawia wzorzec
                if (expectedBlackHeight == -1)
                {
                    expectedBlackHeight = blackCount;
                    return true;
                }

                // kolejne musza miec ten sam black height
                return blackCount == expectedBlackHeight;
            }

            // RED node nie moze miec RED child
            if (node->color == Kolor::red)
            {
                if (node->left->color == Kolor::red ||
                    node->right->color == Kolor::red)
                {
                    return false;
                }
            }

            // BST property
            if (node->left != NIL &&
                node->left->key > node->key)
            {
                return false;
            }

            if (node->right != NIL &&
                node->right->key < node->key)
            {
                return false;
            }

            // liczymy black node
            if (node->color == Kolor::black)
                blackCount++;

            return validateNode(node->left,
                                blackCount,
                                expectedBlackHeight)
                &&
                validateNode(node->right,
                                blackCount,
                                expectedBlackHeight);
        }

    //TO DO
    void removieGivenNodebyKey(reblNode<T>* TOREM){
        //find min in right
        //or find max in left
        //becomes succesor
        //repair COLORS
    }

    /**
     * @brief oblicz height RECZNIE
     * implmntd przed size w strukturze
     */
    int height(reblNode<T>* toCalc) {
        if(toCalc == NIL) return 0; //no root

        return 1 + std::max(
            height(toCalc->left),
            height(toCalc->right)
            );
    }

};