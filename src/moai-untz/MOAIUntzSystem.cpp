// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-untz/MOAIUntzSystem.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_getDeviceCount ( lua_State* L ) {
	UNUSED ( L );
	
	//UInt32 deviceCount = UNTZ::System::get ()->getDeviceCount ();
	//lua_pushnumber ( L, deviceCount );
	
	return 1;
}

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_getDeviceInfo ( lua_State* L ) {
	MOAILuaState state ( L );
	
	//u32 deviceIndex = state.GetValue ( 1, 0 );
	//UNTZ::DeviceInfo info = UNTZ::System::get ()->getDeviceInfo ( deviceIndex );
	//
	//lua_pushstring ( L, info.name.c_str ());
	//lua_pushnumber ( L, info.numInputChannels );
	//lua_pushnumber ( L, info.numOutputChannels );
	
	return 3;
}

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_getOptions ( lua_State* L ) {
	UNUSED ( L );

	//UInt32 options = UNTZ::System::get ()->getOptions ();
	//lua_pushnumber ( L, options );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	getSampleRate
	@text	Return the system's current sample rate.
	
	@out	number sampleRate
*/
int MOAIUntzSystem::_getSampleRate ( lua_State* L ) {
	MOAILuaState state ( L );
	
	UInt32 sampleRate = UNTZ::System::get ()->getSampleRate ();
	lua_pushnumber ( L, sampleRate );
	
	return 1;
}

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_getSupportedFormats ( lua_State* L ) {
	MOAILuaState state ( L );
	
	//RStringArray& formats = UNTZ::System::get ()->getSupportedFormats ();
	//
	//lua_newtable ( L );
	//for ( RStringArray::size_type i = 0; i < formats.size (); ++i ) {
	//	lua_pushboolean ( L, true );
	//	lua_setfield ( L, -2, formats [ i ].c_str ());
	//}
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	initialize
	@text	Inititalize the sound system.
	
	@opt	number sampleRate		Default value is 44100.
	@opt	number numFrames		Default value is 8192
	@out	nil
*/
int MOAIUntzSystem::_initialize ( lua_State* L ) {
	MOAILuaState state ( L );
	
	u32 sampleRate = state.GetValue ( 1, DEFAULT_SAMPLE_RATE );
	u32 numFrames = state.GetValue ( 2, DEFAULT_FRAMES_PER_BUFFER );
	u32 options = state.GetValue ( 3, DEFAULT_OPTIONS );
	
	UNTZ::System::get ()->initialize ( sampleRate, numFrames, options );
	
	return 0;
}

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_setInputDevice ( lua_State* L ) {
	MOAILuaState state ( L );
	
	//u32 deviceIndex = state.GetValue ( 1, 0 );
	//UNTZ::System::get ()->setInputDevice ( deviceIndex );
	
	return 0;
}

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_setOptions ( lua_State* L ) {
	MOAILuaState state ( L );
	
	//u32 options = state.GetValue ( 1, DEFAULT_OPTIONS );
	//UNTZ::System::get ()->_setOptions ( options );
	
	return 0;
}

//----------------------------------------------------------------//
// placeholder
int MOAIUntzSystem::_setOutputDevice ( lua_State* L ) {
	MOAILuaState state ( L );
	
	//u32 deviceIndex = state.GetValue ( 1, 0 );
	//UNTZ::System::get ()->setOutputDevice ( deviceIndex );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setSampleRate
	@text	Set the system sample rate.
	
	@opt	number sampleRate		Default value is 44100.
	@out	nil
*/
int MOAIUntzSystem::_setSampleRate ( lua_State* L ) {
	MOAILuaState state ( L );
	
	u32 sampleRate = state.GetValue ( 1, DEFAULT_SAMPLE_RATE );
	UNTZ::System::get ()->setSampleRate ( sampleRate );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setVolume
	@text	Set the system level volume.
	
	@opt	number volume		Valid Range: 0 >= x <= 1.0 (Default value is 1.0)
	@out	nil
*/
int MOAIUntzSystem::_setVolume ( lua_State* L ) {
	MOAILuaState state ( L );
	
	float volume = ( float )state.GetValue ( 1, 1.0 );
	UNTZ::System::get ()->setVolume ( volume );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getVolume
	@text	Return the system's current volume
	
	@out	number volume
*/
int MOAIUntzSystem::_getVolume ( lua_State* L ) {
	MOAILuaState state ( L );
	
	float volume = UNTZ::System::get ()->getVolume ();
	lua_pushnumber ( L, volume );
	
	return 1;
}

//================================================================//
// MOAIUntzSystem
//================================================================//

//----------------------------------------------------------------//
MOAIUntzSystem::MOAIUntzSystem () {
	
	RTTI_BEGIN ( MOAIUntzSystem )
		RTTI_VISITOR ( MOAIAbstractLuaRegistrationVisitor, MOAILuaRegistrationVisitor < MOAIUntzSystem >)
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIUntzSystem::~MOAIUntzSystem () {
}

//----------------------------------------------------------------//
void MOAIUntzSystem::Resume () {
	
	if ( UNTZ::System::get () ) {
		UNTZ::System::get ()->resume ();
	}
}

//----------------------------------------------------------------//
void MOAIUntzSystem::Suspend () {

	if ( UNTZ::System::get () ) {
		UNTZ::System::get ()->suspend ();
	}
}

//================================================================//
// virtual
//================================================================//

//----------------------------------------------------------------//
void MOAIUntzSystem::_RegisterLuaClass ( RTTIVisitorHistory& history, MOAILuaState& state ) {
	if ( history.DidVisit ( *this )) return;
	
	luaL_Reg regTable [] = {
		//{ "getDeviceCount",			_getDeviceCount },
		//{ "getDeviceInfo",			_getDeviceInfo },
		//{ "getOptions",				_getOptions },
		{ "getSampleRate",			_getSampleRate },
		//{ "getSupportedFormats",	_getSupportedFormats },
		{ "initialize",				_initialize },
		//{ "setInputDevice",			_setInputDevice },
		//{ "setOptions",				_setOptions },
		//{ "setOutputDevice",		_setOutputDevice },
		{ "setSampleRate",			_setSampleRate },
		{ "setVolume",				_setVolume },
		{ "getVolume",				_getVolume },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
	
	state.SetField(-1,"RECORDABLE", (u32) UNTZ::RECORDABLE ); // bitwise
}

//----------------------------------------------------------------//
void MOAIUntzSystem::_RegisterLuaFuncs ( RTTIVisitorHistory& history, MOAILuaState& state ) {
	UNUSED ( state );
	if ( history.DidVisit ( *this )) return;
}
