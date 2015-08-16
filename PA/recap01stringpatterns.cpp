// recap01stringpatterns.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;
/***************************
String Matching
*******************/

//KMP - Knuth-Morris-Pratt
#define nMax 1000
#define mMax 255

int Urm[mMax];
char Te[nMax], Pe[mMax];
int n, m;

void Urmatorul(char *P)
{
	int k = -1, x;
	Urm[0] = 0;
	for (x = 1; x<m; x++){
		while (k>0 && P[k + 1] != P[x]) k = Urm[k];
		if (P[k + 1] == P[x]) k++;
		Urm[x] = k;
	}
}

int main()
{
	//naiva
	string T, P;
	cout << "String T: ";
	cin >> T;
	cout << "Pattern P: ";
	cin >> P;

	//KMP - Knuth-Morris-Pratt
	cout << "KMP.....................\n";
	int i, x = -1;
	ifstream f("KMP.in");
	//ofstream g("KMP.out");

	f.getline(Te, 1000); 
	f.getline(Pe, 255);

	n = strlen(Te); m = strlen(Pe);
	Urmatorul(Pe);

	for (i = 0; i<n; i++)
	{
		while (x>0 && Pe[x + 1] != Te[i]) x = Urm[x];
		if (Pe[x + 1] == Te[i]) x++;//s-au potrivit
		if (x == m - 1)
		{
			cout << "Am gasit subsirul in pozitia " << i - m + 1 << endl;
			x = Urm[x];
		}
	}
	//g.close();


	return 0;
}
