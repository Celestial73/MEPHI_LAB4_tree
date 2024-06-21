#include <iostream>
#include "./UI/menu.h"
#include "./tests/PriorityQueue_tests.h"

using namespace std;

int main()
{
	try
	{
		testPriorityQueue();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	cout << "END" << endl;
}