#include "stdafx.h"
#include "pQ.h"
#include <stdlib.h>
#include <memory.h>
#include "data.h"

int FindPath( Vertex* buildings, int nSize );

int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf( "Problem with file to read! Use file name as parametr, e.g. main.cpp input.txt\n" );
		return 1;
	}

	Vertex* buildings = NULL;
	int NumOfVertices = ReadData( argv[1], &buildings );
	if( !NumOfVertices )
	{
		printf( "There is no Vertices!\n" );
		return 1;
	}
	
	int* visited = (int*)calloc( NumOfVertices, sizeof( int ) );
	if( !visited )
	{
		printf( "ERROR! Main - no memory for visited\n" );
		return 1;
	}
	DFS( buildings, 0, visited );

	if( !FindPath( buildings, NumOfVertices ) )
	{
		printf( "Can't find path!" );
		return 1;
	}
	
	PrintData( buildings, NumOfVertices );
	printf( "The result in the file \"results.txt\"\n" );

	for( int i = 0; i < NumOfVertices; i++ )
	{
		while( ListItem* tmp = buildings[i].pNeighbours->pHead )
		{
			buildings[i].pNeighbours->pHead = tmp->pNext;
			free( tmp );
		}
	}
	free( visited );
	free( buildings );
	visited = NULL;
	buildings = NULL;
	return 0;
}

//======================================================================================
int FindPath( Vertex* buildings, int nSize )
{
	for( int i = 0; i < nSize; i++ )
	{
		if( !buildings[i].Type ) //jeœli nie jest sklepem
		{
			buildings[i].DistanceToShop = Dijkstra( buildings, nSize, i ); //najkrótsza droga
			buildings[i].TimeToShop = buildings[i].DistanceToShop / SPEED; //oblicza czas drogi do sklepu

			int* Path = (int*)calloc( nSize, sizeof( int ) ); 
			if( !Path )
			{
				printf( "ERROR! FindPath - No memory for path\n!" );
				return 0;
			}

			int temp = buildings[i].ShopVertex;
			int p = 0;

			while( Path[p - 1] != i )//zapisanie œcie¿ki (wpisuj dopóki nie dojdziesz do wierzcho³ka z którego wyszed³eœ)
			{
				Path[p++] = temp;
				temp = buildings[i].RoadToShop[temp];
			}

			for( int j = 0; j < ( p / 2 ); j++ ) //odwracanie tablicy œcie¿ki
			{
				temp = Path[j];
				Path[j] = Path[p - 1 - j];
				Path[p - 1 - j] = temp;
			}
			free( buildings[i].RoadToShop ); 
			buildings[i].RoadToShop = Path;
		}
	}
	return 1;
}
