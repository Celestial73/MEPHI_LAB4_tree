#include <iostream>
#include "./UI/menu.h"

using namespace std;

int main()
{
	try
	{
		menu();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	cout << "END" << endl;
}