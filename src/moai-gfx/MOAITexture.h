// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAITEXTURE_H
#define	MOAITEXTURE_H

#include <moai-gfx/MOAIGfxConsts.h>
#include <moai-gfx/MOAIGfxResource.h>

//================================================================//
// MOAITexture
//================================================================//
class MOAITexture :
	public virtual MOAIGfxResource {
protected:

	// debug name for memory use reporting
	STLString					mDebugName;
	
	// size of the original texture
	u32							mWidth;
	u32							mHeight;

	MOAITextureFilterEnum::_	mMinFilter;
	MOAITextureFilterEnum::_	mMagFilter;
	MOAITextureWrapEnum::_		mWrap;
	
	size_t						mTextureSize;

	//----------------------------------------------------------------//

public:

	static const u32 DEFAULT_TRANSFORM = ZLImageTransform::TRUECOLOR | ZLImageTransform::PREMULTIPLY_ALPHA;

	GET_CONST ( u32, Height, mHeight );
	GET_CONST ( u32, Width, mWidth );

	GET_SET ( cc8*, DebugName, mDebugName );

	//----------------------------------------------------------------//
					MOAITexture					();
					~MOAITexture				();
	void			SetFilter					( MOAITextureFilterEnum::_ filter );
	void			SetFilter					( MOAITextureFilterEnum::_ min, MOAITextureFilterEnum::_ mag );
	void			SetWrap						( MOAITextureWrapEnum::_ wrap );
};

#endif