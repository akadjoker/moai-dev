// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIPIPELINESNAPSHOTVK_H
#define MOAIPIPELINESNAPSHOTVK_H

#include <moai-gfx-vk/MOAIGfxConstsVK.h>
#include <moai-gfx-vk/MOAIGfxStructVK.h>
#include <moai-gfx-vk/MOAIPipelineLayoutVK.h>
#include <moai-gfx-vk/MOAIShaderProgramVK.h>
#include <moai-gfx-vk/MOAIShaderVK.h>
#include <moai-gfx-vk/MOAISnapshotVK.h>
#include <moai-gfx-vk/MOAIVertexFormatVK.h>

class MOAIPipelineCachePageVK;
class MOAIPipelineCacheVK;
class MOAIPipelineParamsVK;

typedef ZLRefKey < MOAIPipelineParamsVK > MOAIPipelineKeyVK;

//================================================================//
// MOAIPipelineParamsVK
//================================================================//
class MOAIPipelineParamsVK {
public:

	MOAILogicalDeviceVK* 	mLogicalDevice;
	VkRenderPass* 			mRenderPass;
	VkPrimitiveTopology 	mTopology;
	MOAIVertexFormatVK* 	mVertexFormat;
	MOAIShaderVK* 			mShader;
	MOAIBlendMode* 			mBlendMode;

	//----------------------------------------------------------------//
	bool operator < ( const MOAIPipelineParamsVK& other ) const {
	
		return ( memcmp ( this, &other, sizeof ( MOAIPipelineParamsVK )) < 0 );
	}

	//----------------------------------------------------------------//
	MOAIPipelineParamsVK (
		MOAILogicalDeviceVK& logicalDevice,
		VkRenderPass& renderPass,
		VkPrimitiveTopology topology,
		MOAIVertexFormatVK* vertexFormat,
		MOAIShaderVK* shader,
		MOAIBlendMode* blendMode = NULL
	) {
		this->mLogicalDevice	= &logicalDevice;
		this->mRenderPass		= &renderPass;
		this->mTopology			= topology;
		this->mVertexFormat		= vertexFormat;
		this->mShader			= shader;
		this->mBlendMode		= blendMode;
	}
};

//================================================================//
// MOAIPipelineSnapshotVK
//================================================================//
class MOAIPipelineSnapshotVK :
	public MOAISnapshotVK < MOAIPipelineSnapshotVK >,
	public ZLFinalizable_DependsOn < MOAILogicalDeviceVK >,
	public MOAIPipelineParamsVK {
protected:

	friend class MOAIPipelineCacheVK;
	friend class MOAIPipelineCachePageVK;

	MOAIPipelineCacheVK*		mCache;
	MOAIPipelineCachePageVK*	mPage;

	MOAIPipelineKeyVK			mKey;
	VkPipeline					mPipeline;

	//----------------------------------------------------------------//
	void 				_Finalize							();
	void				MOAIAbstractSnapshotVK_OnPin		( MOAICommandBufferVK& commandBuffer );
	void				MOAIAbstractSnapshotVK_OnUnpin		();
	MOAIPipelineSnapshotVK*		MOAISnapshotFactoryVK_GetSnapshot	();

public:

	IMPLEMENT_DEPENDS_ON ( MOAIPipelineSnapshotVK )

	//----------------------------------------------------------------//
	operator bool () const {
		return ( this->mPipeline != VK_NULL_HANDLE );
	}
	
	//----------------------------------------------------------------//
	operator const MOAIPipelineKeyVK () const {
		return this->mKey;
	}
	
	//----------------------------------------------------------------//
	operator VkPipeline* () {
		return &this->mPipeline;
	}
	
	//----------------------------------------------------------------//
	operator VkPipeline& () {
		return this->mPipeline;
	}

	//----------------------------------------------------------------//
					MOAIPipelineSnapshotVK			( const MOAIPipelineParamsVK& params );
					~MOAIPipelineSnapshotVK			();
};

#endif