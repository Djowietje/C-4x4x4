#include "Descriptors.hpp"

Descriptors::Descriptors(HWND hWnd)
{
	setupSwapChainDesc(hWnd);
	setupBufferDescriptors();
	setupDepthStencilDescriptors();
	setupViewPort();
}

Descriptors::~Descriptors()
{
}

DXGI_SWAP_CHAIN_DESC* Descriptors::getSwapChainDesc()
{
	return &sd;
}

D3D11_BUFFER_DESC* Descriptors::getVertexBufferDesc()
{
	return &vbd;
}

D3D11_BUFFER_DESC* Descriptors::getIndicesBufferDesc()
{
	return &ibd;
}

D3D11_BUFFER_DESC* Descriptors::getConstantBufferDesc()
{
	return &cbd;
}

D3D11_DEPTH_STENCIL_DESC* Descriptors::getDepthStencilDesc()
{
	return &dsDesc;
}

D3D11_DEPTH_STENCIL_VIEW_DESC* Descriptors::getDepthStencilViewDesc()
{
	return &descDepthView;
}

D3D11_TEXTURE2D_DESC* Descriptors::getDepthDesc()
{
	return &descDepth;
}

D3D11_VIEWPORT* Descriptors::getViewPortDesc()
{
	return &vp;
}

void Descriptors::setupSwapChainDesc(HWND hWnd) {
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
}

void Descriptors::setupBufferDescriptors()
{
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.StructureByteStride = sizeof(Vertex);

	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.StructureByteStride = sizeof(Index);

	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = (UINT) sizeof(DirectX::XMMATRIX);
	cbd.StructureByteStride = 0u;
}

void Descriptors::setupDepthStencilDescriptors()
{
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS; // Only show closer z values.

	descDepth.Width = 800;
	descDepth.Height = 600;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	descDepthView.Format = DXGI_FORMAT_D32_FLOAT;
	descDepthView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepthView.Texture2D.MipSlice = 0u;
}

void Descriptors::setupViewPort()
{
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
}

void Descriptors::updateBufferDescriptors(size_t vertexSize, size_t indicesSize)
{
	vbd.ByteWidth = (UINT)(sizeof(Vertex) * vertexSize);
	ibd.ByteWidth = (UINT)(sizeof(Index) * indicesSize);
}