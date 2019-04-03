#include "stdafx.h"
#include <stdlib.h>
#include "list.h"
#include "global.h"

ListItem* MakeEmptyList() //Wk³ada pusty element na Head listy
{
	ListItem* pHead = (ListItem*)malloc( sizeof( ListItem ) );
	if( !pHead )
	{
		printf( "ERROR! CreatList pHead - malloc\n" );
		return 0;
	}
	memset( pHead, 0, sizeof( ListItem ) );
	return pHead;
}

//-----------------------------------------------------------------------------
void Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	ListItem* p = (ListItem*)malloc( sizeof( ListItem ) );
	if( !p )
	{
		printf( "ERROR! No memory to insert p\n" );
		return;
	}
	memset( p, 0, sizeof( ListItem ) );
	p->m_pInfo = pInfo;				//Wstaw wartoœæ
	p->m_pNext = pAfter->m_pNext;	//Wstaw adres nastêpnego elementu,z poprzedniego
	pAfter->m_pNext = p;			//Wstaw adres nowego elementu, do m_pNext poprzedniego
}

//-----------------------------------------------------------------------------
void InsertFront( ListItem* pList, LISTINFO* pInfo )
{
	Insert( pList, pInfo );
}

//-----------------------------------------------------------------------------
void Remove( ListItem* pAfter )
{
	if( !isEmpty( pAfter ) )			//Jeœli istnieje element, który chcemy usun¹æ
	{
		ListItem* p = pAfter->m_pNext; //zapisuje element który chcemy usun¹æ
		pAfter->m_pNext = p->m_pNext;  //przewi¹zuje elementy
		free( p );					   //usuwa element
	}
	else
	{
		printf( "ERROR! Remove - there is no item!\n" );
		return;
	}
}

//-----------------------------------------------------------------------------
void RemoveFront( ListItem* pList )
{
	Remove( pList );
}

//-----------------------------------------------------------------------------
int isEmpty( ListItem* pList )
{
	return !( pList->m_pNext );
}

//-----------------------------------------------------------------------------
ListItem* Front( ListItem* pList )
{
	if( !isEmpty( pList ) )
		return pList->m_pNext;

	printf( "ERROR! Front - List is empty\n" );
	return 0;
	
}

//-----------------------------------------------------------------------------
void FreeList( ListItem* pList )
{
	while( !isEmpty( pList ) )
		RemoveFront( pList );
}

//-----------------------------------------------------------------------------
ListItem* Find( ListItem* pList, const void* search, ListItem** pPrev,
		int( __cdecl* compare )( const void* p, const void* v ) )
{
	ListItem* p = pList->m_pNext;
		*pPrev = pList;
		while( p )
		{
			if( !compare( p->m_pInfo, search ) ) return p;
			else
			{
				*pPrev = p;
				p = p->m_pNext;
			}
		}
		return *pPrev = NULL;
}

//-----------------------------------------------------------------------------
void SortList( ListItem* pList, int( __cdecl *compare )( const void* p, const void* v ) )
{

		ListItem* pBegin = pList; //wskazuje na pocz¹tek listy

		while( pBegin->m_pNext ) //dopóki nie wskazuje na NULL-a
		{
			ListItem* pMin = pBegin; //Pierwszy element przyjmujemy jako najmniejszy (Przy pierwszym przejœciu wska¿e na Head)
			ListItem* p = pBegin->m_pNext;

			while( p->m_pNext )
			{
				if( compare( p->m_pNext->m_pInfo, pMin->m_pNext->m_pInfo ) == -1 ) //If p->m_pNext < pMin->m_pNext
					pMin = p;
				p = p->m_pNext;
			}

			if( pMin != pBegin ) //Jeœli najmniejszy element nie jest na pocz¹tku
			{
				ListItem* pTemp = pMin->m_pNext->m_pNext;	//zapisuje na co wskazuje najmniejszy element
				pMin->m_pNext->m_pNext = pBegin->m_pNext;	//najmniejszy element wskazuje na pierwszy element po pBegin
				pBegin->m_pNext = pMin->m_pNext;			//Wstawiamy najmniejszy element przewi¹zuj¹c pBegin do najmniejszego
				pMin->m_pNext = pTemp;						//element przed najmniejszym wskazuje na to co wskazywa³ najmniejszy
			}
			pBegin = pBegin->m_pNext; //Zaczynamy od kolejnego elementu
		}

}