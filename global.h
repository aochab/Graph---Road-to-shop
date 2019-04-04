#ifndef _GLOBAL_INCLUDE_FILE_
#define _GLOBAL_INCLUDE_FILE_

typedef struct tagQFIFOItem
{
	int n_Key; 
	tagQFIFOItem* pNext; 
}QFIFOItem;

#define QFIFOITEM QFIFOItem

#endif
