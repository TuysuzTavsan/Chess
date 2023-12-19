#include <apl.h>


#include <firstscript.h>
#include <scene/scene.h>


int main()
{

	if (!APL::Init()) 
		return -1;

	//pseudo code
	SceneManager* manager = new SceneManager;
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
	}


	APL::Run();

	APL::Terminate();
	return 0;
}



