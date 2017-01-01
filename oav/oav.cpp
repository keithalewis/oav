// oav.cpp
#include <cassert>
#include "object.h"

using namespace std;
using namespace oav;

using json_variant = std::variant<std::monostate, double, std::string, bool>;
using json_object = oav::object<std::string, json_variant>;
using json_array = oav::array<std::string, json_variant>;
using json_value = oav::value<std::string, json_variant>;

using json_index = oav::index<std::string>;

void test_object()
{
	{
		json_object o{
			{"null", json_value{}},
			{"number", json_value{1.23}},
			{"string", json_value{"foo"}},
			{"boolean", json_value{true}}
		};
		assert (o.size() == 4);
		assert (o["null"] == json_value{});
		assert (o["number"] == json_value{1.23});
		assert (o["string"] == json_value{"foo"});
		assert (o["boolean"] == json_value{true});
	}
/*
{
		json_object o  = {
			{"null", {}},
			{"number", 1.23},
			{"string", "foo"},
			{"boolean", true},
		};
		o["object"] = o;
		assert (o.size()) == 5);
		const auto& oo = o["object"];
	}
	*/
}

void test_array()
{
	{
		json_array a{json_value{}, json_value{1.2}, json_value{"foo"}, json_value{true}};
		assert (a.size() == 4);
		assert (a[1] == json_value{1.2});
	}
	/*
	{
		json_array a{{}, 1.2, "foo", true};
		assert (a.size() == 4);
		assert (a[1] == json_value{1.2});
	}
	*/
}

void test_value()
{
	{
		json_value v;
		assert (v.is_value());

		v = 1.2;
		assert (v.is_value());
		assert (v == json_variant{1.2});
		assert (v == 1.2);

		v = "foo";
		assert (v.is_value());
		assert (v == json_variant{"foo"});
		assert (v == "foo");

		v = true;
		assert (v.is_value());
		assert (v == json_variant{true});
		assert (v == true);
	}
	{
		json_value v{1.2};
		assert (v == 1.2);
		v = 2.3;
		assert (v == 2.3);
		v = "foo";
		assert (v == "foo");
		v = false;
		assert (v == false);
	}
}
void test_index()
{
	json_index i;
}

int main()
{
	test_object();
	test_array();
	test_value();

	return 0;
}