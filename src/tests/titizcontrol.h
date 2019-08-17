/*
 * File:			titizcontrol.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_TEST_TITIZCONTROL_H
#define WIN32_BASED_QTCLASSES_TEST_TITIZCONTROL_H

#define		_RECTANGLE_SHAPE_		0
#define		_ELLIPSE_SHAPE_			1

#define		_CHECKED_LINE_COLOR_	RGB(0,0,0)
#define		_UNCHECKED_LN_COLOR_	RGB(100,100,100)


#include "headers/qwidgetprivate.h"


class TitizControl : public QWidgetPrivate
{
public:
	TitizControl( QWidgetPrivate* parent, UCHAR a_Shape = 0, COLORREF a_Color = GetSysColor(COLOR_BTNFACE) );
	//TitizControl( QWidgetPrivate* parent, UCHAR a_Shape = 1, COLORREF a_Color = RGB(255,0,0) );

	virtual ~TitizControl();

protected:
	int					CreateProt2(	const wchar_t* a_ClassName, const wchar_t* a_WndText, 
										DWORD a_dwStyles, int left, int top, int nWidth, int nHeight);

	virtual UCHAR		IsChecked()const;

	virtual int			DrawItemMe( UCHAR& howCnt, DRAWITEMSTRUCT* pdis );

	LRESULT CALLBACK	PreWndProc( UCHAR& howCnt, UINT message, WPARAM wParam, LPARAM lParam );

protected:
	UCHAR				m_cDrawStyle	: 1;
	UCHAR				m_bIsChecked	: 1;
	COLORREF			m_ColorF;
	COLORREF			m_ColorT;

	HBRUSH				m_BrushT;
	HBRUSH				m_BrushF;

	HPEN				m_PenT;
	HPEN				m_PenF;
};

#endif //#ifndef WIN32_BASED_QTCLASSES_TEST_TITIZCONTROL_H
