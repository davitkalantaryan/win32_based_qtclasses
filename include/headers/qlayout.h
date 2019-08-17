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

#include "win32_based_qtclasses_internal.h"
#include "qobject.h"
#include "qt_namspace.h"
#include <list>

class QWidget;

class QLayout : public QObject
{
	friend class QWidget;
public:
	// Construction destruction
	QLayout( class QWidget* parent );
	QLayout();
	virtual ~QLayout();

	virtual void				addWidget ( QWidget*, int = 0, Qt::Alignment = 0 );

protected:
	QObject*					GetWidget( const HWND& a_hWnd )const;
	virtual void				CreateAllWidgets ( );
	virtual void				SetAllWidgetsVisible ( );
	virtual UCHAR				IsVisibleProt()const;
	virtual UCHAR				IsCreatedProt()const;
	virtual int					DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis );
	
private:
	virtual LRESULT CALLBACK	PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam );
	virtual LRESULT CALLBACK	PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam );

private:
	WORD							m_wIndexOfCntrls;
	::std::list<QWidget*>			m_allWidgets;
	::std::list<QLayout*>			m_allLayouts;

};


#endif //#ifndef __qlayout_h__