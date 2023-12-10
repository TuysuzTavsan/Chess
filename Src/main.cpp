#include <apl.h>
#include <ecs/ecs.h>
#include <components/script.h>



struct Transform
{
	float x, y, z;
};

System<Transform> transformSystem;

class firstScript : public Scriptable
{
public:
	int count = 0;

	void Instantiate() override
	{
		std::cout << "Hello from the script!\n";
		transformSystem.InsertComponent(instance, Transform());
		auto temp = ECS::GetComponent<Transform>(instance);
		std::cout << "Transform component: X: " << temp->x << " Y: " << temp->y << " Z: " 
			<< temp->z << "\n";
		
	}

	void Update(const float& dt) override
	{

		auto temp = ECS::GetComponent<Transform>(instance);
		temp->x++;
		temp->y++;
		temp->z++;

		count++;
		std::cout << "Updating script!\t" << "#Frame# " << this->count << "\n";
	}

	void Free() override
	{
		std::cout << "Free called from the script! GOODBYE :( \n";
		auto temp = ECS::GetComponent<Transform>(instance);
		std::cout << "Transform component: X: " << temp->x << " Y: " << temp->y << " Z: " 
			<< temp->z << "\n";

	}
};



int main()
{
	


	if (!APL::Init()) 
		return -1;
	
	firstScript firstscript;
	ScriptComponent script;
	script.Scriptify(firstscript);
	ScriptSystem scriptSystem;
	scriptSystem.PushBack(script);

	scriptSystem.Instantiate();

	scriptSystem.ScriptOnInit();

	for (int i = 0; i < 50; i++)

	{
		scriptSystem.ScriptOnUpdate(13);
	}
	
	scriptSystem.ScriptOnFree();
	scriptSystem.Free();

	


	APL::Run();


	APL::Terminate();
	return 0;
}



