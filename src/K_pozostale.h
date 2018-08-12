#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <SFML/Graphics.hpp>

//Funkcja pobieraj�ca od u�ytkownika liczb� z zadanego przedzia�u domkni�tego
unsigned int pobierz_unsigned(unsigned int min, unsigned int max) {
	long long liczba = 0;
	do {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "niepoprawna wartosc \n";
		}
		std::cin >> static_cast<long long>(liczba);
	} while (liczba < min || liczba > max || std::cin.fail());
	unsigned wynik = static_cast<unsigned int>(liczba);
	std::cout << "pobrano liczbe: " << wynik << "\n";
	return wynik;
}

//klasa s�u��ca do ustawiania parametr�w programu (w wi�kszo�ci przed kompilacj�)
class Ustawienia
{
public:
	//wymiary okna (w pikselach)
	const static int rozmiar_x = 1024;
	const static int rozmiar_y = 540;
	//pozycja  okna (w pikselach)
	const static int pozycja_x = 250;
	const static int pozycja_y = 155;

	const static int szerokosc_dna = 60;
		//okre�la do jakiego poziomu mog� pojawia� si� i p�ywa� organizmy
		const static int wysokosc_dna = rozmiar_y - szerokosc_dna;
	//sr oznacza �redni� warto��
	const static int temperatura_sr = 10;
	const static int glebokosc_sr = 1000;
	const static int procentowe_odchylenie_przystosowan = 25;
	const static int odchylenie_temperatury = static_cast<int>(temperatura_sr * (procentowe_odchylenie_przystosowan / 100.0));
	const static int odchylenie_glebokosci = static_cast<int>(glebokosc_sr * (procentowe_odchylenie_przystosowan / 100.0));

	//je�li u�ytkownik korzysta z w�asnych ustawie� to ta zmienna ma warto�� "true"
	bool ustawienia_wlasne;
	const static int liczba_skal = 5;
	int Xliczba_skal;

	const static int ilosc_ryb_na_poczatku = 240;
	int Xilosc_ryb_na_poczatku;
	const static int ilosc_gabek_na_poczatku = 100;
	int Xilosc_gabek_na_poczatku;

	const static int max_ilosc_ryb = 300;
	int Xmax_ilosc_ryb;
	const static int max_ilosc_gabek = 200;
	int Xmax_ilosc_gabek;

	//okre�la ile procent organizm�w prze�yje eliminacj� metod� ruletki
	const static int ile_po_ruletce = 92;

	const static int co_ktora_gabka_sie_rozmnaza = 2;

	const static int sredni_czas_zycia_ryby = 40;
	const static int sredni_czas_zycia_gabki = 60;
	const static int srednia_liczba_rozmnozen = 3;
	const static int odchylenie_sredniego_czasu_zycia = 15;
		const static int co_ile_cykli_rozmnozenie = sredni_czas_zycia_ryby / srednia_liczba_rozmnozen;

	const static int klatki_na_sekunde = 9;

	const static int max_ilo��_przebiegow_sieci = 4;

	float wylosowane_skalowania_wsp_x[2][liczba_skal];
	Ustawienia();

	//Funkcja pobieraj�ca od u�ytkownika parametry symulacji
	void wlasne_ustawienia();
};
inline Ustawienia::Ustawienia()
{
	for (int i = 0; i < liczba_skal; i++)
	{
		wylosowane_skalowania_wsp_x[0][i] = (std::rand() % 10 + 5) / static_cast<float>(10);
		wylosowane_skalowania_wsp_x[1][i] = static_cast<float>(std::rand() % (static_cast<int>(Ustawienia::rozmiar_x * 0.9)));
	}
}

inline void Ustawienia::wlasne_ustawienia()
{
	std::cout << "Podaj liczbe skal <0, 10> \n";
	this->Xliczba_skal = pobierz_unsigned(0, 10);
	std::cout << "Podaj ilosc ryb na poczatku <2, 300> \n";
	Xilosc_ryb_na_poczatku = pobierz_unsigned(2, 300);
	std::cout << "Podaj ilosc gabek na poczatku <1, 200> \n";
	Xilosc_gabek_na_poczatku = pobierz_unsigned(1, 200);
	std::cout << "Podaj maksymalna ilosc ryb <50, 500> \n";
	Xmax_ilosc_ryb = pobierz_unsigned(50, 500);
	std::cout << "Podaj maksymalna ilosc gabek <40, 400> \n";
	Xmax_ilosc_gabek = pobierz_unsigned(40, 400);
}

//Klasa zawieraj�ca cz�� wsp�ln� klasy: Ryba i G�bka
class Organizm
{
public:
	//Ps oznacza przystosowanie do �redniej warto�ci 
	int temperatura_Ps;
	unsigned glebokosc_Ps;
	//okre�la ca�kowite przystosowanie do danych warunk�w
	double przystosowanie_calkowite;
	//wsp�rz�dne
	int x, y;
	//okre�la przez ile cykli dany organizm b�dzie jeszcze �y�, jest zmniejszana przez funkcj� "uplyw_czasu"
	int czas_do_smierci;
	//kolor organizmu
	sf::Color kolor;
	//rozmiar (przy wy�wietlaniu)
	int rozmiar;

	//okre�la czy dany organizm ma prze�y� selekcje metod� ruletki
	bool ruletka = false;

	Organizm(const int& temperatura, const unsigned& glebokosc, const unsigned& _x, const unsigned& _y, const sf::Color& color);
};
inline Organizm::Organizm(const int& temperatura, const unsigned& glebokosc, const unsigned& _x,
	const unsigned& _y, const sf::Color& color)
	: temperatura_Ps(temperatura), glebokosc_Ps(glebokosc), x(_x), y(_y), kolor(color) {}

class Ryba : public Organizm
{
public:
	Ryba(const int & temperatura, const unsigned & glebokosc, const unsigned & _x, const unsigned & _y, const sf::Color & color);
};
inline Ryba::Ryba(const int& temperatura, const unsigned& glebokosc, const unsigned& _x, const unsigned& _y, const sf::Color& color)
	: Organizm(temperatura, glebokosc, _x, _y, color)
{
	czas_do_smierci = Ustawienia::sredni_czas_zycia_ryby + std::rand() %
		(2 * Ustawienia::odchylenie_sredniego_czasu_zycia) - Ustawienia::odchylenie_sredniego_czasu_zycia;
	rozmiar = std::rand() % 9 + 3;
}

class Gabka : public Organizm
{
public:
	Gabka(const int & temperatura, const unsigned & glebokosc, const unsigned & _x, const unsigned & _y, const sf::Color & color);
};
inline Gabka::Gabka(const int& temperatura, const unsigned& glebokosc, const unsigned& _x, const unsigned& _y, const sf::Color& color)
	: Organizm(temperatura, glebokosc, _x, _y, color)
{
	czas_do_smierci = Ustawienia::sredni_czas_zycia_gabki + std::rand() %
		(2 * Ustawienia::odchylenie_sredniego_czasu_zycia) - Ustawienia::odchylenie_sredniego_czasu_zycia;
	rozmiar = std::rand() % 14 + 2;
}


//Funkcja zwraca "true" z prawdopodobie�stwem "p"
static bool z_prawdopodobienstwem(const double & p) {
	return rand() / (RAND_MAX + 1.0) < p;
}

//Klasa odpowiedzialna za  selekcj� i rozmna�anie organizm�w
class Algorytm_genetyczny
{
	//Podprocedura funkcji "ocena_przystosowania"
	static double oblicz_skladni(const int & _Ps, const int & _sr);
	
	//Funkcja usuwa organizmy wskazane metod� ruletki
	static void wynik_ruletki(std::vector<Ryba*> & wektor);
	void wynik_ruletki(std::vector<Gabka*> & wektor);
	
	//Funkcja ocenia przystosowanie organizm�w
	static double ocena_przystosowania(std::vector<Ryba*> & wektor);
	double ocena_przystosowania(std::vector<Gabka*> & wektor);

	//Funkcja wykorzystuj�c metod� ruletki decyduje, kt�re organizmy zostan� usuni�te z powodu zbyt s�abego przystosowania 
	//do otoczenia (pozosta�e b�d� si� mno�y�)
	static void selekcja(std::vector<Ryba*> & wektor);
	void selekcja(std::vector<Gabka*> & wektor);

	//Funkcja wywo�ywana tylko przez funkcje "krzyzowanie" i "mutacja"; tworzy jeden organizm danego typu
	static void rozmnoz_organizmy(const std::vector<Ryba*>::iterator & it, 
		const std::vector<Ryba*>::iterator & it_temp,std::vector<Ryba*> & wektor_temp);
	void rozmnoz_organizmy(std::vector<Gabka*> & gabki, const int & licznik_gabek);

	//Funkcja rozmna�aj�ca obiekty typu Ryba. Parametry nowej ryby s� obliczane w nast�puj�cy spos�b: 
	//przystosowanie do �rednich warto�ci s� dziedziczone po osobno po jednym z rodzic�w z r�wnym prawdopodobie�stwem, 
	//po�o�enie to �rednia wsp�rz�dnych rodzic�w, kolor to z�o�enie po�owy koloru ka�dego z rodzic�w
	static void krzyzowanie(std::vector<Ryba*> & ryby);

	//Funkcja rozmna�aj�ca obiekty typu Gabka. Parametry nowej g�bki s� obliczane w nast�puj�cy spos�b: 
	//przystosowanie do �rednich warto�ci i kolor s� obliczane tak jak przy generacji organizm�w pocz�tkowych, 
	//po�o�enia s� losowe ale zbli�one do danej g�bki, kt�ra mutuje
	void mutacja(std::vector<Gabka*>& gabki);

	//obliczenia dla zbioru ryb
	static void watek_ryby(std::vector<Ryba*>& ryby);
public:
	//Funkcja uruchamiaj�ca funkcje algorytmu genetycznego
	void rozpocznij(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki);

	//Funkcja "postarza" i usuwa organizmy
	void uplyw_czasu(std::vector<Ryba*>& wektor);
	void uplyw_czasu(std::vector<Gabka*>& wektor);
};

inline double Algorytm_genetyczny::oblicz_skladni(const int& _Ps, const int& _sr)
{
	int granica = 4;
	int roznica = abs(_Ps - _sr);
	if (roznica < granica)
		return 100;
	if (roznica < granica * 3)
		return 50;
	if (roznica < granica * 6)
		return 20;
	return 0.1;
}

inline void Algorytm_genetyczny::wynik_ruletki(std::vector<Ryba*>& wektor)
{
	std::vector<Ryba*>::iterator it = wektor.begin();
	while (it != wektor.end())
	{
		if (!(*it)->ruletka)
		{
			delete (*it);
			it = wektor.erase(it);
		}
		else {
			(*it)->ruletka = false;
			++it;
		}
	}
}
inline void Algorytm_genetyczny::wynik_ruletki(std::vector<Gabka*>& wektor)
{
	std::vector<Gabka*>::iterator it = wektor.begin();
	while (it != wektor.end())
	{
		if (!(*it)->ruletka)
		{
			delete (*it);
			it = wektor.erase(it);
		}
		else {
			(*it)->ruletka = false;
			++it;
		}
	}
}

inline double Algorytm_genetyczny::ocena_przystosowania(std::vector<Ryba*>& wektor)
{
	double suma = 0;
	for (std::vector<Ryba*>::iterator it = wektor.begin(); it < wektor.end(); it++)
	{
		double skladnikT = oblicz_skladni((*it)->temperatura_Ps, Ustawienia::temperatura_sr);
		double skladnikG = oblicz_skladni((*it)->glebokosc_Ps, Ustawienia::glebokosc_sr);
		(*it)->przystosowanie_calkowite = skladnikT * skladnikG;
		suma += (*it)->przystosowanie_calkowite;
	}
	return suma;
}
inline double Algorytm_genetyczny::ocena_przystosowania(std::vector<Gabka*>& wektor)
{
	double suma = 0;
	for (std::vector<Gabka*>::iterator it = wektor.begin(); it < wektor.end(); it++)
	{
		double skladnikT = oblicz_skladni((*it)->temperatura_Ps, Ustawienia::temperatura_sr);
		double skladnikG = oblicz_skladni((*it)->glebokosc_Ps, Ustawienia::glebokosc_sr);
		(*it)->przystosowanie_calkowite = skladnikT * skladnikG;
		suma += (*it)->przystosowanie_calkowite;
	}
	return suma;
}

inline void Algorytm_genetyczny::selekcja(std::vector<Ryba*>& wektor)
{
	double suma_przystosowan = ocena_przystosowania(wektor);
	for (int i = 0; i < static_cast<int>(wektor.size() * (Ustawienia::ile_po_ruletce / 100.0)); i++)
	{
		float prawdopodobienstwo = (std::rand() % 10000) / static_cast<float>(10000);
		float suma_prawdopodobienstw = 0;
		for (unsigned j = 0; j < wektor.size(); j++)
		{
			//obliczenie przystosowania danego organizmu w stosunku do sumy przystosowa� wszystkich organizm�w
			suma_prawdopodobienstw += wektor[j]->przystosowanie_calkowite / suma_przystosowan;
			if (!wektor[j]->ruletka)
			{
				if (prawdopodobienstwo < suma_prawdopodobienstw)
				{
					wektor[j]->ruletka = true;
					break;
				}
			}
		}
	}
	wynik_ruletki(wektor);
}
inline void Algorytm_genetyczny::selekcja(std::vector<Gabka*>& wektor)
{
	double suma_przystosowan = ocena_przystosowania(wektor);
	for (int i = 0; i < static_cast<int>(wektor.size() * (Ustawienia::ile_po_ruletce / 100.0)); i++)
	{
		float prawdopodobienstwo = (std::rand() % 10000) / 10000.0;
		float suma_prawdopodobienstw = 0;
		for (int j = 0; j < wektor.size(); j++)
		{
			suma_prawdopodobienstw += wektor[j]->przystosowanie_calkowite / suma_przystosowan;
			if (!wektor[j]->ruletka)
			{
				if (prawdopodobienstwo < suma_prawdopodobienstw)
				{
					wektor[j]->ruletka = true;
					break;
				}
			}
		}
	}
	wynik_ruletki(wektor);
}

inline void Algorytm_genetyczny::rozmnoz_organizmy(const std::vector<Ryba*>::iterator& it, 
	const std::vector<Ryba*>::iterator& it_temp, std::vector<Ryba*>& wektor_temp)
{
	int temperatura;
	if (z_prawdopodobienstwem(0.5))
		temperatura = (*it)->temperatura_Ps;
	else
		temperatura = (*it_temp)->temperatura_Ps;

	int glebokosc;
	if (z_prawdopodobienstwem(0.5))
		glebokosc = (*it)->glebokosc_Ps;
	else
		glebokosc = (*it_temp)->glebokosc_Ps;

	sf::Color kolor(0, (*it)->kolor.g, (*it)->kolor.b);
	wektor_temp.push_back(new Ryba(temperatura, glebokosc, std::rand() % Ustawienia::rozmiar_x,
		std::rand() % Ustawienia::wysokosc_dna, kolor));
}
inline void Algorytm_genetyczny::rozmnoz_organizmy(std::vector<Gabka*>& gabki, const int& licznik_gabek)
{
	int wspolrzedna_y = gabki.at(licznik_gabek)->y + std::rand() % 10 - 5;
	if (wspolrzedna_y > Ustawienia::szerokosc_dna)
	{
		wspolrzedna_y = Ustawienia::szerokosc_dna - std::rand() % 8;
	}
	wspolrzedna_y += Ustawienia::wysokosc_dna;
	sf::Color kolor(std::rand() % 55 + 170, 0, std::rand() % 155);
	gabki.push_back(new Gabka(std::rand() % Ustawienia::odchylenie_temperatury -
		Ustawienia::odchylenie_temperatury / 2 + Ustawienia::temperatura_sr,
		std::rand() % Ustawienia::odchylenie_glebokosci - Ustawienia::odchylenie_glebokosci / 2 + Ustawienia::glebokosc_sr,
		(gabki.at(licznik_gabek)->x + std::rand() % 20 - 10) % Ustawienia::rozmiar_x,
		wspolrzedna_y, kolor));
}

inline void Algorytm_genetyczny::krzyzowanie(std::vector<Ryba*>& ryby)
{
	std::vector<Ryba*> ryby_temp;
	std::vector<Ryba*>::iterator it = ryby.begin();
	if (it == ryby.end())
		return;
	++it;
	std::vector<Ryba*>::iterator it_temp = ryby.begin();
	while (true)
	{
		if (it == ryby.end())
			break;
		rozmnoz_organizmy(it, it_temp, ryby_temp);
		++it;
		if (it == ryby.end())
			break;
		it_temp = it;
		++it;
	}
	int rozmiar = ryby_temp.size();
	for (int i = 0; i < rozmiar; i++)
	{
		ryby.push_back(ryby_temp.back());
		ryby_temp.pop_back();
	}
}

inline void Algorytm_genetyczny::mutacja(std::vector<Gabka*>& gabki)
{
	int licznik_gabek = 0;
	int ilosc_gabek_przed_rozmnazaniem = gabki.size();
	while (true)
	{
		if (licznik_gabek >= ilosc_gabek_przed_rozmnazaniem)
			return;
		if (licznik_gabek % Ustawienia::co_ktora_gabka_sie_rozmnaza == 0)
		{
			rozmnoz_organizmy(gabki, licznik_gabek);
		}
		licznik_gabek++;
	}
}

inline void Algorytm_genetyczny::watek_ryby(std::vector<Ryba*>& ryby)
{
	selekcja(ryby);
	krzyzowanie(ryby);
}

inline void Algorytm_genetyczny::rozpocznij(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki)
{
	//obliczenia dla zbioru ryb odbywaj� si� w osobnym w�tku, natomiast dla g�bek w�tku g��wnym
	std::thread watek(&Algorytm_genetyczny::watek_ryby, std::ref(ryby));
	selekcja(gabki);
	mutacja(gabki);
	watek.join();
}

inline void Algorytm_genetyczny::uplyw_czasu(std::vector<Ryba*>& wektor)
{
	for (std::vector<Ryba*>::iterator it = wektor.begin(); it != wektor.end();)
	{
		(*it)->czas_do_smierci--;
		if ((*it)->czas_do_smierci <= 0)
		{
			delete (*it);
			it = wektor.erase(it);
		}
		else
			++it;
	}
}

inline void Algorytm_genetyczny::uplyw_czasu(std::vector<Gabka*>& wektor)
{
	for (std::vector<Gabka*>::iterator it = wektor.begin(); it != wektor.end();)
	{
		(*it)->czas_do_smierci--;
		if ((*it)->czas_do_smierci <= 0)
		{
			delete (*it);
			it = wektor.erase(it);
		}
		else
			++it;
	}
}

