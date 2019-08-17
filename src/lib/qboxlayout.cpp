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


QBoxLayout::QBoxLayout( Direction dir, QWidget* parent )
	:	QLayout(parent)
{
}


QBoxLayout::~QBoxLayout( )
{
}


void QBoxLayout::addWidget ( QWidget* a_widget, int a_stretch, Qt::Alignment a_alignment )
{
	QLayout::addWidget(a_widget);
	
	if( m_pParent && m_pParent->IsCreatedProt() )
	{
		
		if(a_widget->IsCreatedProt() ){
			QWidget* pParentWidget = dynamic_cast<QWidget*>(m_pParent);
			if(pParentWidget){ // this means we have QWidget
				SetParent(a_widget->GetHWND(), pParentWidget->GetHWND());
			}
			UpdateWindow(a_widget->GetHWND());
		}
		else{
			a_widget->CreateProt();
		}


	}
	else
	{
		DestroyWindow(a_widget->GetHWND() );
	}

}
