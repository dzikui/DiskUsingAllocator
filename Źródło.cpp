#include <iostream>
#include <vector>
#include "plik.h"

using namespace std;


int main()
{
	std::vector<int, std::My_Own_Allocator<int>> my_vector;
	my_vector.emplace_back(1);
	std::cout << endl;
	system("pause");
	return 0;
}

