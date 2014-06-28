#ifndef HAFASWTYCZKA_HPP
#define HAFASWTYCZKA_HPP
#include "hafas.hpp"
class hafaswtyczka
{
	public:
	hafaswtyczka(hafas_center* hafa, string keynpkt, string keytln);
	//generuje sieć z podanego hafas_center dla edytora TOR-EDIT, w której mamy punkty - węzły z nazwą jako wartośćią klucza keynpkt
	//typ odcinka jako klucz zdefiniowany w keytln : połączenie komunikacyjne - "relation", droga "way"
	void generujsiec2(int idstart, int time, string keydrz, string keytime);
	//generuje najlepsze trasy z idstart do reszty wierzchołków (wyruszamy o czasie time), w postaci drzewa, krawędzie drzewowe są oznaczane jako keydrz -> "tak"
	//w każdym wierzchołu jest zapisywany czas dotarcia pod kluczem keytime
	string generujsiec3(int idstart, int idstop, int time, string keydrz, string keytime);
	//generuje najlepsze trasy z idstart do idstop (wyruszamy o czasie time), w postaci ścieżki, krawędzie sciezki są oznaczane jako keydrz -> "tak"
	//w każdym wierzchołu jest zapisywany czas dotarcia pod kluczem keytime
	//zwraca ciąg tekstowy o wygenerowanej trasie
	map<int, string> lg1();
	//generuje mapę: id punktu w hafas -> id punktu w edytorze
	map<pair <string, string>, string> lg2();
	//generuje mapę: id punktów w edytorze -> id linii je łączące w edytorze (linia występuje tylko raz)
	private:
	map<int, string> zal1;
	map<pair<string, string>, string> zal2;
	hafas_center* haf;
	void wczytajliniefde(int nkol, string keytln);
	void wczytajsciezkefde(int nkol, string keytln);
};
#endif
