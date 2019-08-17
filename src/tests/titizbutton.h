/*
 * File:			testcontrol.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_TEST_TITIZBUTTON_H
#define WIN32_BASED_QTCLASSES_TEST_TITIZBUTTON_H

#include "titizcontrol.h"
#include <QString>

class TitizButton : public TitizControl
{
public:
	//TitizButton( QWidgetPrivate* parent, const QString& a_String = "", UCHAR a_Shape = 0, COLORREF a_Color = GetSysColor(COLOR_BTNFACE) );
	TitizButton( QWidgetPrivate* parent, const QString& a_String = "", UCHAR a_Shape = 1, COLORREF a_Color = RGB(255,0,0) );

	virtual ~TitizButton();

protected:
	int					CreateProt( );

	virtual int			DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis );

protected:
	QString				m_text;

};


#endif // #ifndef WIN32_BASED_QTCLASSES_TEST_TITIZBUTTON_H
