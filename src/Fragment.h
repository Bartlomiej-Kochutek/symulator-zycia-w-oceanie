#pragma once
#include "Plik_XML.h"

//Klasa steruj¹ca przebiegiem ca³ej symulacji.
class Fragment_oceanu
{
	//zbiory organizmów 
	std::vector<Ryba*> ryby;
	std::vector<Gabka*> gabki;

	Ustawienia ustawienia_;

	Algorytm_genetyczny algorytm;

	Obserwator obserwator_;

	//Funkcja zmieniaj¹ca po³o¿enie organizmów; je¿eli których z nich przekroczy praw¹ stronê ekranu to pojawi siê po lewej (i na odwrót)
	void przemiesc_organizmy();

	//Funkcja dorysowuj¹ca na ekranie ("window") roœline na dnie we wspó³rzêdnej wsp_x	
	void rysuj_roslinke(sf::RenderWindow& window, float wsp_x);

	//Funkcja dorysowuj¹ca na ekranie ("window") ska³e na dnie we wspó³rzêdnej wsp_x i o wielkoœci proporcjonalnej do 'skalowanie'	
	void rysuj_skale(sf::RenderWindow& window, float skalowanie, float wsp_x);
	//Funkcja rysuj¹ca na ekranie kilka ska³
	void rysuj_fragmenty_skal(sf::RenderWindow& window);

	//Funkcja rysuj¹ca ryby, które maj¹ kszta³t trójk¹ta z kwadratem
	void rysuj_ryby(sf::RenderWindow& window);
	//Funkcja rysuj¹ca g¹bki które maj¹ kszta³t prostok¹ta z ko³em u góry	
	void rysuj_gabki(sf::RenderWindow& window);

	//Funkcja wywo³uj¹ca wszystkie funkcje wyœwietlaj¹ce coœ w oknie
	void rysuj_wszystko(sf::RenderWindow& window);

	//Funkcja obs³uguj¹ca zdarzenia w oknie symulacji. zwraca "true" jeœli okno zostanie zamkniête, w przeciwnym razie "false"
	//je¿eli u¿ytkownik wciœnie dowolny klawisz symulacja zostanie zapisana i zamkniêta
	bool zdarzenia(sf::Window& window);

	//Funkcja pobieraj¹ca parametry symulacji od u¿ytkownika
	void czy_wlasne_ustawienia();

	//Funkcja sprawdzaj¹ca czy u¿ytkownik chce wczytaæ z pliku stan symulacji
	void czy_wczytac();

	//Funkcja usuwaj¹ca nadmiar organizmów z symulacji
	void zniwiarz(std::vector<Ryba*>& wektor);
	void zniwiarz(std::vector<Gabka*>& wektor);
public:
	//Funkcja steruj¹ca ca³ym przebiegiem symulacji fragmentu oceanu
	void symuluj_fragment_oceanu();

	//Konstruktor tworz¹cy fragment oceanu. Tworzy dwa zbiory organizmów w liczbie podanej przez parametr. Organizmy s¹ losowo
	//przystosowane ale œrednia wartoœæ danego przystosowania do czynnika jest taka jak ten czynnik w oceanie
	Fragment_oceanu();
};

inline void Fragment_oceanu::przemiesc_organizmy()
{
	for (unsigned i = 0; i < ryby.size(); i++)
	{
		//okreœla maksymaln¹ prêdkoœæ z jak¹ mog¹ poruszaæ siê organizmy
		const int przesuniecie = 4;
		ryby[i]->x = (ryby[i]->x + std::rand() % (2 * przesuniecie) - przesuniecie / 2);
		if (ryby[i]->x < 0)
			ryby[i]->x += Ustawienia::rozmiar_x;
		else
			ryby[i]->x %= Ustawienia::rozmiar_x;

		ryby[i]->y = (ryby[i]->y + std::rand() % (2 * przesuniecie) - przesuniecie);
		if (ryby[i]->y < 0)
			ryby[i]->y = 0;
		else if (ryby[i]->y > Ustawienia::wysokosc_dna)
			ryby[i]->y -= przesuniecie;
	}
}

inline void Fragment_oceanu::rysuj_roslinke(sf::RenderWindow& window, float wsp_x)
{
	sf::Color kolor1(133, 193, 66);
	sf::Color kolor2(81, 119, 38);
	sf::Vertex liscie[5][2] = {
		sf::Vertex(sf::Vector2f(wsp_x, Ustawienia::rozmiar_y)), sf::Vertex(sf::Vector2f(wsp_x - 0.03 * static_cast<float>(Ustawienia::rozmiar_x), 0.9 * static_cast<float>(Ustawienia::rozmiar_y))),
		sf::Vertex(sf::Vector2f(wsp_x, Ustawienia::rozmiar_y)), sf::Vertex(sf::Vector2f(wsp_x - 0.015 * static_cast<float>(Ustawienia::rozmiar_x), 0.85 * static_cast<float>(Ustawienia::rozmiar_y))),
		sf::Vertex(sf::Vector2f(wsp_x, Ustawienia::rozmiar_y)), sf::Vertex(sf::Vector2f(wsp_x, 0.86 * static_cast<float>(Ustawienia::rozmiar_y))),
		sf::Vertex(sf::Vector2f(wsp_x, Ustawienia::rozmiar_y)), sf::Vertex(sf::Vector2f(wsp_x + 0.015 * static_cast<float>(Ustawienia::rozmiar_x), 0.87 * static_cast<float>(Ustawienia::rozmiar_y))),
		sf::Vertex(sf::Vector2f(wsp_x, Ustawienia::rozmiar_y)), sf::Vertex(sf::Vector2f(wsp_x + 0.03 * static_cast<float>(Ustawienia::rozmiar_x), 0.87 * static_cast<float>(Ustawienia::rozmiar_y))),
	};
	for (int i = 0; i < 5; i++)
	{
		liscie[i][0].color = kolor1;
		liscie[i][1].color = kolor2;
		window.draw(liscie[i], 2, sf::Lines);
	}
}

inline void Fragment_oceanu::rysuj_skale(sf::RenderWindow& window, float skalowanie, float wsp_x)
{
	sf::Vector2f pozycja(0, Ustawienia::rozmiar_y);
	sf::ConvexShape skala(7);
	skala.setPosition(pozycja);
	skala.setPoint(0, sf::Vector2f(wsp_x / skalowanie + 0.03 * static_cast<float>(Ustawienia::rozmiar_x), 0));
	skala.setPoint(1, sf::Vector2f(wsp_x / skalowanie + 0.06 * static_cast<float>(Ustawienia::rozmiar_x), 0));
	skala.setPoint(2, sf::Vector2f(wsp_x / skalowanie + 0.07 * static_cast<float>(Ustawienia::rozmiar_x), -0.03 * static_cast<float>(Ustawienia::rozmiar_y)));
	skala.setPoint(3, sf::Vector2f(wsp_x / skalowanie + 0.06 * static_cast<float>(Ustawienia::rozmiar_x), -0.05 * static_cast<float>(Ustawienia::rozmiar_y)));
	skala.setPoint(4, sf::Vector2f(wsp_x / skalowanie + 0.04 * static_cast<float>(Ustawienia::rozmiar_x), -0.06 * static_cast<float>(Ustawienia::rozmiar_y)));
	skala.setPoint(5, sf::Vector2f(wsp_x / skalowanie + 0.03 * static_cast<float>(Ustawienia::rozmiar_x), -0.04 * static_cast<float>(Ustawienia::rozmiar_y)));
	skala.setPoint(6, sf::Vector2f(wsp_x / skalowanie + 0.02 * static_cast<float>(Ustawienia::rozmiar_x), -0.02 * static_cast<float>(Ustawienia::rozmiar_y)));
	int odcien = std::rand() % 40 + 100;
	sf::Color kolor(odcien, odcien, odcien);
	skala.setFillColor(kolor);
	skala.setScale(skalowanie, skalowanie);
	window.draw(skala);
}

inline void Fragment_oceanu::rysuj_fragmenty_skal(sf::RenderWindow& window)
{
	int liczba_skal;
	if (ustawienia_.ustawienia_wlasne)
		liczba_skal = ustawienia_.Xliczba_skal;
	else
		liczba_skal = Ustawienia::liczba_skal;
	for (int i = 0; i < liczba_skal; i++)
	{
		rysuj_skale(window, ustawienia_.wylosowane_skalowania_wsp_x[0][i], ustawienia_.wylosowane_skalowania_wsp_x[1][i]);
	}
}

inline void Fragment_oceanu::rysuj_ryby(sf::RenderWindow& window)
{
	for (unsigned i = 0; i < ryby.size(); i++)
	{
		sf::CircleShape ogon(ryby[i]->rozmiar, 3);
		ogon.setFillColor(ryby[i]->kolor);
		ogon.rotate(90);
		ogon.setPosition(ryby[i]->x, ryby[i]->y);
		window.draw(ogon);

		sf::CircleShape glowa(ryby[i]->rozmiar, 4);
		glowa.setFillColor(ryby[i]->kolor);
		glowa.rotate(90);
		glowa.setPosition(ryby[i]->x + ryby[i]->rozmiar, ryby[i]->y);
		window.draw(glowa);
	}
}

inline void Fragment_oceanu::rysuj_gabki(sf::RenderWindow& window)
{
	for (unsigned i = 0; i < gabki.size(); i++)
	{
		int x = 60;
		sf::Color kolor(std::rand() % x, 0, std::rand() % x);
		sf::CircleShape gora(static_cast<int>(gabki[i]->rozmiar * 0.4), 70);
		gora.setFillColor(gabki[i]->kolor + kolor);
		gora.setPosition(gabki[i]->x - 0.2 * gabki[i]->rozmiar, gabki[i]->y - gabki[i]->rozmiar);
		window.draw(gora);

		sf::RectangleShape dol(sf::Vector2f(gabki[i]->rozmiar * 0.4, gabki[i]->rozmiar));
		dol.setFillColor(gabki[i]->kolor + kolor);
		dol.setPosition(gabki[i]->x, gabki[i]->y - 0.3 * gabki[i]->rozmiar);
		window.draw(dol);
	}
}

inline void Fragment_oceanu::rysuj_wszystko(sf::RenderWindow& window)
{
	window.clear();
	rysuj_ryby(window);
	rysuj_gabki(window);
	rysuj_fragmenty_skal(window);
	rysuj_roslinke(window, 500);
	rysuj_roslinke(window, 200);
	rysuj_roslinke(window, 50);
	window.display();
}

inline bool Fragment_oceanu::zdarzenia(sf::Window& window)
{
	sf::Event zdarzenie;
	while (window.pollEvent(zdarzenie))
	{
		if (zdarzenie.type == sf::Event::Closed)
		{
			window.close();
			return true;
		}
		if (zdarzenie.type == sf::Event::KeyPressed)
		{
			Plik_XML::zapisz_calosc(ryby, gabki);
			window.close();
			return true;
		}
		return false;
	}
	return false;
}

inline void Fragment_oceanu::czy_wlasne_ustawienia()
{
	std::cout << "Czy chcesz uzyc wlasnych ustawien ? \n1 - tak \n0 - nie \n";
	if (pobierz_unsigned(0, 1))
	{
		ustawienia_.wlasne_ustawienia();
		ustawienia_.ustawienia_wlasne = true;
	}
	else
	{
		ustawienia_.ustawienia_wlasne = false;
	}
}

inline void Fragment_oceanu::czy_wczytac()
{
	std::cout << "Czy chcesz wczytac symulacje ? \n1 - tak \n0 - nie \n";
	if (pobierz_unsigned(0, 1))
		Plik_XML::wczytaj_calosc(ryby, gabki);
}

inline void Fragment_oceanu::zniwiarz(std::vector<Ryba*>& wektor)
{
	int max_ilosc_ryb;
	if (ustawienia_.ustawienia_wlasne)
		max_ilosc_ryb = ustawienia_.Xmax_ilosc_ryb;
	else
		max_ilosc_ryb = Ustawienia::max_ilosc_ryb;
	if (wektor.size() > max_ilosc_ryb)
	{
		int ilosc = wektor.size() - max_ilosc_ryb;
		for (int i = 0; i < ilosc; i++)
		{
			delete (*(wektor.rbegin()));
			wektor.pop_back();
		}
	}
}
inline void Fragment_oceanu::zniwiarz(std::vector<Gabka*>& wektor)
{
	int max_ilosc_gabek;
	if (ustawienia_.ustawienia_wlasne)
		max_ilosc_gabek = ustawienia_.Xmax_ilosc_gabek;
	else
		max_ilosc_gabek = Ustawienia::max_ilosc_gabek;
	if (wektor.size() > max_ilosc_gabek)
	{
		int ilosc = wektor.size() - max_ilosc_gabek;
		for (int i = 0; i < ilosc; i++)
		{
			delete (*(wektor.rbegin()));
			wektor.pop_back();
		}
	}
}

inline void Fragment_oceanu::symuluj_fragment_oceanu()
{
	czy_wczytac();
	sf::RenderWindow window(sf::VideoMode(Ustawienia::rozmiar_x, Ustawienia::rozmiar_y), "Fragment oceanu");
	window.setPosition(sf::Vector2i(Ustawienia::pozycja_x, Ustawienia::pozycja_y));
	unsigned i = 0;
	int i2 = 0;
	while (window.isOpen())
	{
		clock_t zegar = clock();
		if (zdarzenia(window))
			break;
		if (i == Ustawienia::co_ile_cykli_rozmnozenie)
		{
			i2++;
			if (i2 == 5)
				i2 = 0;
			i = 0;
			algorytm.rozpocznij(ryby, gabki);
			obserwator_.naucz_siec(ryby, gabki);
			obserwator_.rozpoznaj_organizm(ryby, gabki);
		}
		przemiesc_organizmy();
		algorytm.uplyw_czasu(ryby);
		algorytm.uplyw_czasu(gabki);
		zniwiarz(ryby);
		zniwiarz(gabki);
		rysuj_wszystko(window);
		while (static_cast<float>(clock() - zegar) / CLOCKS_PER_SEC < 1.0 / ustawienia_.klatki_na_sekunde)
			_sleep(20);
		i++;
	}
}

inline Fragment_oceanu::Fragment_oceanu()
{
	czy_wlasne_ustawienia();
	int ilosc_ryb_na_poczatku;
	if (ustawienia_.ustawienia_wlasne)
		ilosc_ryb_na_poczatku = ustawienia_.Xilosc_ryb_na_poczatku;
	else
		ilosc_ryb_na_poczatku = Ustawienia::ilosc_ryb_na_poczatku;
	for (unsigned i = 0; i < ilosc_ryb_na_poczatku; i++)
	{
		sf::Color kolor(0, std::rand() % 255, std::rand() % 255);
		ryby.push_back(new Ryba(std::rand() % Ustawienia::odchylenie_temperatury - 
			Ustawienia::odchylenie_temperatury / 2 + Ustawienia::temperatura_sr,
			std::rand() % Ustawienia::odchylenie_glebokosci - Ustawienia::odchylenie_glebokosci/2 + Ustawienia::glebokosc_sr,
			std::rand() % Ustawienia::rozmiar_x, std::rand() % Ustawienia::wysokosc_dna, kolor));
	}
	int ilosc_gabek_na_poczatku;
	if (ustawienia_.ustawienia_wlasne)
		ilosc_gabek_na_poczatku = ustawienia_.Xilosc_gabek_na_poczatku;
	else
		ilosc_gabek_na_poczatku = Ustawienia::ilosc_gabek_na_poczatku;
	for(unsigned i = 0; i < ilosc_gabek_na_poczatku; i++)
	{
		sf::Color kolor(std::rand() % 55 + 170, 0, std::rand() % 155);
		gabki.push_back(new Gabka(std::rand() % Ustawienia::odchylenie_temperatury - 
			Ustawienia::odchylenie_temperatury / 2 + Ustawienia::temperatura_sr,
			std::rand() % Ustawienia::odchylenie_glebokosci - Ustawienia::odchylenie_glebokosci / 2 + Ustawienia::glebokosc_sr,
			std::rand() % Ustawienia::rozmiar_x, std::rand() % Ustawienia::szerokosc_dna + Ustawienia::wysokosc_dna, kolor));
	}
}
