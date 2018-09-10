#include <iostream>
#include <string>

#include "calculator.h"

using namespace std;


int main(int argc, char* argv[])
{
	Calculator calc;
	string sInput;
	do
	{
		cout << "Please enter formula (empty input to quit):" << endl;
		getline(cin, sInput);
		if (sInput.empty())
			break;

		try
		{
			auto result = calc.Calculate(sInput);
			cout << "\"" << sInput << "\" = " << result << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << "; original input: " << sInput << endl << endl;
		}
	} while (sInput.size() > 0);
}
