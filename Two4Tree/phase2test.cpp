#include <iostream>
#include <string>
using namespace std;
#include "Two4Tree.cpp"

void SieveOfEratosthenes(int n);

int main() {
    for(int i = 400; i <= 400; i++) {
        cout << i << endl;
        SieveOfEratosthenes(i);
    }
	return 0;
}

void SieveOfEratosthenes(int n) {
    Two4Tree<int, int> sieve;
    for (int i = n; i >= 2; i--) sieve.insert(i, i);
    // sieve.printTree();
    // cout << sieve.size() << endl;

    for (int r = 1; r <= sieve.size(); r++) {
        // sieve.inorder();
        // cout << r << endl << endl << endl << endl << endl;
        // sieve.printTree();
        int p = sieve.select(r);
        // cout << p << endl;
        for (int e = 2 * p; e <= n; e += p) {
            // cout << "removing " << e << endl;
            int res = sieve.remove(e);
            // if(r == 4 && res == 1) {
                
            //     sieve.inorder();
            //     sieve.printTree();
            //     cout << endl << endl;
            // }
        }
    }
    // sieve.printTree();
    sieve.inorder(); cout << endl;
    for(int i = 0; i < sieve.size()-1; i++) {
        cout << sieve.successor(i) << endl;
    }
}