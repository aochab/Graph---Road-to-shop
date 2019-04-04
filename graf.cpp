#include "stdafx.h"
#include "graf.h"
#include "pQ.h"
#include "FIFO.h"
#include "data.h"

double Dijkstra( Vertex* buildings, int nSize, int nFirst )
{
	PQueue* pQ = PQInit( nSize );
	double* d = (double*)calloc( 1, nSize * sizeof( double ) ); //distance

	buildings[nFirst].RoadToShop = (int*)calloc( nSize, sizeof( int ) );

	if( !d || !(buildings[nFirst].RoadToShop) )
	{
		printf( "ERROR! Dijkstra - no memory\n" );
		return 1;
	}

	for( int i = 0; i < nSize; i++ )
	{
		d[i] = INT_MAX; //tablica odleg³oœci danego wez³a do poszczególnych wierzcho³ków
		buildings[nFirst].RoadToShop[i] = -1;
	}

	double length = 0;
	d[nFirst] = 0;
	PQEnqueue( pQ, nFirst, 0 );
	while( !PQisEmpty( pQ ) )
	{
		int u = PQDequeue( pQ );
		
		if( buildings[u].Type )
		{
			buildings[nFirst].ShopVertex = u;
			length = d[u];
			PQRelease( &pQ ); 
			break;
		}
		else
		{
			ListItem* neighbour = buildings[u].pNeighbours->pHead;
			while( neighbour )
			{
				int i = neighbour->n_Key;
				if( d[i] > d[u] + neighbour->Length )
				{
					d[i] = d[u] + neighbour->Length; //dystans
					buildings[nFirst].RoadToShop[i] = u; //poprzednik
					PQEnqueue( pQ, i, d[i] );
				}
				neighbour = neighbour->pNext;
			}
		}
	}
	free( d );
	return length;
}

//------------------------------------------------------------------------------
void DFS( Vertex* buildings, int v, int* visited )
{
	ListItem* u = buildings[v].pNeighbours->pHead;
	visited[v] = 1;
	while( u )
	{
		u->Time = u->Length / SPEED;
		if( !visited[u->n_Key] )
			DFS( buildings, u->n_Key, visited );
		u = u->pNext;
	}
}




/*
//-----------------------------------------------------------------------
void BFS( Vertex* buildings, int v, int* visited ) //v - pierwszy wierzcho³ek
{
	QueueFIFO* q = (QueueFIFO*)calloc( 1, sizeof( QueueFIFO ) );
	if( !QFCreate( q ) )
	{
		printf( "ERROR! BFS : QFCreate\n" );
		return;
	}

	QFEnqueue( q, v );
	visited[v] = 1;
	while( !QFEmpty( q ) )
	{
		v = QFDequeue( q );
		ListItem* u = buildings[v].pNeighbours; //lista s¹siadów
		while( u ) //dopóki s¹ s¹siedzi
		{
			if( !visited[u->n_Key] )
			{
				QFEnqueue( q, u->n_Key );
				visited[u->n_Key] = 1;
			}
			u = u->pNext;
		}
	}
}
*/
