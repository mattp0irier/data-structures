#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename keytype, typename valuetype>
class Two4Tree {
    private:
        struct Two4Node {
            // NODE INSTANCE VARIABLES
            keytype* keys; // pointer for array of keys
            valuetype* values; // pointer for array of values
            Two4Node** children; // pointer for array of children pointers
            int subtreeSize;
            Two4Node* parent; // parent pointer
            int nodeSize;

            // NODE CONSTRUCTOR
            Two4Node() {
                keys = new keytype[3];
                values = new valuetype[3];
                children = new Two4Node*[4];
                // set pointers to NULL
                for(int i = 0; i < 4; i++) {
                    children[i] = NULL;
                }
                parent = NULL;
                nodeSize = 2;
                subtreeSize = 0;
            }
            
            // NODE DESTRUCTOR
            ~Two4Node() {
                delete[] keys;
                delete[] values;
                delete[] children;
            }

            // adds key to node in proper place, shifting others over
            void addKey(keytype k, valuetype v) {
                switch (nodeSize) { // check node size
                case 2:
                    if(k < keys[0]) { // if new key is lower, shift and add to beginning
                        keys[1] = keys[0];
                        values[1] = values[0];
                        keys[0] = k;
                        values[0] = v;
                    }
                    else { // else new key is higher, add to end
                        keys[1] = k;
                        values[1] = v;
                    }
                    nodeSize++;
                    break;
                case 3:
                    if(k < keys[0]) { // if new key is lowest, shift and add to beginning
                        keys[2] = keys[1];
                        values[2] = values[1];
                        keys[1] = keys[0];
                        values[1] = values[0];
                        keys[0] = k;
                        values[0] = v;
                    }
                    else if(k < keys[1] && k >= keys[0]) { // if new key is in between, shift right key and add to middle
                        keys[2] = keys[1];
                        values[2] = values[1];
                        keys[1] = k;
                        values[1] = v;
                    }
                    else { // else new key is highest, so add to end
                        keys[2] = k;
                        values[2] = v;
                    }
                    nodeSize++; // increase node size
                    break;
                default:
                    cout << "Node has invalid size" << endl;
                    break;
                }
            }

            // PREEMPTIVE SPLIT
            void splitNode() {
                if(parent == NULL) { // if root node
                    // new child nodes
                    Two4Node* leftChild = new Two4Node();
                    Two4Node* rightChild = new Two4Node();
                    // copy items into left child from current root
                    leftChild->keys[0] = keys[0];
                    leftChild->values[0] = values[0];
                    leftChild->children[0] = children[0];
                    leftChild->children[1] = children[1];
                    if(leftChild->children[0] != NULL) {
                        leftChild->children[0]->parent = leftChild;
                        leftChild->children[1]->parent = leftChild;
                    }
                    leftChild->parent = this;
                    // copy items into right child from current root
                    rightChild->keys[0] = keys[2];
                    rightChild->values[0] = values[2];
                    rightChild->children[0] = children[2];
                    rightChild->children[1] = children[3];
                    if(rightChild->children[0] != NULL) {
                        rightChild->children[0]->parent = rightChild;
                        rightChild->children[1]->parent = rightChild;
                    }
                    rightChild->parent = this;
                    // correct subtree sizes based on children
                    for(int i = 0; i < 2; i++) {
                        if(leftChild->children[i] != NULL) {
                            leftChild->subtreeSize += leftChild->children[i]->subtreeSize;
                        }
                        if(rightChild->children[i] != NULL) {
                            rightChild->subtreeSize += rightChild->children[i]->subtreeSize;
                        }
                    }
                    // add keys in node themselves to subtree size
                    leftChild->subtreeSize++;
                    rightChild->subtreeSize++;
                    // reassign root node values
                    keys[0] = keys[1];
                    values[0] = values[1];
                    children[0] = leftChild;
                    children[1] = rightChild;
                    nodeSize = 2;
                }
                else {
                    Two4Node* newChild = new Two4Node();
                    if(parent->nodeSize == 2) { // if two node
                        if(parent->children[1] == this) { // if right child
                            parent->keys[1] = keys[1];
                            parent->values[1] = values[1];
                            parent->nodeSize++;
                            newChild->parent = parent;
                            newChild->keys[0] = keys[2];
                            newChild->values[0] = values[2];
                            newChild->subtreeSize++;
                            newChild->children[0] = children[2];
                            newChild->children[1] = children[3];
                            if(newChild->children[0] != NULL) {
                                newChild->children[0]->parent = newChild;
                                newChild->children[1]->parent = newChild;
                                newChild->subtreeSize += newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                                subtreeSize -= newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                            }
                            subtreeSize -= 2;
                            parent->children[2] = newChild;
                            children[2] = NULL;
                            children[3] = NULL;
                            nodeSize = 2;
                        }
                        else if(parent->children[0] == this) { // if left child
                            // shift key, value, and child right
                            parent->keys[1] = parent->keys[0];
                            parent->values[1] = parent->values[0];
                            parent->children[2] = parent->children[1];
                            parent->keys[0] = keys[1];
                            parent->values[0] = values[1];
                            parent->nodeSize++;
                            newChild->parent = parent;
                            newChild->keys[0] = keys[2];
                            newChild->values[0] = values[2];
                            newChild->subtreeSize++;
                            newChild->children[0] = children[2];
                            newChild->children[1] = children[3];
                            if(newChild->children[0] != NULL) {
                                newChild->children[0]->parent = newChild;
                                newChild->children[1]->parent = newChild;
                                newChild->subtreeSize += newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                                subtreeSize -= newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                            }
                            subtreeSize -= 2;
                            parent->children[1] = newChild;
                            children[2] = NULL;
                            children[3] = NULL;
                            nodeSize = 2;
                        }
                    }
                    else if(parent->nodeSize == 3) { // if three node
                        if(parent->children[2] == this) { // if right child
                            // shift key, value and child left
                            parent->keys[2] = keys[1];
                            parent->values[2] = values[1];
                            parent->nodeSize++;
                            newChild->parent = parent;
                            newChild->keys[0] = keys[2];
                            newChild->values[0] = values[2];
                            newChild->subtreeSize++;
                            newChild->children[0] = children[2];
                            newChild->children[1] = children[3];
                            if(newChild->children[0] != NULL) {
                                newChild->children[0]->parent = newChild;
                                newChild->children[1]->parent = newChild;
                                newChild->subtreeSize += newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                                subtreeSize -= newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                            }
                            subtreeSize -= 2;
                            parent->children[3] = newChild;
                            children[2] = NULL;
                            children[3] = NULL;
                            nodeSize = 2;
                        }
                        else if (parent->children[0] == this) { // if left child
                            // shift key, value, and child right
                            parent->keys[2] = parent->keys[1];
                            parent->values[2] = parent->values[1];
                            parent->children[3] = parent->children[2];
                            parent->keys[1] = parent->keys[0];
                            parent->values[1] = parent->values[0];
                            parent->children[2] = parent->children[1];
                            parent->keys[0] = keys[1];
                            parent->values[0] = values[1];
                            parent->nodeSize++;
                            newChild->parent = parent;
                            newChild->keys[0] = keys[2];
                            newChild->values[0] = values[2];
                            newChild->subtreeSize++;
                            newChild->children[0] = children[2];
                            newChild->children[1] = children[3];
                            if(newChild->children[0] != NULL) {
                                newChild->children[0]->parent = newChild;
                                newChild->children[1]->parent = newChild;
                                newChild->subtreeSize += newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                                subtreeSize -= newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                            }
                            subtreeSize -= 2;
                            parent->children[1] = newChild;
                            children[2] = NULL;
                            children[3] = NULL;
                            nodeSize = 2;
                        }
                        else if (parent->children[1] == this) { // if middle child
                            // shift key, value, and child right
                            parent->keys[2] = parent->keys[1];
                            parent->values[2] = parent->values[1];
                            parent->children[3] = parent->children[2];
                            parent->keys[1] = keys[1];
                            parent->values[1] = values[1];
                            parent->nodeSize++;
                            newChild->parent = parent;
                            newChild->keys[0] = keys[2];
                            newChild->values[0] = values[2];
                            newChild->subtreeSize++;
                            newChild->children[0] = children[2];
                            newChild->children[1] = children[3];
                            if(newChild->children[0] != NULL) {
                                newChild->children[0]->parent = newChild;
                                newChild->children[1]->parent = newChild;
                                newChild->subtreeSize += newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                                subtreeSize -= newChild->children[0]->subtreeSize + newChild->children[1]->subtreeSize;
                            }
                            subtreeSize -= 2;
                            parent->children[2] = newChild;
                            children[2] = NULL;
                            children[3] = NULL;
                            nodeSize = 2;
                        }
                    }
                }
            }

            // PREEMPTIVE MERGE ON ROOT
            void mergeRoot() {
                // set pointers for nodes to be deleted
                Two4Node *oldLeftChild = children[0];
                Two4Node *oldRightChild = children[1];
                
                // add keys and values to root
                keys[1] = keys[0];
                values[1] = values[0];
                keys[0] = children[0]->keys[0];
                values[0] = children[0]->values[0];
                keys[2] = children[1]->keys[0];
                values[2] = children[1]->values[0];
                nodeSize = 4;

                // move children
                children[0] = oldLeftChild->children[0];
                children[1] = oldLeftChild->children[1];
                children[2] = oldRightChild->children[0];
                children[3] = oldRightChild->children[1];

                // update parent pointers
                for(int i = 0; i < 4; i++) {
                    if(children[i] != NULL) {
                        children[i]->parent = this;
                    }
                }

                // delete old nodes
                delete oldLeftChild;
                delete oldRightChild;
            }
            
            // PREEMPTIVE MERGE ON NON-ROOT
            void mergeNode() {
                // identify which child node is
                int thisChildIndex = 0;
                while(this != parent->children[thisChildIndex]) {
                    thisChildIndex++;
                }
                // when adjacent sibling is 3 or 4 node, rotate
                if(thisChildIndex < parent->nodeSize-1 && parent->children[thisChildIndex+1]->nodeSize > 2) {
                    keys[1] = parent->keys[thisChildIndex];
                    values[1] = parent->values[thisChildIndex];
                    subtreeSize++;
                    children[2] = parent->children[thisChildIndex+1]->children[0];
                    if(children[2] != NULL) {
                        children[2]->parent = this;
                        subtreeSize += children[2]->subtreeSize;
                        parent->children[thisChildIndex+1]->subtreeSize -= children[2]->subtreeSize;
                    }

                    parent->keys[thisChildIndex] = parent->children[thisChildIndex+1]->keys[0];
                    parent->values[thisChildIndex] = parent->children[thisChildIndex+1]->values[0];

                    // fix donor node
                    for(int i = 0; i < parent->children[thisChildIndex+1]->nodeSize-1; i++) {
                        parent->children[thisChildIndex+1]->keys[i] = parent->children[thisChildIndex+1]->keys[i+1];
                        parent->children[thisChildIndex+1]->values[i] = parent->children[thisChildIndex+1]->values[i+1];
                        parent->children[thisChildIndex+1]->children[i] = parent->children[thisChildIndex+1]->children[i+1];
                    }
                    parent->children[thisChildIndex+1]->subtreeSize--;

                    parent->children[thisChildIndex+1]->nodeSize--;
                    nodeSize++;
                }
                else if(thisChildIndex > 0 && parent->children[thisChildIndex-1]->nodeSize > 2) {
                    // shift this child's keys, values, and children, increase nodeSize
                    keys[1] = keys[0];
                    values[1] = values[0];
                    subtreeSize++;
                    children[2] = children[1];
                    children[1] = children[0];
                    
                    // rotate
                    keys[0] = parent->keys[thisChildIndex-1];
                    values[0] = parent->values[thisChildIndex-1];
                    children[0] = parent->children[thisChildIndex-1]->children[parent->children[thisChildIndex-1]->nodeSize-1];
                    if(children[0] != NULL) {
                        children[0]->parent = this;
                        subtreeSize += children[0]->subtreeSize;
                        parent->children[thisChildIndex-1]->subtreeSize -= children[0]->subtreeSize;
                    }

                    parent->keys[thisChildIndex-1] = parent->children[thisChildIndex-1]->keys[parent->children[thisChildIndex-1]->nodeSize-2];
                    parent->values[thisChildIndex-1] = parent->children[thisChildIndex-1]->values[parent->children[thisChildIndex-1]->nodeSize-2];
                    parent->children[thisChildIndex-1]->children[parent->children[thisChildIndex-1]->nodeSize-1] = NULL;
                    parent->children[thisChildIndex-1]->subtreeSize--;

                    parent->children[thisChildIndex-1]->nodeSize--;
                    nodeSize++;
                }
                // when adjacent siblings are 2 nodes, pull parent key down
                else {
                    if(thisChildIndex < parent->nodeSize-1) {
                        keys[1] = parent->keys[thisChildIndex];
                        values[1] = parent->values[thisChildIndex];
                        subtreeSize++;
                        keys[2] = parent->children[thisChildIndex+1]->keys[0];
                        values[2] = parent->children[thisChildIndex+1]->values[0];
                        subtreeSize += parent->children[thisChildIndex+1]->subtreeSize;
                        children[2] = parent->children[thisChildIndex+1]->children[0];
                        children[3] = parent->children[thisChildIndex+1]->children[1];
                        if(children[2] != NULL) {
                            children[2]->parent = this;
                            children[3]->parent = this;
                        }
                        parent->children[thisChildIndex+1]->children[0] = NULL;
                        parent->children[thisChildIndex+1]->children[1] = NULL;

                        // delete old node
                        delete parent->children[thisChildIndex+1];

                        // fix parent
                        for(int i = thisChildIndex; i < parent->nodeSize-2; i++) {
                            parent->keys[i] = parent->keys[i+1];
                            parent->values[i] = parent->values[i+1];
                            parent->children[i+1] = parent->children[i+2];
                        }
                        parent->children[parent->nodeSize-1] = NULL;

                        // adjust sizes
                        parent->nodeSize--;
                        nodeSize += 2;
                    }
                    else {
                        // shift key and children in thisChild
                        keys[2] = keys[0];
                        values[2] = values[0];
                        subtreeSize++;
                        children[2] = children[0];
                        children[3] = children[1];
                        
                        // pull keys and values from sibling and parent and children from sibling
                        keys[1] = parent->keys[thisChildIndex-1];
                        values[1] = parent->values[thisChildIndex-1];
                        keys[0] = parent->children[thisChildIndex-1]->keys[0];
                        values[0] = parent->children[thisChildIndex-1]->values[0];
                        subtreeSize += parent->children[thisChildIndex-1]->subtreeSize;
                        children[0] = parent->children[thisChildIndex-1]->children[0];
                        children[1] = parent->children[thisChildIndex-1]->children[1];
                        if(children[0] != NULL) {
                            children[0]->parent = this;
                            children[1]->parent = this;
                        }
                        parent->children[thisChildIndex-1]->children[0] = NULL;
                        parent->children[thisChildIndex-1]->children[1] = NULL;

                        // delete old node
                        delete parent->children[thisChildIndex-1];

                        // fix parent
                        parent->children[thisChildIndex-1] = this;
                        parent->children[thisChildIndex] = NULL;

                        // adjust sizes
                        parent->nodeSize--;
                        nodeSize += 2;
                    }
                }
            }
            
            // TEST PRINT FUNCTION
            void printNode() {
                if(parent != NULL) {
                    cout << "Parent has key(s) ";
                    for(int i = 0; i < parent->nodeSize-1; i++) {
                        cout << parent->keys[i] << " ";
                    }
                    cout << endl;
                }
                cout << "Keys: ";
                for(int i = 0; i < nodeSize-1; i++) {
                    cout << keys[i] << " ";
                }
                cout << endl << "Values: ";
                for(int i = 0; i < nodeSize-1; i++) {
                    cout << values[i] << " ";
                }
                cout << endl << "Children: ";
                for(int i = 0; i < nodeSize; i++) {
                    if(children[i] != NULL) {
                        cout << "Child " << i << " has key(s) ";
                        for(int j = 0; j < children[i]->nodeSize-1; j++) {
                            cout << children[i]->keys[j] << " ";
                        }
                        cout << " | ";
                    }
                }
                cout << "Node Size: " << nodeSize << endl;
                cout << "Subtree Size: " << subtreeSize << endl;
            }
        };

        // TRAVERSAL RECURSION FUNCTIONS
        void preorderRecursive(Two4Node* n) {
            if(n != NULL) { // if node is not null, print keys, then recurse to children
                for(int i = 0; i < n->nodeSize-1; i++) {
                    cout << n->keys[i] << " ";
                }
                for(int i = 0; i < n->nodeSize; i++) {
                    preorderRecursive(n->children[i]);
                }
            }
        }

         void inorderRecursive(Two4Node* n) {
            if(n != NULL) { // if node is not null, recurse to child then print key, repeat for each key
                int i;
                for(i = 0; i < n->nodeSize-1; i++) {
                    inorderRecursive(n->children[i]);
                    cout << n->keys[i] << " ";
                }
                inorderRecursive(n->children[i]); // last child
            }
        }

        void postorderRecursive(Two4Node* n) {
            if(n != NULL) { // if node is not null, recurse to children first, then print keys
                for(int i = 0; i < n->nodeSize; i++) {
                    postorderRecursive(n->children[i]);
                }
                for(int i = 0; i < n->nodeSize-1; i++) {
                    cout << n->keys[i] << " ";
                }
            }
        }

        void deleteTreeRecursive(Two4Node* n) {
            if(n != NULL) { // if non node null, recurse to all children, then delete child pointer
                for(int i = 0; i < n->nodeSize; i++) {
                    deleteTreeRecursive(n->children[i]);
                    delete n->children[i];
                }
            }
        }

        Two4Node* copyTreeRecursive(Two4Node *src) {
            if(src == NULL) { // base case
                return NULL;
            }
            Two4Node* newNode = new Two4Node();
            for(int i = 0; i < 4; i++) {
                if(i < 3) { // copy keys and values
                    newNode->keys[i] = src->keys[i];
                    newNode->values[i] = src->values[i];
                }
                newNode->children[i] = copyTreeRecursive(src->children[i]); // recurse to children
                newNode->nodeSize = src->nodeSize;
                newNode->subtreeSize = src->subtreeSize;
                if(src->children[i] != NULL) {
                    newNode->children[i]->parent = newNode; // update parent pointer of children if not null
                }
            }
            return newNode;
        }

        // TREE INSTANCE VARIABLES
        Two4Node* head;

    public:
        // CONSTRUCTORS
        Two4Tree() {
            head = NULL;
        }

        Two4Tree(keytype k[], valuetype V[], int s) {
            head = NULL;
            for(int i = 0; i < s; i++) {
                insert(k[i], V[i]);
            }
        }

        // DESTRUCTOR
        ~Two4Tree() {
            deleteTreeRecursive(head);
            delete head;
        }

        // COPY CONSTRUCTOR AND COPY ASSIGNMENT CONSTRUCTOR
        Two4Tree(const Two4Tree &src) {
            head = copyTreeRecursive(src.head);
        }
        Two4Tree& operator=(const Two4Tree& src) {
            if(this != &src) {
                deleteTreeRecursive(head);
                delete head;
                head = copyTreeRecursive(src.head);
            }
            return *this;
        }

        // SEARCH
        valuetype * search(keytype k) {
            Two4Node* traverseNode = head;
            while(traverseNode != NULL) {
                int childToTraverse = 0;
                for(int i = 0; i < traverseNode->nodeSize-1; i++) {
                    if(traverseNode->keys[i] == k) { // if equal, return value
                        return &traverseNode->values[i];
                    }
                    if(k >= traverseNode->keys[i]) { // else next child should be checked
                        childToTraverse++;
                    }
                }
                traverseNode = traverseNode->children[childToTraverse]; // go to child found in above loop
            }
            return NULL;
        }

        // INSERT
        void insert(keytype k, valuetype v) {
            if(head == NULL) {
                Two4Node* newNode = new Two4Node();
                newNode->keys[0] = k;
                newNode->values[0] = v;
                newNode->subtreeSize++;
                head = newNode;
            }
            else {
                Two4Node* traverseNode = head;
                if(traverseNode->nodeSize == 4) {
                    traverseNode->splitNode();
                }
                traverseNode->subtreeSize++;
                while(traverseNode->children[0] != NULL) { // while not a leaf node
                    switch (traverseNode->nodeSize) {
                    case 2: // if two node, find child to traverse
                        if(k < traverseNode->keys[0]) {
                            traverseNode = traverseNode->children[0];
                        }
                        else {
                            traverseNode = traverseNode->children[1];
                        }
                        break;
                    case 3: // if three node, find child to traverse
                        if(k < traverseNode->keys[0]) {
                            traverseNode = traverseNode->children[0];
                        }
                        else if(k < traverseNode->keys[1] && k >= traverseNode->keys[0]) {
                            traverseNode = traverseNode->children[1];
                        }
                        else {
                            traverseNode = traverseNode->children[2];
                        }
                        break;
                    case 4: // if four node, find child to traverse
                        if(k < traverseNode->keys[0]) {
                            traverseNode = traverseNode->children[0];
                        }
                        else if(k < traverseNode->keys[1] && k >= traverseNode->keys[0]) {
                            traverseNode = traverseNode->children[1];
                        }
                        else if(k < traverseNode->keys[2] && k >= traverseNode->keys[1]) {
                            traverseNode = traverseNode->children[2];
                        }
                        else {
                            traverseNode = traverseNode->children[3];
                        }
                        break;
                    default:
                        cout << "Child node selection error" << endl;
                        break;
                    }
                    if(traverseNode->nodeSize == 4) { // call preemptive split if necessary
                        traverseNode->splitNode();
                        traverseNode = traverseNode->parent; // go back up to parent and check new children
                    }
                    else {
                        traverseNode->subtreeSize++; // increase subtree size on way down
                    }
                }
                traverseNode->addKey(k, v); // add key when node is found
            }
        }

        // REMOVE
        int remove(keytype k) {
            // ensure k is in the tree
            if(search(k) == NULL) {
                return 0;
            }
            // if k is only key in tree (root node)
            if(head->subtreeSize == 1) {
                delete head;
                head = NULL;
                return 1;
            }
            else {
                Two4Node* traverseNode = head;
                Two4Node* nodeWithKey = NULL;
                Two4Node* nodeWithSuccessor = NULL;
                // case for ROOT 2 NODE with 2 node children
                if(traverseNode->nodeSize == 2 && traverseNode->children[0]->nodeSize == 2 && traverseNode->children[1]->nodeSize == 2) {
                    traverseNode->mergeRoot();
                }
                // traverse down tree in search of k in while loop, mark k with pointer, but keep traversing for successor
                while(traverseNode != NULL) {
                    int childToTraverse = 0;
                    if(nodeWithKey == NULL) { // if node with key has not been found, keep searching for it
                        for(int i = 0; i < traverseNode->nodeSize-1; i++) {
                            if(traverseNode->keys[i] == k) {
                                nodeWithKey = traverseNode;
                            }
                            if(k >= traverseNode->keys[i]) {
                                childToTraverse++;
                            }
                        }
                        traverseNode->subtreeSize--;
                        traverseNode = traverseNode->children[childToTraverse];
                        if(traverseNode != NULL && traverseNode->nodeSize == 2) {
                            traverseNode->mergeNode();
                            if(nodeWithKey != NULL) {
                                for(int i = 0; i < traverseNode->nodeSize-1; i++) {
                                    if(traverseNode->keys[i] == k) {
                                        traverseNode = traverseNode->parent;
                                        traverseNode->subtreeSize++;
                                        nodeWithKey = NULL;
                                    }
                                }
                            }
                        }
                    }
                    else { // if node with key has been found, search for successor
                        // if(traverseNode->keys[traverseNode->nodeSize-2] >= k) {
                            nodeWithSuccessor = traverseNode;
                            traverseNode->subtreeSize--;
                            traverseNode = traverseNode->children[childToTraverse];
                            if(traverseNode != NULL && traverseNode->nodeSize == 2) {
                                traverseNode->mergeNode();
                                if(nodeWithKey != NULL) {
                                    for(int i = 0; i < traverseNode->nodeSize-1; i++) {
                                        if(traverseNode->keys[i] == k) {
                                            // nodeWithKey = traverseNode;
                                            traverseNode = traverseNode->parent;
                                            traverseNode->subtreeSize++;
                                            nodeWithKey = NULL;
                                        }
                                    }
                                }
                            }
                        // }
                        // else {
                        //     for(int i = 0; i < traverseNode->parent->nodeSize-2; i++) {
                        //         if(traverseNode == traverseNode->parent->children[i]) {
                        //             if(traverseNode->parent->children[i+1]->nodeSize == 2) {
                        //                 traverseNode = traverseNode->parent;
                        //                 traverseNode->subtreeSize++;
                        //                 nodeWithKey = NULL;
                        //             }
                        //             else {
                        //                 nodeWithSuccessor = traverseNode->parent->children[i+1];
                        //                 traverseNode->subtreeSize--;
                        //                 traverseNode = traverseNode->children[childToTraverse];
                        //                 if(traverseNode != NULL && traverseNode->nodeSize == 2) {
                        //                     traverseNode->mergeNode();
                        //                     if(nodeWithKey != NULL) {
                        //                         for(int i = 0; i < traverseNode->nodeSize-1; i++) {
                        //                             if(traverseNode->keys[i] == k) {
                        //                                 nodeWithKey = traverseNode;
                        //                             }
                        //                         }
                        //                     }
                        //                 }
                        //             }
                        //         }
                        //     }
                        // }
                    }
                }

                // find index of key
                int indexOfKey = 0;
                while(k != nodeWithKey->keys[indexOfKey]) {
                    indexOfKey++;
                }
                // node with key is not a leaf
                if(nodeWithSuccessor != NULL) {
                    // copy successor key and value
                    nodeWithKey->keys[indexOfKey] = nodeWithSuccessor->keys[0];
                    nodeWithKey->values[indexOfKey] = nodeWithSuccessor->values[0];

                    // fix successor node
                    // shift keys down
                    for(int i = 0; i < nodeWithSuccessor->nodeSize-2; i++ ) {
                        nodeWithSuccessor->keys[i] = nodeWithSuccessor->keys[i+1];
                        nodeWithSuccessor->values[i] = nodeWithSuccessor->values[i+1];
                    }
                    nodeWithSuccessor->nodeSize--; // decrease successor node size
                }
                // node with key is a leaf
                else {
                    // shift keys down
                    for(int i = indexOfKey; i < nodeWithKey->nodeSize-2; i++ ) {
                        nodeWithKey->keys[i] = nodeWithKey->keys[i+1];
                        nodeWithKey->values[i] = nodeWithKey->values[i+1];
                    }
                    nodeWithKey->nodeSize--; // decrease key node size
                }
                return 1;
            }
        }

        // RANK
        int rank(keytype k) {
            if(search(k) == NULL) { // key does not exist, no rank
                return 0;
            }
            else {
                Two4Node* traverseNode = head;
                int rank = 0;
                while(traverseNode != NULL) {
                    int childToTraverse = 0;
                    for(int i = 0; i < traverseNode->nodeSize-1; i++) {
                        if(k >= traverseNode->keys[i]) { // if key is greater than current key, look at next child and add to rank
                            if(traverseNode->children[i] != NULL) {
                                rank += traverseNode->children[i]->subtreeSize; // add subtree size to rank of node
                            }
                            childToTraverse++;
                        }
                        if(traverseNode->keys[i] == k) { // if key found
                            return rank + i + 1;
                        }
                    }
                    rank += childToTraverse; // factor in keys of node that are less
                    traverseNode = traverseNode->children[childToTraverse]; // go to child to traverse 
                }
                return 0;
            }
        }

        // SELECT
        keytype select(int pos) {
            Two4Node* traverseNode = head;
            int rankOfPredecessors = 0;
            while(traverseNode != NULL) {
                int childToTraverse = 0;
                for(int i = 0; i < traverseNode->nodeSize; i++) { // search children
                    if(traverseNode->children[i] != NULL) { // while not leaf node
                        if(rankOfPredecessors + traverseNode->children[i]->subtreeSize + 1 == pos) { // if elements to left and predecessors are equal to current position, key found
                            return traverseNode->keys[i];
                        }
                        else if (rankOfPredecessors + traverseNode->children[i]->subtreeSize + 1 <= pos) { // if elements to left and predecessors are less than current position, keep searching next child
                            rankOfPredecessors += traverseNode->children[i]->subtreeSize + 1; // add to rank of predecessors based on subtree and key
                            childToTraverse++;
                        }
                        else {
                            i = 5; // break loop
                        }
                    }
                    else { // if leaf node and position matches, return key
                        if(rankOfPredecessors + i + 1 == pos) {
                            return traverseNode->keys[i];
                        }
                    }
                }
                traverseNode = traverseNode->children[childToTraverse]; // iterate to next node
            }
            return 0;
        }

        // SUCCESSOR / PREDECESSOR
        keytype successor(keytype k) {
            return select(rank(k)+1);
        }
        keytype predecessor(keytype k) {
            return select(rank(k)-1);
        }

        // SIZE
        int size() {
            return head->subtreeSize;
        }

        // TRAVERSALS
        void preorder() {
            preorderRecursive(head);
            cout << endl;
        }
        void inorder() {
            inorderRecursive(head);
            cout << endl;
        }
        void postorder() {
            postorderRecursive(head);
            cout << endl;
        }

        // TESTER FUNCTIONS
        // void printTree() {
        //     printTreeRecursive(head);
        // }

        // static void printTreeRecursive(Two4Node* n) {
        //     if(n != NULL) {
        //         n->printNode();
        //         for(int i = 0; i < n->nodeSize; i++) {
        //             printTreeRecursive(n->children[i]);
        //         }
        //     }
        // }
};