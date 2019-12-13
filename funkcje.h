#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>

using namespace std;

//funkcja sprawdzaj¹ca obecnoœæ nauczycieli
void check()
{
	ifstream nauczyciele;
	nauczyciele.open("pliki/nauczyciele.txt");
	string imie;
	string check;
	ofstream obecnosc("pliki/obecnoœæ.txt");

	while (!nauczyciele.eof())
	{
		cout << "Obecny - 1	Nieobecny - 0" << endl;
		getline(nauczyciele, imie);
		do
		{
			cout << imie << " ";
			cin >> check;
			if (check != "0" && check != "1")
			{
				cout << "wprowadz 1 lub 0!" << endl;
			}
		} while (check != "0" && check != "1");
		if (check == "1")
			obecnosc << imie << ">OBECNY" << endl;
		else
			obecnosc << imie << ">NIEOBECNY" << endl;
		system("cls");
	}
	nauczyciele.close();
	obecnosc.close();
}

//funkcja zliczaj¹ca g³osy
void zlicz_glosy(int obecni_count)
{
	ifstream glosy;
	glosy.open("pliki/glosowanie.txt");
	ofstream z_glosy("pliki/zliczone_glosy.txt");
	int tak = 0, nie = 0, nwm = 0;
	string nazwisko;

	while (!glosy.eof())
	{
		getline(glosy, nazwisko);
		istringstream split(nazwisko);
		vector<string> tokens;
		for (string each; getline(split, each, '>'); tokens.push_back(each));
		if (tokens[1] == "TAK")
			tak++;
		else if (tokens[1] == "NIE")
			nie++;
		else
			nwm++;
	}
	if (tak + nie + nwm == obecni_count)
	{
		z_glosy << "iloœæ g³osów na TAK: " << tak << endl;
		z_glosy << "iloœæ g³osów na NIE: " << nie << endl;
		z_glosy << "iloœæ wstrzymania siê od g³osów: " << nwm;
	}
	else
		cout << "blad glosowania! Niepoprawna liczba oddanych glosow!";
	glosy.close();
}

//funkcja do g³osowania
void glosowanie()
{
	ifstream obecnosc;
	obecnosc.open("pliki/obecnoœæ.txt");
	string nauczyciel;
	string glos;
	ofstream glosowanie("pliki/glosowanie.txt");
	int obecni_count = 0;

	while (!obecnosc.eof())
	{
		getline(obecnosc, nauczyciel);
		istringstream split(nauczyciel);
		vector<string> tokens;
		for (string each; getline(split, each, '>'); tokens.push_back(each));
		if (tokens[1] == "OBECNY")
		{
			obecni_count++;
			cout << "Prosze wpisac 'TAK', 'NIE' lub 'NWM dla wstrzymania sie od glosu'" << endl;
			do
			{
				cout << tokens[0] << " ";
				cin >> glos;
				if (glos != "TAK" && glos != "NIE" && glos != "NWM")
				{
					cout << "Wprowadz poprawny glos!" << endl;
				}
			} while (glos != "TAK" && glos != "NIE" && glos != "NWM");
			if (glos == "NWM")
			{
				glos = "WSYTRZYMA£ SIÊ";
			}
			glosowanie << tokens[0] << ">" << glos << endl;
		}
		system("cls");
	}
	glosowanie.close();
	obecnosc.close();
	zlicz_glosy(obecni_count);
}