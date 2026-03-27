#pragma once
#include <string>

class InputSystem
{
public:
	// min과 max 사이의 값만 return
	static int getInputInt(int min, int max);
	static std::string getInputStr();
};

