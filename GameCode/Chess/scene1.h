#pragma once
#include <scene.h>
#include <Chess/firstscript.h>

Scene* InitScene1()
{
	NEW_SCENE(scene1);
	ADD_SCRIPT(scene1, firstScript);
	RETURN_SCENE(scene1);
}