// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-gfx-vk/MOAIAbstractDescriptorElementVK.h>
#include <moai-gfx-vk/MOAIDescriptorSetSnapshotVK.h>
#include <moai-gfx-vk/MOAIDescriptorSetVK.h>
#include <moai-gfx-vk/MOAIGfxMgrVK.h>
#include <moai-gfx-vk/MOAIGfxStructVK.h>
#include <moai-gfx-vk/MOAIDescriptorSetLayoutImplVK.h>
#include <moai-gfx-vk/MOAIDescriptorSetLayoutImplVK.h>

//================================================================//
// MOAIDescriptorSetSnapshotVK
//================================================================//

//----------------------------------------------------------------//
void MOAIDescriptorSetSnapshotVK::Invalidate () {

	if ( !this->mIsValid ) return;

	ZLSize sigSize = this->mSignature.Size ();
	for ( ZLIndex index = 0; index < sigSize; ++index ) {
		this->mSignature [ index ]->RemoveDescriptorSet ( *this );
	}
	this->mIsValid = false;

	if ( this->HasDependency < MOAIDescriptorSetLayoutImplVK >()) {
		MOAIDescriptorSetLayoutImplVK& descriptorSetLayout = this->GetDependency < MOAIDescriptorSetLayoutImplVK >();
		descriptorSetLayout.RetireDescriptorSet ( *this );
	}
}

//----------------------------------------------------------------//
MOAIDescriptorSetSnapshotVK::MOAIDescriptorSetSnapshotVK () :
	mKey ( this->mSignature ),
	mDescriptorSet ( VK_NULL_HANDLE ),
	mIsValid ( false ),
	mPool ( NULL ) {
}

//----------------------------------------------------------------//
MOAIDescriptorSetSnapshotVK::~MOAIDescriptorSetSnapshotVK () {

	this->Invalidate ();
}

//================================================================//
// virtual
//================================================================//

//----------------------------------------------------------------//
void MOAIDescriptorSetSnapshotVK::MOAIAbstractSnapshotVK_OnPin ( MOAICommandBufferVK& commandBuffer ) {
	
	assert ( this->mIsValid );
	
	ZLSize sigSize = this->mSignature.Size ();
	for ( ZLIndex index = 0; index < sigSize; ++index ) {
		commandBuffer.Pin ( *this->mSignature [ index ]);
	}
}

//----------------------------------------------------------------//
void MOAIDescriptorSetSnapshotVK::MOAIAbstractSnapshotVK_OnUnpin () {

	this->GetDependency < MOAIDescriptorSetLayoutImplVK >().RetireDescriptorSet ( *this );
}

//----------------------------------------------------------------//
MOAIDescriptorSetSnapshotVK* MOAIDescriptorSetSnapshotVK::MOAISnapshotFactoryVK_GetSnapshot () {

	return this;
}