// PA03.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cmath>
#define MAX_LIST 15
using namespace std;

struct Punct{
	int x;
	int y;
}list[MAX_LIST];

ifstream fin("Input.in");

void ReadList(int n){
	int i;
	for (i = 0; i < n; i++)
		fin >> list[i].x >> list[i].y;
}


bool check[MAX_LIST][MAX_LIST]; // este setat by default cu false
Punct minPct;

Punct closestPair(int n){
	int i, j, dist;
	for (i = 0; i < n; i++)
		check[i][i] = true;
	
	int min=999; //diameter set: int max=0;

	
	int xx, yy;
	for (i = 0; i < n; i++)
	{
		//cout << "\t\n i=" << i;
		for (j = 0; j < n; j++)
		{ 
			//cout << "\n    j=" << j;
			
			//cout << " check[i][j]=" << check[i][j];
			if (check[i][j] == false)
			{	
				xx = list[j].x - list[i].x;
				yy = list[j].y - list[i].y;
				dist = sqrt(xx*xx+yy*yy);
				if (dist < min){   //diameter set: if(dist > max)
					min = dist;	    //diameter set: max = dist;
					minPct.x = i;
					minPct.y = j;
				}
				check[i][j] = true;
				check[j][i] = true;
			}
		}
	}

	return minPct;
}

int nearest_neighbour(Punct P, int n){
	int i;
	int min = 999;
	int dist, xx, yy;
	int rez=0;

	for (i = 0; i < n; i++){
		xx = list[i].x - P.x;
		yy = list[i].y - P.y;
		dist = sqrt(xx*xx + yy*yy);
		if (dist < min)
		{
			min = dist;
			rez = i + 1;
		}
	}

	return rez;
}

int main()
{
	//PR!1
	int n;

	//cout << "\ncheck[0] : " << check[0][0];
	//cout << "\ncheck[0] : " << true;
	n = 6;
	cout << "\nhow many elements ? (<15) "<<n; 
		//cin >> n;
	ReadList(n);

	Punct rez;
	rez = closestPair(n);

	cout << "\n\nCea mai apropiata pereche este: " << rez.x + 1 <<" si "<< rez.y + 1;


	//PR!2
	Punct P;
	cout << "\n\n\nDati punctul P: "; cin >> P.x; cin >> P.y;
	cout << "\nCel mai apropiat vecin a lui P este: " << nearest_neighbour(P,n);


	return 0;
}
