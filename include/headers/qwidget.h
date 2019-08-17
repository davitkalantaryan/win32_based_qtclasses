/*
 * File:			qwidget.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17 
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QWIDGET_H
#define WIN32_BASED_QTCLASSES_QWIDGET_H

#include "qwidgetprivate.h"
#include "qt_namspace.h"

class QWidget : public QWidgetPrivate
{
public:
	QWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );

protected:
	QWidget( UCHAR a_Props, class QLayout* a_pLayout, QWidget* parent );

public:
	virtual ~QWidget();

	virtual int CreateProt( );


};

#endif  // #ifndef WIN32_BASED_QTCLASSES_QWIDGET_H
