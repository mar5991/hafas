#include "hafas.hpp"
#ifndef READZTM_HPP
#define READZTM_HPP
class readztm
{
	public:
	hafas_center* haf;
	map <string, int> pktzal;
	vector <pair <long long, long long> > dati;
	readztm (string sciez, hafas_center* h) : haf(h)
	{
		fstream plik;
		plik.open(sciez.c_str());
		char data[100000];
		while(plik.getline(data,100000))
		{
			stringstream plt;
			plt<<data;
			string lll;
			plt>>lll;
			int s9=lll.size();
			string roftl;
			for(int i=1; i<s9; i++)
			{
				roftl+=lll[i];
			}
			if(roftl=="LL")
				readll(roftl, plik);
			else
			{
				if(roftl=="ZP")
					readzp(roftl, plik);
				else
					readobszar(roftl, plik);
			}
		}
	}
	private:
	string doprzecinka(stringstream& ttt)
	{
		bool ok=1;
		string lol;
		string wynik;
		int licznik=0;
		while(ok && ttt>>lol)
		{
			if(licznik>0)
				wynik+="_";
			wynik+=lol;
			licznik++;
			if(lol.length()>0)
				if(lol[lol.length()-1]==',')
					ok=0;
		}
		string wynik2;
		for(int i=0; i<(wynik.length()-1); i++)
			wynik2+=wynik[i];
		return wynik2;
	}

	void readobszar(string nazwa, fstream& plik)
	{
		nazwa="#"+nazwa;
		char data[100000];
		bool ok=1;
		while(ok && plik.getline(data, 100000))
		{
			stringstream plt;
			plt<<data;
			string lll;
			plt>>lll;
			if(lll==nazwa)
				ok=0;
		}
	}

	void readwk(string nazwa, fstream& plik, string nazwa2)
	{
		vector <kurs_suchy> listka;
		nazwa="#"+nazwa;
		char data[100000];
		bool ok=1;
		while(ok && plik.getline(data, 100000))
		{
			stringstream plt;
			plt<<data;
			string lll;
			plt>>lll;
			if(lll==nazwa)
				ok=0;
			else
			{
				string id;
				plt>>id;
				string type;
				plt>>type;
				string time;
				plt>>time;
				kurs_suchy foo;
				int czas=get_times(time)*60;
				if(czas<(3*60*60))
					czas+=(1440*60);
				foo.przyjazd=czas;
				foo.odjazd=czas;
				foo.punkt_id=pktzal[id];
				listka.push_back(foo);
				if(!plt.eof())
				{
					string zik;
					plt>>zik;
					if(zik=="P")
					{
						if(type=="DP")
						{
							haf->dodajkurs(listka, 0, nazwa2);
						}
						listka.clear();
					}
				}
			}
		}
	}

	void pominlinie(int liczba, fstream& plik)
	{
		char data[100000];
		for(int i=0; i<liczba; i++)
		{
			plik.getline(data, 100000);
		}
	}
	string podkr(char* data)
	{
		stringstream zonk;
		zonk<<data;
		int licznik=0;
		string tmp;
		string wynik;
		while(zonk>>tmp)
		{
			if(licznik>0)
				wynik+="_";
			wynik+=tmp;
			licznik++;
		}
		return wynik;
	}
	void readll(string nazwa, fstream& plik)
	{
		nazwa="#"+nazwa;
		char data[100000];
		bool ok=1;
		string nazwa1;
		while(ok && plik.getline(data, 100000))
		{
			stringstream plt;
			plt<<data;
			string lll;
			plt>>lll;
			if(lll==nazwa)
				ok=0;
			if(lll=="*WK")
				readwk("WK", plik, nazwa1);
			if(lll=="Linia:")
			{
				string pup;
				plt>>pup;
				nazwa1=pup;
			}
		}
	}

	void readpr(string nazwa, fstream& plik, string akt)
	{
		nazwa="#"+nazwa;
		char data[100000];
		bool ok=1;
		double y1=0;
		double x1=0;
		while(ok && plik.getline(data, 100000))
		{
			stringstream plt;
			plt<<data;
			string lll;
			plt>>lll;
			if(lll==nazwa)
				ok=0;
			else
			{
				int licz;
				plt>>licz;
				string gowno;
				if(!plt.eof())
					plt>>gowno;
				string alfa=doprzecinka(plt);
				string beta;
				if(!plt.eof())
					plt>>gowno;
				if(!plt.eof())
					beta=doprzecinka(plt);
					
				if(!plt.eof())
				{
					plt>>gowno;
					bool okbis=1;
					if(gowno.length()>=3)
					{
						if(gowno[2]=='y')
							okbis=0;
					}
					if(okbis)
					{
						plt>>y1;
						plt>>gowno;
						plt>>x1;
					}
				}
				long long x=1000000*x1;
				long long y=1000000*y1;
				int lol=haf->dodajpunkt(x, y, akt+lll);
				if(x>10 && y>10)
				{
					for(int j=0; j<dati.size(); j++)
					{
						double hus=distance(dati[j].first, dati[j].second, x, y);
						if(hus<400)
						{
							haf->dodajdroge(j, lol, hus, 0, "");
							haf->dodajdroge(lol, j, hus, 0, "");
						}
					}
				}
				dati.push_back(pair<long long, long long>(x, y));
				pktzal[lll]=lol;
				pominlinie(licz, plik);
			}
		}
	}

	void readzp(string nazwa, fstream& plik)
	{
		nazwa="#"+nazwa;
		char data[100000];
		bool ok=1;
		string aktnazwa;
		while(ok && plik.getline(data, 100000))
		{
			stringstream plt;
			plt<<data;
			string lll;
			plt>>lll;
			if(lll==nazwa)
				ok=0;
			else
			{
				if(lll=="*PR")
				{
					readpr("PR", plik, aktnazwa);
				}
				else
				{
					aktnazwa=doprzecinka(plt);
				}
			}
		}
	}


	
};
#endif
