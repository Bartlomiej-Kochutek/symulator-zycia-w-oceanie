#pragma once
#include "Perceptron.h"
#include "tinyxml.h"

//Klasa s³u¿¹ca do obs³ugi plików XML
class Plik_XML
{
	//funkcja zapisuj¹ca do pliku XML podany zbiór organizmów
	static void Zapisz_do_pliku(const char* nazwa_pliku, std::vector<Ryba*>& wektor);
	static void Zapisz_do_pliku(const char* nazwa_pliku, std::vector<Gabka*>& wektor);

	//funkcja usuwaj¹ca z wektora wszystkie elementy
	static void oproznij_zbior(std::vector<Ryba*>& wektor);
	static void oproznij_zbior(std::vector<Gabka*>& wektor);

	//funkcja wywo³ywana tylko w funkcji "Wczytaj_z_pliku". S³u¿y do otwarcia pliku
	static void wczytaj(TiXmlDocument& doc);

	//funkcja wczytuj¹ca z pliku XML podany zbiór organizmów
	static bool Wczytaj_z_pliku(const char* nazwa_pliku, std::vector<Ryba*>& wektor);
	static bool Wczytaj_z_pliku(const char* nazwa_pliku, std::vector<Gabka*>& wektor);
public:
	//funkcje zapisuj¹ce/wczytuj¹ce ca³y stan zbiorów organizmów
	static void zapisz_calosc(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki);

	static void wczytaj_calosc(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki);
};

inline void Plik_XML::Zapisz_do_pliku(const char* nazwa_pliku, std::vector<Ryba*>& wektor)
{
	TiXmlDocument doc;
	std::string str = "ryby";
	TiXmlElement* root = new TiXmlElement(str.c_str());
	doc.LinkEndChild(root);
	str = "ryba";
	TiXmlElement* wpisy_konkretnego = nullptr;
	TiXmlElement* wpis = nullptr;
	TiXmlText* tekst = nullptr;
	for (std::vector<Ryba*>::iterator iter = wektor.begin(); iter != wektor.end(); iter++)
	{
		wpisy_konkretnego = new TiXmlElement(str.c_str());
		root->LinkEndChild(wpisy_konkretnego);

		wpis = new TiXmlElement("temperatura");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->temperatura_Ps)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("glebokosc");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->glebokosc_Ps)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("x");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->x)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("y");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->y)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("kolorG");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->kolor.g)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("kolorB");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->kolor.b)).c_str());
		wpis->LinkEndChild(tekst);
	}
	doc.SaveFile(nazwa_pliku);
}
inline void Plik_XML::Zapisz_do_pliku(const char* nazwa_pliku, std::vector<Gabka*>& wektor)
{
	TiXmlDocument doc;
	std::string str = "gabki";
	TiXmlElement* root = new TiXmlElement(str.c_str());
	doc.LinkEndChild(root);
	str = "gabka";
	TiXmlElement* wpisy_konkretnego = nullptr;
	TiXmlElement* wpis = nullptr;
	TiXmlText* tekst = nullptr;
	for (std::vector<Gabka*>::iterator iter = wektor.begin(); iter != wektor.end(); iter++)
	{
		wpisy_konkretnego = new TiXmlElement(str.c_str());
		root->LinkEndChild(wpisy_konkretnego);

		wpis = new TiXmlElement("temperatura");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->temperatura_Ps)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("glebokosc");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->glebokosc_Ps)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("x");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->x)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("y");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->y)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("kolorR");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->kolor.r)).c_str());
		wpis->LinkEndChild(tekst);

		wpis = new TiXmlElement("kolorB");
		wpisy_konkretnego->LinkEndChild(wpis);
		tekst = new TiXmlText((std::to_string((*iter)->kolor.b)).c_str());
		wpis->LinkEndChild(tekst);
	}
	doc.SaveFile(nazwa_pliku);
}

inline void Plik_XML::oproznij_zbior(std::vector<Ryba*>& wektor)
{
	std::vector<Ryba*>::iterator it = wektor.begin();
	while (it != wektor.end())
	{
		delete (*it);
		it = wektor.erase(it);
	}
}
inline void Plik_XML::oproznij_zbior(std::vector<Gabka*>& wektor)
{
	std::vector<Gabka*>::iterator it = wektor.begin();
	while (it != wektor.end())
	{
		delete (*it);
		it = wektor.erase(it);
	}
}

inline void Plik_XML::wczytaj(TiXmlDocument& doc)
{
	try
	{
		std::string blad = "nie wczytano pliku\n";
		if (!doc.LoadFile())
			throw blad;
	}
	catch (std::string& blad)
	{
		std::cout << blad;
		return;
	}
}

inline bool Plik_XML::Wczytaj_z_pliku(const char* nazwa_pliku, std::vector<Ryba*>& wektor)
{
	oproznij_zbior(wektor);
	TiXmlDocument doc(nazwa_pliku);
	wczytaj(doc);
	TiXmlHandle uchwyt_Doc(&doc);
	TiXmlHandle uchwyt_korzen = uchwyt_Doc.FirstChildElement("ryby").Element();
	std::string str = "ryba";
	TiXmlElement* uchwyt_konkretnego_organizmu = uchwyt_korzen.FirstChildElement(str.c_str()).Element();
	TiXmlElement* uchwyt_wpisu = nullptr;
	while (uchwyt_konkretnego_organizmu)
	{
		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("temperatura");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int temperatura = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("glebokosc");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int glebokosc = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("x");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int x = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("y");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int y = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("kolorG");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int KolorG = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("kolorB");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int KolorB = std::stoi(str);

		sf::Color kolor(0, KolorG, KolorB);
		wektor.push_back(new Ryba(temperatura, glebokosc, x, y, kolor));
		uchwyt_konkretnego_organizmu = uchwyt_konkretnego_organizmu->NextSiblingElement();
	}
	return true;
}
inline bool Plik_XML::Wczytaj_z_pliku(const char* nazwa_pliku, std::vector<Gabka*>& wektor)
{
	oproznij_zbior(wektor);
	TiXmlDocument doc(nazwa_pliku);
	wczytaj(doc);
	TiXmlHandle uchwyt_Doc(&doc);
	TiXmlHandle uchwyt_korzen = uchwyt_Doc.FirstChildElement("gabki").Element();
	std::string str = "gabka";
	TiXmlElement* uchwyt_konkretnego_organizmu = uchwyt_korzen.FirstChildElement(str.c_str()).Element();
	TiXmlElement* uchwyt_wpisu = nullptr;
	while (uchwyt_konkretnego_organizmu)
	{
		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("temperatura");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int temperatura = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("glebokosc");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int glebokosc = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("x");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int x = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("y");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int y = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("kolorR");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int KolorR = std::stoi(str);

		uchwyt_wpisu = uchwyt_konkretnego_organizmu->FirstChildElement("kolorB");
		if (!uchwyt_wpisu)
			return false;
		str = uchwyt_wpisu->GetText();
		int KolorB = std::stoi(str);

		sf::Color kolor(KolorR, 0, KolorB);
		wektor.push_back(new Gabka(temperatura, glebokosc, x, y, kolor));
		uchwyt_konkretnego_organizmu = uchwyt_konkretnego_organizmu->NextSiblingElement();
	}
	return true;
}

inline void Plik_XML::zapisz_calosc(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki)
{
	const char nazwa_pliku_ryby[] = "_ryby.xml\0";
	const char nazwa_pliku_gabki[] = "_gabki.xml\0";
	Zapisz_do_pliku(nazwa_pliku_ryby, ryby);
	Zapisz_do_pliku(nazwa_pliku_gabki, gabki);
}

inline void Plik_XML::wczytaj_calosc(std::vector<Ryba*>& ryby, std::vector<Gabka*>& gabki)
{
	const char nazwa_pliku_ryby[] = "_ryby.xml\0";
	const char nazwa_pliku_gabki[] = "_gabki.xml\0";
	if (!Wczytaj_z_pliku(nazwa_pliku_ryby, ryby))
		std::cout << "nie udalo sie wczytac zbioru ryb \n";
	if(!Wczytaj_z_pliku(nazwa_pliku_gabki, gabki))
		std::cout << "nie udalo sie wczytac zbioru gabek \n";
}

