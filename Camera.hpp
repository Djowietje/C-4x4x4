#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera() {};
	~Camera() {};

	DirectX::XMVECTOR getPosition();
	DirectX::XMVECTOR getLookAt();
	DirectX::XMMATRIX getViewMatrix();

	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void mouseMoved(int x, int y);

	float getPosX();
	float getPosY();
	float getPosZ();


private:
	float posX = 1.0f;
	float posY = 1.0f;
	float posZ = 1.0f;

	float lookAtX = 0.0f;
	float lookAtY = 0.0f;
	float lookAtZ = 0.0f;

	float movementSpeed = 0.1f;

	float yaw = 0.0f;
	float pitch = 0.0f;

	float cosPitch = 0.0f;
	float sinPitch = 0.0f;
	float cosYaw = 0.0f;
	float sinYaw = 0.0f;

	DirectX::XMMATRIX viewMatrix = {};
	DirectX::XMFLOAT3 xaxis = {};
	DirectX::XMFLOAT3 yaxis = {};
	DirectX::XMFLOAT3 zaxis = {};

	void updateViewMatrix();

};