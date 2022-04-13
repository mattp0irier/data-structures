#include <iostream>
using namespace std;
#include "CDA.cpp"

void foo(CDA<int> x) {
	for (int i=0; i<x.Length()/2; i++)
		x[i] = x[x.Length()/2+i];
	cout << "SetOrdered in foo is " << x.SetOrdered() << endl;
	// x => "5 6 7 8 9 5 6 7 8 9" Ordered => 0	
}

int main(){
	CDA<float> C(10);
	for (int i=0; i< C.Length();i++) C[i] = i;
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.DelFront();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.DelEnd();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.AddEnd(100.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"
	C.AddEnd(101.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100 101"
	C.DelEnd(); C.DelEnd();
	C.AddFront(-100.0); C.AddFront(-200.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "-200 -100 1 2 3 4 5 6 7 8"

	CDA<int> A;
	for(int i=0; i<10;i++) A.AddEnd(i);
	cout << "SetOrdered is " << A.SetOrdered() << endl;
	// A => "0 1 2 3 4 5 6 7 8 9" SetOrdered => 1
	cout << "Select is " << A.Select(3) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9" Select => 2
	cout << "Search is " << A.Search(5) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9" Search => 5
	A.AddFront(10); 
	// A => "10 0 1 2 3 4 5 6 7 8 9"
	cout << "Ordered is " << A.Ordered() << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9" Ordered => 0
	cout << "Select is " << A.Select(3) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9" Select => 2
	cout << "Search is " << A.Search(5) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9" Search => 6
	A.InsertionSort();
	// A => "10 9 8 7 6 5 4 3 2 1 0"
	cout << "Ordered is " << A.Ordered() << endl;
	// A => "10 9 8 7 6 5 4 3 2 1 0" Ordered => -1
	A.AddEnd(11);
	// A => "10 9 8 7 6 5 4 3 2 1 0 11"
	cout << "Ordered is " << A.Ordered() << endl;
	// A => "10 9 8 7 6 5 4 3 2 1 0 11" Ordered => 0
	A.MergeSort();
	// A => "11 10 9 8 7 6 5 4 3 2 1 0"
	cout << "Ordered is " << A.Ordered() << endl;
	// A => "11 10 9 8 7 6 5 4 3 2 1 0" Ordered => -1
	A.DelFront(); A.DelFront(); A.AddEnd(5);
	// A => "9 8 7 6 5 4 3 2 1 0 5"
	A.CountingSort(9);
	// A => "9 8 7 6 5 5 4 3 2 1 0"
	for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;

	foo(A);
	cout << "SetOrdered is " << A.SetOrdered() << endl;
	// A => "9 8 7 6 5 5 4 3 2 1 0" Ordered => -1
}