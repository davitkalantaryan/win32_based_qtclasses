/*
 * File:			qabstractbutton.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qabstractbutton.h"
#include "headers/qlayout.h"


QAbstractButton::QAbstractButton( QWidget* parent )
	:	QWidget(parent)
{
}


QAbstractButton::QAbstractButton( UCHAR a_Props, class QLayout* a_pLayout, QWidget* parent )
	:	QWidget(a_Props,a_pLayout,parent)
{
}


QAbstractButton::~QAbstractButton()
{
}

