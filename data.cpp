#include "stdafx.h"
#include <stdlib.h>
#include "graf.h"
#include "data.h"

int ReadData( const char* sFileName, Vertex** pBuildings )
{
	FILE* fin = NULL;
	if( ( fin = fopen( sFileName, "r" ) ) == NULL )
	{
		printf( "ERROR! Problem with file to read! \n" );
		return -1;
	}

	int NumOfVertices = 0; //Liczba wierzcho³ków
	int tabSize = 0; //aktualny rozmiar tablicy

	Vertex* pCopyBuilding = *pBuildings;
	
	while( !feof( fin ) )
	{
		if( NumOfVertices == tabSize )
		{
			tabSize += AllocAddMem( &pCopyBuilding, NumOfVertices );
			if( NumOfVertices == tabSize ) break;
		}

		Vertex* newVertex = &( pCopyBuilding[NumOfVertices++] );
		fscanf( fin, "%d %d %d", &newVertex->Number, &newVertex->Type, &newVertex->NumOfNeighbours );
	
		newVertex->pNeighbours = (List*)calloc( 1, sizeof( List ) );
		if( !newVertex->pNeighbours )
		{
			printf( "ERROR! ReadData - no memory for pNeighbours!\n" );
			return -1;
		}
		List* pList = newVertex->pNeighbours;
		char c;

		while( ( ( c = fgetc( fin ) ) != '\n' ) && ( c != EOF ) )
		{
			ungetc( c, fin );
			ListItem* neighbour = (ListItem*)calloc( 1, sizeof( ListItem ) );
			if( !neighbour )
			{
				printf( "ERROR! ReadData - no memory for neighbour!\n" );
				return -1;
			}
			fscanf( fin, "%d %lf", &neighbour->n_Key, &neighbour->Length );

			if( !pList->pHead ) //Jeœli nie ma ¿adnego s¹siada
				pList->pHead = neighbour;
			else
				pList->pTail->pNext = neighbour;
			pList->pTail = neighbour;
		}
	}
	fclose( fin );
	*pBuildings = pCopyBuilding;
	return NumOfVertices;
}

//-------------------------------------------------------------------------------
int AllocAddMem( Vertex** pBuildings, int nCurrentSize )
{
	int newSize = nCurrentSize + REALLOC;
	Vertex* pTemp = (Vertex*)realloc( *pBuildings, newSize * sizeof( Vertex ) );
	if( !pTemp )
	{
		printf( "ERROR!AllocAddMem - realloc problem!\n" );
		return 0;
	}
	*pBuildings = pTemp;
	memset( *pBuildings + nCurrentSize, 0, REALLOC * sizeof( Vertex ) );
	return REALLOC;
}

//-------------------------------------------------------------------------------
void PrintData( Vertex* buildings, int nSize )
{
	FILE* fout = NULL;
	if( ( fout = fopen( "results.txt", "w" ) ) == NULL )
	{
		printf( "ERROR! Problem with output file!\n" );
		return;
	}
	fprintf( fout, "Vertex:\tShop:\tDistance:\tTime:\t\tPath:" );
	for( int i = 0; i < nSize; i++ )
	{
		if( buildings[i].Type ) continue;
		fprintf( fout, "\n%d\t", buildings[i].Number );
		fprintf( fout, "%d\t", buildings[i].ShopVertex );
		fprintf( fout, "%.2lf km\t\t", buildings[i].DistanceToShop );
		fprintf( fout, "%.2lf\tmin\t", buildings[i].TimeToShop * 60 );
		int j = 0;
		while( buildings[i].RoadToShop[j] != buildings[i].ShopVertex )
			fprintf( fout, "%d -> ", buildings[i].RoadToShop[j++] );
		fprintf( fout, "%d ", buildings[i].RoadToShop[j] );
	}
	fclose( fout );
}


















/*
//-----------------------------------------------------------------
int AllocAddMemNeigh( ListItem** pNeighbours, int nCurrentSize )
{
	int newSize = nCurrentSize + REALLOC;
	ListItem* pTemp = (ListItem*)realloc( *pNeighbours, newSize * sizeof( ListItem ) );
	if( !pTemp )
	{
		printf( "ERROR!AllocAddMemNeigh - realloc problem!\n" );
		return 0;
	}
	*pNeighbours = pTemp;
	memset( *pNeighbours + nCurrentSize, 0, REALLOC * sizeof( ListItem ) );
	return REALLOC;
}

ListItem* neighbour = newVertex->pNeighbours;
int NumOfNeighbours = 0;
int tabSizeNeigh = 0;

if( NumOfNeighbours == tabSizeNeigh )
{
tabSizeNeigh += AllocAddMemNeigh( &neighbour, NumOfNeighbours );
if( NumOfNeighbours == tabSizeNeigh ) break;
}
*/



/*	if( !newVertex->pNeighbours ) //Jeœli nie ma ¿adegno s¹siada
newVertex->pNeighbours = neighbour; //dodaj
else
{
ListItem* temp = newVertex->pNeighbours; //Wskazuje na pocz¹tek tablicy s¹siadów

while( temp->pNext ) //Przechodzimy do ostatniego wczytanego wiercho³ka s¹siada
temp = temp->pNext;
temp->pNext = neighbour; //Wstawiamy na koniec listy nowego s¹siada
}*/