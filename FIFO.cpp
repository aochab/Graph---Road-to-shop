#include "stdafx.h"
#include <stdlib.h>
#include "FIFO.h"

//----------------------------------------------------------------------
int QFCreate( QueueFIFO* q )
{
	if( !q )
	{
		printf( "ERROR! QFCreate\n" );
		return 0;
	}
	q->pHead = q->pTail = NULL;
	return 1;
}

//----------------------------------------------------------------------
int QFEmpty( QueueFIFO* q )
{
	return !(q->pHead); //Je�li q nie wskazuje na pocz�tek kolejki tzn. pusta, zwraca 1
}

//----------------------------------------------------------------------
void QFEnqueue( QueueFIFO* q, int x )
{
	QFIFOITEM* p = (QFIFOITEM*)calloc( 1, sizeof( QFIFOITEM ) ); //Tworzy nowy element
	if( !p )
	{
		printf( "ERROR! QFEnqueue - no memory for new item\n" );
		return;
	}
	p->n_Key = x;				//Wstawia warto�� nowego elementu										
	if( !QFEmpty(q) )
		q->pTail->pNext = p;	//Wstawia element do kolejki
	else
		q->pHead = p;			//Je�li kolejka jest pusta, nowy element wstawiamy na pocz�tek kolejki
	
	q->pTail = p;				//Nowy element ustawiamy jako ogon kolejki
}

//----------------------------------------------------------------------
int QFDequeue( QueueFIFO* q )
{
	if( !QFEmpty( q ) )
	{
		int x = q->pHead->n_Key; //zapisuje warto�� usuwanego elementu
		QFDel( q );				 //Usuwa element
		return x;
	}
	printf( "QFDequeue - queue is empty!\n" );
	return 0;
}

//----------------------------------------------------------------------
void QFClear( QueueFIFO* q )
{
	while( !QFEmpty( q ) ) //Usuwa wszystkie elementy kolejki
		QFDel( q );
}

//----------------------------------------------------------------------
void QFRemove( QueueFIFO* q )
{
	QFClear( q );
}

//----------------------------------------------------------------------
void QFDel( QueueFIFO* q )
{
	if( !QFEmpty( q ) )
	{
		QFIFOITEM* p = q->pHead;		//Zapisuje pierwszy element
							//Je�li istnieje kolejny element
	    q->pHead = p->pNext;		//Ustawia nowy pierwszy element
		if(!q->pHead )
			q->pTail = NULL;
		
		free( p );						//Czy�ci pami�� z pierwszego elementu
	}
	else
	{
		printf( "QFDel - queue is empty!" );
		return;
	}
}

//----------------------------------------------------------------------