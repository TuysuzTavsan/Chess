#pragma once
#include <scene.h>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <exception>

/*
SceneManager is a top level class that manages scenes.
ScenesManager can be accessed within a script to support scene changing and instancing.
*/

class SceneManager
{
public:

	SceneManager() = default;
	~SceneManager() = default;

	void Update(const float dt)
	{
		for (auto& scene : activeScenes)
		{
			scene.ScriptOnUpdate(dt);
		}
	}

	//Add a scene to the inActiveScene pool.
	void AddScene(Scene& scene)
	{
		inactiveScenes.emplace_back(std::move(scene));
	}

	//Start playing specified named scene.
	void StartScene(const std::string& _name)
	{
		//search
		auto it = std::find_if(inactiveScenes.begin(), inactiveScenes.end(), [&_name](Scene e) -> bool {return e.name == _name; });

		//Throw if not found.
		if (it == inactiveScenes.end())
		{
			throw std::logic_error("Can not find specified scene name!");
		}

		//init
		it->Prepare();
		it->ScriptOnInit();

		//move scene to active vector.
		activeScenes.emplace_back(std::move(it));
		inactiveScenes.erase(it);

	}

	//Stop playing specified named scene.
	void StopScene(const std::string& _name)
	{
		//search
		auto it = std::find_if(activeScenes.begin(), activeScenes.end(), [&_name](Scene e) -> bool {return e.name == _name; });

		//Throw if not found.
		if (it == activeScenes.end())
		{
			throw std::logic_error("Can not find specified scene name!");
		}

		//Call onFree script functions.
		it->ScriptOnFree();

		//free
		it->Free();

		//erase from active vector.
		activeScenes.erase(it);
	}

private:

	std::vector<Scene> inactiveScenes;
	std::vector<Scene> activeScenes;

};