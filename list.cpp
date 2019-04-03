#include "stdafx.h"
#include <stdlib.h>
#include "list.h"
#include "global.h"

ListItem* MakeEmptyList() //Insert new element on the head of the list
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
	p->m_pInfo = pInfo;			//insert value
	p->m_pNext = pAfter->m_pNext;		
	pAfter->m_pNext = p;			
}

//-----------------------------------------------------------------------------
void InsertFront( ListItem* pList, LISTINFO* pInfo )
{
	Insert( pList, pInfo );
}

//-----------------------------------------------------------------------------
void Remove( ListItem* pAfter )
{
	if( !isEmpty( pAfter ) )		
	{
		ListItem* p = pAfter->m_pNext; 
		pAfter->m_pNext = p->m_pNext;  
		free( p );					  
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

		ListItem* pBegin = pList; 

		while( pBegin->m_pNext ) 
		{
			ListItem* pMin = pBegin; //The first element has the smallest value
			ListItem* p = pBegin->m_pNext;

			while( p->m_pNext )
			{
				if( compare( p->m_pNext->m_pInfo, pMin->m_pNext->m_pInfo ) == -1 ) 
					pMin = p;
				p = p->m_pNext;
			}

			if( pMin != pBegin ) /
			{
				ListItem* pTemp = pMin->m_pNext->m_pNext;	
				pMin->m_pNext->m_pNext = pBegin->m_pNext;	
				pBegin->m_pNext = pMin->m_pNext;			
				pMin->m_pNext = pTemp;						
			}
			pBegin = pBegin->m_pNext; 
		}

}
