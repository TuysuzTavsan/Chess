#pragma once
#include <scene.h>
#include <Chess/menuBackground.h>
#include <Chess/playButton.h>
#include <Chess/settingsButton.h>
#include <Chess/exitButton.h>
#include <Chess/settingsBackground.h>
#include <Chess/backMainButton.h>

#include <vector>
#include <memory>

#define NEW_SCENE(scenes, new_scene_name) Scene new_scene_name(std::string(#new_scene_name)); 
#define ADD_ENTITY(scene_name, scriptable_name) scene_name.AddScript(new scriptable_name);
#define PUSH_SCENE(scenes, scene_name) scenes.emplace_back(std::move(scene_name));

std::vector<Scene> InitClientScenes()
{
	std::vector<Scene> scenes;
	NEW_SCENE(scenes, main);

	ADD_ENTITY(main, MenuBackGround);
	ADD_ENTITY(main, PlayButton);
	ADD_ENTITY(main, ExitButton);
	ADD_ENTITY(main, SettingsButton);

	PUSH_SCENE(scenes, main);


	NEW_SCENE(scenes, settings);

	ADD_ENTITY(settings, SettingsBackground);
	ADD_ENTITY(settings, backMainButton);

	PUSH_SCENE(scenes, settings);



	return scenes;
}