// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAITILEDECK2D_H
#define	MOAITILEDECK2D_H

#include <moai-sim/MOAIDeck.h>
#include <moai-sim/MOAIMaterialBatchHolder.h>
#include <moai-sim/MOAIQuadBrush.h>

//================================================================//
// MOAITileDeck2D
//================================================================//
/**	@lua	MOAITileDeck2D
	@text	Subdivides a single texture into uniform tiles enumerated
			from the texture's left top to right bottom.
*/
class MOAITileDeck2D :
	public MOAIDeck,
	public MOAIMaterialBatchHolder,
	public MOAIGridSpace {
private:
	
	MOAIQuadBrush mQuad;
	
	//----------------------------------------------------------------//
	static int		_setQuad				( lua_State* L );
	static int		_setRect				( lua_State* L );
	static int		_setUVQuad				( lua_State* L );
	static int		_setUVRect				( lua_State* L );
	static int		_setSize				( lua_State* L );
	static int		_transform				( lua_State* L );
	static int		_transformUV			( lua_State* L );
	
	//----------------------------------------------------------------//
	ZLBounds				MOAIDeck_ComputeMaxBounds		();
	void					MOAIDeck_Draw					( u32 idx );
	ZLBounds				MOAIDeck_GetBounds				( u32 idx );
	MOAICollisionShape*		MOAIDeck_GetCollisionShape		( u32 idx );
	bool					MOAIDeck_Overlap				( u32 idx, const ZLVec2D& vec, u32 granularity, ZLBounds* result );
	bool					MOAIDeck_Overlap				( u32 idx, const ZLVec3D& vec, u32 granularity, ZLBounds* result );
	
public:
	
	DECL_LUA_FACTORY ( MOAITileDeck2D )
	
	//----------------------------------------------------------------//
					MOAITileDeck2D			();
					~MOAITileDeck2D			();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			SerializeIn				( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut			( MOAILuaState& state, MOAISerializer& serializer );
	void			Transform				( const ZLAffine3D& mtx );
	void			TransformUV				( const ZLAffine3D& mtx );
};

#endif
