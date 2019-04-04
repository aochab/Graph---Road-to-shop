#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "graf.h"

#define REALLOC 3
#define SPEED 5

int ReadData( const char* sFileName, Vertex** pBuildings );
int AllocAddMem( Vertex** pBuildings, int nCurrentSize );
void PrintData( Vertex* buildings, int nSize );

