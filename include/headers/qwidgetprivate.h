/*
 * File:			qwidgetprivate.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QWIDGETPRIVATE_H
#define WIN32_BASED_QTCLASSES_QWIDGETPRIVATE_H

#define		__CREATION_ERROR		-2

/*
	UCHAR			m_bIsVisible		: 1;
	UCHAR			m_bIsCreated		: 1;
	UCHAR			m_bIsRegisteresd	: 1;
	UCHAR			m_bLaytoutNotNeeded	: 1;
	UCHAR			m_bLaytCrtdOutside	: 1;
 */

#define		_VISIBLE_FLAG_			(UCHAR)0x01
#define		_CREATED_FLAG_			(UCHAR)0x02
#define		_REGISTER_FLAG_			(UCHAR)0x04
#define		_LAYT_NOT_NEEDED_		(UCHAR)0x08
#define		_LAYOUT_CRT_FLAG_		(UCHAR)0x10


#include "qobject.h"


class QWidgetPrivate : public QObject
{

public:
	// Contruction destruction
	QWidgetPrivate( UCHAR a_Props, class QLayout* a_pLayout, QWidgetPrivate* parent );

	virtual ~QWidgetPrivate();

	///////////////////////////////////////////////////////////////////
	void						SetIsVisibleProt( const UCHAR& a_ucIsVisible );

	UCHAR						IsVisibleProt()const;
	
	//void						SetIsCreatedProt( const UCHAR& a_ucIsCreated );

	UCHAR						IsCreatedProt()const;

	virtual void				show();

	virtual void				hide();

	class QLayout*				layout()const;

	virtual int					CreateProt() = 0;

	virtual int					DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* );

private:
	//virtual LRESULT CALLBACK	WndProcEvnt( UINT, WPARAM, LPARAM ) = 0;
	
	//LRESULT CALLBACK			WndProc( UINT message, WPARAM wParam, LPARAM lParam );

	virtual LRESULT CALLBACK	PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam );

	virtual LRESULT CALLBACK	PostWndProc( LRESULT lDef, UINT message, WPARAM wParam, LPARAM lParam );


protected:
	UCHAR			m_bIsVisible		: 1;
	UCHAR			m_bIsCreated		: 1;
	UCHAR			m_bIsRegisteresd	: 1;

	UCHAR			m_bLaytoutNotNeeded	: 1;
	class QLayout*	m_pLayout;
	UCHAR			m_bLaytCrtdOutside	: 1;

};


#endif // #ifndef WIN32_BASED_QTCLASSES_QWIDGETPRIVATE_H
