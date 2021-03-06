// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIMUTEX_WIN32_H
#define MOAIMUTEX_WIN32_H

#ifdef _WIN32

#include <moai-util/MOAIMutex.h>
#include <windows.h>

//================================================================//
// MOAIMutexImpl
//================================================================//
class MOAIMutexImpl {
private:

	friend class MOAIMutex;
	friend class MOAIConditionVariableImpl;

	CRITICAL_SECTION	mCriticalSection;

	//----------------------------------------------------------------//
	void			Lock				();
					MOAIMutexImpl		();
					~MOAIMutexImpl		();
	void			Unlock				();
};

#endif
#endif
