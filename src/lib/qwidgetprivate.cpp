/*
 * File:			qwidgetprivate.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qwidgetprivate.h"


#include "headers/qapplication.h"
#include "headers/qboxlayout.h"

/*
#define		_VISIBLE_FLAG_		(UCHAR)0x01
#define		_CREATED_FLAG_		(UCHAR)0x02
#define		_REGISTER_FLAG_		(UCHAR)0x04
#define		_LAYOUT_CRT_FLAG_	(UCHAR)0x08
*/



QWidgetPrivate::QWidgetPrivate( UCHAR a_Props, class QLayout* a_pLayout, QWidgetPrivate* parent )
	:	QObject(parent),
		m_bIsVisible		( a_Props & _VISIBLE_FLAG_ ),
		m_bIsCreated		( a_Props & _CREATED_FLAG_ ),
		m_bIsRegisteresd	( a_Props & _REGISTER_FLAG_ ),
		m_bLaytoutNotNeeded	( a_Props & _LAYT_NOT_NEEDED_ ),
		m_pLayout( 0 ),
		m_bLaytCrtdOutside	( a_Props & _LAYOUT_CRT_FLAG_ )
{

	if( m_bLaytoutNotNeeded )
	{
		m_bLaytCrtdOutside = 1;
	}
	else
	{
		if( m_bLaytCrtdOutside )
		{
			m_pLayout = a_pLayout;
		}
		else
		{
			m_pLayout = new QBoxLayout(QBoxLayout::TopToBottom,(class QWidget*)((void*)this)) ;
		}

		if( !m_pLayout )
			throw ; // no layout
	}


	if( parent )
	{
		QLayout* pLayout = parent->layout();

		if( pLayout )
		{
			pLayout->addObject( this );
		}

	}

}



QWidgetPrivate::~QWidgetPrivate()
{
	if( m_bIsCreated )
		DestroyWindow( m_hWnd );

	if( !m_bLaytCrtdOutside)
		delete m_pLayout;
}



void QWidgetPrivate::SetIsVisibleProt( const UCHAR& a_ucIsVisible )
{
	m_bIsVisible = a_ucIsVisible;
}



UCHAR QWidgetPrivate::IsVisibleProt()const
{
	return m_bIsVisible;
}



/*void QWidgetPrivate::SetIsCreatedProt( const UCHAR& a_ucIsCreated )
{
	m_bIsCreated = a_ucIsCreated;
}*/



UCHAR QWidgetPrivate::IsCreatedProt()const
{
	return m_bIsCreated;
}



void QWidgetPrivate::show()
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



void QWidgetPrivate::hide()
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



class QLayout* QWidgetPrivate::layout()const
{
	return m_pLayout ;
}



int QWidgetPrivate::DrawItemMe( UCHAR&, DRAWITEMSTRUCT* )
{
	return 0;
}



LRESULT CALLBACK QWidgetPrivate::PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam )
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


LRESULT CALLBACK QWidgetPrivate::PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam )
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

