/*
 * File:			qwidgetprivate.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qwidgetprivate.h"


#include "headers/qapplication.h"
#include "headers/qboxlayout.h"

/*
#define		_VISIBLE_FLAG_		(UCHAR)0x01
#define		_CREATED_FLAG_		(UCHAR)0x02
#define		_REGISTER_FLAG_		(UCHAR)0x04
#define		_LAYOUT_CRT_FLAG_	(UCHAR)0x08
*/



QWidgetPrivate::QWidgetPrivate( UCHAR a_Props, class QLayout* a_pLayout, QWidgetPrivate* parent )
	:	QObject(parent)
{
}



QWidgetPrivate::~QWidgetPrivate()
{
}
