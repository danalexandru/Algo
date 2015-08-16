// specPA2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
//pentru regex
#include <regex>

//pentru parsator
#include <cstring> //eventuale functii pe char
#include <string> //pentru citire string
#include <cctype> //pentru verificare caracter alfabet
#define MAX_PROTO 200 //maximul de solutii din L(e) posibile

using namespace std;

string prototype[MAX_PROTO];
	//primul din string il las liber, in caz ca voi prinde epsilon = empty ?
	int repetitions = 2;

//am presupus citirea normala, de la stanga la dreapta
	//dar nu ar fi mai usor, cel putin pentru '*' folosit ca si modificator
	//sa citesc de la dreapta la stanga ?
		//implementez asta separat
int parseFormula(string form){
	int i = 0;
	int leng = form.length;
	int BraceOpen = 0;
	
	char buffer = '~';//buffere ar trebui sa fie doua stringuri
	char OpBuffer = '~';
	
	char buffer2 = '~';

	
	while (i<leng){
		if (form[i] == '(')
			BraceOpen++;
		else if (form[i] == ')')
		{
			if (BraceOpen>0)
				BraceOpen--;
			else return -1;
		}
		else if (isalpha(form[i])) //alternativa: foloseste codul ASCII
		{
			if (buffer != '~')
			{
				if (OpBuffer != '~')
				{
					cout << "";//placeholder
					if(isalpha(form[i+1]))
						buffer2 = form[i+1];
					
				}
				else
					cout << "";//placeholder
			}
			else
				buffer = form[i];
		}
		else if (ispunct(form[i]))
		{
			if (buffer != '~'){
			//if(OpBuffer != '~')
				if (form[i] == '+' || form[i] == '*')// atentie: '*' ca operatie
					OpBuffer = form[i];
			}
			else return -1;
		}

		i++;
	}


}

//parse V.2 => facut la seminarul special
// s=((a+ab)*ba)
//Prima si ultima paranteza pot fi scoase la procesare.

	//exemple pe regexp de mai sus:
	//first(s)='('
	//last(s)=a
	//tail_back(s)=(a+ab)*b
	//tail_front(s)=a+ab)*ba
	//firstCorectBal(s)=((a+ab)*,ba) //doua stringuri pentru reprezentare
	//isLetter(s)

//string(const char * s); //incerc fara constructor definit, momentan => alternativa: functia str

	string first(string s){
		//return s[0];
		//char k = s[0];
		//string str(k);
		string sOk;
		sOk = s[0];

		return sOk;
	}
	string last(string s){
		string sOk = s[s.length-1];//sper
		return sOk;
	}
	string tail_back(string s){
		s-=s[s.length];//length ia ultima pozitie ?
		return s;
	}
	string tail_front(string s){
		//string str = s[0];//problema de constructor string vs char
		//s-=s[0];
		return s;
	}

struct Pereche{
	string s1;
	string s2;
}per;

	Pereche firstCorrectBal(string s){
		//pe exemplul ab*
		// s1=a, s2=b*
	//sure, all fine and dandy, but: struct, or no struct(double parameter recursion, maybe) ? 
		per.s1 = " ";
		per.s2 = " ";

		return per;
	}

		bool isLetter(string s){
			if (s.length() == 1){
				char str = s[0];
				if (isalpha(str))
					return true;
			}
			return false;
		}

		string letter(string s){//aici .............
			string sk = s[0];

			return sk; 
		}
		string star(string s); //repetitie - AST ?
			//strict simbolul de repetitie din RegExp
			//daca nu stabilesti prioritati, ...
			// ab* vs a(b*)
			//ai putea: ab* => s1, si s2 sir vid
		string pluss(string s1, string s2); //disjunctie - AST ?
		string conc(string s1, string s2); //concatenare - AST ?



string parse(string S){ //definesc un struct tree ?
	//de ce dai return, daca vrei sa parsezi toata expresia ?
		//recursivarea e valabila doar daca treeParser si parse sunt una si aceeasi functie...
	//de aici in jos era parse
	try{
		Pereche receive;
		string s1, s2;
		string pStg,pDrp,plu,inm;
		pStg[0] = '(';
		pDrp[0] = ')';
		plu[0] = '+';
		inm[0] = '*';
		//TODO: check length for any previous string !

		if (first(S).c_str() == pStg && last(S).c_str() == pDrp)
			return parse(tail_front(tail_back(s1)));//elimin sfarsit si inceput
		if(isLetter(S)) return letter(first(S));//first(n), dar n nu este nicaieri
			//ok, acopar situatia cand este tot S este doar o litera, dar daca primul 
		//caracter din S este litera ... ce fac ?
			//problema e ca letter cere string, si first returneaza char, si aici ii problema
				//ca nu ai constructor implicit...
					//pp ca letter are ca si constructor un char.

		if (last(S) == inm)
			return star(parse(tail_front(S)));//nu are cum sa fie tail_first
		receive=firstCorrectBal(S); //first corect balanced
		s1 = receive.s1;
		s2 = receive.s2;

		if (first(s2) == plu)
			return pluss(parse(s1), tail_back(s2));
		if (isLetter(first(s2)) || first(s2) == pStg)
			return conc(parse(s1), parse(s2));
		throw("expresia nu a fost procesata/e gresita ?");//trebuie sa fie prins ...
	}
	catch (string t){
		cout << "Stay a bit: " << t;
	}
}






int main()
{
//experimentare cu pachetul regex din C++
	
	//TODO: deschide fisier: fopen sau FILE ?

//Parsator de expresii regulate:
	// - parseaza formula (verifica corectitudinea dupa setul de reguli definit)
	// - genereaza spatiul de formule posibile

	//TODO: sa verific daca ispunct merge cum trebuie ?
	/*
	string form;
	cout << "Dati formula de parsat: ";
	cin >> form;

	int rez = parseFormula(form);

	if (rez == -1)
		cout << "Parsing error !";
	else 
	{ 
		cout << "Parsing ok. Here are results: "<<endl;
		cout << "\tWhat you wanted to be parsed: " << form;
		cout << "\tWhat are the possible solutions: " << endl;
		//showSolutions(); //sau ceva in genul ?

	}

	*/

	//parse V.2 ......................................
	string S;
	cout << "Dati expresia regulata: ";
	cin >> S;

	parse(S);


	return 0;
}
