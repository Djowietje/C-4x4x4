#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <iterator>
#include <d3dcompiler.h>

#include "Box.hpp"
#include "Drawable.hpp"
#include "DrawableWithSize.hpp"


namespace wrl = Microsoft::WRL;

class Graphics
{
public:
	Graphics(HWND, int, int);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void swapBackToFrontBuffer();
	ID3D11DeviceContext* getContextPointer();
	ID3D11Device* getDevicePointer();
	void clearBuffer(float red, float green, float blue) noexcept;
	void drawObject(DrawableWithSize);

private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> pTargetView;
};