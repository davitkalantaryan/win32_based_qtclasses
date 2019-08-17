/*
 * File:			qwidget.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17  
 *
 */
#include "stdafx.h"
#include "headers/qwidget.h"
#include "headers/qapplication.h"
#include "headers/qboxlayout.h"



QWidget::QWidget( QWidget * parent, Qt::WindowFlags )
	:	QWidgetPrivate(0,0,parent)
{
}



QWidget::QWidget( UCHAR a_Props, class QLayout* a_pLayout, QWidget* parent )
	:	QWidgetPrivate(a_Props,a_pLayout,parent)
{
}



QWidget::~QWidget()
{
}



int QWidget::CreateProt( )
{

	static int nTry = 0;

	int			x, y;
	int			nWidth, nHeight;
	HWND		aParent;


	aParent = m_pParent ? ((QWidget*)m_pParent)->GetHWND() : 0 ;

	
	
	if( nTry++ )
	{
		y = x = 1;
		nWidth = 20;
		nHeight = 10;
	}
	else
	{
		y = x = CW_USEDEFAULT;
		nWidth = 430;
		nHeight = 655;
	}
	
	
	
	//// Piti lock arvi
	QApplication::SetObjCreating( this );
	
	m_hWnd = CreateWindowExW(
		0,										/* Extended possibilites for variation */
		L"_WINDOW_CLS_",						/* Classname */
		QApplication::GetAppName(),				/* Title Text */
		WS_OVERLAPPEDWINDOW,					/* default window */
		x,										/* Windows decides the position */
		y,										/* where the window ends up on the screen */
		nWidth,									/* The programs width */
		nHeight,								/* and height in pixels */
//		NULL,									/* The window is a child-window to desktop */
		aParent,								/* The window is a child-window to aParent */
		(HMENU)m_lCntrlIndex,					/* Menu */
		//NULL,									/* No menu */
		QApplication::GetInstance(),			/* Program Instance handler */
		NULL									/* No Window Creation data */
		);

	QApplication::SetObjCreating( 0 );
	/// Lock@ piti bacvi
	
	
	if (!m_hWnd)
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


	m_pLayout->CreateAllCntrls();

	m_bIsCreated = 1;

	return 0;
}
