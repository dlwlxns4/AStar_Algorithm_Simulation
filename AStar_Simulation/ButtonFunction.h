#pragma once
#include "Config.h"
#include "Button.h"

class ButtonFunction
{
public:
	void ChangeScene(ArgumentFuncPtr* arg = nullptr);
	void QuitProgram(ArgumentFuncPtr* arg = nullptr);

};