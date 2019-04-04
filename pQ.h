#pragma once
#ifndef _QUEUE_INCLUDE_
#define _QUEUE_INCLUDE_

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int nKey;
	double nPrior;
} PQItem;

typedef struct
{
	PQItem* pQueue;//pQueue //kolejka realizowana w postaci stogu(kopca) //to bêdzie jako tablica o zadanej maksymalnej wielkoœci, wiêc musimy pamietaæ rozmiar maksymalny tablicy jak rozmiar ca³kowity kolejki prorytetowej
	int PQSize; // rozmiar kolejki priorytetiwej
	int PQCurrSize;// ilosc elementów w kolejce // to te¿ jednoczenie indeks elementu do tablicy, gdzie wstawiany nowy element (wstawiamy o ile jest mniejsze od iloœci tablicy) po wstawieniu trzeba uaktualniæ kopiec od do³u do góry
} PQueue;

//œci¹gamy zawsze element 0, ostatni przerzucamy na 0 i uaktualniamy stog od góry do do³u, zmniejszaj¹c PQCurrSize o 1, a¿ do tego a¿ zostanie 1
PQueue* PQInit( int nSize ); // ma stowrzyæ kolejke, tworzy strukture pQueue dynamicznie, dla pola pQueue przydziela pamiêæ o rozmiarze int, ustawia PQSize i PQCurrSize na 0
int PQisEmpty( PQueue* q); //zwraca wartoœæ 0 lub 1, w przypadku gdy klejka jest pusta to 1, jak  jest to 0 
void PQEnqueue( PQueue* q, int nKey, double nPrior ); //wk³ada do kolejki proiorytetowej, o kluczu i priorytecie jak podane
int PQDequeue( PQueue* q ); //wyci¹ga z kolejki 1 element który ma najwy¿sczy lub najmniejszy priorytet, my zrobimy ¿e na najwy¿szy priorytet!
void PQClearQueue( PQueue* q ); // ma wyczyœciæ kolejkê, ca³a zostaje, tylko jest wyczyszczona
void PQRelease( PQueue** q ); //ca³kowicie usuwa kolejkê zwraca w parametrze we/wy NULLA, po zwolnieniu dynamicznej tablicy i ca³ej struktrury te¿ zwalniamy, wrócimy do startu, ¿e mamy wskaŸnik, ale brak kolejki
void PQPrint( PQueue* q );//drukawnie kolejki/ mo¿e byæ na warunkowej kompilacji , inorder drukowaæ(nie wiem co to znaczy xd), stog traktujemy jak drzwo binarne, tak to drukujemy
void DecreaseKey( PQueue* q, int nKey, double nPrior ); //(nPrior < Item.nPrior) jeœli parametr nie jest mniejszy od aktualnego tego co ma w kluczu to nic nie robie, jeœli jest to coœ zmieniamu i uaktualniam
void IncreaseKey( PQueue* q, int nKey, double nPrior ); //(nPrior > Item.nPrior) jeœli nPrior nie jest silnie wiêkszy od tego item npror to nic nie robiê

#endif