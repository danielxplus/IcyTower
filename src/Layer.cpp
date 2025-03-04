#include "Layer.h"
//=======================================================================
Layer::Layer()
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	cam_posY = 0;
	speed_delta = 1;
	step = const_cam_start_step;
	const_step = step;
}
//=======================================================================
Layer::Layer(float speed_delta)
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	cam_posY = 0;
	step = const_cam_start_step - const_cam_start_step / speed_delta;
	this->speed_delta = speed_delta;
	const_step = step;
}
//=======================================================================
void Layer::logic()
{
	float camSpeed = Camera::getCamSpeed();
	view.reset(sf::FloatRect(0, cam_posY, 640, 480));
	cam_posY -= const_cam_speed_delta * camSpeed * speed_delta;
	step -= camSpeed;
	if (step <= 0)
	{
		cam_posY = 0;
		if (speed_delta != 1)
		{
			step = const_cam_start_step - const_cam_start_step / speed_delta;
		}
		else step = const_cam_start_step;
	}
}
//=======================================================================
void Layer::render(sf::RenderWindow& window, sf::Drawable& drawable)
{	
	window.setView(view); // look at the current play field
	window.draw(drawable);
}
//=======================================================================
void Layer::render(sf::RenderWindow& window, sf::Sprite& drawable)
{
	window.setView(view); // look at the current play field
	window.draw(drawable);
}
//=======================================================================
void Layer::setView(sf::View new_view)
{
	view = new_view;
}
//=======================================================================
float Layer::getViewCenter()
{
	return view.getCenter().y;
}
//=======================================================================
void Layer::reset()
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	cam_posY = 0;
	step = const_step;
}
