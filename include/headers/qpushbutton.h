/*
 * File:			qpushbutton.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QPUSHBUTTON_H
#define WIN32_BASED_QTCLASSES_QPUSHBUTTON_H

#include "qabstractbutton.h"
#include "qstring.h"

class QPushButton : public QAbstractButton
{
public:
	QPushButton( QWidget* parent = 0 );

	QPushButton( const QString& text, QWidget* parent = 0 );

	virtual ~QPushButton();

protected:
	int					CreateProt( );

	//LRESULT CALLBACK	WndProcEvnt( UINT message, WPARAM wParam, LPARAM lParam );

protected:
	QString		m_text;
	DWORD		m_dwBkColor;
};


#endif // #ifndef WIN32_BASED_QTCLASSES_QPUSHBUTTON_H
