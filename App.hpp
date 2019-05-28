#include "Main.hpp"

class App
{
public:
	App();
	int setup();
	std::optional<int> processMessages();
private:
	void update();
	Window* window;
};