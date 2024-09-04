#pragma once
#include "Engine/Graphics/TextureManager/Texture/Texture.h"
#include "Engine/Core/DescriptorHeap/Descriptor.h"

#include "Utils/SafePtr.h"
#include <memory>

/// <summary>
/// ポストエフェクト用のレンダーターゲットリソース等を管理するクラス
/// </summary>
class RenderTarget final : public Descriptor {
public:
	RenderTarget();
	RenderTarget(uint32_t width, uint32_t height);
	~RenderTarget();

	RenderTarget(const RenderTarget&) = delete;
	RenderTarget(RenderTarget&&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	RenderTarget& operator=(RenderTarget&&) = delete;

public:
	// レンダーターゲットに設定する
	void SetThisRenderTarget(const D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle);

	void ChangeResourceState();

	// メインレンダーターゲットに変更(RenderTarget::SetThisTarget()を使ったら必ず呼ばなければならない)
	void SetMainRenderTarget(const D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle);

	// レンダーターゲットに設定したResourceをShaderResourceとして使う
	void UseThisRenderTargetShaderResource();

	void CreateView(D3D12_CPU_DESCRIPTOR_HANDLE heapHandleCPU,
		D3D12_GPU_DESCRIPTOR_HANDLE heapHandleGPU,
		UINT heapHandle
	);
	void CreateRTV(D3D12_CPU_DESCRIPTOR_HANDLE descHeapHandle, UINT descHeapHandleUINT);

	Texture* GetTex() const {
		return tex_.get();
	}

	const D3D12_CPU_DESCRIPTOR_HANDLE& GetRtvHandleCPU() const;
	UINT GetRtvHandleUINT() const;

public:
	static void SetRenderTargets(Lamb::SafePtr<RenderTarget*> renderTargetPtrs, uint32_t numRenderTarget, const D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle);
	static void SetMainAndRenderTargets(Lamb::SafePtr<RenderTarget*> renderTargetPtrs, uint32_t numRenderTarget, const D3D12_CPU_DESCRIPTOR_HANDLE* depthHandle);
	static void ResourceStateChangeRenderTargets(Lamb::SafePtr<RenderTarget*> renderTargetPtrs, uint32_t numRenderTarget);
	static void ClearRenderTargets(Lamb::SafePtr<RenderTarget*> renderTargetPtrs, uint32_t numRenderTarget);

private:
	Lamb::LambPtr<ID3D12Resource> resource_;
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle_;
	UINT rtvHeapHandleUint_;

	std::unique_ptr<Texture> tex_;

	bool isWrightResouceState_;

	uint32_t width_, height_;
};
