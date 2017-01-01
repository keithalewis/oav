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
	using array = std::vector<value<K,V>>;
	
	template<typename K, typename V>
	using object = std::map<K,value<K,V>>;

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

		value(const V& v)
			: value_(v)
		{ }
		value(const array<K,V>& a)
			: value_(a)
		{ }
		/*
		template<typename... T>
		value(T&& ...t)
			: value_(std::initializer_list<value>(t...))
		{ }
		*/
		value(const object<K,V>& o)
			: value_(o)
		{ }

		value& operator=(const V& v)
		{
			value_ = v;

			return *this;
		}
		value& operator=(const array<K,V>& a)
		{
			value_ = a;

			return *this;
		}
		value& operator=(const object<K,V>& o)
		{
			value_ = o;

			return *this;
		}

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

		V& as_value()
		{
			return get<0>(value_);
		}
		const V& as_value() const
		{
			return get<0>(value_);
		}

		V& as_array()
		{
			return get<1>(value_);
		}
		const V& as_array() const
		{
			return get<1>(value_);
		}

		V& as_object()
		{
			return get<2>(value_);
		}
		const V& as_object() const
		{
			return get<2>(value_);
		}

		bool operator==(const value& v) const
		{
			if (value_.index() != v.value_.index())
				return false;

			return value_ == v.value_;
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

		// object index
		value<K,V>& operator[](const K& k)
		{
			return as_object()[k];
		}
		const value<K,V>& operator[](const K& k) const
		{
			return as_object()[k];
		}

		// array index
		value<K,V>& operator[](size_t j)
		{
			return as_array()[j];
		}
		const value<K,V>& operator[](size_t j) const
		{
			return as_array()[j];
		}

	};

	template<typename K, typename V>
	inline auto make_value(V&& v)
	{
		return value<K,V>(v);
	}

	template<typename K>
	class index {
		using entry = std::variant<K,index<K>>;
		std::vector<entry> index_;
	public:
		index()
		{ }
		index(const K& k)
			: index_{k}
		{ }
		index(const index&) = default;
		index& operator=(const index&) = default;
		~index()
		{ }

		size_t size() const
		{
			return index_.size();
		}
		entry& operator[](size_t i)
		{
			return index_[i];
		}
		const entry& operator[](size_t i) const
		{
			return index_[i];
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