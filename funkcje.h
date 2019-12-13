#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>

using namespace std;

//funkcja sprawdzaj�ca obecno�� nauczycieli
void check()
{
	ifstream nauczyciele;
	nauczyciele.open("pliki/nauczyciele.txt");
	string imie;
	string check;
	ofstream obecnosc("pliki/obecno��.txt");

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

//funkcja zliczaj�ca g�osy
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
		z_glosy << "ilo�� g�os�w na TAK: " << tak << endl;
		z_glosy << "ilo�� g�os�w na NIE: " << nie << endl;
		z_glosy << "ilo�� wstrzymania si� od g�os�w: " << nwm;
	}
	else
		cout << "blad glosowania! Niepoprawna liczba oddanych glosow!";
	glosy.close();
}

//funkcja do g�osowania
void glosowanie()
{
	ifstream obecnosc;
	obecnosc.open("pliki/obecno��.txt");
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
				glos = "WSYTRZYMA� SI�";
			}
			glosowanie << tokens[0] << ">" << glos << endl;
		}
		system("cls");
	}
	glosowanie.close();
	obecnosc.close();
	zlicz_glosy(obecni_count);
}