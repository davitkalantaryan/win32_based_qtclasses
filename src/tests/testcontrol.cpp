#include "stdafx.h"
#include "../headers/testcontrol.h"

#include <tchar.h>

#include "../headers/qlayout.h"
#include "../headers/qapplication.h"


bool	g_bPushed = false;



LRESULT CALLBACK TestWidget::PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam )
{

	char vBuff[51];

	static COLORREF aColorT = RGB(255,60,60);
	static COLORREF aColorF = RGB(255,0,0);

	static HBRUSH aBrushT = CreateSolidBrush( aColorT );
	static HBRUSH aBrushF = CreateSolidBrush( aColorF );

	static HPEN aPenT  = CreatePen( PS_SOLID, 6 , RGB(0,0,0) );
	//static HPEN aPenF  = CreatePen( PS_SOLID, 3, GetSysColor(COLOR_BTNFACE) );
	static HPEN aPenF  = CreatePen( PS_SOLID, 3, RGB(100,100,100) );

	DRAWITEMSTRUCT* pdis;
	int nTest = 0;
	
	switch (message) 
	{
		
	case WM_DRAWITEM:

		pdis = (DRAWITEMSTRUCT*) lParam;

		if( g_bPushed )
		{
			SelectObject( pdis->hDC, aBrushT );
			SelectObject( pdis->hDC, aPenT );
			SetBkColor( pdis->hDC, aColorT );
		}
		else
		{
			SelectObject( pdis->hDC, aBrushF );
			SelectObject( pdis->hDC, aPenF );
			SetBkColor( pdis->hDC, aColorF );
		}

		if( !Ellipse( 
						pdis->hDC, 
						pdis->rcItem.left + 5, pdis->rcItem.top + 5, 
						pdis->rcItem.right - 5, pdis->rcItem.bottom - 5 ) )
		{
			return FALSE;
		}

		GetWindowText( pdis->hwndItem, vBuff, 50 );

		DrawText( pdis->hDC, vBuff, -1, &(pdis->rcItem), DT_CENTER|DT_SINGLELINE|DT_VCENTER);

		howCnt = 1;

		return TRUE;

		break;

	default:
		break;
	
	}

	return 0;
	
}


/*LRESULT CALLBACK TestWidget::PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam )
{
	
	
	switch (message) 
	{
	case WM_PAINT:
		
		break;
			

	default:
		break;
	
	}

	return lDef;
	
}*/





///////////////////////////////////////////////////////////////////
TestControl::TestControl( const char* a_String, QWidget* parent )
	:	QPushButton(a_String, parent),
		m_bPushed(false)
{
}



int TestControl::CreateProt( )
{

	if( m_pParent )
	{


		m_hWnd = CreateWindowW(
			L"_QPSHBUTTON_",
			m_text.GetString(),
			WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
			//WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,
			101, 1, 200, 50,
			m_pParent->GetHWND(),
			(HMENU) m_lCntrlIndex,
			NULL, NULL);
		
		
		if( !m_hWnd )
		{
			return __CREATION_ERROR;
		}
//		SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this);
#ifdef _WIN64
		SetWindowLongPtr( m_hWnd, GWLP_USERDATA, (LONG_PTR)this );
#else
		SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );
#endif

		//ShowWindow( m_hWnd, SW_HIDE );
		UpdateWindow( m_hWnd );
	}
	
	return 0;

}


void TestControl::DrawAll( WPARAM wParam )
{

	char vBuff[51];
	HDC hdc;
	PAINTSTRUCT ps;
	RECT aRect;
	int nRet ;


	static COLORREF cColorT = RGB(255,50,0);
	static COLORREF cColorF = RGB(255,0,0);

	static HBRUSH aBrushT = CreateSolidBrush( cColorT );
	static HBRUSH aBrushF = CreateSolidBrush( cColorF );

	static HPEN pPenT  = CreatePen( PS_SOLID, 8 , RGB(0,0,0) );
	//static HPEN pPenF  = CreatePen( PS_SOLID, 10, GetSysColor(COLOR_BTNFACE) );
	static HPEN pPenF  = CreatePen( PS_SOLID, 1, RGB(50,50,50) );


	hdc = wParam ? (HDC)wParam : BeginPaint( m_hWnd, &ps );

	GetWindowText( m_hWnd, vBuff, 50 );
	GetClientRect( m_hWnd, &aRect );

	if( m_bPushed )
	{
		SetBkColor( hdc, cColorT );
		SelectObject( hdc, aBrushT );
		SelectObject( hdc, pPenT );
	}
	else
	{
		SetBkColor( hdc, cColorF );
		SelectObject( hdc, aBrushF );
		SelectObject( hdc, pPenF );
	}

	if( !Ellipse( hdc, aRect.left, aRect.top, aRect.right, aRect.bottom ) )
	{
		return;
	}

	nRet = DrawText(hdc, vBuff, -1, &aRect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	if( !wParam )
	{
		EndPaint( m_hWnd, &ps );
	}

}


LRESULT CALLBACK TestControl::PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam )
{

	int nTest = 0;
	
	switch (message) 
	{
	case WM_PAINT:

		return 0;
		
		DrawAll( wParam );
		
		howCnt = 1;
		return 0;
		
		break;


	case WM_LBUTTONDOWN:

		g_bPushed = true;

		UpdateWindow( m_hWnd );

		return 0;

		m_bPushed = true;

		//DrawAll( wParam );
		SendMessage( m_hWnd, WM_PAINT, 0, 0 );

		howCnt = 1;

		return 0;

		break;

	case WM_LBUTTONUP:

		g_bPushed = false;

		UpdateWindow( m_hWnd );

		return 0;

		m_bPushed = false;

		//DrawAll( wParam );
		SendMessage( m_hWnd, WM_PAINT, 0, 0 );

		howCnt = 1;

		return 0;

		break;
			

	default:
		break;
	
	}

	return 0;
	
}


LRESULT CALLBACK TestControl::PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam )
{

	char vBuff[51];
	HDC hdc;
	PAINTSTRUCT ps;
	RECT aRect;
	
	
	switch (message) 
	{
	case WM_PAINT:
		
		GetWindowText( m_hWnd, vBuff, 50 );

		GetWindowRect( m_hWnd, &aRect ); 

		hdc = wParam ? (HDC)wParam : BeginPaint( m_hWnd, &ps );

		DrawText( hdc, vBuff, 50, &aRect, DT_CENTER );

		UpdateWindow( m_hWnd );

		if( !wParam )
		{
			EndPaint( m_hWnd, &ps );
		}
		
		break;
			

	default:
		break;
	
	}

	return lDef;
	
}
