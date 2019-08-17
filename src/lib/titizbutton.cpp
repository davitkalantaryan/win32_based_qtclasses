#include "stdafx.h"
#include "../headers/titizbutton.h"


TitizButton::TitizButton( QWidgetPrivate* parent, const QString& a_String, UCHAR a_Shape, COLORREF a_Color )
	:	TitizControl(parent, a_Shape, a_Color),
		m_text(a_String)
{

	m_ColorT = m_ColorF + 1000;

	m_BrushT = CreateSolidBrush( m_ColorT );

	m_PenT  = CreatePen( PS_SOLID, 5, RGB(0,0,0) );
	m_PenF  = CreatePen( PS_SOLID, 3, RGB(100,100,100) );
}



TitizButton::~TitizButton()
{

	DeleteObject( m_PenF );
	DeleteObject( m_PenT );
	DeleteObject( m_BrushT );

}



int TitizButton::CreateProt( )
{

	TitizControl::CreateProt2( L"_QPSHBUTTON_", m_text.GetString(), WS_CHILD, 101, 1, 200, 50 );
	
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



int TitizButton::DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis )
{

	//static HPEN aPen  = CreatePen( PS_DASH, 1, RGB(60,60,60) );

	/*
	 typedef struct tagLOGPEN { 
		UINT lopnStyle; 
		POINT lopnWidth; 
		COLORREF lopnColor; 
		} LOGPEN;
	 */

	LOGPEN lpPen;
	POINT aPoint;

	aPoint.x = 0;
	aPoint.y = 0;

	lpPen.lopnStyle = PS_DOT;
	lpPen.lopnWidth = aPoint;
	lpPen.lopnColor = RGB(60,60,60);

	static HPEN aPen  = CreatePenIndirect( &lpPen );


	char vBuff[51];


	if( m_bIsChecked )
	{
		SelectObject( pdis->hDC, m_BrushT );
		SelectObject( pdis->hDC, m_PenT );
		SetBkColor( pdis->hDC, m_ColorT );
	}
	else
	{
		SelectObject( pdis->hDC, m_BrushF );
		SelectObject( pdis->hDC, m_PenF );
		SetBkColor( pdis->hDC, m_ColorF );
	}

	if( m_cDrawStyle )// shape is eliptical
	{
		if( !Ellipse( 
					pdis->hDC, 
					pdis->rcItem.left + 5, pdis->rcItem.top + 5, 
					pdis->rcItem.right - 5, pdis->rcItem.bottom - 5 ) )
		{
			return FALSE;
		}


		if( GetFocus() == m_hWnd )
		{
			SelectObject( pdis->hDC, aPen );

			if( !Ellipse( 
						pdis->hDC, 
						pdis->rcItem.left + 8, pdis->rcItem.top + 8, 
						pdis->rcItem.right - 8, pdis->rcItem.bottom - 8 ) )
			{
				return FALSE;
			}
		}
	}
	else
	{
		if( !Rectangle( 
					pdis->hDC, 
					pdis->rcItem.left + 5, pdis->rcItem.top + 5, 
					pdis->rcItem.right - 5, pdis->rcItem.bottom - 5 ) )
		{
			return FALSE;
		}

		if( GetFocus() == m_hWnd )
		{
			SelectObject( pdis->hDC, aPen );

			if( !Rectangle( 
						pdis->hDC, 
						pdis->rcItem.left + 8, pdis->rcItem.top + 8, 
						pdis->rcItem.right - 8, pdis->rcItem.bottom - 8 ) )
			{
				return FALSE;
			}
		}
	}
	

	GetWindowText( pdis->hwndItem, vBuff, 50 );

	DrawText( pdis->hDC, vBuff, -1, &(pdis->rcItem), DT_CENTER|DT_SINGLELINE|DT_VCENTER);

	howCnt = 1;

	return TRUE;

}

