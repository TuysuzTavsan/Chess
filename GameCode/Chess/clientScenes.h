#pragma once
#include <scene.h>
#include <Chess/firstscript.h>
#include <Chess/playButton.h>
#include <Chess/settingsButton.h>
#include <Chess/exitButton.h>
#include <vector>

#define NEW_SCENE(scenes, new_scene_name) Scene* new_scene_name = new Scene; scenes.push_back(new_scene_name); 
#define ADD_ENTITY(scene_name, new_script) scene_name->AddScript(new Script(new new_script))

void InitClientScenes(std::vector<Scene*>& scenes)
{
	NEW_SCENE(scenes, scene1);
	ADD_ENTITY(scene1, MenuBackGround);
	ADD_ENTITY(scene1, PlayButton);
	ADD_ENTITY(scene1, ExitButton);
	ADD_ENTITY(scene1, SettingsButton);

}