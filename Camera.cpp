#include "Camera.hpp"

DirectX::XMVECTOR Camera::getPosition() { return DirectX::XMVECTOR{ posX, posY, posZ }; }

DirectX::XMVECTOR Camera::getLookAt() { return DirectX::XMVECTOR{ lookAtX, lookAtY, lookAtZ }; }

DirectX::XMMATRIX Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::setPosX(float x) { posX = x; }

void Camera::setPosY(float y) { posY = y; }

void Camera::setPosZ(float z) { posZ = z; }

void Camera::mouseMoved(int x, int y)
{
	yaw += (0.01f*x);// (x / 10);
	pitch += (0.01f * -y);
	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	DirectX::XMFLOAT3 xaxis = { cosYaw, 0, -sinYaw };
	DirectX::XMFLOAT3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	DirectX::XMFLOAT3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	viewMatrix = {
		xaxis.x,yaxis.x,zaxis.x,0.0f,
		xaxis.y,yaxis.y,zaxis.y,0.0f,
		xaxis.z,yaxis.z,zaxis.z,00.0f,
		-DirectX::XMVectorGetX(DirectX::XMVector3Dot(XMLoadFloat3(&xaxis), getPosition())), 
		-DirectX::XMVectorGetX(DirectX::XMVector3Dot(XMLoadFloat3(&yaxis), getPosition())),
		-DirectX::XMVectorGetX(DirectX::XMVector3Dot(XMLoadFloat3(&zaxis), getPosition())), 1.0f
	};
}

void Camera::setLookAtX(float x) { lookAtX = x; }

void Camera::setLookAtY(float y) { lookAtY = y; }

void Camera::setLookAtZ(float z) { lookAtZ = z; }
