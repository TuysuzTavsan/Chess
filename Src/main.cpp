#include <apl.h>

#include <ecs/ecs.h>

#include <text.h>
#include <random>

struct Transform
{
	float x;
	float y;
	float z;
};

class RigidBody
{
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
};

struct mySystem : public System<Transform>
{
	void Operate()
	{
		std::cout << "Updating transform system!\n";
		int i = 1;
		for (auto& x : pPool->pool)
		{
			//std::cout << "#" << i << "\t";
			i++;
			//std::cout << x.x << " " << x.y << " " << x.z << "\n";
			x.x++;
			x.y++;
			x.z++;
		}
	}

	void Operate2()
	{
		std::cout << "Printing transform system!\n";
		for (auto& x : pPool->pool)
		{
			std::cout << x.x << " " << x.y << " " << x.z << "\n";

		}
	}
};

int main()
{

	if (!APL::Init()) 
		return -1;

	std::srand(13);

	mySystem system;
	ECS::ComponentPool<Transform> pool;
	
	ECS::RegisterComponent<Transform>();
	system.AttachPool(&pool);

	for (int i = 0; i < 100; i++)
	{
		auto entity = ECS::CreateEntity();

		Transform transformC{ 
			static_cast<float>(std::rand()),
			static_cast<float>(std::rand()),
			static_cast<float>(std::rand()) };

		pool.InsertComponent(entity, transformC);
	}

	int i = 0;
	for (i = 0; i < 1000; i++)
	{
		system.Operate();
		
	}

	std::cout << "Operated #" << i << " times.\n";

	APL::Run();

	



	APL::Terminate();
	return 0;
}



