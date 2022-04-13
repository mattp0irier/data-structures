#include <iostream>
#include <stdlib.h>
#ifndef CDA_CPP
#define CDA_CPP
    #include "CDA.cpp"
#endif
using namespace std;

template <typename keytype>
class BHeap {
    private:
        // STRUCT FOR NODES
        struct Node {
            keytype data;
            Node* child;
            Node* sibling;
            int degree;

            // Node Constructor
            Node(keytype d) {
                data = d;
                degree = 0;
                child = NULL;
                sibling = NULL;
            }

            // Node Destructor
            ~Node() {
                delete child;
                delete sibling;
            }
        };
        
        // INSTANCE VARIABLES
        CDA<Node*>* trees; // CDA to store pointers to roots of trees

        // ADD NODE (to empty heap)
        void addNode(keytype k) {
            Node* newNode = new Node(k);
            trees->AddEnd(newNode);
        }

        // ADD Tree (to empty heap)
        void addTree(Node* n) {
            for(int i = 0; i < n->degree; i++) {
                trees->AddEnd(NULL);
            }
            trees->AddEnd(n);
        }

        // MERGE TREES
        Node* mergeTrees(Node* a, Node* b) {
            Node* mergedNode;
            if(a->data < b->data) { // set root based on which one has lesser value
                mergedNode = a;
                b->sibling = mergedNode->child; 
                mergedNode->child = b; // ensure largest child has the child pointer
            }
            else {
                mergedNode = b;
                a->sibling = mergedNode->child;
                mergedNode->child = a; // ensure largest child has the child pointer
            }

            mergedNode->degree++; // increase degree
            return mergedNode;
        }

        void printKeyRecursive(Node* n) {
            cout << n->data << " "; // print data first
            if(n->child != NULL) {
                printKeyRecursive(n->child); // if child, go to the child first
            }
            if(n->sibling != NULL) {
                printKeyRecursive(n->sibling); // then go to sibling if sibling
            }
        }

        Node* copyRecursive(Node* src) {
            if(src == NULL) { // base case
                return NULL;
            }
            Node* newNode = new Node(src->data); // create node
            newNode->degree = src->degree;
            if(src->child != NULL) {
                newNode->child = copyRecursive(src->child); // if child, copy the child first
            }
            if(src->sibling != NULL) {
                newNode->sibling = copyRecursive(src->sibling); // then copy the sibling if sibling
            }
            return newNode;
        }

    public:
        // CONSTRUCTORS
        BHeap() {
            trees = new CDA<Node*>();
        }

        BHeap(keytype k[], int s) {
            trees = new CDA<Node*>();
            for(int i = 0; i < s; i++) {
                insert(k[i]);
            }
        }

        // DESTRUCTOR
        ~BHeap() {
            for(int i = 0; i < trees->Length(); i++) { // delete root nodes, which will call delete on all children
                delete ((*trees)[i]);
            }
            delete trees;
        }

        // COPY CONSTRUCTOR AND COPY ASSIGNMENT CONSTRUCTOR
        BHeap(const BHeap &src) {
            trees = new CDA<Node*>();
            for(int i = 0; i < src.trees->Length(); i++) { // copy all roots, which will call copy on all children
                trees->AddEnd(copyRecursive(src.trees->get(i)));
            }
        }
        BHeap& operator=(const BHeap& src) {
            if(this != &src) {
                delete trees;
                trees = new CDA<Node*>();
                for(int i = 0; i < src.trees->Length(); i++) { // copy all roots, which will call copy on all children
                    trees->AddEnd(copyRecursive(src.trees->get(i)));
                }
            }
            return *this;
        }

        // PEEK KEY
        keytype peekKey() {
            keytype min; // temp var to hold min
            int indexOfMin = -1; // index of min

            // loop through root list
            for(int i = 0; i < trees->Length(); i++) {
                if(indexOfMin == -1 && (*trees)[i] != NULL) { // if min is not set and current root is not null
                    min = (*trees)[i]->data;
                    indexOfMin = i;
                }
                else {
                    if((*trees)[i] != NULL && (*trees)[i]->data < min) { // if current root is not null and new minimum
                        min = (*trees)[i]->data;
                        indexOfMin = i;
                    }
                }
            }
            return min;
        }

        // EXTRACT MIN
        keytype extractMin() {
            keytype min; // temp var to hold min
            int indexOfMin = -1; // index of min

            // loop through root list
            for(int i = 0; i < trees->Length(); i++) {
                if(indexOfMin == -1 && (*trees)[i] != NULL) { // if min is not set and current root is not null
                    min = (*trees)[i]->data;
                    indexOfMin = i;
                }
                else {
                    if((*trees)[i] != NULL && (*trees)[i]->data < min) { // if current root is not null and new minimum
                        min = (*trees)[i]->data;
                        indexOfMin = i;
                    }
                }
            }

            // extract
            if((*trees)[indexOfMin]->child == NULL) { // if a B0
                (*trees)[indexOfMin] = NULL;
                if(indexOfMin == trees->Length()-1) {
                    trees->DelEnd();
                }
            }
            else { // otherwise any other order
                Node* ptrToChild = (*trees)[indexOfMin]->child;
                (*trees)[indexOfMin] = NULL;
                while(ptrToChild != NULL) {
                    BHeap<keytype> temp; // temp heap to be merged
                    temp.addTree(ptrToChild); // add child tree of min to new tree
                    int degreeOfChild = ptrToChild->degree; // set degree
                    ptrToChild = ptrToChild->sibling; // iterate to next sibling
                    temp.trees->get(degreeOfChild)->sibling = NULL; // clear sibling pointer of root
                    merge(temp); // merge to existing heap
                }
            }

            return min;
        }

        // INSERT
        void insert(keytype k) {
            BHeap<keytype> temp; // create temp BHeap
            temp.addNode(k); // create new node in temp
            merge(temp); // merge this with temp
        }

        // MERGE
        void merge(BHeap<keytype> &H2) {
            for(int i = 0; i < H2.trees->Length(); i++) {
                if(H2.trees->get(i) != NULL && i >= trees->Length()) { // if at end of trees, simply add to it
                    trees->AddEnd(H2.trees->get(i));
                    H2.trees->get(i) = NULL;
                }
                else if(H2.trees->get(i) != NULL && (*trees)[i] == NULL) { // if spot in current heap is open, simply add tree from H2
                    (*trees)[i] = H2.trees->get(i);
                    H2.trees->get(i) = NULL;
                }
                else if(H2.trees->get(i) != NULL && (*trees)[i] != NULL) { // if two trees of the same size
                    int j = i;
                    Node* pointerToMergedTree = mergeTrees((*trees)[j],H2.trees->get(i));
                    (*trees)[j] = NULL;
                    H2.trees->get(i) = NULL;
                    while(j < trees->Length()) {
                        if(j+1 >= trees->Length()) { // if at end of trees, simply add to it
                            trees->AddEnd(pointerToMergedTree);
                            break;
                        }
                        else if((*trees)[j+1] == NULL) { // if next tree is blank, just place it there
                            (*trees)[j+1] = pointerToMergedTree;
                            break;
                        }
                        else if((*trees)[j+1] != NULL) { // if next tree is not blank
                            pointerToMergedTree = mergeTrees(pointerToMergedTree, (*trees)[j+1]); // merge current pointer to merged tree and next tree
                            (*trees)[j+1] = NULL; // clear next tree
                        }
                        j++;
                    }
                }
            }
            // cleanup extra spaces on end of trees array
            while((*trees)[trees->Length()-1] == NULL) {
                trees->DelEnd();
            }

            // consume H2
            H2.trees->Clear();
        }

        // PRINT KEY
        void printKey() {
            for(int i = 0; i < trees->Length(); i++) {
                if((*trees)[i] != NULL) {
                    cout << endl << "B" << i << endl;
                    printKeyRecursive((*trees)[i]); // call printKeyRecursive on root nodes, which will call it for all children
                    cout << endl;
                }
            }
        }
};