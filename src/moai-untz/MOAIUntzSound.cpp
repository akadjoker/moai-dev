// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-untz/MOAIUntzSound.h>
#include <moai-untz/MOAIUntzSampleBuffer.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	getLength
	@text	Return the duration of the sound.
               
	@in		MOAIUntzSound self
	@out	number length
*/
int MOAIUntzSound::_getLength ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
               
	if ( self->mSound ) {
		lua_pushnumber ( state, self->mSound->getInfo().mLength );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getPosition
	@text	Return the position of the cursor in the sound.
	
	@in		MOAIUntzSound self
	@out	number position
*/
int MOAIUntzSound::_getPosition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		lua_pushnumber ( state, self->mSound->getPosition ());
		return 1; 
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getVolume
	@text	Return the volume of the sound.
	
	@in		MOAIUntzSound self
	@out	number volume
*/
int MOAIUntzSound::_getVolume ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		lua_pushnumber ( state, self->mSound->getVolume ());
		return 1; 
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getFilename
 @text	Return the file name of the sound.
 
 @in	MOAIUntzSound self
 @out	string filename
 */
int MOAIUntzSound::_getFilename ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		lua_pushstring( state, self->mFilename.str() );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	isLooping
	@text	Return the looping status if the sound.
	
	@in		MOAIUntzSound self
	@out	boolean looping
*/
int MOAIUntzSound::_isLooping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		lua_pushboolean ( state, self->mSound->isLooping ());
		return 1; 
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	isPaused
	@text	Return the pause status of the sound.
	
	@in		MOAIUntzSound self
	@out	boolean paused
*/
int MOAIUntzSound::_isPaused ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		lua_pushboolean ( state, self->mSound->isPaused ());
		return 1; 
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	isPlaying
	@text	Return the playing status of the sound.
	
	@in		MOAIUntzSound self
	@out	boolean playing
*/
int MOAIUntzSound::_isPlaying ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		lua_pushboolean ( state, self->mSound->isPlaying ());
		return 1; 
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	load
	@text	Loads a sound from disk.
	
	@in		MOAIUntzSound self
	@in		string filename
	@out	nil
*/
int MOAIUntzSound::_load ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )

	if ( self->mSound ) {
		UNTZ::Sound::dispose ( self->mSound );
		self->mSound = 0;
	}

	MOAIUntzSampleBuffer* data = state.GetLuaObject < MOAIUntzSampleBuffer >( 2, false );
	if ( data ) {
	
		self->mSound = UNTZ::Sound::create(data->GetSoundInfo (), data->GetSampleBuffer ());
		self->mInMemory = true;
	}
	else if ( state.IsType( 2, LUA_TSTRING )) {
	
		cc8* filename = state.GetValue < cc8* >( 2, "" );
		bool loadIntoMemory = state.GetValue < bool >( 3, true );	

		self->mFilename = filename;
		self->mInMemory = loadIntoMemory;
		//printf ( "creating sound: %s - %s\n", self->mFilename.str(), (loadIntoMemory) ? "in memory" : "not in memory" );
		if ( MOAILogMgr::CheckFileExists ( filename )) {
			self->mSound = UNTZ::Sound::create ( filename, loadIntoMemory );
		}
		else {
			self->mSound = NULL;
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	moveVolume
	@text	Animation helper for volume attribute,
	
	@in		MOAITransform self
	@in		number vDelta		Delta to be added to v.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH. Defaults to MOAIEaseType.SMOOTH.

	@out	MOAIEaseDriver easeDriver
*/
int MOAIUntzSound::_moveVolume ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "UNN" )
	
	float volume	= state.GetValue < float >( 2, 0.0f );
	float delay		= state.GetValue < float >( 3, 0.0f );
	
	if ( delay > 0.0f ) {
	
		u32 mode = state.GetValue < u32 >( 4, ZLInterpolate::kSmooth );
		
		MOAIEaseDriver* action = new MOAIEaseDriver ();
		action->ReserveLinks ( 1 );
		
		action->SetLink ( ZLIndexOp::ZERO, self, AttrID::Pack ( ATTR_VOLUME ), volume, mode );
		
		action->SetSpan ( delay );
		action->Start ( 0, false );
		action->PushLuaUserdata ( state );

		return 1;
	}
	
	self->mSound->setVolume ( self->mSound->getVolume () + volume );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	pause
	@text	Pause the sound.
	
	@in		MOAIUntzSound self
	@out	nil
*/
int MOAIUntzSound::_pause ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		self->mSound->pause ();
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	play
	@text	Play the sound.
	
	@in		MOAIUntzSound self
	@out	nil
*/
int MOAIUntzSound::_play ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		self->mSound->play ();
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	seekVolume
	@text	Animation helper for volume attribute,
	
	@in		MOAITransform self
	@in		number vGoal		Desired resulting value for v.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH. Defaults to MOAIEaseType.SMOOTH.

	@out	MOAIEaseDriver easeDriver
*/
int MOAIUntzSound::_seekVolume ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "UNN" )

	float volume	= state.GetValue < float >( 2, 0.0f );
	float delay		= state.GetValue < float >( 3, 0.0f );
	
	if ( delay > 0.0f ) {
	
		u32 mode = state.GetValue < u32 >( 4, ZLInterpolate::kSmooth );
		
		MOAIEaseDriver* action = new MOAIEaseDriver ();
		action->ReserveLinks ( 1 );
		
		action->SetLink ( ZLIndexOp::ZERO, self, AttrID::Pack ( ATTR_VOLUME ), volume - self->mSound->getVolume (), mode );
		
		action->SetSpan ( delay );
		action->Start ( 0, false );
		action->PushLuaUserdata ( state );

		return 1;
	}
	
	self->mSound->setVolume ( volume );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setLooping
	@text	Set or clear the looping status of the sound.
	
	@in		MOAIUntzSound self
	@opt	boolean looping		Default value is 'false.'
	@out	nil
*/
int MOAIUntzSound::_setLooping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		bool loop = state.GetValue < bool >( 2, false );
		self->mSound->setLooping ( loop );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setLoopPoints
	@text	Sets the start and end looping positions for the sound
	
	@in		MOAIUntzSound self
	@in		double startTime
	@in		double endTime
	
	@out	nil
*/
int MOAIUntzSound::_setLoopPoints ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		double startTime = state.GetValue < double >( 2, 0.0 );
		double endTime = state.GetValue < double >( 3, 0.0 );
		self->mSound->setLoopPoints ( startTime, endTime );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setPosition
	@text	Sets the position of the sound cursor.
	
	@in		MOAIUntzSound self
	@opt	boolean position		Default value is 0.
	@out	nil
*/
int MOAIUntzSound::_setPosition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		double position = state.GetValue < double >( 2, 0.0 );
		self->mSound->setPosition ( position );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setVolume
	@text	Sets the volume of the sound.
	
	@in		MOAIUntzSound self
	@opt	boolean volume			Default value is 0.
	@out	nil
*/
int MOAIUntzSound::_setVolume ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		float volume = state.GetValue < float >( 2, 0.0f );
		self->mSound->setVolume ( volume );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	stop
	@text	Stops the sound from playing.
	
	@in		MOAIUntzSound self
	@out	nil
*/
int MOAIUntzSound::_stop ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIUntzSound, "U" )
	
	if ( self->mSound ) {
		self->mSound->stop ();
	}
	return 0;
}

//================================================================//
// MOAIUntzSound
//================================================================//

//----------------------------------------------------------------//
MOAIUntzSound::MOAIUntzSound () :
	mSound ( 0 ),
	mFilename ( 0 ),
	mInMemory ( false ) {

	RTTI_SINGLE ( MOAINode )
}

//----------------------------------------------------------------//
MOAIUntzSound::~MOAIUntzSound () {

	//if (mFilename != NULL)
		//printf ( "deleteing sound: %s - %s\n", mFilename.str(), (mInMemory) ? "in memory" : "not in memory" );
		
	if ( this->mSound ) {
		UNTZ::Sound::dispose ( this->mSound );
	}
}
//----------------------------------------------------------------//
void MOAIUntzSound::MOAILuaObject_RegisterLuaClass ( MOAIComposer& composer, MOAILuaState& state ) {

	MOAI_CALL_SUPER_ONCE ( composer, MOAINode, MOAILuaObject_RegisterLuaClass ( composer, state ));

	state.SetField ( -1, "ATTR_VOLUME", AttrID::Pack ( ATTR_VOLUME ).ToRaw ());
}

//----------------------------------------------------------------//
void MOAIUntzSound::MOAILuaObject_RegisterLuaFuncs ( MOAIComposer& composer, MOAILuaState& state ) {

	MOAI_CALL_SUPER_ONCE ( composer, MOAINode, MOAILuaObject_RegisterLuaFuncs ( composer, state ));

	luaL_Reg regTable [] = {
		{ "getLength",			_getLength },
		{ "getPosition",		_getPosition },
		{ "getVolume",			_getVolume },
		{ "isLooping",			_isLooping },
		{ "isPaused",			_isPaused },
		{ "isPlaying",			_isPlaying },
		{ "load",				_load },
		{ "moveVolume",			_moveVolume },
		{ "pause",				_pause },
		{ "play",				_play },
		{ "seekVolume",			_seekVolume },
		{ "setLooping",			_setLooping },
		{ "setLoopPoints",		_setLoopPoints },
		{ "setPosition",		_setPosition },
		{ "setVolume",			_setVolume },
		{ "stop",				_stop },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// virtual
//================================================================//

//----------------------------------------------------------------//
bool MOAIUntzSound::MOAINode_ApplyAttrOp ( ZLAttrID attrID, ZLAttribute& attr, u32 op ) {

	if ( AttrID::Check ( attrID )) {
		if ( attrID.Unpack () == ATTR_VOLUME ) {
			this->mSound->setVolume ( attr.Apply ( this->mSound->getVolume (), op, ZLAttribute::ATTR_READ_WRITE ));
			return true;
		}
	}
	return false;
}
