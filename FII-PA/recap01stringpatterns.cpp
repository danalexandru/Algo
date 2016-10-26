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

int Next[mMax];
char Te[nMax], Pe[mMax];
int n, m;

void Next(char *P)
{
	int k = -1, x;
	Next[0] = 0;
	for (x = 1; x<m; x++){
		while (k>0 && P[k + 1] != P[x]) k = Next[k];
		if (P[k + 1] == P[x]) k++;
		Next[x] = k;
	}
}

int main()
{
	//naive
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
	Next(Pe);

	for (i = 0; i<n; i++)
	{
		while (x>0 && Pe[x + 1] != Te[i]) x = Next[x];
		if (Pe[x + 1] == Te[i]) x++; //match
		if (x == m - 1)
		{
			cout << "Found substring at position " << i - m + 1 << endl;
			x = Next[x];
		}
	}
	//g.close();


	return 0;
}
