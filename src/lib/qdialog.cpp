#include "stdafx.h"
#include "../headers/qdialog.h"

#include "../headers/qapplication.h"
#include "../headers/qboxlayout.h"


QDialog::QDialog( QWidget * parent, Qt::WindowFlags )
	:	QWidget(0,0,parent)
{

	m_pLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);

	if( parent )
	{
		QLayout* pLayout = parent->layout();

		pLayout->addWidget( this, 0, 0 );
	}
	else if( CreateProt( )  )
		throw;

}


QDialog::~QDialog( )
{
}


int QDialog::CreateProt( )
{

	int			x, y;
	int			nWidth, nHeight;
	HWND		aParent;

	aParent = m_pParent ? ((QWidget*)m_pParent)->GetHWND() : 0 ;
		
	y = x = CW_USEDEFAULT;
	
	nWidth = 430;
	nHeight = 655;


	//// Piti lock arvi
	QApplication::SetObjCreating( this );
	
	m_hWnd = CreateWindowExW(
		WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,	/* Extended possibilites for variation */
		L"_WINDOW_CLS_",						/* Classname */
		QApplication::GetAppName(),				/* Title Text */
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION,	/* default window */
		x,										/* Windows decides the position */
		y,										/* where the window ends up on the screen */
		nWidth,									/* The programs width */
		nHeight,								/* and height in pixels */
		aParent,								/* The window is a child-window to desktop */
		//NULL,									/* No menu */
		(HMENU)m_lCntrlIndex,					/* Menu */
		QApplication::GetInstance(),			/* Program Instance handler */
		NULL									/* No Window Creation data */
		);

	QApplication::SetObjCreating( 0 );
	/// Lock@ piti bacvi
	
	
	if (!m_hWnd)
	{
		return __CREATION_ERROR;
	}
#ifdef _WIN64
	SetWindowLongPtr( m_hWnd, GWLP_USERDATA, (LONG_PTR)this );
#else
	SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );
#endif
	

	if( m_bIsVisible )
	{
		ShowWindow( m_hWnd, SW_SHOW );
	}
	else
	{
		ShowWindow( m_hWnd, SW_HIDE );
	}
	UpdateWindow( m_hWnd );
	

	m_bIsCreated = 1;

	m_pLayout->CreateAllCntrls();

	return 0;

}
