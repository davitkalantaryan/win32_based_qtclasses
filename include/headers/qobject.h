/*
 * File:			qobject.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QOBJECT_H
#define WIN32_BASED_QTCLASSES_QOBJECT_H

#include "win32_based_qtclasses_internal.h"
#include <stddef.h>
#include <stdint.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <list>

class QObject
{
public:
	QObject( QObject* parent = NEWNULLPTR2 );
	virtual ~QObject();

	void						SetParentObj( QObject* parent );
	QObject*					GetParent()const;
	virtual UCHAR				IsVisibleProt()const = 0;
	virtual UCHAR				IsCreatedProt()const = 0;
	virtual UCHAR				IsChecked()const{ return 0; };
	virtual int					DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis ) = 0;
	virtual LRESULT CALLBACK	PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam ) = 0;
	virtual LRESULT CALLBACK	PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam ) = 0;

protected:
	QObject*		m_pParent;
};

#endif  // #ifndef WIN32_BASED_QTCLASSES_QOBJECT_H
