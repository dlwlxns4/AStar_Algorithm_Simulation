#include "ButtonFunction.h"

void ButtonFunction::ChangeScene(ArgumentFuncPtr* arg)
{
	SceneManager::GetSingleton()->ChangeScene(arg->sceneName, arg->loadingSceneName);
}

void ButtonFunction::QuitProgram(ArgumentFuncPtr* arg)
{
	PostQuitMessage(0);
}
