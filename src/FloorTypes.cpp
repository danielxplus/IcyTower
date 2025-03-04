#include "FloorTypes.h"

// left, top, width, height.

sf::IntRect FloorTypes::snow_left(0, 0, 21, 37);
sf::IntRect FloorTypes::snow_mid(21, 0, 16, 37);
sf::IntRect FloorTypes::snow_right(37, 0, 21, 37);

sf::IntRect FloorTypes::ice_left(0, 38, 25, 37);
sf::IntRect FloorTypes::ice_mid(25, 38, 16, 37);
sf::IntRect FloorTypes::ice_right(41, 38, 17, 37);

sf::IntRect FloorTypes::wood_left(0, 80, 21, 21);
sf::IntRect FloorTypes::wood_mid(21, 80, 16, 21);
sf::IntRect FloorTypes::wood_right(37, 80, 21, 21);

sf::IntRect FloorTypes::metal_left(0, 103, 21, 12);
sf::IntRect FloorTypes::metal_mid(21, 103, 16, 12);
sf::IntRect FloorTypes::metal_right(37, 103, 20, 12);

sf::IntRect FloorTypes::gum_left(1, 119, 21, 23);
sf::IntRect FloorTypes::gum_mid(21, 119, 16, 22);
sf::IntRect FloorTypes::gum_right(37, 119, 20, 21);

sf::IntRect FloorTypes::bone_left(0, 144, 21, 21);
sf::IntRect FloorTypes::bone_mid(21, 144, 16, 21);
sf::IntRect FloorTypes::bone_right(37, 144, 22, 21);

sf::IntRect FloorTypes::rainbow_left(0, 167, 21, 12);
sf::IntRect FloorTypes::rainbow_mid(21, 167, 16, 12);
sf::IntRect FloorTypes::rainbow_right(37, 167, 20, 12);

std::vector<sf::IntRect> FloorTypes::getIntRects(int type)
{
	std::vector<sf::IntRect> m_vector;

	switch (type)
	{
	case Snow:
		m_vector.push_back(snow_left);
		m_vector.push_back(snow_mid);
		m_vector.push_back(snow_right);
		return m_vector;
	case Ice:
		m_vector.push_back(ice_left);
		m_vector.push_back(ice_mid);
		m_vector.push_back(ice_right);
		return m_vector;
	case Wood:
		m_vector.push_back(wood_left);
		m_vector.push_back(wood_mid);
		m_vector.push_back(wood_right);
		return m_vector;
	case Metal:
		m_vector.push_back(metal_left);
		m_vector.push_back(metal_mid);
		m_vector.push_back(metal_right);
		return m_vector;
	case Gum:
		m_vector.push_back(gum_left);
		m_vector.push_back(gum_mid);
		m_vector.push_back(gum_right);
		return m_vector;
	case Bone:
		m_vector.push_back(bone_left);
		m_vector.push_back(bone_mid);
		m_vector.push_back(bone_right);
		return m_vector;
	default:
		m_vector.push_back(rainbow_left);
		m_vector.push_back(rainbow_mid);
		m_vector.push_back(rainbow_right);
		return m_vector;
	}
}
