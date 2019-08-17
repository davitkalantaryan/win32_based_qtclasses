/*
 * File:			qlayout.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qlayout.h"


QLayout::QLayout( class QWidget* parent )
	:	QObject( (QObject*)((void*)parent) ),
		m_wIndexOfCntrls( INITIAL_CNTRL_ID ),
		m_Controls(DESIGNED_NUMB_OF_OBJS)
{
}



QLayout::QLayout()
	:	QObject(0),
		m_wIndexOfCntrls( INITIAL_CNTRL_ID ),
		m_Controls(DESIGNED_NUMB_OF_OBJS)
{
}



QLayout::~QLayout()
{
}


void QLayout::addObject ( class QObject* a_pObject )
{
//	a_pObject->SetParentObj( a_pObject );
	a_pObject->SetParentObj( m_pParent );
	a_pObject->SetCntrlIndex( m_wIndexOfCntrls++ );
	m_Controls.push_back( a_pObject );
}



int QLayout::CreateProt()
{
	return 0;
}



LRESULT CALLBACK QLayout::PreWndProc( UCHAR& howCnt, UINT, WPARAM, LPARAM )
{
	return 0;
}



LRESULT CALLBACK QLayout::PostWndProc( LRESULT, UINT, WPARAM, LPARAM )
{
	return 0;
}



void QLayout::CreateAllCntrls ( )
{

	size_t unSize( m_Controls.size() );

	for( size_t i(0); i < unSize; ++i )
	{
		m_Controls[i]->CreateProt();
	}
}


void QLayout::SetAllVisible ( )
{
	//m_pHashCntrls.ClearData( QBoxLayout::CreateWin );
	size_t unSize( m_Controls.size() );

	for( size_t i(0); i < unSize; ++i )
	{
		if( m_Controls[i]->IsCreatedProt() && m_Controls[i]->IsVisibleProt() )
		{
			ShowWindow( m_Controls[i]->GetHWND(), SW_SHOW );
			UpdateWindow( m_Controls[i]->GetHWND() );
		}
	}
}



UCHAR QLayout::IsVisibleProt()const
{
	return m_pParent->IsVisibleProt();
}



UCHAR QLayout::IsCreatedProt()const
{
	return m_pParent->IsCreatedProt();
}



int QLayout::DrawItemMe( UCHAR&, DRAWITEMSTRUCT* )
{
	return 0;
}

