#pragma once
#include "K_pozostale.h"

//Klasa jest sieci� neuronow�. Na podstawie zachowywania si� obserwowanych we fragmencie oceanu organizm�w uczy si� jak je rozpoznawa�
class Obserwator
{
	int wykonano_przebiegow;
	double x0 = -1;
	//Zmienne modyfikowane w czasie nauki sieci
	double waga0 = (std::rand() % 10000) / 10000.0;
	double waga1 = (std::rand() % 10000) / 10000.0;
	double waga2 = (std::rand() % 10000) / 10000.0;
	//okre�la wielko�� zachodz�cych w sieci zmian w przypadku z�ego rozpoznania 
	double zmiana = 0.005;
	//Funkcja ucz�ca sie� na grupie konkretnego typu organizm�w
	void naucz_na(std::vector<Ryba*>& wektor);
	void naucz_na(std::vector<Gabka*>& wektor);
public:
	//funkcja ucz�ca sie� na wszystkich organizmach
	void naucz_siec(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki);

	//funkcja losuj�ca z prawdopodobie�stwem 50% jedn� grup� organizm�w (ryb� lub g�bk�) 
	//nast�pnie wy�wietla czy pierwszy organizm z tego zbioru zosta� prawid�owo rozpoznany
	void rozpoznaj_organizm(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki);
};

inline void Obserwator::naucz_na(std::vector<Ryba*>& wektor)
{
	wykonano_przebiegow = 0;
	bool pojawil_sie_blad = true;
	while (pojawil_sie_blad && wykonano_przebiegow < Ustawienia::max_ilo��_przebiegow_sieci)
	{
		pojawil_sie_blad = false;
		int y;
		for (int i = 0; i < wektor.size(); i++)
		{ //doprowadzenie warto�ci wej�ciowych sieci do warto�ci z przedzia�u <0;1>
			double x1 = wektor[i]->y / (static_cast<double>(Ustawienia::rozmiar_y));
			double x2 = wektor[i]->kolor.r / (static_cast<double>(255));
			//sprawdzenie czy sie� poprawnie rozpoznaje obiekt
			if (((waga1 * x1) + (waga2 * x2) - waga0) < 0)
				y = -1;
			else
				y = 1;
			if (y != 1)
			{ // z�e rozpoznanie skutkuje zmin� w wagach
				pojawil_sie_blad = true;
				waga0 = waga0 + zmiana * (1 - y) * x0 / 2;
				waga1 = waga1 + zmiana * (1 - y) * x1 / 2;
				waga2 = waga2 + zmiana * (1 - y) * x2 / 2;
			}
		}
		wykonano_przebiegow++;
	}
}
inline void Obserwator::naucz_na(std::vector<Gabka*>& wektor)
{
	wykonano_przebiegow = 0;
	bool pojawil_sie_blad = true;
	while (pojawil_sie_blad && wykonano_przebiegow < Ustawienia::max_ilo��_przebiegow_sieci)
	{
		pojawil_sie_blad = false;
		int y;
		for (int i = 0; i < wektor.size(); i++)
		{
			double x1 = wektor[i]->y / (static_cast<double>(Ustawienia::rozmiar_y));
			double x2 = wektor[i]->kolor.r / (static_cast<double>(255));
			if (((waga1 * x1) + (waga2 * x2) - waga0) < 0)
				y = -1;
			else
				y = 1;
			if (y != -1)
			{
				pojawil_sie_blad = true;
				waga0 = waga0 + zmiana * (-1 - y) * x0 / 2;
				waga1 = waga1 + zmiana * (-1 - y) * x1 / 2;
				waga2 = waga2 + zmiana * (-1 - y) * x2 / 2;
			}
		}
		wykonano_przebiegow++;
	}
}

inline void Obserwator::naucz_siec(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki)
{
	for (int i = 0; i < 8; i++)
	{
		naucz_na(ryby);
		naucz_na(gabki);
	}
}

inline void Obserwator::rozpoznaj_organizm(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki)
{
	if (!(gabki.empty()) && !(ryby.empty()))
	{
		int y;
		bool rozpoznano_prawidlowo = false;
		if (z_prawdopodobienstwem(0.5))
		{
			std::cout << "wylosowano rybe \n";
			double x1 = ryby.front()->y / (static_cast<double>(Ustawienia::rozmiar_y));
			double x2 = ryby.front()->kolor.r / (static_cast<double>(255));
			if (!(((waga1 * x1) + (waga2 * x2) - waga0) < 0))
				rozpoznano_prawidlowo = true;
		}
		else
		{
			std::cout << "wylosowano gabke \n";
			double x1 = gabki.front()->y / (static_cast<double>(Ustawienia::rozmiar_y));
			double x2 = gabki.front()->kolor.r / (static_cast<double>(255));
			if (((waga1 * x1) + (waga2 * x2) - waga0) < 0)
				rozpoznano_prawidlowo = true;
		}
		if (rozpoznano_prawidlowo)
			std::cout << "rozpoznano prawidlowo \n";
		else
			std::cout << "nie rozpoznano prawidlowo \n";
	}
}
