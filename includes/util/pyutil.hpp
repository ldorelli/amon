#ifndef __PYUTIL_HPP__
#define __PYUTIL_HPP__

#include <boost/python.hpp>
#include <unordered_set>
#include <unordered_map>
#include <vector>

template <class K, class V>
boost::python::dict toPythonDict(std::unordered_map<K, V> map) {
	boost::python::dict dictionary;
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		dictionary[iter->first] = iter->second;
	}
	return dictionary;
}

template <class V> 
boost::python::list toPythonList(std::vector<V> v) {
	boost::python::list res;
	for (auto x : v) res.append(x);
	return res;
}

template <class V>
std::vector<V> toStdVector(boost::python::list& v) {
	std::vector<V> res;
	boost::python::ssize_t n = boost::python::len(v);
	for (boost::python::ssize_t i = 0;i < n; ++i) {
		boost::python::object elem = v[i];
		res.push_back(boost::python::extract<V>(elem));
	}
	return res;
}

template <class V>
std::unordered_set<V> toStdSet(boost::python::list& v) {
	std::unordered_set<V> res;
	boost::python::ssize_t n = boost::python::len(v);
	for (boost::python::ssize_t i = 0;i < n; ++i) {
		boost::python::object elem = v[i];
		res.insert(boost::python::extract<V>(elem) );
	}
	return res;
}

#endif 