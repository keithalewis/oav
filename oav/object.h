#pragma once
#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace oav {
	
	template<typename K, typename V>
	class value;

	template<typename K, typename V>
	using object = std::map<K,value<K,V>>;

	template<typename K, typename V>
	using array = std::vector<value<K,V>>;
	
	template<typename K, typename V>
	class value 
	{
		std::variant<V,array<K,V>,object<K,V>> value_;
	public:
		value()
		{ }
		value(const value&) = default;
		value& operator=(const value&) = default;
		~value()
		{ }

		template<typename T>
		value(const T& t)
			: value_(t)
		{ }
		template<typename T>
		value& operator=(const T& t)
		{
			value_ = t;

			return *this;
		}
		/*
		template<typename... T>
		value(T&& ...t)
			: value_(std::forward(value(t))...)
		{ }
		*/
		bool is_value() const
		{
			return value_.index() == 0;
		}
		bool is_array() const
		{
			return value_.index() == 1;
		}
		bool is_object() const
		{
			return value_.index() == 2;
		}

		bool operator==(const value& v) const
		{
			if (value_.index() != v.value_.index())
				return false;

			if (v.is_value())
				return std::get<0>(value_) == std::get<0>(v.value_);
			
			if (v.is_array())
				return std::get<1>(value_) == std::get<1>(v.value_);
			
			if (v.is_object())
				return std::get<2>(value_) == std::get<2>(v.value_);

			return false; // throw!!!
		}
		bool operator==(const V& v) const
		{
			return is_value() && std::get<0>(value_) == v;
		}
		template<typename T>
		bool operator==(const T& t) const
		{
			return operator==(V(t));
		}

		value<K,V>& operator[](const K& k)
		{
			return get<2>(value_)[k];
		}
		const value<K,V>& operator[](const K& k) const
		{
			return get<2>(value_)[k];
		}

		value<K,V>& operator[](size_t j)
		{
			return get<1>(value_)[j];
		}
		const value<K,V>& operator[](size_t j) const
		{
			return get<1>(value_)[j];
		}

	};
}
#if 0
//template<typename K>
//using index = std::vector<

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
#endif // 0