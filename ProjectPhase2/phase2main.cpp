#include <iostream>
using namespace std;
#include "Two4Tree.cpp"

int main(){
	// Two4Tree<int,int> T1;
	// for(int i = 18; i >= 1; i--) {
	// 	T1.insert(i,i);
	// }
	// T1.printTree();
	// for(int i = 1; i <= 18; i++) {
	// 	cout << T1.select(i) << endl;
	// }
	// T1.remove(4);
	// T1.remove(6);
	// T1.printTree();
	// cout << T1.size() << endl;
	
	// for(int i = 12; i < 18; i++) {
	// 	T1.insert(i,i);
	// }
	// for(int i = 6; i < 12; i++) {
	// 	T1.insert(i,i);
	// }
	// Two4Tree<int,int> T2;
	// T2 = T1;
	// T1.remove(11);
	// T1.printTree();

	
	string K[10] = {"A","B","C","D","E","F","G","H","I","K"};
	int V[10] = {10,9,8,7,6,5,4,3,2,1};
	
	Two4Tree<string,int> T1, T2(K,V,10);
	
	for(int i=0; i<10; i++) T1.insert(K[i],V[i]);
	// T1 and T2 should be identical trees
	
	cout << *(T2.search("C")) << endl;
	// Should output 8
	
	cout << T1.rank("C") << endl;
	//Should output 3
	
	cout << T1.select(3) << endl;
	//Should output C 
	
	T2.preorder();
	//Should output D B A C F H E G I K
	
	T2.inorder();
	//Should output	A B C D E F G H I K

	cout << T2.remove("C") << endl;
	// Should output 1
	
	T2.preorder();
	// Should output F B A D E H G I K
	
	T2.inorder();
	// Should output A B D E F G H I K
	
	cout << T2.remove("J") << endl;
	// Should output 0

	cout <<T2.rank("G") << endl;
	//Should output 6
	
	cout <<T1.successor("C")<<endl;
	//Should output D
	
	cout <<T1.predecessor("C")<<endl;
	//Should output B		

	// T1.printTree();

    Two4Tree<int,int> X;
	for (int i=1;i<100000;i++) X.insert(i,i);
	cout << X.size() << endl;
	for (int i=1;i<100000;i++) {
		if(X.rank(i) != i) cout << "Rank error" << endl;
		if(X.select(i) != i) cout << "Select error" << endl;
		if(*(X.search(i)) != i) cout << "Search error" << endl;
	}
	// Should be no output and should take seconds, not minutes
	return 0;
}
