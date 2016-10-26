// 05Paginare-FIFO-01.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <list>
//#include <vector>//nu are push_front
#define MAX_VECT 100
using namespace std;

list<int> page;

bool isInCache(int n){
	list<int>::iterator it;
	
	it = find(page.begin(), page.end(), n);
	
	if (it != page.end())
		return true;

	return false;
}

void showCache(){
	list<int>::iterator itt = page.begin();

	while(itt != page.end())
	{
		cout << *itt << " ";
		itt++;
	}
}

int main(int argc, _TCHAR* argv[])
{
	int pgNum, N, cache[MAX_VECT];
	cout << "Paginare la cerere - algoritmul FIFO (first in, first out)\n";


	cout << "Dati nr de pagini din buffer: ";
	cin >> pgNum;

	cout << "Dati nr de pagini solicitate: ";
	cin >> N;

	cout << "Dati paginile solicitate (eg: 1 2 5): ";
	int i = 0;
	while (i < N){
		int temp;
		cin >> temp;
		cache[i]=temp;
		i++;
	}

	cout << "\nMost recent ... most old" << endl;

	i = 0;
	bool pageChange;
	int PFIcount = 0;
	while (i < N){
		cout << "pagina solicitata: "<<cache[i] << endl;
		int temp;
		temp = cache[i];

		pageChange = true;

		if (!isInCache(temp)) //page.size()<pgNum && 
		{
			if (page.size() == pgNum)
				page.pop_back();
			page.push_front(cache[i]);
		}
		else{
			pageChange = false;
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
