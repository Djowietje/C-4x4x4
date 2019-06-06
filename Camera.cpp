#include "Camera.hpp"

DirectX::XMVECTOR Camera::getPosition() { return DirectX::XMVECTOR{ posX, posY, posZ }; }

DirectX::XMVECTOR Camera::getLookAt() { return DirectX::XMVECTOR{ lookAtX, lookAtY, lookAtZ }; }

DirectX::XMMATRIX Camera::getViewMatrix()
{
	return viewMatrix;
}


void Camera::moveForward()
{
	posX += movementSpeed * sinf(yaw) * cosf(pitch);
	posY += movementSpeed * -sinf(pitch);
	posZ += movementSpeed * cosf(yaw) * cosf(pitch);

	updateViewMatrix();
}

void Camera::moveBackward()
{
	posX -= movementSpeed * sinf(yaw) * cosf(pitch);
	posY -= movementSpeed * -sinf(pitch);
	posZ -= movementSpeed * cosf(yaw) * cosf(pitch);

	updateViewMatrix();
}

void Camera::strafeLeft()
{
	posX -= movementSpeed * cosf(yaw) * cosf(pitch);
	posZ += movementSpeed * sinf(yaw) * cosf(pitch);

	updateViewMatrix();
}

void Camera::strafeRight()
{
	posX += movementSpeed * cosf(yaw) * cosf(pitch);
	posZ -= movementSpeed * sinf(yaw) * cosf(pitch);

	updateViewMatrix();
}

void Camera::mouseMoved(int x, int y)
{
	yaw -= (0.01f*x);// (x / 10);
	pitch += (0.01f * -y);
	cosPitch = cos(pitch);
	sinPitch = sin(pitch);
	cosYaw = cos(yaw);
	sinYaw = sin(yaw);

	xaxis = { cosYaw, 0, -sinYaw };
	yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	updateViewMatrix();
}

float Camera::getPosX()
{
	return posX;
}

float Camera::getPosY()
{
	return posY;
}

float Camera::getPosZ()
{
	return posZ;
}

void Camera::updateViewMatrix()
{
	viewMatrix = {
		xaxis.x,yaxis.x,zaxis.x,0.0f,
		xaxis.y,yaxis.y,zaxis.y,0.0f,
		xaxis.z,yaxis.z,zaxis.z,00.0f,
		-DirectX::XMVectorGetX(DirectX::XMVector3Dot(XMLoadFloat3(&xaxis), getPosition())),
		-DirectX::XMVectorGetX(DirectX::XMVector3Dot(XMLoadFloat3(&yaxis), getPosition())),
		-DirectX::XMVectorGetX(DirectX::XMVector3Dot(XMLoadFloat3(&zaxis), getPosition())), 1.0f
	};
}
