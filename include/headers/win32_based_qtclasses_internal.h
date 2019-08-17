/*
 * File:			win32_based_qtclasses_internal.h
 * Created on:		2016 Nov 8
 * Created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
 *
 * Last modified:	2019 Aug 17
 *
 */
#ifndef WIN32_BASED_QTCLASSES_WIN32_BASED_INTERNAL_H
#define WIN32_BASED_QTCLASSES_WIN32_BASED_INTERNAL_H


// All compilers should be discussed here
#ifdef _MSC_VER
#define CPP11_OR_HIGHER
#define EXPORT_SYMB_FROM_LIB2	_declspec(dllexport)
#define IMPORT_SYMB_FROM_LIB2	_declspec(dllimport)
#define HIDE_SYMB_FROM_LIB2		
#elif defined(__GNUC__)
#define EXPORT_SYMB_FROM_LIB2
#define IMPORT_SYMB_FROM_LIB2
#define HIDE_SYMB_FROM_LIB2		__attribute__((visibility("hidden")))
#endif


#if defined(__cplusplus) && defined(CPP11_OR_HIGHER)
#define NEWNULLPTR2		nullptr
#define OVERRIDE2		override
#else
#define NEWNULLPTR2		NULL
#define OVERRIDE2
#endif


#endif  // #ifndef WIN32_BASED_QTCLASSES_WIN32_BASED_INTERNAL_H
