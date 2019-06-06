#include "Graphics.hpp"
#include "Window.hpp"

#include <map>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace dx = DirectX;

Graphics::Graphics(HWND hWnd, int width, int height, Window* _parent)
{
	parent = _parent;
	desc = new Descriptors(hWnd);
	cp = new ComPointers();
	cam = new Camera();

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		desc->getSwapChainDesc(),
		&cp->pSwap,
		&cp->pDevice,
		nullptr,
		&cp->pContext
	);

	//Create a Render Target View
	ID3D11Resource* pBackBuffer = nullptr;
	cp->pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	if (cp->pDevice && pBackBuffer) cp->pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &cp->pTargetView);
	else throw "Device and/or Backbuffer was not succesfully created!";
	pBackBuffer->Release();

	//Create a Font ( for drawing text )
	m_font = std::make_unique<DirectX::SpriteFont>(cp->pDevice.Get(), L"Courier.spritefont");
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(cp->pContext.Get());

	//Create Shaders
	D3DReadFileToBlob(L"PixelShader.cso", &cp->pBlob);
	cp->pDevice->CreatePixelShader(cp->pBlob->GetBufferPointer(), cp->pBlob->GetBufferSize(), nullptr, &cp->pPixelShader);

	D3DReadFileToBlob(L"VertexShader.cso", &cp->pBlob);
	cp->pDevice->CreateVertexShader(cp->pBlob->GetBufferPointer(), cp->pBlob->GetBufferSize(), nullptr, &cp->pVertexShader);

	//Bind Shaders
	cp->pContext->PSSetShader(cp->pPixelShader.Get(), nullptr, 0u);
	cp->pContext->VSSetShader(cp->pVertexShader.Get(), nullptr, 0u);

	//Input Descriptor of Vertex Data
	const D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },

	};

	cp->pDevice->CreateInputLayout(
		inputDesc, (UINT)std::size(inputDesc),
		cp->pBlob->GetBufferPointer(),
		cp->pBlob->GetBufferSize(),
		&cp->pInputLayout
	);

	// Bind Vertex Layout
	cp->pContext->IASetInputLayout(cp->pInputLayout.Get());

	// Set Primitive Topology (how it will read the vertices)
	cp->pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// Bind Viewport
	cp->pContext->RSSetViewports(1u, desc->getViewPortDesc());

	//Setup Depth Stencil State
	cp->pDevice->CreateDepthStencilState(desc->getDepthStencilDesc(), &cp->pDSState);
	
	//Bind Depth Stencil State
	cp->pContext->OMSetDepthStencilState(cp->pDSState.Get(), 1u);

	//Create Depth Stencil Texture	
	cp->pDevice->CreateTexture2D(desc->getDepthDesc(), nullptr, &cp->pDepthStencil);
	
	auto a = cp->pDepthStencil.Get();
	auto b = desc->getDepthStencilViewDesc();
	auto c = cp->pDepthStencilView.GetAddressOf();

	cp->pDevice->CreateDepthStencilView(a,b,c);

	// Bind Render Target View
	cp->pContext->OMSetRenderTargets(1u, cp->pTargetView.GetAddressOf(), cp->pDepthStencilView.Get());
	
}

Graphics::~Graphics()
{
	cp->~ComPointers();
}

void Graphics::swapBackToFrontBuffer()
{
	cp->pSwap->Present(1u, 0u);
}


void Graphics::clearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue, 1.0f };
	cp->pContext->ClearRenderTargetView(cp->pTargetView.Get(), color);
	cp->pContext->ClearDepthStencilView(cp->pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::drawObject(DrawableWithSize* struc)
{
	D3D11_SUBRESOURCE_DATA colorData;

	dx::XMMATRIX transform = {
		dx::XMMatrixTranspose(
			dx::XMMatrixRotationX(struc->obj->getRotation()->x) *
			dx::XMMatrixRotationY(struc->obj->getRotation()->y) *
			dx::XMMatrixRotationZ(struc->obj->getRotation()->z) *
			dx::XMMatrixScaling(struc->obj->getScale(), struc->obj->getScale(), struc->obj->getScale()) *
			dx::XMMatrixTranslation(struc->obj->getLocation()->x, struc->obj->getLocation()->y, struc->obj->getLocation()->z + 1.0f) *
			cam->getViewMatrix() *
			dx::XMMatrixPerspectiveFovLH(70.0f, 800.0f/600.0f, 0.1f, 100.0f)
		)
	};

	std::vector<unsigned short>* indices;
	if (struc->obj->getDrawMode() == 0) {
		indices = struc->obj->getIndices();
	}
	else {
		cp->pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		indices = struc->obj->getIndicesTriangles();
	}

	desc->updateBufferDescriptors(struc->obj->getVertices()->size(), indices->size(), 1);


	vsd.pSysMem = struc->obj->getVertices()->data();
	isd.pSysMem = indices->data();
	csd.pSysMem = &transform;
	colorData.pSysMem = struc->obj->getColor();

	cp->pDevice->CreateBuffer(desc->getVertexBufferDesc(), &vsd, &cp->pVertexBuffer);
	cp->pDevice->CreateBuffer(desc->getIndicesBufferDesc(), &isd, &cp->pIndexBuffer);
	cp->pDevice->CreateBuffer(desc->getConstantBufferDesc(), &csd, &cp->pConstantBuffer);
	cp->pDevice->CreateBuffer(desc->getColorBufferDesc(), &colorData, &cp->pColorBuffer);

	// Bind vertex buffer to pipeline
	cp->pContext->IASetVertexBuffers(0u, 1u, cp->pVertexBuffer.GetAddressOf(), &stride, &offset);

	//Bind index buffer to pipeline
	cp->pContext->IASetIndexBuffer(cp->pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	//Bind Constant buffer to Vertex shader
	cp->pContext->VSSetConstantBuffers(0u, 1u, cp->pConstantBuffer.GetAddressOf());

	//Bind Color buffer to Pixel shader
	cp->pContext->PSSetConstantBuffers(0u, 1u, cp->pColorBuffer.GetAddressOf());

	//Draw the object
	cp->pContext->DrawIndexed((UINT)indices->size(),0u, 0u);

	//Set drawmode back to default:
	cp->pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

}



ComPointers* Graphics::getComPointer()
{
	return cp;
}

Camera* Graphics::getCamPointer()
{
	return cam;
}

Window* Graphics::getParent()
{
	return parent;
}

