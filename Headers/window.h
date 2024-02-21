#pragma once

#include <glfw/glfw3.h>
#include <cstdint>
#include <stdexcept>

//TODO std::uint8 MAX VALUE EXCEPTION!!!!!!

/*
Safe window wrapper based on GLFWwindow object.
Behaves like a std::shared_ptr.
*/

class Window
{
public:

	Window()
		:
		ptr{ nullptr },
		refCount{ nullptr }
	{

	}

	Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr)
		:
		ptr(glfwCreateWindow(width, height, title, monitor, share)),
		refCount( new std::uint8_t{1})
	{	
		//Window creation failed. Throw error.
		if (ptr == nullptr)
		{
			throw std::logic_error("Window creation failed! SOURCE: Window class");
		}
	}
	
	~Window()
	{
		CleanUp();
	}

	//copy constructor.
	Window(const Window& other)
		:
		ptr(other.ptr),
		refCount(other.refCount)
	{
		if (refCount)
		{
			(*refCount)++;
		}
		
	}

	//copy assignment.
	Window& operator=(const Window& other)
	{
		//throw if operation is performed on same object.
		if (this == &other)
		{
			throw std::logic_error("Copy assigning same window object!");
		}

		//Check if this already has a valid window object. If so delete properly.
		if (ptr)
		{
			CleanUp();
		}

		//copy pointers and increase refcount.

		if (!other.ptr)
		{
			ptr = other.ptr;
			(*refCount)++;
		}
		

		return *this;

	}

	//move constructor. TODO: just copy assign? or move???
	Window(Window&& other) noexcept
		:
		ptr(std::move(other.ptr)),
		refCount(std::move(other.refCount))
	{
		other.ptr = nullptr;
		other.refCount = nullptr;
	}

	//move assignment operator.
	Window& operator=(Window&& other) noexcept
	{
		if (ptr)
		{
			CleanUp();
		}
		
		ptr = std::move(other.ptr);
		refCount = std::move(other.refCount);

		other.ptr = nullptr;
	}

	GLFWwindow* operator->() const
	{
		return ptr;
	}

	GLFWwindow* get()
	{
		return ptr;
	}

	void CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr)
	{
		if (ptr)
		{
			CleanUp();
		}

		ptr = (glfwCreateWindow(width, height, title, monitor, share));

		//Window creation failed. Throw error.
		if (ptr == nullptr)
		{
			throw std::logic_error("Window creation failed! SOURCE: Window class");
		}
	}

private:
	
	void CleanUp()
	{
		if (!refCount)
			return;

		//Always -1 refcount.
		(*refCount)--;

		if (*refCount == 0)
		{
			//Destroy glfw window when the refCount is 0.
			if (ptr)
			{
				glfwDestroyWindow(ptr);
			}

			//also delete refCount.
			delete refCount;

		}
	}

	GLFWwindow* ptr;
	std::uint8_t* refCount;

};