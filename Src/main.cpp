#include <apl.h>

int main()
{

	if (!APL::Init())
		return -1;

	APL::audioManager.Request("Resources/Waltz.wav", AudioAttribute::playOnce, 1.0);

	APL::Run();

	APL::Terminate();
	return 0;
}