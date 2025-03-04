#include "Menu.h"
#include <exception>
#include "Controller.h"

int main()
{
	try {

		Controller con;
		con.run();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}