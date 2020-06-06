// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIRENDERPASSVK_H
#define MOAIRENDERPASSVK_H

#include <moai-gfx-vk/MOAISnapshotVK.h>

class MOAICommandBufferVK;
class MOAILogicalDeviceVK;

//================================================================//
// MOAIRenderPassDescriptionVK
//================================================================//
class MOAIRenderPassDescriptionVK :
	public ZLRefCountedObject {
private:

	friend class MOAIRenderPassVK;
	
	typedef ZLLeanArray < VkAttachmentReference > ReferenceArray;
	typedef ZLLeanArray < u32 > PreserveArray;

	ZLLeanArray < u32 >							mClearTypes;

	ZLLeanArray < VkAttachmentDescription >		mAttachments;
	ZLLeanArray < VkSubpassDependency >			mDependencies;
	ZLLeanArray < ReferenceArray >				mReferenceArrays;
	ZLLeanArray < PreserveArray >				mPreserveArrays;
	ZLLeanArray < VkSubpassDescription >		mSubpasses;
};

// TODO: separate into render pass object and snapshot

//================================================================//
// MOAIRenderPassVK
//================================================================//
class MOAIRenderPassVK :
	public MOAISnapshotVK < MOAIRenderPassVK >,
	public ZLFinalizable_DependsOn < MOAILogicalDeviceVK > {
private:

	ZLStrongPtr < MOAIRenderPassDescriptionVK > mDescription;
	VkRenderPass mRenderPass;
	
	//----------------------------------------------------------------//
	void					AffirmDescription					();
	
	//----------------------------------------------------------------//
	void 					_Finalize							();
	void					MOAIAbstractSnapshotVK_OnPin		( MOAICommandBufferVK& commandBuffer );
	void					MOAIAbstractSnapshotVK_OnUnpin		();
	MOAIRenderPassVK*		MOAISnapshotFactoryVK_GetSnapshot	();

public:

	enum {
		CLEAR_NONE,
		CLEAR_COLOR,
		CLEAR_DEPTH_STENCIL,
	};

	IMPLEMENT_DEPENDS_ON ( MOAIRenderPassVK )

	//----------------------------------------------------------------//
	operator bool () const {
		return ( this->mRenderPass != VK_NULL_HANDLE );
	}
	
	//----------------------------------------------------------------//
	operator VkRenderPass* () {
		return &this->mRenderPass;
	}
	
	//----------------------------------------------------------------//
	operator VkRenderPass& () {
		return this->mRenderPass;
	}

	//----------------------------------------------------------------//
	void					AffirmRenderPass					( MOAILogicalDeviceVK& logicalDevice );
	ZLSize					CountAttachments					() const;
	u32						GetAttachmentClearType				( ZLIndex index ) const;
							MOAIRenderPassVK					();
							~MOAIRenderPassVK					();
	void					ReserveAttachments					( ZLSize count );
	void					ReserveDependencies					( ZLSize count );
	void					ReservePreserveArrays				( ZLSize count );
	void					ReservePreserves					( ZLIndex index, ZLSize count );
	void					ReserveReferenceArrays				( ZLSize count );
	void					ReserveReferences					( ZLIndex index, ZLSize count );
	void					ReserveSubpasses					( ZLSize count );
	void					SetAttachment						( ZLIndex index, const VkAttachmentDescription& description, u32 clearType = CLEAR_NONE );
	void					SetDependency						( ZLIndex index, const VkSubpassDependency& dependency );
	void					SetPreserve							( ZLIndex arrayIndex, ZLIndex subIndex, ZLIndex preserveIndex );
	void					SetReference						( ZLIndex arrayIndex, ZLIndex subIndex, const VkAttachmentReference& reference );
	void					SetSubpass							( ZLIndex index, VkPipelineBindPoint pipelineBindPoint, VkSubpassDescriptionFlags flags = 0 );
	void					SetSubpassColorReferenceArray		( ZLIndex index, ZLIndex arrayID );
	void					SetSubpassDepthStencilReference		( ZLIndex index, ZLIndex arrayID, ZLIndex refIndex = 0 );
	void					SetSubpassInputReferenceArray		( ZLIndex index, ZLIndex arrayID );
	void					SetSubpassPreserveIndexArray		( ZLIndex index, ZLIndex arrayID );
	void					SetSubpassResolveReferenceArray		( ZLIndex index, ZLIndex arrayID );
};

#endif