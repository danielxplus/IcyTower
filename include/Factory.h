#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include "Object.h"
using namespace std;

typedef std::map<std::string, std::unique_ptr<Object>(*)()> mymap;
// ================   class Factory   ============================
class Factory {
public:
	static std::unique_ptr<Object> create(const std::string& name);
	static std::unique_ptr<Object> createInitialized(const std::string& type, float posX, float posY,Layer &layer);
	static bool registerit(const std::string& name, std::unique_ptr<Object>(*)());
private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};

// =========   end of class Factory   ============================