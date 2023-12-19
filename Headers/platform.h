#pragma once

#include <Windows.h>
#include "atlstr.h"


typedef Scriptable* (*MYFUNC)();

FILETIME GetTime(const char* path)
{

	HANDLE hFile;
	TCHAR fileName[512];
	FILETIME ftWrite;
	USES_CONVERSION;
	_tcscpy_s(fileName, A2T(path));

	hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);

	assert(hFile && "Error! Can not open specified file.");

	// Retrieve the file times for the file.
	assert(GetFileTime(hFile, NULL, NULL, &ftWrite) != 0);
		

	CloseHandle(hFile);

	return ftWrite;
}

bool IsClientChanged(const char* path, FILETIME lastTime)
{
	FILETIME newTime = GetTime(path);
	return(CompareFileTime(&lastTime, &newTime) != 0);

}



SceneManager* LoadClient(HINSTANCE& hInstance)
{
	hInstance = LoadLibrary(TEXT("C:\\Users\\fatma\\Desktop\\Client\\Build\\Debug\\Client.dll"));

	assert(hInstance && "Can not load specified library!");

	MYFUNC ProcAdd = (MYFUNC)GetProcAddress(hInstance, "CreateScript");

	assert(ProcAdd);


	Script* script = new Script(ProcAdd());
	Scene* scene1 = new Scene;
	SceneManager* manager = new SceneManager;

	scene1->AddScript(script);
	manager->AddScene(scene1);
	return manager;
}