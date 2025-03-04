#pragma once
#include <SFML/Graphics.hpp>

// left, top, width, height.

class Animation
{
public:
	static sf::IntRect animation_idle1;// (3, 4, 28, 52);
	static sf::IntRect animation_walk1;// (36, 4, 28, 52);
	static sf::IntRect animation_walk2;// (69, 4, 28, 52);
	static sf::IntRect animation_walk3;// (103, 4, 28, 52);
	static sf::IntRect animation_walk4;// (137, 4, 28, 52);
	static sf::IntRect animation_jump1;// (171, 4, 28, 52);
	static sf::IntRect animation_jump2;// (205, 4, 28, 52);
	static sf::IntRect animation_jump3;// (239, 4, 28, 52);
	static sf::IntRect animation_jump;// (273, 4, 28, 58);
	static sf::IntRect animation_idle2;// (307, 4, 28, 52);
	static sf::IntRect animation_idle3;// (340, 4, 28, 52);
	static sf::IntRect animation_chock;// (373, 4, 28, 52);
	static sf::IntRect animation_rotate;// (407, 4, 42, 60);
	static sf::IntRect animation_edge2;// (456, 4, 35, 51);
	static sf::IntRect animation_edge1;// (498, 4, 35, 51);

};

