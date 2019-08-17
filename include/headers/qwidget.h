/*
 * File:			qwidget.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17 
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QWIDGET_H
#define WIN32_BASED_QTCLASSES_QWIDGET_H

#include "win32_based_qtclasses_internal.h"
#include "qwidgetprivate.h"
#include "qt_namspace.h"
#include <list>

#define		__CREATION_ERROR		-2

#define		_VISIBLE_FLAG_			(UCHAR)0x01
#define		_CREATED_FLAG_			(UCHAR)0x02
#define		_REGISTER_FLAG_			(UCHAR)0x04
#define		_LAYT_NOT_NEEDED_		(UCHAR)0x08
#define		_LAYOUT_CRT_FLAG_		(UCHAR)0x10

class QLayout;
class QBoxLayout;
class QPushButton;

class QWidget : public QObject
{
	friend class QLayout;
	friend class QBoxLayout;
	friend class QPushButton;
public:
	QWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );
protected:
	QWidget( UCHAR a_Props, QLayout* a_pLayout, QWidget* parent );

public:
	virtual ~QWidget();

	virtual void				show();
	virtual void				hide();
	QLayout*					layout()const;

protected:
	const HWND&					GetHWND()const;
	void						SetIsVisibleProt(const UCHAR& a_ucIsVisible);
	UCHAR						IsVisibleProt()const;
	UCHAR						IsCreatedProt()const;
	virtual int					CreateProt();
	virtual int					DrawItemMe(UCHAR& howCnt, DRAWITEMSTRUCT*);
	void						SetCntrlIndex(const LONG& a_lCntrlIndex);

protected:
	virtual LRESULT CALLBACK	PreWndProc(UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam) OVERRIDE2;
	virtual LRESULT CALLBACK	PostWndProc(LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam) OVERRIDE2;

protected:
	QLayout*						m_pLayout;
	UCHAR							m_bIsVisible : 1;
	UCHAR							m_bIsCreated : 1;
	UCHAR							m_bIsRegisteresd : 1;
	UCHAR							m_bLaytoutNotNeeded : 1;
	UCHAR							m_bLaytCrtdOutside : 1;
	HWND							m_hWnd;
	ptrdiff_t						m_lCntrlIndex;
	::std::list<QWidget*>::iterator	m_thisIter;

};

#endif  // #ifndef WIN32_BASED_QTCLASSES_QWIDGET_H
