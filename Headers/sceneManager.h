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

enum SceneRequestType
{
	start,
	stop
};

struct SceneRequest
{
	SceneRequest(const std::string& _name, SceneRequestType _type)
		:
		name{_name},
		type{_type}
	{
		
	}

	std::string name;
	SceneRequestType type;
};

class SceneManager
{
public:

	SceneManager() = default;
	~SceneManager() = default;

	void Update(const float dt)
	{
		//Process scene requests before running update on scripts.
		for (auto it = requests.begin(); it != requests.end();)
		{

			if (it->type == SceneRequestType::stop)
			{
				StopScene(it->name);
			}
			
			if (it->type == SceneRequestType::start)
			{
				StartScene(it->name);
			}

			//Request is processed, remove it from the vector.
			it = requests.erase(it);

		}

		//Run update on scripts.
		for (auto& scene : activeScenes)
		{
			scene.ScriptOnUpdate(dt);
		}

	}

	//Request a scene to play or stop. Scene names must be unique.
	void Request(const std::string& _name, SceneRequestType _type)
	{
		requests.emplace_back(SceneRequest(_name, _type));
	}

	//Add a scene to the inActiveScene pool.
	void AddScene(Scene& scene)
	{
		inactiveScenes.emplace_back(std::move(scene));
	}

private:

	//Start playing specified named scene.
	void StartScene(const std::string& _name)
	{
		//search
		auto it = std::find_if(inactiveScenes.begin(), inactiveScenes.end(), [&_name](const Scene& e) -> bool {return e.name == _name; });

		//Throw if not found.
		if (it == inactiveScenes.end())
		{
			throw std::logic_error("Can not find specified scene name!");
		}
		//init
		it->Prepare();
		it->ScriptOnInit();

		//move scene to active vector.
		activeScenes.emplace_back(std::move(*it));
		inactiveScenes.erase(it);

	}

	//Stop playing specified named scene.
	void StopScene(const std::string& _name)
	{
		//search
		auto it = std::find_if(activeScenes.begin(), activeScenes.end(), [&_name](const Scene& e) -> bool {return e.name == _name; });

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
		inactiveScenes.emplace_back(std::move(*it));
		activeScenes.erase(it);
	}

	std::vector<Scene> inactiveScenes;
	std::vector<Scene> activeScenes;
	std::vector<SceneRequest> requests;
	

};