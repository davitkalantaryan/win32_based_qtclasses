/*
 * File:			qobject.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qobject.h"

QObject::QObject( QObject* parent )
	:	m_pParent(parent),
		m_hWnd(0),

		m_lCntrlIndex(0)
{
}


QObject::~QObject()
{
}


const HWND& QObject::GetHWND()const
{
	return m_hWnd;
}



void QObject::SetParentObj( QObject* parent )
{
	m_pParent = parent;
}


QObject* QObject::GetParent()const
{
	return m_pParent;
}


void QObject::SetCntrlIndex( const LONG& a_lCntrlIndex )
{
	m_lCntrlIndex = a_lCntrlIndex ;
}
