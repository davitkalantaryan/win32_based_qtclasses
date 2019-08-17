/*
 * File:			main_w32qt_test1.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17 (also renamed from test.cpp to main_w32qt_test1.cpp)
 *
 */
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QPushButton>

#include "testcontrol.h"
#include "titizbutton.h"


class MyBewButton : public QPushButton
{

public:
	MyBewButton( const char* a_String, QWidget* parent )
		:QPushButton( a_String, parent )
	{
	}

	/*LRESULT CALLBACK PreWndProc( UINT message, WPARAM wParam, LPARAM lParam )
	{

		//int nTest = 0;
		
		switch (message) 
		{
		case WM_PAINT:
			
			return -1;
			
			break;
				

		default:
			break;
		
		}

		return 0;
		
	}


	LRESULT CALLBACK PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam )
	{

		int nTest = 0;

		char vBuff[51];
		HDC hdc;
		PAINTSTRUCT ps;
		RECT aRect;
		int nRet ;
		
		switch (message) 
		{
		case WM_PAINT:
			

			hdc = wParam ? (HDC)wParam : BeginPaint( m_hWnd, &ps );

			GetWindowText( m_hWnd, vBuff, 50 );

			GetClientRect( m_hWnd, &aRect );
			SetBkColor( hdc, RGB(255,0,0) );
			nRet = DrawText(hdc, vBuff, -1, &aRect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);


			if( !wParam )
			{
				EndPaint( m_hWnd, &ps );
			}
			else
			{
				nTest = 1;
			}
			
			return lDef;
			
			break;
				

		default:
			break;
		
		}

		return 0;
	}*/
};


class TestClass
{
public:
	TestClass( int a_nMember = 0 )
		:	m_nMember( a_nMember )
	{
	}


	operator const int&()
	{
		return m_nMember ;
	}

private:
	int m_nMember;
};





class BaseCls
{

protected:
	BaseCls()
	{
		Bla();
	}

	virtual ~BaseCls(){}

	virtual void Bla()=0;

	void Bla2()
	{
		Bla();
	}
};



class Derived : public BaseCls
{
	void Bla()
	{
	}
};


#include <stdio.h>

void F1()
{
	printf( "function F1()\n" );
}


void F2()
{
	/*_asm
	{
		call F1
	};*/
}



int main( int argc, char* argv[] )
{

	/*F2();

	int nTest2 = _MSC_VER;

	nTest2 = int(2);

	int &rnTest = nTest2;

	int* pnTest = &rnTest;
	pnTest = &nTest2;

	printf( "nTest = %d\n", nTest2 );

	return 0;*/


#ifdef WIN32
	int ntest = WM_LBUTTONDOWN;
#else
#endif
	
	QApplication app( argc, argv );
	
	QWidget widget;
	
	widget.show();

	//QDialog dialog;

	//dialog.show();

	QPushButton aButton1( "AAA1", &widget );
	aButton1.show();

	//MyBewButton aButton2( "AAA2", &widget );
	//aButton2.show();

#ifdef WIN32
	//TestControl aButton3( "AAA3", &widget );
	//aButton3.show();

	//TitizButton aButton4(&widget, "AAA4" );
	//aButton4.show();
#else
#endif

	//widget.hide();
	
	QApplication::exec();

	return 0;
}
