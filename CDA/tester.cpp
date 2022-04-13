#include <iostream>
#include <unordered_map>
#include <vector>

#include "CDA.cpp"

using namespace std;

bool nameExists(vector<string> list, string name) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == name) { return true; }
	}
	return false;
}

int main(void) {
	vector<string> listNames;
	unordered_map<string, CDA<int>* > lists;

	do {
		cout << endl;
		cout << "Main menu:" << endl;
		cout << " [L]ist current lists" << endl;
		cout << " [C]reate a new list" << endl;
		cout << " [D]elete a list" << endl;
		cout << " [A]ct on a list" << endl;
		cout << " [Q]uit" << endl;
		cout << "> ";

		char choice;
		cin >> choice;

		switch (toupper(choice)) {
			case 'L':
				cout << "Current lists:" << endl;
				if (listNames.size()) {
					for (int i = 0; i < listNames.size(); i++) {
						cout << " - " << listNames[i]
							<< "(" << lists[listNames[i]]->Length() << ")" << endl;
					}
				} else {
					cout << " no lists stored" << endl;
				}
				break;
			case 'C': {
				cout << "What would you like to name this list?  (Single strings with no spaces please)" << endl;
				cout << "> ";
				string name;
				cin >> name;

				if (nameExists(listNames, name)) {
					cout << "This name already exists." << endl;
					cout << "Returning to main menu." << endl;
				}

				cout << "How would you like to create the list?" << endl;
				cout << " 1. CDA() Default constructor" << endl;
				cout << " 2. CDA(int s) Specified size/capacity" << endl;
				cout << " 3. CDA(CDA src) Copy constructor" << endl;
				cout << " 4. operator=(CDA src) Copy assignment operator" << endl;
				cout << "> ";

				int choice;
				cin >> choice;

				switch (choice) {
					case 1:
						listNames.push_back(name);
						lists[name] = new CDA<int>();
						break;
					case 2: {
						cout << "How large would you like the size/capacity to be?" << endl;
						cout << "> ";

						int size;
						cin >> size;

						listNames.push_back(name);
						lists[name] = new CDA<int>(size);
						break;
					} case 3: {
						cout << "What list would you like to copy from?" << endl;
						cout << "> ";

						string src;
						cin >> src;

						if (!nameExists(listNames, src)) {
							cout << "This list does not exist." << endl;
							cout << "Returning to main menu." << endl;
							break;
						}

						listNames.push_back(name);
						lists[name] = new CDA<int>(*(lists[src]));
						break;
					} case 4: {
						cout << "What list would you like to copy from?" << endl;
						cout << "> ";

						string src;
						cin >> src;

						if (!nameExists(listNames, src)) {
							cout << "This list does not exist." << endl;
							cout << "Returning to main menu." << endl;
							break;
						}

						CDA<int> *newList = new CDA<int>;
						(*newList) = *(lists[src]);

						listNames.push_back(name);
						lists[name] = newList;
						break;
					} default:
						cout << "Invalid choice.  Returning to main menu." << endl;
						break;
				}

				if (nameExists(listNames, name)) {
					cout << "List `" << name << "` was created." << endl;
				}

				break;
			} case 'D': {
				cout << "What list would you like to delete?" << endl;
				cout << "> ";

				string name;
				cin >> name;

				if (!nameExists(listNames, name)) {
					cout << "This list does not exist." << endl;
					break;
				}

				for (int i = 0; i < listNames.size(); i++) {
					if (listNames[i] == name) {
						listNames.erase(listNames.begin()+i);
						break;
					}
				}

				delete lists[name];

				cout << "Deleted list `" << name << "`" << endl;

				break;
			} case 'A': {
				cout << "What list would you like to perform actions on?" << endl;
				cout << "> ";

				string name;
				cin >> name;

				if (!nameExists(listNames, name)) {
					cout << "This list does not exist." << endl;
					break;
				}

				CDA<int> *list = lists[name];

				bool remain = true;

				do {
					cout << "What action would you like to perform on `" << name << "`?" << endl;
					cout << " [P]rint info (Length, EmptySlots, Ordering, and [] operator for contents)" << endl;
					cout << " [F]ill the array" << endl;
					cout << " [D]elete element(s)" << endl;
					cout << " Set [O]rdered" << endl;
					cout << " Find s[M]allest (Select)" << endl;
					cout << " [S]earch" << endl;
					cout << " So[R]ting" << endl;
					cout << " [Q]uit to main menu" << endl;
					cout << "[" << name << "] > ";

					char choice;
					cin >> choice;

					switch (toupper(choice)) {
						case 'P':
							cout << "Length: " << list->Length() << endl;
							cout << "EmptySlots: " << list->EmptySlots() << endl;
							cout << "Capacity (Length + EmptySlots): "
								<< (list->Length()+list->EmptySlots()) << endl;
							cout << "Ordering: " << list->Ordered();
							switch (list->Ordered()) {
								case -1: cout << " (DECREASING)" << endl; break;
								case  0: cout << " (UNORDERED)" << endl; break;
								case  1: cout << " (INCREASING)" << endl; break;
								default: cout << " (INVALID VALUE)" << endl; break;
							}
							cout << "Contents: " << endl;
							cout << "  { ";
							for (int i = 0; i < list->Length(); i++) {
								if (i != 0) {	
									cout << ", ";
								}
								cout << (*list)[i];
							}
							cout << " }" << endl;

							break;
						case 'F': {
							cout << "What would you like to fill the list with?" << endl;
							cout << " [R]andom values" << endl;
							cout << " [I]ncreasing values" << endl;
							cout << " [D]ecreasing values" << endl;
							cout << " [C]onstant values" << endl;
							cout << "> ";

							char fillCommand;
							cin >> fillCommand;

							int min=0, max=0;
							bool choiceValid = true;

							switch (toupper(fillCommand)) {
								case 'R':
								case 'I':
								case 'D': {
									cout << "Please enter a minimum and maximum value for the range (inclusive):" << endl;
									cout << "> ";
									int a, b;
									cin >> a >> b;
									if (a < b) {
										min = a;
										max = b;
									} else {
										min = b;
										max = a;
									}
									break;
								} case 'C': {
									cout << "Please enter the value to insert:" << endl;
									cout << "> ";
									int a;
									cin >> a;
									min = max = a;
									break;
								} default:
									cout << "Invalid choice." << endl;
									choiceValid = false;
									break;
							}

							if (toupper(fillCommand) == 'D') {
								fillCommand = 'I';
								int tmp = min;
								min = max;
								max = tmp;
							}

							if (choiceValid) {
								cout << "Where would you like to add these items?" << endl;
								cout << " [F]ront" << endl;
								cout << " [E]nd" << endl;
								cout << "> ";

								char fillDest;
								cin >> fillDest;

								if (toupper(fillDest) != 'F' && toupper(fillDest) != 'E') {
									cout << "Invalid choice." << endl;
									break;
								}

								cout << "How many would you like to insert?" << endl;
								cout << "> ";

								int num;
								cin >> num;

								for (int i = 0; i < num; i++) {
									int valToInsert = min;
									if (toupper(fillCommand) == 'R') {
										valToInsert = rand() % (max - min + 1) + min;
									} else if (toupper(fillCommand) == 'I') {
										// increasing is decreasing in reverse
										valToInsert = min + ((i * (max - min))/(num-1));
									}

									if (toupper(fillDest) == 'F') {
										cout << i << ": Inserting " << valToInsert << endl;
										list->AddFront(valToInsert);
									} else {
										list->AddEnd(valToInsert);
									}
								}
							}
							break;
						} case 'D': {
							cout << "Choose an option:" << endl;
							cout << " [C]lear all elements from the array" << endl;
							cout << " Delete element(s) from the [E]nd" << endl;
							cout << " Delete element(s) from the [F]ront" << endl;
							cout << "> ";

							char deleteOption;
							cin >> deleteOption;

							switch (toupper(deleteOption)) {
								case 'C':
									list->Clear();
									break;
								case 'E':
								case 'F':
									cout << "How many element(s) do you want to remove?" << endl;
									cout << "> ";

									int num;
									cin >> num;

									for (int i = 0; i < num; i++) {
										if (toupper(deleteOption) == 'E') {
											list->DelEnd();
										} else {
											list->DelFront();
										}
									}

									break;
								default:
									cout << "Invalid choice." << endl;
							}
						} case 'O':
							cout << "SetOrdered returns: " << list->SetOrdered() << endl;
							break;
						case 'M': {
							cout << "Which k^th smallest element would you like to view?" << endl;
							cout << "> ";

							int k;
							cin >> k;

							cout << k;
							if (k == 1) cout << "st ";
							else if (k == 2) cout << "nd ";
							else cout << "th ";

							cout << "smallest element is " << list->Select(k) << endl;

							break;
						} case 'S': {
							cout << "What would you like to search for?" << endl;
							cout << "> ";

							int v;
							cin >> v;

							cout << v << " is located at " << list->Search(v) << endl;

							break;
						} case 'R': {
							cout << "What sort would you like to use?" << endl;
							cout << " [I]nsertion Sort" << endl;
							cout << " [M]erge Sort" << endl;
							cout << " [C]ounting Sort" << endl;
							cout << "> ";

							char sort;
							cin >> sort;

							switch (toupper(sort)) {
								case 'I':
									list->InsertionSort();
									break;
								case 'M':
									list->MergeSort();
									break;
								case 'C': {
									cout << "What is the largest value in the array (m)?" << endl;
									cout << "> ";

									int m;
									cin >> m;

									list->CountingSort(m);
									break;
								}
								default:
									cout << "Invalid choice" << endl;
							}

							break;
						} case 'Q':
							remain = false;
							break;
						default:
							cout << "Invalid choice." << endl;
					}

				} while (remain);
				break;
			} case 'Q':
				return 0;
			default:
				cout << "Invalid choice." << endl;
				break;
		}
	} while (true);
}
