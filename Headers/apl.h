#ifndef APPLICATION_H
#define APPLICATION_H
#include <glad/glad.h>
#include <Types/matrix.h>
#include <Types/vector.h>
#include <glfw/glfw3.h>
#include <scene.h>
#include <sceneManager.h>
#include <ecs/SystemManager.h>
#include <AudioEngine/audioManager.h>
#include <thread>

/*
Application name space which holds information and functions related to app.
Also contains helper functions such as loading image, cordinate helper functions.
*/

namespace APL
{
	extern float deltaTime;	// Time between current frame and last frame
	extern float lastFrame; // Time of last frame
	extern unsigned int WINDOW_WIDTH; // Window width.
	extern unsigned int WINDOW_HEIGHT; // Window height.
	extern Mat4x4 Ortho; // Orthographic matrix which used in 2D shaders.
	extern const char* WindowTitle; // Title of the window.
	extern GLFWwindow* window; // GLFW window object.
	extern SceneManager sceneManager;
	extern SystemManager systemManager;
	extern double mousePosx;
	extern double mousePosy;
	extern AudioManager audioManager;
	extern bool AudioFlag;
	extern std::thread AudioThrd;

	
	//Initiliaze window and other minor stuff.
	bool Init();

	//Initiliaze scenes.
	void InitScenes();

	//Register all needed component parts.
	void RegisterComponents();

	//Get the system from client.
	void RegisterSystems();

	//Framebuffer callback function.
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//This function will return true on success and false on failure.
	//Load image from specified path.
	bool load_img(const char* path, unsigned int& texture, int format);
	
	//Returns normalized Vec2 from a position.
	Vec2 PosToScreen(const Vec2& position);

	//Returns normalized screen x value.
	float xPosToScreen(const float& position);

	//Returns normalized screen y value.
	float yPosToScreen(const float& position);

	//Main process function for inputs for now.
	void processInput(GLFWwindow* window);

	//Calculate delta time.
	void SetDelta();

	//Main loop of the application.
	void Run();

	//Terminate application.
	void Terminate();

	void AudioFunc();
}




#endif // !APPLICATION_H

