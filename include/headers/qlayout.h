/*
 * File:			qlayout.h
 * Created on:		2016 Nov 9
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_TEST_QLAYOUT_H
#define WIN32_BASED_QTCLASSES_TEST_QLAYOUT_H

#define		INITIAL_CNTRL_ID		5

#define		DESIGNED_NUMB_OF_OBJS	1024
#define		SMALL_TABLE_SIZE		8

#include "qobject.h"
#include "qt_namspace.h"
#include <vector>

class QLayout : public QObject
{
public:
	// Construction destruction
	QLayout( class QWidget* parent );

	QLayout();

	virtual ~QLayout();

	/////////////////////////////////////////////////////////////////////////
	void						addObject ( class QObject* );

	virtual void				addWidget ( class QWidget*, int = 0, Qt::Alignment = 0 ) = 0;

	QObject*					GetWidget( const HWND& a_hWnd )const;

	virtual void				CreateAllCntrls ( );

	virtual void				SetAllVisible ( );

	virtual UCHAR				IsVisibleProt()const;
	
	virtual UCHAR				IsCreatedProt()const;

	virtual int					DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis );
	
private:
	virtual int					CreateProt();

	virtual LRESULT CALLBACK	PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam );

	virtual LRESULT CALLBACK	PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam );

private:
	WORD						m_wIndexOfCntrls;
	std::vector<QObject*>		m_Controls;

};


#endif //#ifndef __qlayout_h__