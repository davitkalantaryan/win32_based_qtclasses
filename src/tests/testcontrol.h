/*
 * File:			testcontrol.h  
 * Created on:		2016 Nov 8  
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)  
 *
 * Last modified:	2019 Aug 17  
 * 
 */
#ifndef WIN32_BASED_QTCLASSES_TEST_TESTCONTROL_H
#define WIN32_BASED_QTCLASSES_TEST_TESTCONTROL_H


#include <QPushbutton>
#include <QString>


class TestWidget : public QWidget
{
	LRESULT CALLBACK PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam );

	//LRESULT CALLBACK PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam );
};


class TestControl : public QPushButton
{
public:
	TestControl( const char* a_String, QWidget* parent );

	int CreateProt( );

	LRESULT CALLBACK PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam );

	LRESULT CALLBACK PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam );

	void DrawAll( WPARAM wParam );

private:
	bool	m_bPushed;
};


#endif  // #ifndef WIN32_BASED_QTCLASSES_TEST_TESTCONTROL_H
