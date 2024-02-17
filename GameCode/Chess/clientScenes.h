#pragma once
#include <scene.h>
#include <Chess/firstscript.h>
#include <Chess/playButton.h>
#include <Chess/settingsButton.h>
#include <Chess/exitButton.h>
#include <vector>
#include <memory>

#define NEW_SCENE(scenes, new_scene_name) Scene new_scene_name; 
#define ADD_ENTITY(scene_name, scriptable_name) scene_name.AddScript(new scriptable_name);
#define PUSH_SCENE(scenes, scene_name) scenes.emplace_back(std::move(scene_name));

std::vector<Scene> InitClientScenes()
{
	std::vector<Scene> scenes;
	//NEW_SCENE(scenes, scene1);

	//ADD_ENTITY(scene1, MenuBackGround);
	//ADD_ENTITY(scene1, PlayButton);
	//ADD_ENTITY(scene1, ExitButton);
	//ADD_ENTITY(scene1, SettingsButton);

	//PUSH_SCENE(scenes, scene1);

	Scene scene1;

	scene1.AddScript(new MenuBackGround);
	scene1.AddScript(new PlayButton);
	scene1.AddScript(new ExitButton);
	scene1.AddScript(new SettingsButton);

	scenes.emplace_back(std::move(scene1));

	return scenes;
}