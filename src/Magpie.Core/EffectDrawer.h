#pragma once
#include "pch.h"
#include "EffectDesc.h"
#include "MagOptions.h"
#include "SmallVector.h"


namespace Magpie::Core {

union EffectConstant32 {
	float floatVal;
	uint32_t uintVal;
	int32_t intVal;
};

class EffectDrawer {
public:
	EffectDrawer() = default;
	EffectDrawer(const EffectDrawer&) = delete;
	EffectDrawer(EffectDrawer&&) = default;

	bool Initialize(
		const EffectDesc& desc,
		const EffectOption& options,
		ID3D11Texture2D* inputTex,
		ID3D11Texture2D** outputTex,
		RECT* outputRect = nullptr,
		RECT* virtualOutputRect = nullptr
	);

	void Draw(UINT& idx, bool noUpdate = false);

	bool IsUseDynamic() const noexcept {
		return _desc.flags & EffectFlags::UseDynamic;
	}

	const EffectDesc& GetDesc() const noexcept {
		return _desc;
	}

private:
	void _DrawPass(UINT i);

	EffectDesc _desc;

	SmallVector<ID3D11SamplerState*> _samplers;
	SmallVector<winrt::com_ptr<ID3D11Texture2D>> _textures;
	std::vector<SmallVector<ID3D11ShaderResourceView*>> _srvs;
	// 后半部分为空，用于解绑
	std::vector<SmallVector<ID3D11UnorderedAccessView*>> _uavs;

	SmallVector<EffectConstant32, 32> _constants;
	winrt::com_ptr<ID3D11Buffer> _constantBuffer;

	SmallVector<winrt::com_ptr<ID3D11ComputeShader>> _shaders;

	SmallVector<std::pair<UINT, UINT>> _dispatches;
};

}
