// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFRAMEBUFFERTEXTUREGL_H
#define	MOAIFRAMEBUFFERTEXTUREGL_H

#include <moai-gfx-gl/MOAIFrameBufferGL.h>
#include <moai-gfx-gl/MOAITextureGL.h>

//================================================================//
// MOAIFrameBufferTextureGL
//================================================================//
class MOAIFrameBufferTextureGL :
	public virtual MOAIFrameBufferGL,
	public virtual MOAITextureGL {
private:
	
	ZLGfxHandle			mGLColorBuffer;
	ZLGfxHandle			mGLDepthBuffer;
	ZLGfxHandle			mGLStencilBuffer;
	
	ZLGfxEnum::_		mColorFormat;
	ZLGfxEnum::_		mDepthFormat;
	ZLGfxEnum::_		mStencilFormat;
	
	//----------------------------------------------------------------//
	static int			_init							( lua_State* L );
	
	//----------------------------------------------------------------//
	void				_RegisterLuaClass							( RTTIVisitorHistory& history, MOAILuaState& state );
	void				_RegisterLuaFuncs							( RTTIVisitorHistory& history, MOAILuaState& state );
	void				MOAIFrameBufferGL_AffirmBuffers				();
	void				MOAIGfxResourceGL_OnGPUBind					();
	bool				MOAIGfxResourceGL_OnGPUCreate				();
	void				MOAIGfxResourceGL_OnGPUDeleteOrDiscard		( bool shouldDelete );

public:
	
	DECL_LUA_FACTORY ( MOAIFrameBufferTextureGL )
	
	//----------------------------------------------------------------//
	void				Init							( u32 width, u32 height, ZLGfxEnum::_ colorFormat, ZLGfxEnum::_ depthFormat, ZLGfxEnum::_ stencilFormat );
						MOAIFrameBufferTextureGL		();
						~MOAIFrameBufferTextureGL		();
};

#endif