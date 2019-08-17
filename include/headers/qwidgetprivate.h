/*
 * File:			qwidgetprivate.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QWIDGETPRIVATE_H
#define WIN32_BASED_QTCLASSES_QWIDGETPRIVATE_H


#include "qobject.h"


class QWidgetPrivate : public QObject
{

public:
	// Contruction destruction
	QWidgetPrivate( UCHAR a_Props, class QLayout* a_pLayout, QWidgetPrivate* parent );
	virtual ~QWidgetPrivate();

};


#endif // #ifndef WIN32_BASED_QTCLASSES_QWIDGETPRIVATE_H
