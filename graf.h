#pragma once

typedef struct tagListItem
{
	int n_Key; //Numer wierzcho�ka
	double Length; //Odleg�o��
	double Time; //Czas doj�cia
	tagListItem* pNext; //Kolejny s�siad
}ListItem;

typedef struct
{
	ListItem* pHead;
	ListItem* pTail;
}List;

typedef struct
{
	int Number;
	List* pNeighbours;//lista s�siad�w
	int Type; //1 jesli dom, 0  jesli sklep
	int ShopVertex; //wierzcholek najblizszego sklepu
	double DistanceToShop; //dlugosc drogi go sklepu
	int* RoadToShop; //droga do sklepu
	double TimeToShop; //czas dojscia do sklepu
	int NumOfNeighbours;
}Vertex;

double Dijkstra(Vertex* buildings, int nSize, int nFirst);
void DFS( Vertex* buildings, int v, int* visited );
