/*
 * File:			qboxlayout.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QBOXLAYOUT_H
#define WIN32_BASED_QTCLASSES_QBOXLAYOUT_H

#include "qlayout.h"

class QBoxLayout : public QLayout
{
public:
	enum Direction { LeftToRight, RightToLeft, TopToBottom, BottomToTop };

public:
	QBoxLayout( Direction dir, class QWidget* parent = 0 );

	virtual ~QBoxLayout();

	virtual void addWidget ( QWidget* widget, int stretch = 0, Qt::Alignment alignment = 0 );

};


#endif //#ifndef WIN32_BASED_QTCLASSES_QBOXLAYOUT_H
