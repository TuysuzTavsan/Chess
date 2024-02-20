#include <apl.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


#include <Chess/clientScenes.h>
#include <Chess/clientComponents.h>
#include <Chess/clientSystems.h>


//Declaration of variables from Application namespace.
namespace APL 
{
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	unsigned int WINDOW_WIDTH = 800;
	unsigned int WINDOW_HEIGHT = 600;
	Mat4x4 Ortho;
	const char* WindowTitle = "Chess";
	GLFWwindow* window = nullptr;
	SceneManager sceneManager;
	SystemManager systemManager;
	double mousePosx = 0;
	double mousePosy = 0;
	AudioManager audioManager;
	bool AudioFlag = true;
	std::thread AudioThrd(AudioFunc);
}



void APL::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	APL::WINDOW_WIDTH = width;
	APL::WINDOW_HEIGHT = height;
	glViewport(0, 0, APL::WINDOW_WIDTH, APL::WINDOW_HEIGHT);
}

bool APL::Init()
{
	if (!glfwInit()) { std::cout << "Failed to initialize GLFW" << std::endl; return false; }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);


	window = glfwCreateWindow(APL::WINDOW_WIDTH, APL::WINDOW_HEIGHT, APL::WindowTitle, NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(APL::window, APL::framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!\n";
		return false;
	}

	stbi_set_flip_vertically_on_load(true);

	APL::Ortho = Mat4x4::Ortho(0.0f, (float)APL::WINDOW_WIDTH, 0.0f,
									 (float)APL::WINDOW_HEIGHT, -1.0f, 1000.0f);

	glEnable(GL_MULTISAMPLE);


	RegisterComponents();
	RegisterSystems();
	InitScenes();

	sceneManager.Request("main", SceneRequestType::start);

	if (!audioManager.Initialize())
		return false;

	return true;
};

void APL::InitScenes()
{
	std::vector<Scene> scenes(InitClientScenes());

	for (auto& sceneP : scenes)
	{
		sceneManager.AddScene(sceneP);
	}
	
}

void APL::RegisterComponents()
{
	RegisterClientComponents();
}

void APL::RegisterSystems()
{
	SetClientSystems(systemManager);
}

bool APL::load_img(const char* path, unsigned int& texture, int format)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture at" << path << std::endl;
		stbi_image_free(data);
		return false;
	}

	stbi_image_free(data);
	return true;
}

Vec2 APL::PosToScreen(const Vec2& position)
{
	Vec2 temp;
	temp.x = ((position.x) - APL::WINDOW_WIDTH / 2) / (APL::WINDOW_WIDTH / 2);
	temp.y = ((position.y) - APL::WINDOW_HEIGHT / 2) / (APL::WINDOW_HEIGHT / 2);
	return temp;
}

float APL::xPosToScreen(const float& position)
{
	return ((position)-APL::WINDOW_WIDTH / 2) / (APL::WINDOW_WIDTH / 2);
}

float APL::yPosToScreen(const float& position)
{
	return ((position)-APL::WINDOW_HEIGHT / 2) / (APL::WINDOW_HEIGHT / 2);
}

void APL::processInput(GLFWwindow* window)
{

}

void APL::SetDelta()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	APL::deltaTime = currentFrame - APL::lastFrame;
	APL::lastFrame = currentFrame;
}

void AudioThread()
{
	APL::audioManager.Update();
}

void APL::Run()
{

	while (!glfwWindowShouldClose(APL::window))
	{
		SetDelta();
		glfwGetCursorPos(APL::window, &APL::mousePosx, &APL::mousePosy);


		sceneManager.Update(APL::deltaTime);
		

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		systemManager.Update(APL::deltaTime);

		glfwSwapBuffers(APL::window);

		glfwPollEvents();
	}
	
}

void APL::Terminate()
{
	APL::AudioFlag = false;
	AudioThrd.join();
	audioManager.Terminate();
	glfwTerminate();
}

void APL::AudioFunc()
{
	while (APL::AudioFlag)
	{
		APL::audioManager.Update();
	}

}
