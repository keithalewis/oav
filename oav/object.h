#pragma once
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace oav {
	
	template<typename K, typename V>
	struct value;

	template<typename K, typename V>
	using object = std::map<K,value<K,V>>;

	template<typename K, typename V>
	using array = std::vector<value<K,V>>;

	template<typename K, typename V>
	struct value : public std::variant<object<K,V>,array<K,V>,V>
	{ 
		template<typename ...T>
		value(T&& ...t)
			: std::variant<object<K,V>,array<K,V>,V>(std::forward<T>(t)...)
		{ }
	};

	using json_variant = std::variant<std::monostate, double, std::string, bool>;
	using json_object = object<std::string, json_variant>;
	using json_array = array<std::string, json_variant>;
	using json_value = value<std::string, json_variant>;
	/*
	template<typename K, typename V>
	class array 
	{
		std::vector<value<K,V>> data;
	public:
		template<typename ...T>
		array(T&& ...t)
			: data(std::forward<T>(t)...)
		{ }
	};

	template<typename K, typename V>
	class object 
	{
		std::map<K,value<K,V>> data;
	public:
		template<typename ...T>
		object(T&& ...t)
			: data(std::forwart<T>(t)...)
		{ }
	};
	*/
	/*
	template<typename K, typename V>
	using object = std::map<K,value<K,V>>;

	template<class V>
	struct wrapper
	{
		V _;
		template<typename T...>
		wrapper(T&& ...t)
			: _(std::forward<T>(t)...)
		{ }
	};
	*//*
	template<typename K, typename V>
	inline bool subobject(const object<K,V>& a, const object<K,V> b)
	{
		for (const auto& ka : a) {
			const auto kb = b.find(ka.first);
			if (kb == b.end())
				return false;
			if (ka.second != kb.second)
				return false;
		}

		return true;
	}
	*/
}

template<typename K, typename V>
inline bool operator==(const oav::value<K,V>& a, const oav::value<K,V>& b)
{
	size_t ai = a.index();
	
	if (ai != b.index())
		return false;

	switch (ai) {
	case 0:
		return std::get<0>(a) == std::get<0>(b);
	case 1:
		return std::get<1>(a) == std::get<1>(b);
	case 2:
		return std::get<2>(a) == std::get<2>(b);
	}

	throw std::runtime_error("this cannot happen");
}