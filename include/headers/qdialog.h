/*
 * File:			qdialog.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QDIALOG_H
#define WIN32_BASED_QTCLASSES_QDIALOG_H

#include "qwidget.h"

class QDialog : public QWidget
{
public:
	QDialog( QWidget * parent = 0, Qt::WindowFlags f = Qt::Dialog );

	virtual ~QDialog();

protected:
	int CreateProt( );
};

#endif  // #ifndef WIN32_BASED_QTCLASSES_QDIALOG_H
