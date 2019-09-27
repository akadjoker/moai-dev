// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIABSTRACTUNIFORMBUFFER_H
#define	MOAIABSTRACTUNIFORMBUFFER_H

class MOAIUniformSchema;

//================================================================//
// MOAIUniformBuffer
//================================================================//
// TODO: doxygen
class MOAIAbstractUniformBuffer :
	public virtual MOAINode {
protected:

	friend class MOAIUniformComposer;

	ZLLeanArray < u8 >			mUniforms;

	//----------------------------------------------------------------//
	static int					_getAttributeID				( lua_State* L );
	static int					_setUniform					( lua_State* L );
	static int					_setUniformArrayItem		( lua_State* L );

	//----------------------------------------------------------------//
	void						MOAILuaObject_RegisterLuaClass			( MOAIComposer& composer, MOAILuaState& state );
	void						MOAILuaObject_RegisterLuaFuncs			( MOAIComposer& composer, MOAILuaState& state );
	bool						MOAINode_ApplyAttrOp					( ZLAttrID attrID, ZLAttribute& attr, u32 op );

	//----------------------------------------------------------------//
	virtual const MOAIUniformSchema*	MOAIAbstractUniformBuffer_GetSchema		() const = 0;

public:

	//----------------------------------------------------------------//
	const MOAIUniformSchema*	GetSchema						() const;
								MOAIAbstractUniformBuffer		();
								~MOAIAbstractUniformBuffer		();
};

#endif