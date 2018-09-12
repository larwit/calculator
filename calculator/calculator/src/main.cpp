#include <iostream>
#include <string>

#include "calculator.h"

using namespace std;


int main(int argc, char* argv[])
{
	calculator::Calculator calc;
	string input;
	do
	{
		cout << "Please enter formula (empty input to quit):" << endl;
		getline(cin, input);
		if (input.empty())
			break;

		try
		{
			auto result = calc.Calculate(input);
			cout << "\"" << input << "\" = " << result << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << "; original input: " << input << endl << endl;
		}
	} while (input.size() > 0);
}
