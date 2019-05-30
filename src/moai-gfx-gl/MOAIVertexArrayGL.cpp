// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-gfx-gl/MOAIGfxMgrGL.h>
#include <moai-gfx-gl/MOAIVertexArrayGL.h>
#include <moai-gfx-gl/MOAIVertexFormatGL.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIVertexArrayGL::_reserveVAOs ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVertexArrayGL, "U" )
	
	self->ReserveVAOs ( state.GetValue < u32 >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIVertexArrayGL::_reserveVertexBuffers ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVertexArrayGL, "U" )
	
	self->ReserveVertexBuffers ( state.GetValue < u32 >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIVertexArrayGL::_setVertexBuffer ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVertexArrayGL, "U" )
	
	u32 baseParam = 2;
	ZLIndex idx = ZLIndexOp::ZERO;
	
	if ( state.IsType ( baseParam, LUA_TNUMBER )) {
		idx = ZLIndexCast ( state.GetValue < u32 >( baseParam++, 1 ) - 1 );
	}
	
	MOAIVertexBufferGL* buffer	= state.GetLuaObject < MOAIVertexBufferGL >( baseParam++, false );
	MOAIVertexFormatGL* format	= state.GetLuaObject < MOAIVertexFormatGL >( baseParam++, false );
	
	self->SetVertexBuffer ( idx, buffer, format );

	return 0;
}


//================================================================//
// MOAIVertexBufferWithFormatGL
//================================================================//

//----------------------------------------------------------------//
MOAIVertexBufferWithFormatGL::MOAIVertexBufferWithFormatGL () {
}


//----------------------------------------------------------------//
MOAIVertexBufferWithFormatGL::~MOAIVertexBufferWithFormatGL () {
}

//----------------------------------------------------------------//
void MOAIVertexBufferWithFormatGL::SetBufferAndFormat ( MOAIVertexBufferGL* buffer, MOAIVertexFormatGL* format ) {

	this->mBuffer = buffer;
	this->mFormat = format;
}

//================================================================//
// MOAIVertexArrayGL
//================================================================//

//----------------------------------------------------------------//
bool MOAIVertexArrayGL::AffirmVertexBuffers ( u32 idx ) {

	if (( this->mVertexBuffers.Size () == 0 ) && ( idx == 0 )) {
		this->ReserveVertexBuffers ( 1 );
	}
	return ( idx < this->mVertexBuffers.Size ());
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::BindVertexArrayItems () {

	ZLGfx& gfx = this->mGfxMgr->GetDrawingAPI ();

	ZLSize totalVBOs = this->mVertexBuffers.Size ();
	for ( ZLIndex i = ZLIndexOp::ZERO; i < totalVBOs; ++i ) {
	
		MOAIVertexBufferGL* buffer = this->mVertexBuffers [ i ].mBuffer;
		MOAIVertexFormatGL* format = this->mVertexBuffers [ i ].mFormat;
		
		assert ( buffer && format );
		
		assert (( this->mUseVAOs && buffer->IsUsingVBOs ()) || ( !this->mUseVAOs )); // buffer objects must use VBOs to work with VAOs
		
		ZLSharedConstBuffer* bufferForBind = buffer->GetBufferForBind ( gfx );
		
		buffer->Bind ();
		format->Bind ( gfx, bufferForBind );
		buffer->Unbind ();
	}
}

//----------------------------------------------------------------//
MOAIVertexBufferGL* MOAIVertexArrayGL::GetVertexBuffer ( ZLIndex idx ) {

	return idx < this->mVertexBuffers.Size () ? ( MOAIVertexBufferGL* )this->mVertexBuffers [ idx ].mBuffer : ( MOAIVertexBufferGL* )0;
}

//----------------------------------------------------------------//
MOAIVertexFormatGL* MOAIVertexArrayGL::GetVertexFormat ( ZLIndex idx ) {

	return idx < this->mVertexBuffers.Size () ? ( MOAIVertexFormatGL* )this->mVertexBuffers [ idx ].mFormat : ( MOAIVertexFormatGL* )0;
}

//----------------------------------------------------------------//
MOAIVertexArrayGL::MOAIVertexArrayGL () :
	mCurrentVAO ( ZLIndexOp::INVALID ),
	mUseVAOs ( false ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIVertexArray )
		RTTI_EXTEND ( MOAIAbstractGfxResourceGL )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIVertexArrayGL::~MOAIVertexArrayGL () {

	this->ReserveVAOs ( 0 );
	this->ReserveVertexBuffers ( 0 );
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIVertexArray::RegisterLuaClass ( state );
	MOAIAbstractGfxResourceGL::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIVertexArray::RegisterLuaFuncs ( state );
	MOAIAbstractGfxResourceGL::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "reserveVAOs",				_reserveVAOs },
		{ "reserveVertexBuffers",		_reserveVertexBuffers },
		{ "setVertexBuffer",			_setVertexBuffer },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::ReserveVAOs ( u32 total ) {

	for ( ZLIndex i = ZLIndexOp::ZERO; i < this->mVAOs.Size (); ++i ) {
		this->mGfxMgr->DeleteOrDiscard ( this->mVAOs [ i ], false );
	}
	this->mVAOs.Init ( total );
	this->FinishInit ();
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::ReserveVertexBuffers ( u32 total ) {

	for ( ZLIndex i = ZLIndexOp::ZERO; i < this->mVertexBuffers.Size (); ++i ) {
		this->mVertexBuffers [ i ].SetBufferAndFormat ( 0, 0 );
	}
	this->mVertexBuffers.Init ( total );
	
	this->FinishInit ();
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {

	ZLSize totalVAOs = state.GetFieldValue < cc8*, MOAILuaSize >( -1, "mTotalVAOs", 0 );
	this->ReserveVAOs ( totalVAOs );
	
	ZLSize totalVertexBuffers = state.GetFieldValue < cc8*, MOAILuaSize >( -1, "mTotalVertexBuffers", 0 );
	this->ReserveVertexBuffers ( totalVertexBuffers );
	
	if ( state.PushFieldWithType ( -1, "mVertexBuffers", LUA_TTABLE )) {
		int itr = state.PushTableItr ( -1 );
		for ( ZLIndex i = ZLIndexOp::ZERO; state.TableItrNext ( itr ); ++i ) {
			if ( state.IsType ( -1, LUA_TTABLE )) {
				MOAIVertexBufferGL* buffer = serializer.MemberIDToObject < MOAIVertexBufferGL >( state.GetFieldValue < cc8*, MOAISerializer::ObjID >( -1, "mBuffer", 0 ));
				MOAIVertexFormatGL* format = serializer.MemberIDToObject < MOAIVertexFormatGL >( state.GetFieldValue < cc8*, MOAISerializer::ObjID >( -1, "mFormat", 0 ));
				this->SetVertexBuffer ( i, buffer, format );
			}
		}
		state.Pop ();
	}
	this->FinishInit ();
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {

	state.SetField < cc8*, MOAILuaSize >( -1, "mTotalVAOs", this->mVAOs.Size ());
	state.SetField < cc8*, MOAILuaSize >( -1, "mTotalVertexBuffers", this->mVertexBuffers.Size ());
	
	lua_newtable ( state );
	for ( ZLIndex i = ZLIndexOp::ZERO; i < this->mVertexBuffers.Size (); ++i ) {
		state.Push ( MOAILuaIndex ( i ));
		lua_newtable ( state );
		
		MOAIVertexBufferGL* buffer = this->mVertexBuffers [ i ].mBuffer->AsType < MOAIVertexBufferGL >();
		MOAIVertexFormatGL* format = this->mVertexBuffers [ i ].mFormat->AsType < MOAIVertexFormatGL >();
		
		assert ( buffer && format );
		
		state.SetField < cc8*, MOAISerializer::ObjID >( -1, "mBuffer", serializer.AffirmMemberID ( buffer ));
		state.SetField < cc8*, MOAISerializer::ObjID >( -1, "mFormat", serializer.AffirmMemberID ( format ));
		lua_settable ( state, -3 );
	}
	lua_setfield ( state, -2, "mVertexBuffers" );
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::SetVertexBuffer ( ZLIndex idx, MOAIVertexBufferGL* vtxBuffer, MOAIVertexFormatGL* vtxFormat ) {

	if ( this->AffirmVertexBuffers ( idx )) {
		this->mVertexBuffers [ idx ].SetBufferAndFormat ( vtxBuffer, vtxFormat );
		this->ScheduleForGPUUpdate ();
	}
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::UnbindVertexArrayItems () {

	size_t totalVBOs = this->mVertexBuffers.Size ();
	for ( ZLIndex i = ZLIndexOp::ZERO; i < totalVBOs; ++i ) {
	
		MOAIVertexFormatGL* format = this->mVertexBuffers [ i ].mFormat;
		assert ( format );
		format->Unbind ( this->mGfxMgr->GetDrawingAPI ());
	}
}

//================================================================//
// virtual
//================================================================//

//----------------------------------------------------------------//
bool MOAIVertexArrayGL::ZLAbstractGfxResource_OnCPUCreate () {

	return true;
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::ZLAbstractGfxResource_OnCPUDestroy () {
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::ZLAbstractGfxResource_OnGPUBind () {

	if ( this->mUseVAOs && this->mVAOs.Size ()) {
		this->mGfxMgr->GetDrawingAPI ().BindVertexArray ( this->mVAOs [ this->mCurrentVAO ]);
	}
	else {
		this->BindVertexArrayItems ();
	}
}

//----------------------------------------------------------------//
bool MOAIVertexArrayGL::ZLAbstractGfxResource_OnGPUCreate () {

	this->mUseVAOs = false;
	
	size_t totalVAOs = this->mVAOs.Size ();

	if ( totalVAOs ) {
		
		for ( ZLIndex i = ZLIndexOp::ZERO; i < totalVAOs; ++i ) {
			ZLGfxHandle vao = this->mGfxMgr->GetDrawingAPI ().CreateVertexArray (); // OK for this to return 0
			if ( vao.GetType () != ZLGfxResource::NONE ) {
				this->mVAOs [ i ] = vao;
				this->mUseVAOs = true;
			}
		}
	}
	
	this->mCurrentVAO = ZLIndexCast ( 0 );
	this->ZLAbstractGfxResource_OnGPUUpdate ();
	
	return true;
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::ZLAbstractGfxResource_OnGPUDeleteOrDiscard ( bool shouldDelete ) {

	for ( ZLIndex i = ZLIndexOp::ZERO; i < this->mVAOs.Size (); ++i ) {
		this->mGfxMgr->DeleteOrDiscard ( this->mVAOs [ i ], shouldDelete );
	}
}

//----------------------------------------------------------------//
void MOAIVertexArrayGL::ZLAbstractGfxResource_OnGPUUnbind () {

	if ( this->mUseVAOs ) {
		this->mGfxMgr->GetDrawingAPI ().BindVertexArray ( ZLGfxResource::UNBIND );
	}
	else {
		this->UnbindVertexArrayItems ();
	}
}

//----------------------------------------------------------------//
bool MOAIVertexArrayGL::ZLAbstractGfxResource_OnGPUUpdate () {

	if ( !this->mUseVAOs ) return true;
	if ( !this->mVAOs.Size ()) return false;

	this->mCurrentVAO = ZLIndexOp::AddAndWrap ( this->mCurrentVAO, 1, this->mVAOs.Size ());
	const ZLGfxHandle& vao = this->mVAOs [ this->mCurrentVAO ];
	
	if ( vao.CanBind ()) {
		ZLGfx& gfx = this->mGfxMgr->GetDrawingAPI ();
		gfx.BindVertexArray ( vao );
		this->BindVertexArrayItems ();
		gfx.BindVertexArray ( ZLGfxResource::UNBIND );
		return true;
	}
	return false;
}