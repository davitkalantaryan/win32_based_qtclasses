/*
 * File:			qt_namespace.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17  (also renamed from qt_nmespace.cpp to qt_namespace.cpp)
 *
 */
#include "stdafx.h"
#include "headers/qt_namspace.h"


Qt::WindowFlags::WindowFlags( const int& a_nFlag )
	:	m_nFlag(a_nFlag)
{
}


const int& Qt::WindowFlags::Flag()
{
	return m_nFlag;
}


//////////////////////////////////////////////////////
Qt::Alignment::Alignment( const int& a_nAlighn )
	:	m_nAlighn(a_nAlighn)
{
}


const int& Qt::Alignment::Alighn()
{
	return m_nAlighn;
}
