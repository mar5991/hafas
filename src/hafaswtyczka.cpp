#include <iostream>
#include <cstdlib>
#include <cmath>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <vector>
#include "../hafaswtyczka.hpp"
using namespace std;
void hafaswtyczka::wczytajliniefde(int nkol, string keytln)
{
	int s1=haf->kursdlugosc(nkol);
	for(int i=1; i<s1; i++)
	{
		int t1=haf->getpunkt_wkurs(nkol, i);
		int beft1=haf->getpunkt_wkurs(nkol, i-1);
		if(haf->getpktx(t1)>10 && haf->getpktx(beft1)>10)
			if(zal2.find(pair<string,string>(zal1[beft1], zal1[t1]))==zal2.end())
			{
				if(zal2.find(pair<string,string>(zal1[t1], zal1[beft1]))==zal2.end())
				{
					string sio;
					cout<<"SLN "<<zal1[t1]<<" "<<zal1[beft1]<<endl;
					dat foo;
					sio=foo.get(1);
					cout<<"SPP "<<sio<<" "<<keytln<<" "<<"relation"<<endl;
					dat foo3;
					zal2[pair<string,string>(zal1[t1], zal1[beft1])]=sio;
				}
			}
	}
				
}
void hafaswtyczka::wczytajsciezkefde(int nkol, string keytln)
{
		int t1=haf->getsciezka_start(nkol);
		int beft1=haf->getsciezka_stop(nkol);
		if(haf->getpktx(t1)>10 && haf->getpktx(beft1)>10)
			if(zal2.find(pair<string,string>(zal1[beft1], zal1[t1]))==zal2.end())
			{
				if(zal2.find(pair<string,string>(zal1[t1], zal1[beft1]))==zal2.end())
				{
					string sio;
					cout<<"SLN "<<zal1[t1]<<" "<<zal1[beft1]<<endl;
					dat foo;
					sio=foo.get(1);
					cout<<"SPP "<<sio<<" "<<keytln<<" "<<"way"<<endl;
					dat foo3;
					zal2[pair<string,string>(zal1[t1], zal1[beft1])]=sio;
				}
			}
}
hafaswtyczka::hafaswtyczka(hafas_center* hafa, string keynpkt, string keytln) : haf(hafa)
{
	int s1=haf->pktsize();
	for(int i=0; i<s1; i++)
	{
		long long ala=haf->getpktx(i);
		long long bea=haf->getpkty(i);
		string nazwa=haf->getpktnazwa(i);
		if(zal1.find(i)==zal1.end())
		{
			double ala2=ala/1000000.0;
			double bea2=bea/1000000.0;
			ala2-=21.1;
			bea2-=52.5;
			ala2*=10000;
			bea2*=-10000;
			bea2/=0.62;
			string alpha;
			cout<<"SPK "<<ala2<<" "<<bea2<<endl;
			dat foo;
			alpha=foo.get(1);
			cout<<"SPP "<<alpha<<" "<<keynpkt<<" "<<nazwa<<endl;
			dat foo2;
			zal1[i]=alpha;
		}
	}
	s1=haf->kursize();
	for(int i=0; i<s1; i++)
	{
		wczytajliniefde(i, keytln);
	}
	int s2=haf->drosize();
	for(int i=0; i<s2; i++)
	{
		wczytajsciezkefde(i, keytln);
	}
}
void hafaswtyczka::generujsiec2(int idstart, int time, string keydrz, string keytime)
{
	vector <hafas_out1> ddd=haf->dijkstra2(idstart, time);
	int s1=ddd.size();
	for(int i=0; i<s1; i++)
	{
		if(ddd[i].klasa==0)
		{
			if(ddd[i].pstart!=-1)
			{
				int pu1=ddd[i].pstart;
				int pu2=ddd[i].pstop;
				int zik=ddd[i].zid;
				int p1=haf->getpunkt_wkurs(zik, pu1);
				int p2=haf->getpunkt_wkurs(zik, pu2);
				int pt=haf->getodjazd(zik, pu2);
				cout<<"SPP "<<zal1[i]<<" "<<keytime<<" "<<pt/60<<endl;
				dat foo3;
				if(zal1.find(p1)!=zal1.end() && zal1.find(p2)!=zal1.end())
				{
					if(zal2.find(pair<string,string>(zal1[p1],zal1[p2]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p1],zal1[p2])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p1],zal1[p2])]<<" "<<keytime<<" "<<pt/60<<endl;
						dat foo9;
					}
					if(zal2.find(pair<string,string>(zal1[p2],zal1[p1]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p2],zal1[p1])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p2],zal1[p1])]<<" "<<keytime<<" "<<pt/60<<endl;
						dat foo9;
					}
				}
			}
		}
		else
		{
				int pt=ddd[i].zid;
				cout<<"SPP "<<zal1[i]<<" "<<keytime<<" "<<pt/60<<endl;
				dat foo3;
				int p1=ddd[i].pstart;
				int p2=ddd[i].pstop;
				if(zal1.find(p1)!=zal1.end() && zal1.find(p2)!=zal1.end())
				{
					if(zal2.find(pair<string,string>(zal1[p1],zal1[p2]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p1],zal1[p2])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p1],zal1[p2])]<<" "<<keytime<<" "<<pt/60<<endl;
						dat foo9;
					}
					if(zal2.find(pair<string,string>(zal1[p2],zal1[p1]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p2],zal1[p1])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p2],zal1[p1])]<<" "<<keytime<<" "<<pt/60<<endl;
						dat foo9;
					
					}
				}
		}
	}
}
string hafaswtyczka::generujsiec3(int idstart, int idstop, int time, string keydrz, string keytime)
{
	vector <hafas_out1> ddd=haf->dijkstra1(idstart, idstop, time);
	string wynik;
	string wynikakt;
	int s1=ddd.size();
	for(int i=0; i<s1; i++)
	{
		if(ddd[i].klasa==0)
		{
			if(ddd[i].pstart!=-1)
			{
				int pu1=ddd[i].pstart;
				int pu2=ddd[i].pstop;
				int zik=ddd[i].zid;
				int p1=haf->getpunkt_wkurs(zik, pu1);
				int p2=haf->getpunkt_wkurs(zik, pu2);
				int pt=haf->getodjazd(zik, pu2);
				string wynkand=haf->getkurs_name(zik);
				if(wynkand!=wynikakt)
				{
					wynikakt=wynkand;
					wynik+=wynikakt+" ";
				}
				cout<<"SPP "<<zal1[i]<<" "<<keytime<<" "<<pt/60<<endl;
				dat foo3;
				if(zal1.find(p1)!=zal1.end() && zal1.find(p2)!=zal1.end())
				{
					if(zal2.find(pair<string,string>(zal1[p1],zal1[p2]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p1],zal1[p2])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
					}
					if(zal2.find(pair<string,string>(zal1[p2],zal1[p1]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p2],zal1[p1])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
					}
				}
			}
		}
		else
		{
				int pt=ddd[i].zid;
				cout<<"SPP "<<zal1[i]<<" "<<keytime<<" "<<pt/60<<endl;
				dat foo3;
				int p1=ddd[i].pstart;
				int p2=ddd[i].pstop;
				if(zal1.find(p1)!=zal1.end() && zal1.find(p2)!=zal1.end())
				{
					if(zal2.find(pair<string,string>(zal1[p1],zal1[p2]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p1],zal1[p2])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
					}
					if(zal2.find(pair<string,string>(zal1[p2],zal1[p1]))!=zal2.end())
					{
						cout<<"SPP "<<zal2[pair<string,string>(zal1[p2],zal1[p1])]<<" "<<keydrz<<" tak"<<endl;
						dat foo;
					}
				}
		}
	}
	return wynik;
}
map<int, string> hafaswtyczka::lg1()
{
	return zal1;
}
map<pair <string, string>, string> hafaswtyczka::lg2()
{
	return zal2;
}
/*void generujsiec(int idstart, int time, hafas_center* haf)
{
	map <int, string> listka;
	map <pair <string, string>, string> zal2;
	generujsiec2(idstart, time, haf, listka, zal2);
}*/
