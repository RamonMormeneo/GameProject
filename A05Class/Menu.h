#pragma once
#include "Scene.h"
#include "Renderer.h"
class Menu : public Scene
{
public:
	Text Play;
	Text Exit;
	Font Nube;
	
	Menu();
	~Menu();
	void EventHandeler() override;
	void Update() override;
	void Draw() override;
private:
};