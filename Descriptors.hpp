#pragma once

#include "Drawable.hpp"
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

class Descriptors
{
public:
	Descriptors(HWND hWnd);
	~Descriptors();
	DXGI_SWAP_CHAIN_DESC* getSwapChainDesc();
	D3D11_BUFFER_DESC* getVertexBufferDesc();
	D3D11_BUFFER_DESC* getIndicesBufferDesc();
	D3D11_BUFFER_DESC* getConstantBufferDesc();
	D3D11_BUFFER_DESC* getColorBufferDesc();
	D3D11_DEPTH_STENCIL_DESC* getDepthStencilDesc();
	D3D11_DEPTH_STENCIL_VIEW_DESC* getDepthStencilViewDesc();
	D3D11_TEXTURE2D_DESC* getDepthDesc();
	D3D11_VIEWPORT* getViewPortDesc();

	void updateBufferDescriptors(size_t vertexSize, size_t indicesSize, size_t amountOfColors);

private:
	void setupSwapChainDesc(HWND hWnd);
	void setupBufferDescriptors();
	void setupDepthStencilDescriptors();
	void setupViewPort();

	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	D3D11_BUFFER_DESC vbd = { 0 };
	D3D11_BUFFER_DESC ibd = { 0 };
	D3D11_BUFFER_DESC cbd = { 0 };
	D3D11_BUFFER_DESC colorBufferDesc = { 0 };
	D3D11_DEPTH_STENCIL_DESC dsDesc = { 0 };
	D3D11_DEPTH_STENCIL_VIEW_DESC descDepthView = { };
	D3D11_TEXTURE2D_DESC descDepth = { 0 };
	D3D11_VIEWPORT vp = { 0 };


};