#include <apl.h>

#include <newECS/ECSManager.h>
#include <components/mesh.h>

//#include <firstscript.h>
//#include <scene/scene.h>


int main()
{

	if (!APL::Init()) 
		return -1;

	//pseudo code
	/*SceneManager* manager = new SceneManager;
	Scene* scene1 = new Scene;

	scene1->AddScript(new Script(new firstScript));
	
	manager->AddScene(scene1);
	manager->ReadyScenes();
	bool run = true;
	int a = 0;
	while (run)
	{
		a++;
		manager->Play();
		run = (a != 50);
	}*/
	
	ECSManager manager;
	Entity arda = manager.CreateEntity();
	manager.RegisterComponent<Mesh>();
	manager.InsertComponent<Mesh>(arda, Mesh{ 13,13,14 });
	Entity fuat = manager.CreateEntity();
	manager.FreeEntity(arda);
	Entity emine = manager.CreateEntity();
	manager.FreeEntity(emine);

	APL::Run();

	APL::Terminate();
	return 0;
}



