#include "String.h"

int main()
{
	css::String hello("Hello");
	css::String world = "world";
	css::String helloWorld(hello + " " + world + "!");
	std::cout << helloWorld << std::endl;

	return 0;
}
