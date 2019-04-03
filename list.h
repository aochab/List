#ifndef _LIST_INCLUDE_
#define _LIST_INCLUDE_

#include "global.h"

typedef struct tagListItem
{
	LISTINFO* m_pInfo;		//pierwsze pole jest wskaźnikiem do pola nKey w global.h
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
		int( __cdecl* compare )( const void* p, const void* v ) ); //wskaźnik do szukanego,const void*, pPrev, wskaźnik do funkcji otrzymującej dwa parametry const void* i zwracającej int

void SortList( ListItem* pList, int ( __cdecl* compare )( const void* p, const void* v ) );	//wskaźnik do funkcji otrzymującej dwa parametry const void* i zwracającej int

#endif


