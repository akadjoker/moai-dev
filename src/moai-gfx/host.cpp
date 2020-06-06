// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-gfx/host.h>
#include <moai-gfx/headers.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUGfxAppFinalize () {
}

//----------------------------------------------------------------//
void AKUGfxAppInitialize () {
}

//----------------------------------------------------------------//
void AKUGfxContextInitialize () {

	MOAIVertexFormatMgr::Affirm ();
	
	REGISTER_LUA_CLASS ( MOAICamera )
	REGISTER_LUA_CLASS ( MOAIGfxScriptBatch )
	REGISTER_LUA_CLASS ( MOAIMatrix )
	REGISTER_LUA_CLASS ( MOAITransform )
	REGISTER_LUA_CLASS ( MOAIVertexFormatMgr )
	REGISTER_LUA_CLASS ( MOAIViewport )
}