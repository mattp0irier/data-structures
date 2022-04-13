#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "CDA.cpp"

void test0(ostream &fp);
void test1(ostream &fp);
void test2(ostream &fp);
void test3(ostream &fp);
void test4(ostream &fp);
void test5(ostream &fp);
void test6(ostream &fp);

void foo(CDA<int> x) {
	for (int i=0; i<x.Length()/2; i++){
		int temp = x[i];
		x[i] = x[x.Length()/2+i];
		x[x.Length()/2+i] = temp;
	}
	cout << "SetOrdered in foo is " << x.SetOrdered() << endl;
}

int printWrapper = 0;

int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 0:
			test0(cout);
			break;
		case 1:
			test1(cout);
			break;
		case 2:
			test2(cout);
			break;
		case 3:
			test3(cout);
			break;
		case 4:
			test4(cout);
			break;
		case 5:
			test5(cout);
			break;
		case 6:
			test6(cout);
			break;
	}
}

void test0(ostream &fp){
	if(printWrapper) fp << "Running test 0" << endl;
	CDA<int> C(25);
	for (int i=0; i< C.Length();i++) C[i] = i*11;
	for (int i=0; i< C.Length();i++) fp << C[i] << " "; fp << endl;
	fp << "SetOrdered is " << C.SetOrdered() << endl;
	C.DelFront();
	C.DelFront();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd();
	C.DelEnd();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddEnd(1001);
	C.AddEnd(1003);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddFront(1004);
	C.AddEnd(1006);
	fp << "SetOrdered is " << C.SetOrdered() << endl;
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.DelEnd(); C.DelEnd();
	C.AddFront(-105); 
	C.AddFront(-205);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	fp << "EmptySlots is " << C.EmptySlots() << endl;
	
	while(C.Length()){
		C.DelEnd();
	}
	fp << "EmptySlots is " << C.EmptySlots() << endl;
	C.Clear();
	fp << "EmptySlots is " << C.EmptySlots() << endl;
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test1(ostream &fp){
	if(printWrapper) fp << "Running test 1" << endl;
	CDA<int> A;
	int temp = 0;
	for(int i=0; i<19;i++){
		A.AddEnd(i*11);
		if(A.EmptySlots() != temp){
			temp = A.EmptySlots();
			fp << "EmptySlots is " << temp << " ";
		}
	}
    fp << endl;
	fp << "EmptySlots is " << A.EmptySlots() << endl;
	fp << "Search is " << A.Search(165) << endl;
	fp << "Select is " << A.Select(5) << endl;
	A.MergeSort();
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	A.AddFront(12); 
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Search is " << A.Search(165) << endl;
	fp << "Select is " << A.Select(5) << endl;
	A.InsertionSort();
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	A.AddEnd(-10);
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	A.MergeSort();
	fp << "Ordered is " << A.Ordered() << " after merge" << endl;
	A.DelFront(); A.DelEnd(); A.AddEnd(53);
	for (int i=0; i< A.Length();i++) fp << A[i] << " ";  fp << endl;
	A.CountingSort(220);
	if(A.Ordered()) fp << "Ordered after counting sort" << endl;
	CDA<int> B;
	A[0] = -1111;
	B = A;
	A[0] = -1001;
	A[1] = -1003;
	fp << B[0] << endl;
	foo(A);
	for (int i=0; i< B.Length();i++) fp << B[i] << " ";  
	fp << endl;
	CDA<long long int> testGeneric1(10);
	CDA<wchar_t> testGeneric2(10);
	CDA<long double> testGeneric3(10);
	fp << "Passed Generics Test" << endl;
	if(printWrapper)fp << "-----------------Finished Test----------------------" << endl;
}

void test2(ostream &fp){
	if(printWrapper) fp << "Running test 2" << endl;
	CDA<int> A;
	for(int i = 0; i < 101000; i++) A.AddFront(i);
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Select is " << A.Select(4000) << endl;
	A.MergeSort();
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Select is " << A.Select(400) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test3(ostream &fp){
	if(printWrapper) fp << "Running test 3" << endl;
	CDA<int> A;
	for(int i = 0; i < 10004; i++) A.AddFront(i);
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Select is " << A.Select(4000) << endl;
	A.InsertionSort();
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Select is " << A.Select(400) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test4(ostream &fp){
	if(printWrapper) fp << "Running test 4" << endl;
	CDA<int> A;
	for(int i = 0; i < 10004; i++) A.AddFront(i);
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Select is " << A.Select(4000) << endl;
	A.CountingSort(10004);
	fp << "Finished counting sort" << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


void test5(ostream &fp){
	if(printWrapper) fp << "Running test 5" << endl;
	CDA<int> A;
	for(int i = 0; i < 10004; i++) A.AddFront(i*3);
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	for(int i = 1; i <= 15; i++)
		fp << "Select is " << A.Select(1000+i*3) << " "; 
	fp << endl;
	A.MergeSort();
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	for(int i = 1; i <= 15; i++){		
		fp << "Search is " << A.Search(i*3) << " ";
	} 
	fp << endl;
	for(int i = 1; i <= 15; i++){		
		fp << "Select is " << A.Select(i*3) << " ";
	} 
	fp << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}

void test6(ostream &fp){
	if(printWrapper) fp << "Running test 6" << endl;
	CDA<int> A;
	for(int i = 0; i < 100004; i++) A.AddFront(i*2);
	A.MergeSort();
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Search is " << A.Search(40) << endl;
	fp << "Search is " << A.Search(400) << endl;
	fp << "Search is " << A.Search(4000) << endl;
	fp << "Search is " << A.Search(40001) << endl;
	fp << "Select is " << A.Select(4000) << endl;
	if(printWrapper) fp << "-----------------Finished Test----------------------" << endl;
}


