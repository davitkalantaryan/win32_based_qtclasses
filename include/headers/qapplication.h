/*
 * File:			qapplication.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QAPPLICATION_H
#define WIN32_BASED_QTCLASSES_QAPPLICATION_H

#define		_WS_(STR)			L(STR)
// Classes that will be registered
//#define		QWIDGET_CLASS		"QWidgetCls"
#define		_WINDOW_CLS_		"_WINDOW_CLS_"
//#define		QDIALOG_CLASS		"QDialogCls"
#define		_QPSHBUTTON_		"_QPSHBUTTON_"

#include <stddef.h>

#include "qobject.h"


class QApplication
{
public:
	/*
	 * Constuction destruction
	 *
	 */
	QApplication( int argc, char* argv[] );

	virtual ~QApplication();

	static int				exec();

	static const wchar_t*	GetAppName();

	static const HINSTANCE&	GetInstance();

	static void				SetVisible();

	static void				SetHidden();

	static LRESULT CALLBACK	WndProcStat(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK	ButtonProcStat(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static void				SetObjCreating( QObject* a_pObject );

	static ATOM				RegisterWndClass(
											UINT			style,
											WNDPROC			lpfnWndProc,
											int				cbClsExtra,
											int				cbWndExtra,
											HINSTANCE		hInstance,
											HICON			hIcon,
											HCURSOR			hCursor,
											HBRUSH			hbrBackground,
											LPCTSTR			lpszMenuName,
											LPCTSTR			lpszClassName,
											HICON			hIconSm,
											const COLORREF* a_pBkColor = 0
											);

//protected:
	static ATOM				RegisterPrivate(
											UINT			style,
											HICON			hIcon,
											HCURSOR			hCursor,
											HBRUSH			hbrBackground,
											LPCTSTR			lpszMenuName,
											LPCTSTR			lpszClassName,
											HICON			hIconSm
											);


	static ATOM				RegisteringAllClasses();

	static void				UnRegisterAllClasses();


	/*
	 * Members
	 */
protected:
	static QObject*					m_pstObjCreating;
	static HINSTANCE				m_hInstance;
	static class QString*			m_psAppName;
	static size_t					m_unVisibleObjects;

	static WNDCLASSEX				m_wcBut;
	static WNDPROC					m_fpBtnWndProc;
};


#endif  // #ifndef WIN32_BASED_QTCLASSES_QAPPLICATION_H
