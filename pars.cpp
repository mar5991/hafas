#include <iostream>
#include <cstdlib>
#include <cmath>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <vector>
#include "hafas.hpp"
#include "hafaswtyczka.hpp"
#include "readztm.hpp"
using namespace std;


int main(int argc, char** argv)
{
	hafas_center haf;
	readztm ror(argv[1], &haf);
	string time=argv[2];
	int tim=toint(time);
	tim*=60;
	hafaswtyczka wty(&haf, "pname", "ktyp");
	cout<<"CLICK"<<endl;
	char abc[100000];
	cin.getline(abc, 100000);
	vector <string> roz1=rozdziel(abc);
	cin.getline(abc, 100000);
	cout<<"CLICK"<<endl;
	cin.getline(abc, 100000);
	vector <string> roz2=rozdziel(abc);
	cin.getline(abc, 100000);
	string ss1, ss2;
	cout<<"ZAZ "<<roz1[0]<<" "<<roz1[1]<<" X11_set yes"<<endl;
	cin.getline(abc, 100000);
	vector <string> roz3=rozdziel(abc);
	cout<<"ZAZ "<<roz2[0]<<" "<<roz2[1]<<" X11_set yes"<<endl;
	cin.getline(abc, 100000);
	vector <string> roz4=rozdziel(abc);
	int start=0;
	int stop=1;
	if(roz3.size()>1)
		ss1=roz3[1];
	if(roz4.size()>1)
		ss2=roz4[1];
	map <int, string> listka=wty.lg1();
	map<int, string>::iterator it1=listka.begin();
	while(it1!=listka.end())
	{
		if(it1->second==ss1)
			start=it1->first;
		if(it1->second==ss2)
			stop=it1->first;
		it1++;
	}
	for(int i=0; i<100; i++)
	{
		cout<<"UTAG1 rrr"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 timex"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 root_kolor"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 X11_color_alfa"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 X11_color_r"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 X11_color_g"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 X11_color_b"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 X11_grubosc"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 tabula"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 tabula2"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 tabula3"<<endl;
		cin.getline(abc, 100000);
		cout<<"UTAG1 X11_set"<<endl;
		cin.getline(abc, 100000);
		string lol2=wty.generujsiec3(start, stop, tim, "rrr", "timex");
		cout<<"SPEC # @ PE1 # SPP @ X11_color_alfa 255"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ PE1 # SPP @ X11_grubosc 0"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE1 # SPP @ X11_color_g 200"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE1 # SPP @ X11_color_r 200"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE1 # SPP @ X11_color_b 200"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE1 # SPP @ X11_grubosc 1"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE1 # SPP @ X11_kolejnosc a"<<endl;
		cin.getline(abc, 100000);
		
		cout<<"SPEC # @ KE3 rrr tak # SPP @ X11_color_g 0"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE3 rrr tak # SPP @ X11_color_r 0"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE3 rrr tak # SPP @ X11_color_b 0"<<endl;
		cin.getline(abc, 100000);
		
		cout<<"SPEC # @ KE3 rrr tak # SPP @ X11_grubosc 5"<<endl;
		cin.getline(abc, 100000);
		cout<<"SPEC # @ KE3 rrr tak # SPP @ X11_kolejnosc b"<<endl;
		cin.getline(abc, 100000);
		

		
		
		
		/*
		cout<<"SPP "<<listka[pozi]<<" X11_set yes"<<endl;
		cin.getline(abc, 100000);
		cout<<"ZWWW /home/marcin/programowanie/cpp/ProjektyWłasne/TOR-POLECENIA/dfs tabula rrr tak"<<endl;
		cin.getline(abc, 100000);
		cout<<"ZWWW /home/marcin/programowanie/cpp/ProjektyWłasne/TOR-POLECENIA/kolorowanie tabula 20 300"<<endl;
		cin.getline(abc, 100000);
		*/cout<<"UPD"<<endl;
		cin.getline(abc, 100000);
		string pathone="ztmix"+tostring(i)+".bmp";
		string pathtwo="ztmix"+tostring(i)+".png";
		cout<<"PRS "<<pathone<<endl;
		cin.getline(abc, 100000);
		string tekscik=tostring(tim/60)+" "+lol2;
		string pol1="convert -size 320x85 "+pathone+" -size 320x85 -font Bookman-DemiItalic -pointsize 20 -draw \"text 20,20 '"+tekscik+"'\" "+pathtwo;
		string pol2="rm "+pathone;
		system(pol1.c_str());
		system(pol2.c_str());
		tim+=360;
	}
	/*map <string, int> tabzal;
	fstream trik;
	trik.open(argv[2]);
	vector <pair <long long, long long> > dati;
	long long ala;
	while(trik>>ala)
	{
		long long bea;
		string txt1;
		string txt2;
		string txt3;
		trik>>bea;
		trik>>txt1;
		trik>>txt2;
		trik>>txt3;
		if(tabzal.find(txt2)==tabzal.end())
		{
			int alfa1=haf.dodajpunkt(ala,bea, txt1);
			for(int j=0; j<dati.size(); j++)
			{
				int hus=distance(dati[j].first, dati[j].second, ala, bea);
				if(hus<1000)
				{
					haf.dodajdroge(j, alfa1, hus, 0, "");
					haf.dodajdroge(alfa1, j, hus, 0, "");
				}
			}
			dati.push_back(pair<long long, long long>(ala, bea));
			tabzal[txt2]=alfa1;
		}
	}
	fstream pltall;
	pltall.open(argv[1]);
	string path1;
	while(pltall>>path1)
	{
		fstream plik;
		plik.open(path1.c_str());
		wczytajlinie(path1, &haf, plik, tabzal);
		plik.close();
	}
	string alfa;
	string beta;*/
	/*srand(time(NULL));
	while(1)
	{
		vector <hafas_out1> wyy=haf.dijkstra1(rand()%2000, rand()%2000, 600*60);
		int s1=wyy.size();
		for(int i=0; i<s1; i++)
		{
			if(wyy[i].klasa==0)
			{
				cout<<haf.getpunkt_name(haf.getpunkt_wkurs(wyy[i].zid, wyy[i].pstart))<<" "<<godz(haf.getodjazd(wyy[i].zid, wyy[i].pstart))<<" "<<haf.getpunkt_name(haf.getpunkt_wkurs(wyy[i].zid, wyy[i].pstop))<<" "<<godz(haf.getprzyjazd(wyy[i].zid, wyy[i].pstop))<<" "<<haf.getkurs_name(wyy[i].zid)<<endl;
			}
			else
			{
				cout<<haf.getpunkt_name(wyy[i].pstart)<<" "<<haf.getpunkt_name(wyy[i].pstop)<<endl;
			}
		}
		cout<<"***************"<<endl;
	}*/

}
