// oav.cpp
#include <cassert>
#include "object.h"

using namespace std;
using namespace oav;

void test_object()
{
}

void test_array()
{
	{
		json_array a{json_value{}, json_value{1.2}, json_value{"foo"}, json_value{true}};
		assert (a.size() == 4);
		assert (a[1] == json_value{1.2});
	}
}

void test_value()
{
	{
		json_value v;
		assert (v.index() == 0);
		v = 1.2;
		assert (v.index() == 2);
		assert (get<1>(get<2>(v)) == 1.2);
		v = "foo";
		assert (v.index() == 2);
		v = true;
		assert (v.index() == 2);
	}
}


int main()
{
	test_object();
	test_array();
	test_value();

	return 0;
}