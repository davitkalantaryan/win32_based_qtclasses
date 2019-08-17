/*
 * File:			qstring.cpp
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#include "stdafx.h"
#include "headers/qstring.h"

#include <malloc.h>
#include <Windows.h>


QString::QString()
	:	m_pwcString(0)
{
}


QString::QString( const QString& cM )
	:	m_pwcString(0)
{
	operator=( cM.m_pwcString );
}


QString::QString( const char* a_pcString )
	:	m_pwcString(0)
{
	operator=( a_pcString );
}


QString::QString( const wchar_t* a_pwcString )
	:	m_pwcString(0)
{
	operator=( a_pwcString );
}


QString::~QString()
{
	if( m_pwcString )
		free( m_pwcString );
}


QString& QString::operator =( const QString& aM )
{
	return operator=( aM.m_pwcString );
}


QString& QString::operator =( const char* pcStr )
{
	if( pcStr )
	{
		size_t unStrLen = strlen( pcStr );

		wchar_t* pwcString = (wchar_t*)realloc( m_pwcString, (unStrLen + 1) * sizeof(wchar_t) );

		if( pwcString )
		{
			m_pwcString = pwcString ;

			MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, pcStr, (int)unStrLen, m_pwcString, (int)unStrLen );

			m_pwcString[unStrLen] = (wchar_t)0;

			//memcpy( m_pcString, aStr, unStrLen + 1 );
		}
	}
	else
	{
		if( m_pwcString )
		{
			free( m_pwcString );
			m_pwcString = 0;
		}
	}


	return *this;
}


QString& QString::operator =( const wchar_t* pwcStr )
{
	if( pwcStr )
	{
		size_t unStrLen = wcslen( pwcStr );

		wchar_t* pwcString = (wchar_t*)realloc( m_pwcString, (unStrLen + 1) * sizeof(wchar_t) );

		if( pwcString )
		{
			m_pwcString = pwcString ;

			memcpy( m_pwcString, pwcStr, (unStrLen + 1) * sizeof(wchar_t) );
		}
	}
	else
	{
		if( m_pwcString )
		{
			free( m_pwcString );
			m_pwcString = 0;
		}
	}


	return *this;
}


const wchar_t* QString::GetString()const
{
	return m_pwcString;
}
