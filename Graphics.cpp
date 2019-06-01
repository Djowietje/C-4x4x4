#include "Graphics.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace dx = DirectX;

Graphics::Graphics(HWND hWnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 800;
	sd.BufferDesc.Height = 600;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);

	//Create a Render Target View
	ID3D11Resource* pBackBuffer = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	if (pDevice && pBackBuffer) pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTargetView);
	else throw "Device and/or Backbuffer was not succesfully created!";
	pBackBuffer->Release();

	// create pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	// bind pixel shader
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);


	// create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	// bind vertex shader
	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	// input (vertex) layout (2d position only)
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },

	};
	pDevice->CreateInputLayout(
		inputDesc, (UINT)std::size(inputDesc),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);

	// Bind Vertex Layout
	pContext->IASetInputLayout(pInputLayout.Get());

	// Bind Render Target View
	pContext->OMSetRenderTargets(1u, pTargetView.GetAddressOf(), nullptr);

	// Set Primitive Topology (how it will read the vertices)
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// Create ViewPort Config
	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	// Bind Viewport
	pContext->RSSetViewports(1u, &vp);
	
}

Graphics::~Graphics()
{
	if (pTargetView)  pTargetView->Release();
	if (pContext) pContext->Release();
	if (pSwap) pSwap->Release();
	if (pDevice) pDevice->Release();
}

void Graphics::swapBackToFrontBuffer()
{
	pSwap->Present(1u, 0u);
}

ID3D11DeviceContext* Graphics::getContextPointer()
{
	return pContext;
}

ID3D11Device* Graphics::getDevicePointer()
{
	return pDevice;
}

void Graphics::clearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTargetView.Get(), color);
}

void Graphics::drawObject(DrawableWithSize* struc)
{
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;

	D3D11_BUFFER_DESC vbd = {};
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = (UINT) (sizeof(Vertex) * struc->obj->getVertices()->size());
	vbd.StructureByteStride = sizeof(Vertex);

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = (UINT)(sizeof(Index) * struc->obj->getIndices()->size());
	ibd.StructureByteStride = sizeof(Index);

	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = (UINT) sizeof(dx::XMMATRIX);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = struc->obj->getVertices()->data();
	
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = struc->obj->getIndices()->data();

	auto location = struc->obj->getLocation();
	dx::XMMATRIX transform = {
		dx::XMMatrixTranspose(
			//dx::XMMatrixRotationZ(struc->obj->getRotationZ()) * 
			dx::XMMatrixScaling(3.0f/4.0f,1.0f,1.0f) *
			dx::XMMatrixTranslation(location->x, location->y, location->z)
		)
	};

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &transform;

	pDevice->CreateBuffer(&vbd, &vsd, &pVertexBuffer);
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//Bind index buffer
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	//Bind Constant buffer to Vertex shader
	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	//Size will be x 2 because we actually have 2 Index values in 1 Index -> From and To.
	pContext->DrawIndexed((UINT)struc->obj->getIndices()->size()*2,0u, 0u);}
