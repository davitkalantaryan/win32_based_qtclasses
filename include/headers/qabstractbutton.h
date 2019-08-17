/*
 * File:			qabstractbutton.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QABSTRACTBUTTON_H
#define WIN32_BASED_QTCLASSES_QABSTRACTBUTTON_H

#include "qwidget.h"

class QAbstractButton : public QWidget
{
public:
	QAbstractButton( QWidget* parent = 0 );

protected:
	QAbstractButton( UCHAR a_Props, class QLayout* a_pLayout, QWidget* parent );

public:
	virtual ~QAbstractButton();

};


#endif  // #ifndef WIN32_BASED_QTCLASSES_QABSTRACTBUTTON_H
