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
	:	QObject(parent),
		m_pLayout(NEWNULLPTR2),
		m_bIsVisible		( 0 & _VISIBLE_FLAG_ ),
		m_bIsCreated		( 0 & _CREATED_FLAG_ ),
		m_bIsRegisteresd	( 0 & _REGISTER_FLAG_ ),
		m_bLaytoutNotNeeded	( 0 & _LAYT_NOT_NEEDED_ ),		
		m_bLaytCrtdOutside	( 0 & _LAYOUT_CRT_FLAG_ ),
		m_hWnd(NEWNULLPTR2),
		m_lCntrlIndex(0)
{
	if (m_bLaytoutNotNeeded)
	{
		m_bLaytCrtdOutside = 1;
	}
	else
	{
		if (m_bLaytCrtdOutside)
		{
			m_pLayout = NEWNULLPTR2;
		}
		else
		{
			m_pLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
		}

		if (!m_pLayout)
			throw; // no layout
	}


	if (parent)
	{
		QLayout* pLayout = parent->layout();

		if (pLayout)
		{
			pLayout->addWidget(this);
		}

	}
}


const HWND& QWidget::GetHWND()const
{
	return m_hWnd;
}


QWidget::QWidget( UCHAR a_Props, class QLayout* a_pLayout, QWidget* parent )
	:	QObject(parent),
		m_pLayout(NEWNULLPTR2),
		m_bIsVisible		( a_Props & _VISIBLE_FLAG_ ),
		m_bIsCreated		( a_Props & _CREATED_FLAG_ ),
		m_bIsRegisteresd	( a_Props & _REGISTER_FLAG_ ),
		m_bLaytoutNotNeeded	( a_Props & _LAYT_NOT_NEEDED_ ),	
		m_bLaytCrtdOutside	( a_Props & _LAYOUT_CRT_FLAG_ ),
		m_hWnd(NEWNULLPTR2),
		m_lCntrlIndex(0)
{
	if (m_bLaytoutNotNeeded)
	{
		m_bLaytCrtdOutside = 1;
	}
	else
	{
		if (m_bLaytCrtdOutside)
		{
			m_pLayout = a_pLayout;
		}
		else
		{
			m_pLayout = new QBoxLayout(QBoxLayout::TopToBottom, (class QWidget*)((void*)this));
		}

		if (!m_pLayout)
			throw; // no layout
	}


	if (parent)
	{
		QLayout* pLayout = parent->layout();

		if (pLayout)
		{
			pLayout->addWidget(this);
		}

	}
}



QWidget::~QWidget()
{
	if (m_bIsCreated)
		DestroyWindow(m_hWnd);

	if (!m_bLaytCrtdOutside)
		delete m_pLayout;
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


	m_pLayout->CreateAllWidgets();

	m_bIsCreated = 1;

	return 0;
}


void QWidget::SetIsVisibleProt( const UCHAR& a_ucIsVisible )
{
	m_bIsVisible = a_ucIsVisible;
}



UCHAR QWidget::IsVisibleProt()const
{
	return m_bIsVisible;
}



/*void QWidgetPrivate::SetIsCreatedProt( const UCHAR& a_ucIsCreated )
{
	m_bIsCreated = a_ucIsCreated;
}*/



UCHAR QWidget::IsCreatedProt()const
{
	return m_bIsCreated;
}



void QWidget::show()
{

	UCHAR bIsVisible;
	QWidgetPrivate* pwParent = (QWidgetPrivate*)m_pParent;

	// First the case of top up window 
	if( !m_pParent )
	{
		if( !m_bIsVisible )
		{
			bIsVisible = m_bIsVisible;
			m_bIsVisible = 1;
		}

		if( !m_bIsCreated )
		{
			if( !CreateProt() )
			{
				m_bIsCreated = 1;
			}
			else
			{
				return;
			}
		}
		else// window already created
		{
			ShowWindow( m_hWnd, SW_SHOW );
			UpdateWindow( m_hWnd );
		}


		if( !bIsVisible )
		{
			m_bIsRegisteresd = 1;;
			QApplication::SetVisible();
		}

		return;
	}
	else if( pwParent->IsCreatedProt() )
	{
		if( !m_bIsCreated )
		{
			if( !CreateProt() )
			{
				m_bIsCreated = 1;

				if( pwParent->IsVisibleProt() )
				{
					ShowWindow( m_hWnd, SW_SHOW );
					UpdateWindow( m_hWnd );
					m_bIsVisible = 1;
				}
			}

		}
	}
	else
	{
		m_bIsVisible = 1;
		return ;
	}


	//


}


void QWidget::hide()
{

	// First the case of top up window 
	if( !m_pParent )
	{
		if( m_bIsVisible )
		{
			m_bIsVisible = 0;
		}

		if( m_bIsCreated )
		{
			ShowWindow( m_hWnd, SW_HIDE );
			UpdateWindow( m_hWnd );
			QApplication::SetHidden();
		}

		return;
	}


	QWidgetPrivate* pwParent = (QWidgetPrivate*)m_pParent;

	if( pwParent->IsCreatedProt() )
	{
		if( m_bIsCreated )
		{

			ShowWindow( m_hWnd, SW_HIDE );
			UpdateWindow( m_hWnd );
			m_bIsVisible = 0;
		}
	}
	
}



class QLayout* QWidget::layout()const
{
	return m_pLayout ;
}



int QWidget::DrawItemMe( UCHAR&, DRAWITEMSTRUCT* )
{
	return 0;
}



LRESULT CALLBACK QWidget::PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam )
{
	
	switch (message) 
	{
	case WM_NCCREATE:

		m_bIsCreated = 1;

		return 0;

	case WM_NCDESTROY:
		
		howCnt = 2;
		
		break;
			

	default:
		break;
	
	}

	return 0;
	
}


LRESULT CALLBACK QWidget::PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam )
{
	
	
	switch (message) 
	{
	case WM_NCDESTROY:
		
		if( m_bIsRegisteresd )
		{
			QApplication::SetHidden();
		}

		m_bIsCreated = 0;
		
		break;
			

	default:
		break;
	
	}

	return lDef;
	
}


void QWidget::SetCntrlIndex(const LONG& a_lCntrlIndex)
{
	m_lCntrlIndex = a_lCntrlIndex;
}
