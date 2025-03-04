#include "Factory.h"

std::unique_ptr<Object> Factory::create(const std::string& name) {
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second();
}

std::unique_ptr<Object> Factory::createInitialized(const std::string& type, float posX, float posY, Layer& layer)
{
    auto it = getMap().find(type);
    if (it == getMap().end()) {
        return nullptr;
    }
    auto obj = it->second(); // Assuming second is now a factory lambda that creates a new instance

    obj->setBasic(posX, posY, layer);
    return obj;

}

bool Factory::registerit(const std::string& name, std::unique_ptr<Object>(*f)()) {
	getMap().emplace(name, f);
	return true;
}