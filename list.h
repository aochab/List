#ifndef _LIST_INCLUDE_
#define _LIST_INCLUDE_

#include "global.h"

typedef struct tagListItem
{
	LISTINFO* m_pInfo;		//pierwsze pole jest wskaünikiem do pola nKey w global.h
	tagListItem* m_pNext;
} ListItem;

ListItem* MakeEmptyList(); 
void Insert( ListItem* pAfter, LISTINFO* pInfo );
void InsertFront( ListItem* pList, LISTINFO* pInfo );
void Remove( ListItem* pAfter );
void RemoveFront( ListItem* pList );
int isEmpty( ListItem* pList );
ListItem* Front( ListItem* pList );
void FreeList( ListItem* pList );

ListItem* Find( ListItem* pList, const void* search, ListItem** pPrev, 
		int( __cdecl* compare )( const void* p, const void* v ) ); //wskaünik do szukanego,const void*, pPrev, wskaünik do funkcji otrzymujπcej dwa parametry const void* i zwracajπcej int

void SortList( ListItem* pList, int ( __cdecl* compare )( const void* p, const void* v ) );	//wskaünik do funkcji otrzymujπcej dwa parametry const void* i zwracajπcej int

#endif
 //__cdecl domyúlna konwencja wywo≥ywania programÛw C i C++, 

