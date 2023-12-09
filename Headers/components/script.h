#ifndef SCRIPT_COMPONENT
#define SCRIPT_COMPONENT

#include <functional>

/*
* Goal: Have a script component that will provide a interface for
* update
* instantiate
* free 
* methods.
*/

//Interface for a script
class IScript
{
public:
	virtual ~IScript() = default;

	virtual void Instantiate() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Free() = 0;
};

struct Script
{
	std::function<void()> funcInstantiate;
	std::function<void(const float&)> funcUpdate;
	std::function<void()> funcFree;
};

Script Scriptify(IScript& iscript)
{
	Script temp;
	temp.funcInstantiate = [&iscript]() -> void { iscript.Instantiate(); };
	temp.funcUpdate = [&iscript](const float& dt) -> void { iscript.Update(dt); };
	temp.funcFree = [&iscript]() -> void {iscript.Free(); };
	return temp;
}

////Will hold scripted entitys in a place and then run their scripts.
//class ScriptSystem
//{
//
//};

#endif // !SCRIPT_COMPONENT
