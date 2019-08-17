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
#include "headers/qwidget.h"


QLayout::QLayout( QWidget* a_parent )
	:	QObject( a_parent ),
		m_wIndexOfCntrls(INITIAL_CNTRL_ID)
{
}



QLayout::QLayout()
	:	QObject(0),
		m_wIndexOfCntrls( INITIAL_CNTRL_ID )
{
}



QLayout::~QLayout()
{
}


void QLayout::addWidget(QWidget* a_pObject, int, Qt::Alignment)
{
	a_pObject->SetParentObj( m_pParent );
	a_pObject->SetCntrlIndex( m_wIndexOfCntrls++ );
	m_allWidgets.push_back( a_pObject );
}


LRESULT CALLBACK QLayout::PreWndProc( UCHAR& howCnt, UINT, WPARAM, LPARAM )
{
	return 0;
}



LRESULT CALLBACK QLayout::PostWndProc( LRESULT, UINT, WPARAM, LPARAM )
{
	return 0;
}



void QLayout::CreateAllWidgets( )
{
	::std::list<QWidget*>::iterator itWg, itWgEnd=m_allWidgets.end();
	::std::list<QLayout*>::iterator itLy, itLyEnd = m_allLayouts.end();

	for(itWg=m_allWidgets.begin(); itWg != itWgEnd;++itWg){
		(*itWg)->CreateProt();
	}

	for (itLy = m_allLayouts.begin(); itLy != itLyEnd; ++itLy) {
		(*itLy)->CreateAllWidgets();
	}
}


void QLayout::SetAllWidgetsVisible( )
{
	QWidget* pCurWidget;
	::std::list<QWidget*>::iterator it, itEnd = m_allWidgets.end();

	for (it = m_allWidgets.begin(); it != itEnd; ++it) {
		pCurWidget = (*it);
		if (pCurWidget->IsCreatedProt() && pCurWidget->IsVisibleProt())
		{
			ShowWindow(pCurWidget->GetHWND(), SW_SHOW);
			UpdateWindow(pCurWidget->GetHWND());
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

