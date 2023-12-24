#include <apl.h>

int main()
{

	if (!APL::Init()) 
		return -1;

	APL::Run();

	APL::Terminate();
	return 0;
}



