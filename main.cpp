#include "stdafx.h"
#include <stdlib.h>
#include "list.h"
#include "global.h"
#include <time.h>

#define _DEBUG_

using namespace std;

void PrintList( ListItem* pList );

int main()
{
	srand( (unsigned)time( NULL ) );
	
	ListItem* Head = MakeEmptyList();
	if( !Head )
	{
		printf( "ERROR! Head - CreatList() " );
		return 1;
	}
	
	LISTINFO* item1 = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	if( !item1 )
	{
		printf( "ERROR! item1 - malloc! " );
		return 1;
	}
	memset( item1, 0, sizeof( LISTINFO ) );
	item1->nKey = 1;
	InsertFront( Head, item1 ); 

	LISTINFO* item2 = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	if( !item2 )
	{
		printf( "ERROR! item2 - malloc! " );
		return 1;
	}
	memset( item2, 0, sizeof( LISTINFO ) );
	item2->nKey = 2321;
	InsertFront( Head, item2 );

	LISTINFO* item3 = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	if( !item3 )
	{
		printf( "ERROR! item3 - malloc! " );
		return 1;
	}
	memset( item3, 0, sizeof( LISTINFO ) );
	item3->nKey = 3;
	InsertFront( Head, item3 );

	LISTINFO* item4 = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	if( !item4 )
	{
		printf( "ERROR! item4 - malloc! " );
		return 1;
	}
	memset( item4, 0, sizeof( LISTINFO ) );
	item4->nKey = 34;
	InsertFront( Head, item4 );

	//Wstawianie elementu przed wybrany, tutaj o nKey 3
	LISTINFO key = {3};
	ListItem* pPrev = NULL;
	ListItem* p = NULL;
	p = Find( Head, &key, &pPrev, compare );

	LISTINFO* item5 = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	if( !item5 )
	{
		printf( "ERROR! item5 - malloc! " );
		return 1;
	}
	memset( item5, 0, sizeof( LISTINFO ) );
	item5->nKey = 18;

	Insert( p, item5 );
	p = NULL;
	pPrev = NULL;

	//Dodatnie dodatkowy elementów na początek listy
	for( int i = 0; i < 25; i++ )
	{
		LISTINFO* item = (LISTINFO*)malloc( sizeof( LISTINFO ) );
		if( !item )
			{
				printf( "ERROR! item%d - malloc!\n",i );
				return 1;
			}
		memset( item, 0, sizeof( LISTINFO ) );

		item->nKey = rand()%1000;
		InsertFront( Head, item );
	}

	#ifdef _DEBUG_
		PrintList( Head );
		printf( "\n\n" );
	#endif 

	SortList( Head, compare );

	//Usuwanie elementu
	key = {34};
	p = Find( Head, &key, &pPrev, compare );
	Remove( pPrev );
	p = NULL;
	pPrev = NULL;

	#ifdef _DEBUG_
		PrintList( Head );
	#endif 

	printf( "Head value: %d\n", Front( Head )->m_pInfo->nKey ); 

	FreeList( Head );
	free( Head );
	Head = NULL;

	return 0;
}

int compare( const void* p, const void* v ) //wskaźniktypu void, który wskazuje obiekt dowolnego typu
{
	if( ((LISTINFO*)p)->nKey < ((LISTINFO*)v)->nKey )
		return -1;
	if( ( (LISTINFO*)p )->nKey == ( (LISTINFO*)v )->nKey )
		return 0;
	return 1;
}

void PrintList( ListItem* pList )
{
	if( isEmpty( pList ) )
	{
		perror( "ERROR! List is empty. Can't print!" );
		return;
	}

	ListItem* p = pList->m_pNext;
	int i = 1;
	while( p )
	{
		printf( "Item number: %d, value: %d\n", i++, p->m_pInfo->nKey );
		p = p->m_pNext;
	}
}
