#include "Main.hpp"
#include "DrawableWithSize.hpp"
#include <chrono>

class App
{
public:
	App();
	int setup();
	std::optional<int> processMessages();
private:
	void update();
	void draw();
	Window* window;
	DrawableWithSize** objectsToDraw;
	int amountOfObjects= 0;
	ID3D11DeviceContext* pContext;
	ID3D11Device* pDevice;
	float backGroundColor = 0.0f;
	float counter = 0.0f;
};