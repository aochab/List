#include "stdafx.h"
#include <stdlib.h>
#include "list.h"
#include "global.h"

ListItem* MakeEmptyList() //Wk�ada pusty element na Head listy
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
	p->m_pInfo = pInfo;				//Wstaw warto��
	p->m_pNext = pAfter->m_pNext;	//Wstaw adres nast�pnego elementu,z poprzedniego
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
	if( !isEmpty( pAfter ) )			//Je�li istnieje element, kt�ry chcemy usun��
	{
		ListItem* p = pAfter->m_pNext; //zapisuje element kt�ry chcemy usun��
		pAfter->m_pNext = p->m_pNext;  //przewi�zuje elementy
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

		ListItem* pBegin = pList; //wskazuje na pocz�tek listy

		while( pBegin->m_pNext ) //dop�ki nie wskazuje na NULL-a
		{
			ListItem* pMin = pBegin; //Pierwszy element przyjmujemy jako najmniejszy (Przy pierwszym przej�ciu wska�e na Head)
			ListItem* p = pBegin->m_pNext;

			while( p->m_pNext )
			{
				if( compare( p->m_pNext->m_pInfo, pMin->m_pNext->m_pInfo ) == -1 ) //If p->m_pNext < pMin->m_pNext
					pMin = p;
				p = p->m_pNext;
			}

			if( pMin != pBegin ) //Je�li najmniejszy element nie jest na pocz�tku
			{
				ListItem* pTemp = pMin->m_pNext->m_pNext;	//zapisuje na co wskazuje najmniejszy element
				pMin->m_pNext->m_pNext = pBegin->m_pNext;	//najmniejszy element wskazuje na pierwszy element po pBegin
				pBegin->m_pNext = pMin->m_pNext;			//Wstawiamy najmniejszy element przewi�zuj�c pBegin do najmniejszego
				pMin->m_pNext = pTemp;						//element przed najmniejszym wskazuje na to co wskazywa� najmniejszy
			}
			pBegin = pBegin->m_pNext; //Zaczynamy od kolejnego elementu
		}

}