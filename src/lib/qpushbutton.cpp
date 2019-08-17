/*
 * File:			qpushbutton.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qpushbutton.h"
#include "headers/qlayout.h"
#include "headers/qapplication.h"


QPushButton::QPushButton( QWidget* parent )
	:	QAbstractButton( 0,0,parent ),
		m_text(L""),
		m_dwBkColor( COLOR_3DFACE )
{
}


QPushButton::QPushButton( const QString& text, QWidget* parent )
	:	QAbstractButton( 0,0,parent ),
		m_text(text),
		m_dwBkColor( RGB(0,0,255) )
{
}


QPushButton::~QPushButton()
{
}


int QPushButton::CreateProt( )
{
	QWidget* pParentWidget = dynamic_cast<QWidget*>(m_pParent);
	HWND aParWnd = NEWNULLPTR2;

	if(pParentWidget){
		aParWnd = pParentWidget->GetHWND();
	}

	//// Piti lock arvi
	//QApplication::SetObjCreating( this );

	m_hWnd = CreateWindowW(
		L"_QPSHBUTTON_",			// Class name
		m_text.GetString(),			// button text
		WS_VISIBLE | WS_CHILD ,		// styles
		1, 1, 80, 25,				// Coordinates
		aParWnd,					// Parent window
		(HMENU) m_lCntrlIndex,		// Menu or child index
		//NULL,						// May be hInstance will be added
		QApplication::GetInstance(),
		NULL						// Create info in WM_CREATE
		);
	

	//QApplication::SetObjCreating( 0 );
	/// Lock@ piti bacvi
	
	if( !m_hWnd )
	{
		return __CREATION_ERROR;
	}
#ifdef _WIN64
	SetWindowLongPtr( m_hWnd, GWLP_USERDATA, (LONG_PTR)this );
#else
	SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );
#endif

	if( m_bIsVisible )
	{
		ShowWindow( m_hWnd, SW_SHOW );
	}
	else
	{
		ShowWindow( m_hWnd, SW_HIDE );
	}
	UpdateWindow( m_hWnd );

	return 0;

}
