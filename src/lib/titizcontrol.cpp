#include "stdafx.h"
#include "../headers/titizcontrol.h"

#include "../headers/qapplication.h"


TitizControl::TitizControl( QWidgetPrivate* parent, UCHAR a_Shape, COLORREF a_Color )
	:	QWidgetPrivate(_LAYT_NOT_NEEDED_,0,parent),
		m_cDrawStyle( a_Shape ),
		m_bIsChecked(0),
		m_ColorF(a_Color)
{
	m_BrushF = CreateSolidBrush( m_ColorF );
}



TitizControl::~TitizControl()
{
	DeleteObject( m_BrushF );
}



int TitizControl::CreateProt2(const wchar_t* a_ClassName, const wchar_t* a_WndText, 
							  DWORD a_dwStyles, int left, int top, int nWidth, int nHeight)
{

	m_hWnd = CreateWindowW(
		a_ClassName,
		a_WndText,
		a_dwStyles | BS_OWNERDRAW,
		left, top, nWidth, nHeight,
		m_pParent->GetHWND(),
		(HMENU) m_lCntrlIndex,
		QApplication::GetInstance(),
		NULL);
	
	
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



UCHAR TitizControl::IsChecked()const
{
	return m_bIsChecked;
}



int TitizControl::DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis )
{


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
	}
	

	GetWindowText( pdis->hwndItem, vBuff, 50 );

	DrawText( pdis->hDC, vBuff, -1, &(pdis->rcItem), DT_CENTER|DT_SINGLELINE|DT_VCENTER);

	howCnt = 1;

	return TRUE;

}



LRESULT CALLBACK TitizControl::PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam )
{

	
	switch( message ) 
	{
	case WM_LBUTTONDOWN:

		m_bIsChecked = 1;
		UpdateWindow( m_hWnd );
		return 0;

		break;

	case WM_LBUTTONUP:

		m_bIsChecked = 0;
		UpdateWindow( m_hWnd );
		return 0;

		break;		

	default:
		break;
	
	}

	return 0;	
}

