/*
 * File:			qstring.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QSTRING_H
#define WIN32_BASED_QTCLASSES_QSTRING_H

#include <string.h>

class QString
{
public:
	QString();

	QString( const QString& cM );

	QString( const char* a_pcString );

	QString( const wchar_t* a_pwcString );

	virtual ~QString();

	QString& operator=( const QString& aM );

	QString& operator=( const char* pcStr );

	QString& operator=( const wchar_t* pwcStr );

	const wchar_t* GetString()const;

protected:
	wchar_t*		m_pwcString;
};


#endif // #ifndef WIN32_BASED_QTCLASSES_QSTRING_H
