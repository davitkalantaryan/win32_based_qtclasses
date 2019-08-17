/*
 * File:			qboxlayout.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qboxlayout.h"

#include "headers/qwidget.h"
#include "headers/qapplication.h"


QBoxLayout::QBoxLayout( Direction dir, class QWidget* parent )
	:	QLayout(parent)
{
}


QBoxLayout::~QBoxLayout( )
{
}


void QBoxLayout::addWidget ( QWidget* widget, int stretch, Qt::Alignment alignment )
{

	QLayout::addObject( widget );


	//////////////////////////////////////////////////////////////
	QWidget* pwParent = (QWidget*)m_pParent;

	
	if( pwParent && pwParent->IsCreatedProt() )
	{
		
		if( widget->IsCreatedProt() )
		{
			SetParent( widget->GetHWND(), pwParent->GetHWND() );
			UpdateWindow( widget->GetHWND() );
		}
		else
		{
			widget->CreateProt();			
		}


	}
	else
	{
		DestroyWindow( widget->GetHWND() );
	}


}

