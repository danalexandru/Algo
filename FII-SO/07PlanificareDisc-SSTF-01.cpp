// 07PlanificareDisc-SSTF-01.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

list<int> disc;

void showCache(){
	list<int> discCopy = disc;
	//here iterator is allowed...
	while (!discCopy.empty())
	{
		cout << discCopy.front() << " ";
		discCopy.pop_back();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N;

	cout << "Planificarea discului => SSTF (Shortest Seek Time First)\n";

	cout << "Dati nr elemente coada: ";
	cin >> N;

	cout << "Dati elemente coada (eg: 1 2 4): ";
	int i;
	for (i = 0; i < N; i++){
		int temp;
		cin >> temp;
		disc.push_front(temp);
	}

	int start;
	cout << "Dati pozitia de start: ";
	cin >> start;

	disc.sort(); //sa caute cel mai mic la fiecare iteratie ii cam costisitor (chiar ar face asa in practica ?)

	cout << "\nMost old in queue (pop candidate) ... most recent" << endl;

	i = 0;
	//bool pageChange;
	while (i < N){
		int temp;
		temp = disc.back();
		disc.pop_back();

		cout << "zona solicitata: " << temp << endl;
		cout << "\tanterioara: " << start << ", urmatoare: " << temp;
		start = temp;


		cout << "\tcoada: ";
		showCache();
		cout << "\n";

		i++;
	}


	return 0;
}

