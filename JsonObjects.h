#pragma once
#include <vector>
using namespace std;

template<class T>
class JsonObjects
{
public:
	JsonObjects(void) {}
	~JsonObjects(void) 
	{
		for (int i = 0; i < (int)Values.size(); ++i)
		{
			delete Values[i];
		}
		Values.clear();
	}

public:
	vector<T *> Values;
};

