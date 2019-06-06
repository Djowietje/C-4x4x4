#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <iterator>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <stdio.h>
#include <DirectXMath.h>
#include <dwrite.h>
#include "SpriteFont.h"

#include "Descriptors.hpp"
#include "ComPointers.hpp"
#include "Camera.hpp"
#include "Box.hpp"
#include "Drawable.hpp"
#include "DrawableWithSize.hpp"

namespace wrl = Microsoft::WRL;

class Window;

class Graphics
{
public:
	Graphics(HWND, int, int, Window*);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void swapBackToFrontBuffer();
	void clearBuffer(float red, float green, float blue) noexcept;
	void drawObject(DrawableWithSize*);
	ComPointers* getComPointer();
	Camera* getCamPointer();
	Window* getParent();
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
private:
	Descriptors* desc;
	ComPointers* cp;
	Camera* cam;
	D3D11_SUBRESOURCE_DATA vsd = {};
	D3D11_SUBRESOURCE_DATA isd = {};
	D3D11_SUBRESOURCE_DATA csd = {};
	IDWriteFactory* pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	Window* parent;


};