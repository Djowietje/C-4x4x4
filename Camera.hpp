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

	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);

	void mouseMoved(int x, int y);
	void setLookAtX(float x);
	void setLookAtY(float y);
	void setLookAtZ(float z);

	

private:
	float posX = 1.0f;
	float posY = 1.0f;
	float posZ = 1.0f;

	float lookAtX = 0.0f;
	float lookAtY = 0.0f;
	float lookAtZ = 0.0f;

	float yaw = 0.0f;
	float pitch = 0.0f;

	DirectX::XMMATRIX viewMatrix;

};