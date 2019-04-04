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
	PQItem* pQueue;//pQueue //kolejka realizowana w postaci stogu(kopca) //to będzie jako tablica o zadanej maksymalnej wielkości, więc musimy pamietać rozmiar maksymalny tablicy jak rozmiar całkowity kolejki prorytetowej
	int PQSize; // rozmiar kolejki priorytetiwej
	int PQCurrSize;// ilosc elementów w kolejce // to też jednoczenie indeks elementu do tablicy, gdzie wstawiany nowy element (wstawiamy o ile jest mniejsze od ilości tablicy) po wstawieniu trzeba uaktualnić kopiec od dołu do góry
} PQueue;

//ściągamy zawsze element 0, ostatni przerzucamy na 0 i uaktualniamy stog od góry do dołu, zmniejszając PQCurrSize o 1, aż do tego aż zostanie 1
PQueue* PQInit( int nSize ); // ma stowrzyć kolejke, tworzy strukture pQueue dynamicznie, dla pola pQueue przydziela pamięć o rozmiarze int, ustawia PQSize i PQCurrSize na 0
int PQisEmpty( PQueue* q); //zwraca wartość 0 lub 1, w przypadku gdy klejka jest pusta to 1, jak  jest to 0 
void PQEnqueue( PQueue* q, int nKey, double nPrior ); //wkłada do kolejki proiorytetowej, o kluczu i priorytecie jak podane
int PQDequeue( PQueue* q ); //wyciąga z kolejki 1 element który ma najwyżsczy lub najmniejszy priorytet, my zrobimy że na najwyższy priorytet!
void PQClearQueue( PQueue* q ); // ma wyczyścić kolejkę, cała zostaje, tylko jest wyczyszczona
void PQRelease( PQueue** q ); //całkowicie usuwa kolejkę zwraca w parametrze we/wy NULLA, po zwolnieniu dynamicznej tablicy i całej struktrury też zwalniamy, wrócimy do startu, że mamy wskaźnik, ale brak kolejki
void PQPrint( PQueue* q );//drukawnie kolejki/ może być na warunkowej kompilacji , inorder drukować(nie wiem co to znaczy xd), stog traktujemy jak drzwo binarne, tak to drukujemy
void DecreaseKey( PQueue* q, int nKey, double nPrior ); //(nPrior < Item.nPrior) jeśli parametr nie jest mniejszy od aktualnego tego co ma w kluczu to nic nie robie, jeśli jest to coś zmieniamu i uaktualniam
void IncreaseKey( PQueue* q, int nKey, double nPrior ); //(nPrior > Item.nPrior) jeśli nPrior nie jest silnie większy od tego item npror to nic nie robię

#endif
