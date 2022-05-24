#pragma once

#include <string>
#include <functional>

class UserInput
{
public:
	static int getInput(const std::string &inputText, const std::function<bool(int)>& isCorrectInput);
	static double getInput(const std::string &inputText, const std::function<bool(double)>& isCorrectInput);
	static std::string getInput(const std::string &inputText);
};