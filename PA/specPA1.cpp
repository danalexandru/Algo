// specPA1.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//PA: Rabin/Karp, Knuth-Morris-Pratt (KMP), Aho-Corasick
//DFA (deterministic finite automata) & other data structures

//basic compression
//Boost library + STL library

/**************************************************/

//naive string matching

void naiveStringMatching(string T, string P){
	int n, m,s,i;
	int count = 0;
	n = T.length();
	cout << "\n\tThe main string haz " << n << " characters";
	m = P.length();
	cout << "\n\tThe substring haz " << m << " characters\n";
	for (s = 0; s <= n - m; s++) //<= ?
		for (i = 0; i <= m; i++)
		{ 
			if (P[i] == T[s + i])
				count++;
			else count = 0;
			if (count == m){
				cout << "\nPattern occurs with shift " << s /*<< " and " << i*/;
				break;
			}
		}
}



//PA1 - Karp
//orice secventa de m caractere (simbol) - stocate intr-un hash table foarte mare, pt a evita coliziunea
//testeaza pattern p contra unui subsir de lungime m <=> hash da aceeasi valoare pt p si m
	//pt pattern - hash este calculat o singura data
	//functia de dispersie trebuie definita in asa fel incat la deplasarea spre dreapta sa fie simpla
//timpul necesar efectuarii acestui calc trb sa fie mult mai mic decat cel al compararii a 2 siruri de lung m
//#define REHASH(a,b,h) ((((h)-(a)*d)<<1)(b))
int d;
inline long REHASH(char a, char b, int h){
	return (h-a*d) << 1+b;
}
int RK(char *p, int m, char *s, int n){
	long d, hs, hp, i, j;
	/* Preprocesare */
	for (d = i = 1; i < m; ++i)
		d = (d << 1);
	for (hp = hs = i = 0; i < m; ++i)
	{
		hp = ((hp << 1) + p[i]);
		hs = ((hs << 1) + s[i]);
	}
	/* Cautare */
	i = 0;
	while (i <= n - m){
		if (hp == hs && memcmp(p, s + i, m) == 0)
			return i;
		hs = REHASH(s[i], s[i + m], hs);
		++i;
	}
	return -1;
}

//din Cormen
/*
void RabinKarpMatcher(string T, string P, char d, int q){
	int n, m;
	int h;
	int p, t0;
	int i,s;

	n = T.length();
	m = P.length();

	double tempd;
	//h = pow(d, m - 1) % q;//possible loss of data + char
	//sau
	for (i = 1; i <= m - 1; i++)
		tempd = d*i;
	h = ((int)tempd)%q;

	p = 0;
	t0 = 0;

	//preprocesare
	for (i = 1; i <= m; i++) //<= ?
	{
		p = (d*p + P[i]) % q;
		t0 = (d*t0 + T[i]) % q;
	}
	//matching
	for (s = 0; s < n - m; s++)//pp ca nu <= ?
	{
		if (p == ts)	//ce este ts ?
		{
			if (P[1...m] == T[s + 1...s + m])
				cout << "Pattern occurs with shift" << s;
		}
		if (s < n - m)
			ts + 1 = (d(ts - T[s + 1] * h) + T[s + m + 1]) % q;
	}


}
*/
//PA2-Boyer-Moore - versiunea 1
/*
int BM(s, n, p, m, salt){
	int i, j;	
	i = m - 1; j = m - 1;
	repeat
		if (s[i] = p[j]) {
			i = i - 1;
			j = j - 1;
		}
		else if ((m - j) > salt[s[i]]) i = i + m - j;
		else i = i + salt[s[i]];
		j = m - 1;
	until(j<0 or i>n - 1); //se traduce prin do...while(j>0 && i>n-1)
		if (j<0) return i + 1;
		else return -1;
}
*/

//PA3 - functia esec - algoritm
/*
void determinaF(p, m, f) {
	f[0] = -1;
	for (j = 1; j < m; j = j + 1) {
		k = f[j - 1];
		while ((k != -1) && (p[j - 1] != p[k]))
			k = f[k];
		f[j] = k + 1;
	}
}
*/
/*
KMP(s, n, p, m, f) {
	i = 0;
	j = 0;
	while (i < n) {
		while (j != -1) && (p[j] != s[i])
			j = f[j];
		if (j = m - 1)
			return i - m + 1; /* gasit p in s */
/*
		else {
			i = i + 1;
			j = j + 1;
		}
	}
	return -1; /* p nu apare in s */
//}	

int main()
{
	/*
	char ch2str[100];//const
	cout << "French fries, nigga ! ";
	cin >> ch2str;
	string str(ch2str);
	cout << "The size of str is " << str.length() << " bytes.\n";
	*/
	//cout << "The size of str is " << strlen(str) << " bytes.\n"; //niet, doar const char/char.



	char ch2str[100];
	cout << "\nDati string principal: ";
		cin.getline(ch2str,100);
	string search(ch2str);
	cout << "\nDati string de cautat: ";
		cin.getline(ch2str, 100);
	string toSearch(ch2str);

	naiveStringMatching(search, toSearch);


	return 0;
}
