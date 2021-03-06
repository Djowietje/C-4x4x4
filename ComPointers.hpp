#pragma once

#include <wrl.h>
#include <d3d11.h>

namespace wrl = Microsoft::WRL;

class ComPointers
{
public:
	ComPointers(){};
	~ComPointers(){

		if(pVertexBuffer) pVertexBuffer->Release();
		if(pIndexBuffer) pIndexBuffer->Release();
		if(pConstantBuffer) pConstantBuffer->Release();
		if(pColorBuffer) pColorBuffer->Release();

		if(pPixelShader) pPixelShader->Release();
		if(pVertexShader) pVertexShader->Release();
		if(pBlob) pBlob->Release();
		if(pInputLayout) pInputLayout->Release();
		if(pDSState) pDSState->Release();
		if(pDepthStencil) pDepthStencil->Release();
		if(pDepthStencilView) pDepthStencilView->Release();

		if (pTargetView) pTargetView->Release();
		if (pContext) pContext->Release();
		if (pSwap) pSwap->Release();
		if (pDevice) pDevice->Release();
	};

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState; 
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	wrl::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
	
	wrl::ComPtr<ID3D11Device> pDevice;
	wrl::ComPtr<IDXGISwapChain> pSwap;
	wrl::ComPtr<ID3D11DeviceContext> pContext;
	wrl::ComPtr<ID3D11RenderTargetView> pTargetView;
	
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	wrl::ComPtr<ID3D11Buffer> pColorBuffer;


private:
};