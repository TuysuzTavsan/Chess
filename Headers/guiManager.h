#pragma once

#include<components/guiElement.h>
#include <ecs/System.h>
#include <glfw/glfw3.h>
#include <window.h>

/*
Top level class that manages all GUI components.
GUIManager will decide which components need to be updated and run their overrided onHot() functions based on cursor position and window active info.
*/

class GUIManager : System
{
public:

	GUIManager();
	~GUIManager();

	//Generic system base class function that will be called by SystemManager.
	void Operate(const float& dt) override;

	//Attach the window this GUIManager will be responsible from. GLFW window object will be used to check if the window is focused or not.
	void AttachWindow(const Window& window);

private:

	bool windowFocused; //flag that represents windows
	Window window; //Window pointer that GUIManager watching.TODO: how to manage window?
	float cursorPosition; //Cursorposition that updated each frame.

	//helper function to update cursor position and check for window focus.
	void UpdateCursorAndWindow();

};