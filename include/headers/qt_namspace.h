/*
 * File:			qt_namespace.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17  (also renamed from qt_nmespace.h to qt_namespace.h)
 *
 */
#ifndef WIN32_BASED_QTCLASSES_QT_NAMESPACE_H
#define WIN32_BASED_QTCLASSES_QT_NAMESPACE_H

namespace Qt
{
	enum __WindowFlags{ Widget, Window, Dialog };
	enum __Alignment{ RIGHT };

	class WindowFlags
	{
	public:
		WindowFlags( const int& a_nFlag );

		const int& Flag();

	private:
		const int		m_nFlag;
	};


	class Alignment
	{
	public:
		Alignment( const int& a_nAlighn );

		const int& Alighn();

	private:
		const int		m_nAlighn;
	};
};

#endif  // #ifndef WIN32_BASED_QTCLASSES_QT_NAMESPACE_H
