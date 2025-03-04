#pragma once
#include <SFML/Graphics.hpp>

class FloorTypes
{

public:
	enum Type
	{
		Snow, Ice, Wood, Metal, Rainbow, Gum, Bone
	};
	static std::vector<sf::IntRect> getIntRects(int type);

private:
	static sf::IntRect snow_left;
	static sf::IntRect snow_mid;
	static sf::IntRect snow_right;

	static sf::IntRect ice_left;
	static sf::IntRect ice_mid;
	static sf::IntRect ice_right;

	static sf::IntRect wood_left;
	static sf::IntRect wood_mid;
	static sf::IntRect wood_right;

	static sf::IntRect metal_left;
	static sf::IntRect metal_mid;
	static sf::IntRect metal_right;

	static sf::IntRect gum_left;
	static sf::IntRect gum_mid;
	static sf::IntRect gum_right;

	static sf::IntRect bone_left;
	static sf::IntRect bone_mid;
	static sf::IntRect bone_right;

	static sf::IntRect rainbow_left;
	static sf::IntRect rainbow_mid;
	static sf::IntRect rainbow_right;

};
