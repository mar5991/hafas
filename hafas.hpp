#ifndef HAFAS_HPP
#define HAFAS_HPP
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <vector>
#include "stringspecial.hpp"
using namespace std;
struct postoj_kurs;
struct droga;

struct punkt_prz
{
	string nazwa;
	int id;
	long long wspx;
	long long wspy;
	vector <postoj_kurs*> postoje;
	vector <droga*> drogi_wchodzace;
	vector <droga*> drogi_wychodzace;
};

struct droga
{
	int id;
	int typ;
	string szczegoly;
	punkt_prz* pstart;
	punkt_prz* pstop;
	int odleglosc;
};

struct kurs
{
	int id;
	int typ;
	string nazwa;
	vector <postoj_kurs*> postoje;
};

struct postoj_kurs
{
	int id;
	kurs* parent;
	punkt_prz* punkt;
	int przyjazd;
	int odjazd;
};
struct kurs_suchy
{
	int przyjazd;
	int odjazd;
	int punkt_id;
};

struct hafas_out1
{
	bool klasa;
	int pstart;
	int pstop;
	int zid;
};
class hafas_center
{
	public:
	string getpktnazwa(int nkol);
	string getkursnazwa(int nkol);
	long long getpktx(int nkol);
	long long getpkty(int nkol);
	int kursdlugosc(int nkol);
	int pktsize();
	int getsciezka_start(int id);
	int getsciezka_stop(int id);
	int getsciezka_dist(int id);
	int kursize();
	int drosize();
	int getodjazd(int kurs, int poz);
	int getprzyjazd(int kurs, int poz);
	int getpunkt_wkurs(int kurs, int poz);
	string getpunkt_name(int pkt);
	string getkurs_name(int kurs);
	vector <hafas_out1> dijkstra1(int start, int stop, int time);
	vector <hafas_out1> dijkstra1a(int start, int stop, int time);
	vector <hafas_out1> dijkstra2(int start, int time);
	int dodajpunkt(long long wspx, long long wspy, string name);
	int dodajdroge(int start, int stop, int odleglosc, int typ, string szczegoly);
	int dodajkurs(vector <kurs_suchy> data, int typ, string nazwa);
	private:
	vector <punkt_prz*> wszystkie_punkty;
	vector <droga*> wszystkie_drogi;
	vector <kurs*> wszystkie_kursy;
	vector <int> dijkstra(int start, int stop, int time, map <int, postoj_kurs*>& lista1, map<int, droga*>& lista2);
};
#endif
