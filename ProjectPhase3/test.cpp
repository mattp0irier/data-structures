#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "BHeap.cpp"

int main() {
    BHeap<int> h1;
    for(int i = 1; i <= 20; i++) h1.insert(i);
    h1.printKey();

    BHeap<int>h2 = h1;
    h1.extractMin();
    h1.extractMin();
    h1.extractMin();

    h1.printKey();
    h2.printKey();

    // BHeap<int> h3;

    // const int AMOUNT = 10000; //amount of random numbers that need to be generated
    // const int MAX = 10000; //maximum value (of course, this must be at least the same as AMOUNT;

    // int value[AMOUNT]; //array to store the random numbers in

    // srand(time(NULL)); //always seed your RNG before using it

    // //generate random numbers:
    // for (int i=0;i<AMOUNT;i++)
    // {
    //     bool check; //variable to check or number is already used
    //     int n; //variable to store the number in
    //     do
    //     {
    //     n=rand()%MAX;
    //     //check or number is already used:
    //     check=true;
    //     for (int j=0;j<i;j++)
    //         if (n == value[j]) //if number is already used
    //         {
    //             check=false; //set check to false
    //             break; //no need to check the other elements of value[]
    //         }
    //     } while (!check); //loop until new, unique number is found
    //     value[i]=n; //store the generated number in the array
    //     h3.insert(n);
    // }
    // h3.printKey();
    // for(int i = 0; i < AMOUNT; i++) {
    //     cout << h3.extractMin() << " ";
    // }
    // cout << endl;

    // Heap<int> h2 = h1;
    // h3.printKey();
}