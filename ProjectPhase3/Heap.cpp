#include <iostream>
#include <stdlib.h>
#ifndef CDA_CPP
#define CDA_CPP
    #include "CDA.cpp"
#endif
using namespace std;

template <typename keytype>
class Heap {
    private:
        // INSTANCE VARIABLES
        CDA<keytype>* storage; // CDA to store heap

        // heapify recursively
        void heapify(int currentElement) {
            keytype temp;
            while((currentElement*2)+1 < storage->Length()) {
                // if has two children
                if((currentElement*2)+2 < storage->Length()) {
                    // if both children are larger, stop swimming down and break
                    if((*storage)[(currentElement*2)+1] > (*storage)[currentElement] && (*storage)[(currentElement*2)+2] > (*storage)[currentElement]) {
                        return;
                    }
                    // else if left child is less than right child, swap with left child
                    else if((*storage)[(currentElement*2)+1] < (*storage)[(currentElement*2)+2]) {
                        temp = (*storage)[(currentElement*2)+1];
                        (*storage)[(currentElement*2)+1] = (*storage)[currentElement];
                        (*storage)[currentElement] = temp;
                        currentElement = (currentElement*2)+1;
                    }
                    // else right child is lesser, swap with right child
                    else {
                        temp = (*storage)[(currentElement*2)+2];
                        (*storage)[(currentElement*2)+2] = (*storage)[currentElement];
                        (*storage)[currentElement] = temp;
                        currentElement = (currentElement*2)+2;
                    }
                }
                // if only one child
                else {
                    // if child is larger, stop swimming and return root
                    if((*storage)[(currentElement*2)+1] > (*storage)[currentElement]) {
                        return;
                    }
                    // else swap with left child
                    else {
                        temp = (*storage)[(currentElement*2)+1];
                        (*storage)[(currentElement*2)+1] = (*storage)[currentElement];
                        (*storage)[currentElement] = temp;
                        currentElement = (currentElement*2)+1;
                    }
                }
            }
        } 
        
    public:
        // CONSTRUCTORS
        Heap() {
            storage = new CDA<keytype>();
        }
        Heap(keytype k[], int s) {
            storage = new CDA<keytype>(s);
            
            // copy elements into CDA
            for(int i = 0; i < s; i++) {
                (*storage)[i] = k[i];
            }
            
            // heapify
            for(int i = s-1; i >= 0; i--) {
                heapify(i);
            }
        }

        // DESTRUCTOR
        ~Heap() {
            delete storage;
        }

        // COPY CONSTRUCTOR AND COPY ASSIGNMENT CONSTRUCTOR
        Heap(const Heap &src) {
            storage = new CDA<keytype>(src.storage->Length());
            for(int i = 0; i < src.storage->Length(); i++) { // copy all items in array
                (*storage)[i] = (*src.storage)[i];
            }
        }
        Heap& operator=(const Heap& src) {
            if(this != &src) {
                storage = new CDA<keytype>(src.storage->Length());
                for(int i = 0; i < src.storage->Length(); i++) { // copy all items in array
                    (*storage)[i] = (*src.storage)[i];
                }
            }
            return *this;
        }

        // PEEK
        keytype peekKey() {
            return (*storage)[0]; // return root
        }

        // EXTRACT
        keytype extractMin() {
            // store and remove predecessor
            keytype temp = (*storage)[storage->Length()-1];
            storage->DelEnd();

            // if it was only element
            if(storage->Length() == 0) {
                return temp;
            }
            else {
                keytype root = (*storage)[0];
                (*storage)[0] = temp; // store in root

                // swim down
                int currentElement = 0;
                while((currentElement*2)+1 < storage->Length()) {
                    // if has two children
                    if((currentElement*2)+2 < storage->Length()) {
                        // if both children are larger, stop swimming down and return root
                        if((*storage)[(currentElement*2)+1] > (*storage)[currentElement] && (*storage)[(currentElement*2)+2] > (*storage)[currentElement]) {
                            return root;
                        }
                        // else if left child is less than right child
                        else if((*storage)[(currentElement*2)+1] < (*storage)[(currentElement*2)+2]) {
                            temp = (*storage)[(currentElement*2)+1];
                            (*storage)[(currentElement*2)+1] = (*storage)[currentElement];
                            (*storage)[currentElement] = temp;
                            currentElement = (currentElement*2)+1;
                        }
                        // else right child is lesser
                        else {
                            temp = (*storage)[(currentElement*2)+2];
                            (*storage)[(currentElement*2)+2] = (*storage)[currentElement];
                            (*storage)[currentElement] = temp;
                            currentElement = (currentElement*2)+2;
                        }
                    }
                    // if only one child
                    else {
                        // if child is larger, stop swimming and return root
                        if((*storage)[(currentElement*2)+1] > (*storage)[currentElement]) {
                            return root;
                        }
                        // else swap with left child
                        else {
                            temp = (*storage)[(currentElement*2)+1];
                            (*storage)[(currentElement*2)+1] = (*storage)[currentElement];
                            (*storage)[currentElement] = temp;
                            currentElement = (currentElement*2)+1;
                        }
                    }
                }
                return root;
            }
        }

        // INSERT
        void insert(keytype k) {
            storage->AddEnd(k); // insert to CDA

            // swim up
            int currentElement = storage->Length()-1;
            while((currentElement-1)/2 >= 0 && (*storage)[(currentElement-1)/2] > (*storage)[currentElement]) {
                keytype temp = (*storage)[(currentElement-1)/2];
                (*storage)[(currentElement-1)/2] = (*storage)[currentElement];
                (*storage)[currentElement] = temp;
                currentElement = (currentElement-1)/2;
            }
        }

        // PRINT KEY
        void printKey() {
            for(int i = 0; i < storage->Length(); i++) {
                cout << (*storage)[i] << " ";
            }
            cout << endl;
        }
};