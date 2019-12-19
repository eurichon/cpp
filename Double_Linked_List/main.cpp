#include <iostream>
#include "menu.h"
#include "List.h"
#include "time.h"
using namespace std;

int comp(double &first, double &second);

int main(int argc, char *argv[]) {
	list<double> mylist, mylist2;
	list<double>::Iterator it, it2;

	for (int i = 0;i < 10; i++) {
		mylist.push_back(10 - i);
	}

	mylist.push_back(100);
	mylist.push_back(500);
	mylist.push_front(-100);

	mylist.swap(mylist2);

	cout << "storting my list 2" << endl;
	mylist.sort(comp);

	for (it = mylist.begin(); it != mylist.end(); it++) {
		cout << (*it) << " ";
	}

	//mylist.push_back(11.0);
	it = mylist.begin();

	cout << "Size of my list: " << mylist.size() << endl;

	Direction dir = Before;

	mylist.insert(it, 12.0, dir);
	mylist.insert(it, 13.0, dir);

	dir = After;

	mylist.insert(it, 14.0, dir);
	mylist.insert(it, 15.0, dir);


	for (it = mylist.begin(); it != mylist.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;

	//mylist.clear();

	it = mylist.begin();
	it++;
	it++;
	mylist.erase(it);

	for (it = mylist.begin(); it != mylist.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;




	for (it = mylist2.begin(); it != mylist2.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	it2 = mylist2.begin();
	it2++;
	it2++;
	it = it2;
	it++;
	it++;
	mylist2.erase(it2, it);
	for (it = mylist2.begin(); it != mylist2.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;

	mylist.front() += 100;
	mylist.back() -= 100;





	mylist.pop_front();
	mylist.pop_back();


	cout << mylist.front() << endl;
	cout << mylist.back() << endl;

	system("pause");
	return 0;
}


int comp(double &first, double &second) {
	if (std::fabs(first - second) < 1e-6) {
		return 0;
	}
	else if (first > second) {
		return 1;
	}
	else {
		return -1;
	}
}

