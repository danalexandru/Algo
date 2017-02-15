// 05Paginare-LRU-01.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
#define MAX_VECT 100
using namespace std;

list<int> page;

bool isInCache(int n, int &pos){ //#diferentaLRU
	list<int>::iterator it;

	it = find(page.begin(), page.end(), n);

	if (it != page.end()){
		//pos = distance(page.begin(), it);//nu pot folosi, deoarece iteratorul de lista nu poate fi incrementat dupa un index...
		/*
			it - page.begin() => nu compileaza

		*/
		return true;
	}
	return false;
}

void showCache(){
	list<int>::iterator itt = page.begin();

	while (itt != page.end())
	{
		cout << *itt << " ";
		itt++;
	}
}

int main(int argc, _TCHAR* argv[])
{
	int pgNum, N, cache[MAX_VECT];
	cout << "Paginare la cerere - algoritmul LRU (least recently used)\n";


	cout << "Dati nr de pagini din buffer: ";
	cin >> pgNum;

	cout << "Dati nr de pagini solicitate: ";
	cin >> N;

	cout << "Dati paginile solicitate (eg: 1 2 5): ";
	int i = 0;
	while (i < N){
		int temp;
		cin >> temp;
		cache[i] = temp;
		i++;
	}

	cout << "\nMost recent ... most old" << endl;

	i = 0;
	bool pageChange;
	int PFIcount = 0, pos; //fata de FIFO, pos e in plus => //#diferentaLRU
	while (i < N){
		cout << "pagina solicitata: " << cache[i] << endl;
		int temp;
		temp = cache[i];

		pos = -1;
		pageChange = true;

		if (!isInCache(temp, pos)) 
		{
			if (page.size() == pgNum)
				page.pop_back();
			page.push_front(cache[i]);
		}
		else{
			pageChange = false;

			list<int>::iterator it;
			//advance(it, pos);
			it = find(page.begin(), page.end(), temp);
			it = page.erase(it);

			page.push_front(temp);
		}

		if (pageChange){
			cout << "\tpage change -> yes" << endl;
			PFIcount++;
		}
		else
			cout << "\tpage change -> no" << endl;

		cout << "\t";
		showCache();
		cout << "\n";

		i++;
	}

	double A = PFIcount;

	cout << "\nRata erorilor de pagina = " << PFIcount << "/" << N << " = " << (A / N) * 100 << " % \n";//shorter with printf...


	return 0;
}

