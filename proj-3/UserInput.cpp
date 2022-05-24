#include <iostream>
#include "UserInput.h"

int UserInput::getInput(const std::string &inputText, const std::function<bool(int)>& isCorrectInput)
{
	std::cout << inputText;
	int option;
	std::string input;
	while (true)
	{
		std::cin.clear();
		std::getline(std::cin, input);
		try
		{
			option = std::stoi(input);
			if (!isCorrectInput(option))
				std::cout << "Invalid input. Please try again: ";
			else
				break;
		}
		catch (std::exception &e)
		{
			std::cout << "Invalid input. Please try again: ";
		}
	}
	return option;
}

double UserInput::getInput(const std::string &inputText, const std::function<bool(double)>& isCorrectInput)
{
	std::cout << inputText;
	double option;
	std::string input;
	while (true)
	{
		std::cin.clear();
		std::getline(std::cin, input);
		try
		{
			option = std::stod(input);
			if (!isCorrectInput(option))
				std::cout << "Invalid input. Please try again: ";
			else
				break;
		}
		catch (std::exception &e)
		{
			std::cout << "Invalid input. Please try again: ";
		}
	}
	return option;
}

std::string UserInput::getInput(const std::string &inputText)
{
	std::cout << inputText;
	std::string input;
	std::cin.clear();
	std::getline(std::cin, input);
	return input;
}
