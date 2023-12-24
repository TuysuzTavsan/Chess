#include <apl.h>

#include <newECS/ECSManager.h>
#include <components/mesh.h>
#include <newECS/System.h>

#include <newScene/scene.h>
#include <components/script.h>
#include <firstscript.h>

class TempSystem : public System
{
public:
	void Operate() override
	{
		ECSManager* manager = ECSManager::getManager();
		

		for (auto& mesh : manager->GetPoolData<Mesh>())
		{
			mesh.x++;
			mesh.y++;
			mesh.z++;
		}
	}
};



int main()
{

	if (!APL::Init()) 
		return -1;
	

	//pseudo code start

	ECSManager* manager = ECSManager::getManager();
	Entity arda = manager->CreateEntity();
	manager->RegisterComponent<Mesh>();
	manager->InsertComponent<Mesh>(arda, Mesh{ 13,13,14 });
	Entity fuat = manager->CreateEntity();
	manager->FreeEntity(arda);
	Entity emine = manager->CreateEntity();
	manager->InsertComponent<Mesh>(emine, Mesh{ 1,100,231 });
	manager->InsertComponent<Mesh>(fuat, Mesh{ 333,333,444 });

	//pseudo code for scripting

	SceneManager* sceneManager = new SceneManager;
	Scene* scene = new Scene;
	scene->AddScript(new Script(new firstScript));
	sceneManager->AddScene(scene);

	sceneManager->ReadyScenes();

	for (int i = 0; i < 10000; i++)
	{
		sceneManager->Play();
	}



	TempSystem tempSystem;

	for (int i = 0; i < 100000; i++)
	{
		tempSystem.Operate();
	}


	//pseudo code end

	APL::Run();

	APL::Terminate();
	return 0;
}



