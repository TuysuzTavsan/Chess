#include <apl.h>
#include <ecs/ecs.h>
#include <components/script.h>

class firstScript : public IScript
{
public:
	int count = 0;

	void Instantiate() override
	{
		std::cout << "Hello from the script!\n";
	}

	void Update(const float& dt) override
	{
		count++;
		std::cout << "Updating script!\t" << "#Frame# " << this->count << "\n";
	}

	void Free() override
	{
		std::cout << "Free called from the script! GOODBYE :( \n";
	}
};

class ScriptSystem : public System<Script>
{
public:
	void ScriptOnInit()
	{
		for (auto& script : this->pPool->pool)
		{
			script.funcInstantiate();
		}
	}
	void ScriptOnUpdate(const float& dt)
	{
		for (auto& script : this->pPool->pool)
		{
			script.funcUpdate(dt);
		}
	}
	void ScriptOnFree()
	{
		for (auto& script : this->pPool->pool)
		{
			script.funcFree();
		}
	}
};

int main()
{
	


	if (!APL::Init()) 
		return -1;

	ECS::Entity myentity = ECS::CreateEntity();

	ECS::RegisterComponent<Script>();
	ECS::ComponentPool<Script> scriptPool;

	

	firstScript firstscript;
	Script script = Scriptify(firstscript);
	scriptPool.InsertComponent(myentity, script);
	ScriptSystem scriptSystem;
	scriptSystem.AttachPool(&scriptPool);

	scriptSystem.ScriptOnInit();

	for (int i = 0; i < 50; i++)

	{
		scriptSystem.ScriptOnUpdate(13);
	}
	
	scriptSystem.ScriptOnFree();


	


	APL::Run();


	APL::Terminate();
	return 0;
}



