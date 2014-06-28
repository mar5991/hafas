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
	vector <punkt_prz*> wszystkie_punkty;
	vector <droga*> wszystkie_drogi;
	vector <kurs*> wszystkie_kursy;
	vector <int> dijkstra(int start, int stop, int time, map <int, postoj_kurs*>& lista1, map<int, droga*>& lista2)
	{
		set <punkt_prz*> odwiedzone;
		map <punkt_prz*, int> czasbis;
		set <pair<int, punkt_prz*> > czas_odwiedzenia;
		czas_odwiedzenia.insert(pair<int, punkt_prz*>(time, wszystkie_punkty[start]));
		czasbis[wszystkie_punkty[start]]=time;
		while(!czas_odwiedzenia.empty())
		{
			pair <int, punkt_prz*> akt=*(czas_odwiedzenia.begin());
			odwiedzone.insert(akt.second);
			czas_odwiedzenia.erase(czas_odwiedzenia.begin());
			int s1=((akt.second)->drogi_wychodzace).size();
			for(int i=0; i<s1; i++)
			{
				droga* dro=(akt.second)->drogi_wychodzace[i];
				punkt_prz* ord=dro->pstop;
				int newtime=akt.first+((dro->odleglosc));
				if(odwiedzone.find(ord)==odwiedzone.end())
				{
					if(czasbis.find(ord)!=czasbis.end())
					{
						if(newtime<czasbis[ord])
						{
							lista2[ord->id]=dro;
							if(lista1.find(ord->id)!=lista1.end())
								lista1.erase(ord->id);
							czas_odwiedzenia.erase(pair<int, punkt_prz*>(czasbis[ord], ord));
							czas_odwiedzenia.insert(pair<int, punkt_prz*>(newtime, ord));
							czasbis[ord]=newtime;
						}
					}
					else
					{
						lista2[ord->id]=dro;
						if(lista1.find(ord->id)!=lista1.end())
							lista1.erase(ord->id);
						czas_odwiedzenia.insert(pair<int, punkt_prz*>(newtime, ord));
						czasbis[ord]=newtime;
					}
				}
			}
			s1=((akt.second)->postoje).size();
			for(int i=0; i<s1; i++)
			{
				postoj_kurs* pos=(akt.second)->postoje[i];
				if(pos->odjazd>=akt.first)
				{
					kurs* kur=pos->parent;
					int s2=kur->postoje.size();
					if(((pos->id)+1)<s2)
					{
						punkt_prz* ord=(kur->postoje[(pos->id)+1])->punkt;
						int newtime=(kur->postoje[(pos->id)+1])->przyjazd;
						if(odwiedzone.find(ord)==odwiedzone.end())
						{
							if(newtime>=akt.first)
							{
								if(czasbis.find(ord)!=czasbis.end())
								{
									if(newtime<czasbis[ord])
									{
										lista1[ord->id]=kur->postoje[(pos->id)+1];
										if(lista2.find(ord->id)!=lista2.end())
											lista2.erase(ord->id);
										czas_odwiedzenia.erase(pair<int, punkt_prz*>(czasbis[ord], ord));
										czas_odwiedzenia.insert(pair<int, punkt_prz*>(newtime, ord));
										czasbis[ord]=newtime;
									}
								}
								else
								{
									lista1[ord->id]=kur->postoje[(pos->id)+1];
									if(lista2.find(ord->id)!=lista2.end())
										lista2.erase(ord->id);
									czas_odwiedzenia.insert(pair<int, punkt_prz*>(newtime, ord));
									czasbis[ord]=newtime;
								}
							}
						}
					}
				}
			}
		}
		vector <int> wyniki(wszystkie_punkty.size());
		for(int i=0; i<wyniki.size(); i++)
			wyniki[i]=-1;
		for(int i=0; i<wyniki.size(); i++)
		{
			wyniki[i]=czasbis[wszystkie_punkty[i]];
		}
		return wyniki;
	}
	public:
	string getpktnazwa(int nkol)
	{
		return wszystkie_punkty[nkol]->nazwa;
	}
	string getkursnazwa(int nkol)
	{
		return wszystkie_kursy[nkol]->nazwa;
	}
	long long getpktx(int nkol)
	{
		return wszystkie_punkty[nkol]->wspx;
	}
	long long getpkty(int nkol)
	{
		return wszystkie_punkty[nkol]->wspy;
	}
	int kursdlugosc(int nkol)
	{
		return wszystkie_kursy[nkol]->postoje.size();
	}
	int pktsize()
	{
		return wszystkie_punkty.size();
	}
	int getsciezka_start(int id)
	{
		return wszystkie_drogi[id]->pstart->id;
	}
	int getsciezka_stop(int id)
	{
		return wszystkie_drogi[id]->pstop->id;
	}
	int getsciezka_dist(int id)
	{
		return wszystkie_drogi[id]->odleglosc;
	}

	int kursize()
	{
		return wszystkie_kursy.size();
	}
	int drosize()
	{
		return wszystkie_drogi.size();
	}
	int getodjazd(int kurs, int poz)
	{
		return wszystkie_kursy[kurs]->postoje[poz]->odjazd;
	}
	int getprzyjazd(int kurs, int poz)
	{
		return wszystkie_kursy[kurs]->postoje[poz]->przyjazd;
	}
	int getpunkt_wkurs(int kurs, int poz)
	{
		return wszystkie_kursy[kurs]->postoje[poz]->punkt->id;
	}
	string getpunkt_name(int pkt)
	{
		return wszystkie_punkty[pkt]->nazwa;
	}
	string getkurs_name(int kurs)
	{
		return wszystkie_kursy[kurs]->nazwa;
	}
	vector <hafas_out1> dijkstra1(int start, int stop, int time)
	{
		vector <hafas_out1> wyt;
		map <int, postoj_kurs*> lista1;
		map<int, droga*> lista2;
		vector <int> wynik=dijkstra(start, stop, time, lista1, lista2);
		int akt=stop;
		bool ok=1;
		while(ok)
		{
			if(lista1.find(akt)!=lista1.end())
			{
				postoj_kurs* lp1=lista1[akt];
				if(lp1->id>0)
				{
					hafas_out1 apt;
					apt.klasa=0;
					apt.pstart=(lp1->id)-1;
					apt.pstop=(lp1->id);
					apt.zid=lp1->parent->id;
					wyt.push_back(apt);
					akt=lp1->parent->postoje[(lp1->id)-1]->punkt->id;
				}
				else
				{
					ok=0;
				}
			}
			else
			{
				if(lista2.find(akt)!=lista2.end())
				{
					droga* lp1=lista2[akt];
					hafas_out1 apt;
					apt.klasa=1;
					apt.pstart=(lp1->pstart->id);
					apt.pstop=(lp1->pstop->id);
					apt.zid=wynik[akt];
					wyt.push_back(apt);
					akt=lp1->pstart->id;
				}
				else
				{
					ok=0;
				}
			}
		}
		vector <hafas_out1> wytbis;
		int s1=wyt.size();
		for(int i=s1-1; i>=0; i--)
			wytbis.push_back(wyt[i]);
		return wytbis;
	}
	vector <hafas_out1> dijkstra1a(int start, int stop, int time)
	{
		vector <hafas_out1> wyt=dijkstra1(start, stop, time);
		vector <hafas_out1> zik;
		int alo=-1;
		int s1=wyt.size();
		for(int i=0; i<s1; i++)
		{
			if(wyt[i].zid==alo && wyt[i].klasa==0)
			{
				zik[zik.size()-1].pstop=wyt[i].pstop;
			}
			else
			{
				zik.push_back(wyt[i]);
			}
			alo=wyt[i].zid;
		}
		return zik;
	}

	vector <hafas_out1> dijkstra2(int start, int time)
	{
		vector <hafas_out1> wyt;
		map <int, postoj_kurs*> lista1;
		map<int, droga*> lista2;
		vector <int> wynik=dijkstra(start, start, time, lista1, lista2);
		int s1=pktsize();
		for(int i=0; i<s1; i++)
		{
			bool terok=1;
			int akt=i;
			if(lista1.find(akt)!=lista1.end())
			{
				postoj_kurs* lp1=lista1[akt];
				if(lp1->id>0)
				{
					hafas_out1 apt;
					apt.klasa=0;
					apt.pstart=(lp1->id)-1;
					apt.pstop=(lp1->id);
					apt.zid=lp1->parent->id;
					wyt.push_back(apt);
				}
				else
				{
					terok=0;
				}
			}
			else
			{
				if(lista2.find(akt)!=lista2.end())
				{
					droga* lp1=lista2[akt];
					hafas_out1 apt;
					apt.klasa=1;
					apt.pstart=(lp1->pstart->id);
					apt.pstop=(lp1->pstop->id);
					apt.zid=wynik[i];
					wyt.push_back(apt);
				}
				else
				{
					terok=0;
				}
			}
			if(!terok)
			{
				hafas_out1 apt;
				apt.klasa=0;
				apt.pstart=-1;
				apt.pstop=-1;
				apt.zid=-1;
				wyt.push_back(apt);
			}
		}
		return wyt;
	}
	int dodajpunkt(long long wspx, long long wspy, string name)
	{
		punkt_prz* nowy=new punkt_prz;
		nowy->nazwa=name;
		nowy->wspx=wspx;
		nowy->wspy=wspy;
		nowy->id=wszystkie_punkty.size();
		wszystkie_punkty.push_back(nowy);
		return wszystkie_punkty.size()-1;
	}
	int dodajdroge(int start, int stop, int odleglosc, int typ, string szczegoly)
	{
		droga* nowa= new droga;
		nowa->typ=typ;
		nowa->szczegoly=szczegoly;
		nowa->pstart=wszystkie_punkty[start];
		nowa->pstop=wszystkie_punkty[stop];
		nowa->odleglosc=odleglosc;
		nowa->id=wszystkie_drogi.size();
		wszystkie_punkty[start]->drogi_wychodzace.push_back(nowa);
		wszystkie_punkty[stop]->drogi_wchodzace.push_back(nowa);
		wszystkie_drogi.push_back(nowa);
		return wszystkie_drogi.size()-1;
	}
	int dodajkurs(vector <kurs_suchy> data, int typ, string nazwa)
	{
		kurs* nowy=new kurs;
		nowy->typ=typ;
		nowy->nazwa=nazwa;
		nowy->id=wszystkie_kursy.size();
		int s1=data.size();
		for(int i=0; i<s1; i++)
		{
			kurs_suchy akt=data[i];
			postoj_kurs* no=new postoj_kurs;
			no->parent=nowy;
			no->punkt=wszystkie_punkty[akt.punkt_id];
			no->przyjazd=akt.przyjazd;
			no->odjazd=akt.odjazd;
			no->id=nowy->postoje.size();
			nowy->postoje.push_back(no);
			wszystkie_punkty[akt.punkt_id]->postoje.push_back(no);
		}
		wszystkie_kursy.push_back(nowy);
		return wszystkie_kursy.size()-1;
	}
	
};

struct dat
{
	vector <string> dd;
	string get(int id)
	{
		return dd[id];
	}
	dat()
	{
		char slowo[200000];
		cin.getline(slowo, 200000);
		dd=rozdziel(slowo);
	}
	int size()
	{
		return dd.size();
	}
};

#endif
