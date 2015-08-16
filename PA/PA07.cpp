// PA07.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

//almost ...
bool isRotation(string src, string dest){
	if (src.length() != dest.length())
		return false;
	
	unsigned int i;
	for (i = 0; i < src.length(); i++){
		if (dest[0] == src[i] && dest[dest.length() - 1] == src[i])
			return true;
	}
	return false;
}


int areRotations(string str1, string str2)
{
	int size1 = str1.length();
	int size2 = str1.length();
	string temp;
	int ptr;

	if (size1 != size2)
		return 0;

	temp[0] = '\0';
	temp = str1 + str1;

	ptr = temp.find(str2);;
	
	if (ptr != -1)
		return 1;
	else
		return 0;
}

int substringRotation(string str1, string str2)
{
	string temp;
	int ptr;

	temp[0] = '\0';
	temp = str1 + str1;

	ptr = temp.find(str2);;

	if (ptr != -1)
		return 1;
	else
		return 0;
}

int main()
{
	int rez;
	//bool rez;
	//rez = isRotation("arc", "rca");

	cout << "areRotations: ";
	rez = areRotations("arc", "rca");
	if (rez)
		cout << "ok"<<endl;
	else
		cout << "not ok" << endl;

	cout << "substringRotation: ";
	substringRotation("algoritmilor", "rit");
	if (rez)
		cout << "ok" << endl;
	else
		cout << "not ok" << endl;


	return 0;
}
