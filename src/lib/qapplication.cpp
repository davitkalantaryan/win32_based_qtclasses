/*
 * File:			qapplication.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qapplication.h"

#include <stddef.h>
#include <string.h>

#include "headers/qstring.h"

QObject*				QApplication::m_pstObjCreating		= 0;

HINSTANCE				QApplication::m_hInstance			= 0;
QString*				QApplication::m_psAppName			= 0;
size_t					QApplication::m_unVisibleObjects	= 0;

WNDCLASSEX				QApplication::m_wcBut;
WNDPROC					QApplication::m_fpBtnWndProc		= 0;



QApplication::QApplication( int argc, char* argv[] )
{

	if( !m_hInstance )
	{
		//  1.  ////////////////////////////////////////////////////////////////////////////////
		m_hInstance = GetModuleHandle(0);


		//  2.  ////////////////////////////////////////////////////////////////////////////////
		const char* pcAppPath = argv[0];
		const size_t unStrLen( strlen( pcAppPath ) );
		size_t unOffset(unStrLen - 1), unSize(0);

		for( ; unOffset > 0; --unOffset )
		{
			if( pcAppPath[unOffset] == '/' || pcAppPath[unOffset] == '\\' )
			{
				++unOffset;
				break;
			}
			else
			{
				++unSize;
			}
		}

		if( unStrLen > 3 && pcAppPath[unStrLen - 1] == 'e' && pcAppPath[unStrLen - 2] == 'x' && 
			pcAppPath[unStrLen - 3] == 'e' && pcAppPath[unStrLen - 4] == '.' )
		{
			unSize -= 4;
		}


		m_psAppName = new QString( pcAppPath + unOffset );



		//  3.  ///////////////////////////////////////////////////////////////////////////////////////		
		m_unVisibleObjects = 0;


		/// Obtaining functions addresses for all standart controls

		// 1. button
		GetClassInfoEx( NULL, TEXT("button"), &m_wcBut );
		//GetClassInfoEx( m_hInstance, TEXT("button"), &m_wcBut );
		m_fpBtnWndProc = m_wcBut.lpfnWndProc;


		////// Registering all classes
		if( !RegisteringAllClasses() )
		{
			throw;
		}


	}
}


QApplication::~QApplication()
{

	//  2.  ////
	if( m_psAppName )
	{
		delete m_psAppName;
		m_psAppName = 0;
	}


	m_unVisibleObjects = 0;

	UnRegisterAllClasses();

}



ATOM QApplication::RegisteringAllClasses()
{
	ATOM atRet;

	HICON hIcon				= LoadIcon(NULL,IDI_APPLICATION);
	HCURSOR hCursor			= LoadCursor(NULL,IDC_ARROW);
	HBRUSH hBkGround		= GetSysColorBrush(COLOR_3DFACE);
	//HBRUSH hBkGround		= CreateSolidBrush( RGB(255,0,0) );

	// 1. QWidget
	if( !( atRet = RegisterPrivate(CS_HREDRAW|CS_VREDRAW,hIcon,hCursor,hBkGround,NULL,_WINDOW_CLS_,hIcon) ) )
		return 0;


	// 1. QDialog // This is the same as QWidgetClass
	//if( !( atRet = RegisterPrivate(CS_HREDRAW|CS_VREDRAW,hIcon,hCursor,hBkGround,NULL,QWIDGET_CLASS,hIcon) ) )
	//	return 0;


	// 2. QPushButton

	HBRUSH aBrush = CreateSolidBrush( RGB(0,0,255) );


	m_wcBut.cbSize			= sizeof(m_wcBut);
    m_wcBut.lpszClassName	= _QPSHBUTTON_;
    m_wcBut.hInstance		= QApplication::m_hInstance;
    m_wcBut.lpfnWndProc		= QApplication::ButtonProcStat;

	m_wcBut.hbrBackground	= aBrush;

	m_wcBut.cbSize			= sizeof(m_wcBut);

	if( !RegisterClassEx(&m_wcBut) )
	{
		return 0;
	}


	/*WNDCLASSEX	wc;
	GetClassInfoEx( m_hInstance, _WINDOW_CLS_, &wc );
	GetClassInfoEx( m_hInstance, _QPSHBUTTON_, &wc );*/


	return atRet;

}



void QApplication::UnRegisterAllClasses()
{

	// 1. QWidget
	UnregisterClass( _WINDOW_CLS_, QApplication::m_hInstance );

}



int QApplication::exec()
{

	MSG msg;

	FreeConsole();

	if( m_unVisibleObjects )
	{
		while( GetMessage(&msg, NULL, 0, 0) ) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}



const wchar_t* QApplication::GetAppName()
{
	return m_psAppName->GetString();
}


const HINSTANCE& QApplication::GetInstance()
{
	return m_hInstance;
}



void QApplication::SetVisible()
{
	++m_unVisibleObjects;
}


void QApplication::SetHidden()
{
	if( !(--m_unVisibleObjects) )
	{
		PostQuitMessage(0);
	}
}


void QApplication::SetObjCreating( QObject* a_pObject )
{
	m_pstObjCreating = a_pObject;
}



LRESULT CALLBACK QApplication::WndProcStat(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	LRESULT lRet(0);

	BOOL bnRet;

	UCHAR ucHowCnt(0);

#ifdef _WIN64
	QObject* pObject = (QObject*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
	QObject* pObject = (QObject*)GetWindowLong( hWnd, GWL_USERDATA );
#endif

	QObject* pObjectItem = 0;

	DRAWITEMSTRUCT* pdis = 0;


	switch (message) 
	{

	case WM_NCCREATE: case WM_CREATE:
		
		if( m_pstObjCreating )
		{
			pObject = m_pstObjCreating;
			m_pstObjCreating = 0;
			lRet = pObject->PreWndProc( ucHowCnt, message, wParam, lParam );
		}

		break;

	case WM_DRAWITEM:

		pdis = (DRAWITEMSTRUCT*) lParam;

		if( pdis )
		{
#ifdef _WIN64
			pObjectItem = (QObject*)GetWindowLongPtr( pdis->hwndItem, GWLP_USERDATA );
#else
			pObjectItem = (QObject*)GetWindowLong( pdis->hwndItem, GWL_USERDATA );
#endif

			if( pObjectItem )
			{
				bnRet = pObjectItem->DrawItemMe( ucHowCnt, pdis );
			}
		}


		if( ucHowCnt == 1 )
			return bnRet ;

		
	default:

		if( pObject )
		{
			lRet = pObject->PreWndProc( ucHowCnt, message, wParam, lParam );
		}

		break;
	}


	switch( ucHowCnt )
	{
	case 0:
		return DefWindowProc( hWnd, message, wParam, lParam );

	case 1:
		return lRet;

	case 2:
		lRet = DefWindowProc( hWnd, message, wParam, lParam ) ;
		return pObject->PostWndProc( lRet, message, wParam, lParam );

	case 3:
		return pObject->PostWndProc( lRet, message, wParam, lParam );

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

}



LRESULT CALLBACK QApplication::ButtonProcStat(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	LRESULT lRet(0);

	UCHAR ucHowCnt(0);

#ifdef _WIN64
	QObject* pObject = (QObject*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
	QObject* pObject = (QObject*)GetWindowLong( hWnd, GWL_USERDATA );
#endif


	switch (message) 
	{

	case WM_NCCREATE: case WM_CREATE:
		
		if( m_pstObjCreating )
		{
			pObject = m_pstObjCreating;
			m_pstObjCreating = 0;
			lRet = pObject->PreWndProc( ucHowCnt, message, wParam, lParam );
		}

		break;

		
	default:

		if( pObject )
		{
			lRet = pObject->PreWndProc( ucHowCnt, message, wParam, lParam );
		}

		break;
	}


	switch( ucHowCnt )
	{
	case 0:
		return (*m_fpBtnWndProc)(hWnd, message, wParam, lParam);

	case 1:
		return lRet;

	case 2:
		lRet = (*m_fpBtnWndProc)(hWnd, message, wParam, lParam);
		return pObject->PostWndProc( lRet, message, wParam, lParam );

	case 3:
		return pObject->PostWndProc( lRet, message, wParam, lParam );

	default:
		return (*m_fpBtnWndProc)(hWnd, message, wParam, lParam);
	}

	//return (*m_fpBtnWndProc)(hWnd, message, wParam, lParam);

}


ATOM QApplication::RegisterWndClass(
									UINT			style,
									WNDPROC			lpfnWndProc,
									int				cbClsExtra,
									int				cbWndExtra,
									HINSTANCE		hInstance,
									HICON			hIcon,
									HCURSOR			hCursor,
									HBRUSH			hbrBackground,
									LPCTSTR			lpszMenuName,
									LPCTSTR			lpszClassName,
									HICON			hIconSm,
									const COLORREF* a_pBkColor
									)
{

	HBRUSH aBrush;

	if( a_pBkColor )
	{
		aBrush = CreateSolidBrush( *a_pBkColor );
	}
	else if( hbrBackground )
	{
		aBrush = hbrBackground;
	}
	else
	{
		aBrush = GetSysColorBrush(COLOR_3DFACE);
	}

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= style;
	wcex.lpfnWndProc	= lpfnWndProc;
	wcex.cbClsExtra		= cbClsExtra;
	wcex.cbWndExtra		= cbWndExtra;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= hIcon;
	wcex.hCursor		= hCursor;
	wcex.hbrBackground	= aBrush;
	wcex.lpszMenuName	= lpszMenuName;
	wcex.lpszClassName	= lpszClassName;
	wcex.hIconSm		= hIconSm;

	return RegisterClassEx(&wcex);

}



ATOM QApplication::RegisterPrivate(
									UINT			style,
									HICON			hIcon,
									HCURSOR			hCursor,
									HBRUSH			hbrBackground,
									LPCTSTR			lpszMenuName,
									LPCTSTR			lpszClassName,
									HICON			hIconSm
									)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= style;
	wcex.lpfnWndProc	= QApplication::WndProcStat;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= QApplication::m_hInstance;
	wcex.hIcon			= hIcon;
	wcex.hCursor		= hCursor;
	wcex.hbrBackground	= hbrBackground;
	wcex.lpszMenuName	= lpszMenuName;
	wcex.lpszClassName	= lpszClassName;
	wcex.hIconSm		= hIconSm;

	/*if( !RegisterClassExW(&wcex) )
	{
		return UNABLE_TO_REGISTER;
	}*/

	return RegisterClassEx(&wcex);

}

