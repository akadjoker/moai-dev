// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPARTICLECALLBACKPLUGIN_H
#define	MOAIPARTICLECALLBACKPLUGIN_H

#include <moai-sim/MOAIParticlePlugin.h>

//================================================================//
// MOAIParticleCallbackPlugin
//================================================================//
/**	@lua	MOAIParticleCallbackPlugin
	@text	Allows custom particle processing via C language callbacks.
*/
class MOAIParticleCallbackPlugin :
	public virtual MOAIParticlePlugin {
private:

	AKUParticleInitFunc			mInitFunc;
	AKUParticleRenderFunc		mRenderFunc;

public:
	
	DECL_LUA_FACTORY ( MOAIParticleCallbackPlugin )
	
	//----------------------------------------------------------------//
	void			Init							( AKUParticleInitFunc initFunc, AKUParticleRenderFunc renderFunc, int size );
					MOAIParticleCallbackPlugin		();
					~MOAIParticleCallbackPlugin		();
	void			OnInit							( float* particle, float* registers );
	void			OnRender						( float* particle, float* registers, AKUParticleSprite* sprite, float t0, float t1, float term );
	void			MOAILuaObject_RegisterLuaClass				( MOAIComposer& composer, MOAILuaState& state );
	void			MOAILuaObject_RegisterLuaFuncs				( MOAIComposer& composer, MOAILuaState& state );
};

#endif
