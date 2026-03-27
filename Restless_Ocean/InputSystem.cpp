#include <iostream>

#include "InputSystem.h"

int InputSystem::getInputInt(int min, int max)
{
	int input = 0;

	while (true)
	{
		std::cout << "> ";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "잘못 입력하였습니다.\n";
			std::cout << "다시 입력해주세요.\n";
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input < min && input > max)
		{
			std::cout << min << "과 " << max << " 사이의 값만 입력해주세요." << '\n';
			continue;
		}

		return input;
	}
}

std::string InputSystem::getInputStr()
{
	std::cout << "> ";
	std::string input;
	std::getline(std::cin, input);
	return input;
}
