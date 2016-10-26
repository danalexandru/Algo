// 07PlanificareDisc-FCFS-01.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

queue<int> disc;

void showCache(){
	queue<int> discCopy = disc;

	while (!discCopy.empty())
	{
		cout << discCopy.front() << " ";
		discCopy.pop();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N;

	cout << "Planificarea discului => FCFS (First Come, First Served)\n";

	cout << "Dati nr elemente coada: ";
	cin >> N;

	cout << "Dati elemente coada (eg: 1 2 4): ";
	int i;
	for (i = 0; i < N; i++){
		int temp;
		cin >> temp;
		disc.push(temp);
	}

	int start;
	cout << "Dati pozitia de start: ";
	cin >> start;



	cout << "\nMost old in queue (pop candidate) ... most recent" << endl;

	i = 0;
	//bool pageChange;
	while (i < N){
		int temp;
		temp = disc.front();
		disc.pop();

		cout << "pagina solicitata: " << temp << endl;
		cout << "\tanterioara: " << start << ", urmatoare: " << temp;
		start = temp;

		
		cout << "\tcoada: ";
		showCache();
		cout << "\n";

		i++;
	}


	return 0;
}

