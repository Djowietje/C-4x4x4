#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <iterator>
#include <d3dcompiler.h>
#include <stdio.h>
#include <DirectXMath.h>

#include "Descriptors.hpp"
#include "ComPointers.hpp"
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
	void clearBuffer(float red, float green, float blue) noexcept;
	void drawObject(DrawableWithSize*);
	ComPointers* getComPointer();
private:
	Descriptors* desc;
	ComPointers* cp;
	D3D11_SUBRESOURCE_DATA vsd = {};
	D3D11_SUBRESOURCE_DATA isd = {};
	D3D11_SUBRESOURCE_DATA csd = {};
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;


};