#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

void glosowanie();

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
		if (imie != "")
		{
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
	vector<string> file;

	while (!glosy.eof())
	{
		getline(glosy, nazwisko);
		file.push_back(nazwisko);
	}

	for(int i=0; i < file.size(); i++)
	{
		if (file.at(i) != "")
		{
			if (file.at(i).at(file.at(i).length() - 3) == (const char)'T')
				tak++;
			else if (file.at(i).at(file.at(i).length() - 3) == (const char)'N')
				nie++;
			else
				nwm++;
		}
	}
	
	if (tak + nie + nwm == obecni_count)
	{
		if (tak == nie)
		{
			cout << "Glosowanie nierozstrzygniete! Powtorz glosowanie" << endl;
			glosowanie();
		}
		z_glosy << "iloœæ g³osów na TAK: " << tak << endl;
		z_glosy << "iloœæ g³osów na NIE: " << nie << endl;
		z_glosy << "iloœæ wstrzymania siê od g³osów: " << nwm;
		cout << "Glosowanie zakonczone sukcesem!" << endl;
	}
	else
		cout << "blad glosowania! Niepoprawna liczba oddanych glosow!";
	system("pause");
	glosy.close();
}

//funkcja do g³osowania
void glosowanie()
{
	ifstream obecnosc;
	obecnosc.open("pliki/obecnoœæ.txt");
	string nauczyciel;
	vector<string> file;
	string glos;
	ofstream glosowanie("pliki/glosowanie.txt");
	int obecni_count = 0;

	while (!obecnosc.eof())
	{
		getline(obecnosc, nauczyciel);
		file.push_back(nauczyciel);
	}

	for (int i=0; i < file.size(); i++)
	{
		if (file.at(i) != "")
		{
			if (file.at(i).at(file.at(i).length() - 7) == (const char)'>')
			{
				obecni_count++;
				cout << "Prosze wpisac 'TAK', 'NIE' lub 'NWM dla wstrzymania sie od glosu'" << endl;
				do
				{
					for (int j = 0; j < file.at(i).size()-7; j++)
						nauczyciel = nauczyciel+file.at(i).at(j);
					cout << nauczyciel << " ";
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
				glosowanie << nauczyciel << ">" << glos << endl;
			}
			nauczyciel = "";
			system("cls");
		}
	}
	glosowanie.close();
	obecnosc.close();
	zlicz_glosy(obecni_count);
}