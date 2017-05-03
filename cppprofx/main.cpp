#include <iostream>
#include "long_int.h"

using namespace std;

void main()
{
	LONG_INT li1("1232432435598983843587485"), li2("395885473865763764576374");
	LONG_INT li3;
	li3 = li1 * li2;
	cout << li2 << endl;
	cout << li3 << endl;
	cout << "secondBranch" << endl;
}