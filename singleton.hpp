#pragma once

#include <Windows.h>

template <typename T>
class Singleton {
public:
	static T& get() {

		// make one instance and one instance only
		static T instance;
		return instance;
	}

	// no!! we dont want to accedently create a new instance
	Singleton(const Singleton& s) = delete;
	void operator= (const Singleton&) = delete;
protected:

	// boo
	Singleton() { };
	~Singleton() { };
};