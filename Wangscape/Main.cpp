#include "Main.h"
#include <iostream>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include "Curve.h"
#include "Spline.h"


Main::Main()
{
    Curve<2> c(Interval(0.0, 1.0),
               { {1.1,2.2},{3.3,4.4} },
               { {5.5,6.6},{7.7,8.8} });
    Spline<2> s(0.0, 1.0,
                { 1.1,2.2 },{ 3.3,4.4 },
                { 5.5,6.6 },{ 7.7,8.8 });
    s.valid();
    s.setKnot(-0.5, { -10,-11 }, { -12,-13 });
    s.valid();
}


Main::~Main()
{
}

void main()
{
	std::cout << "Teeeeeeeeeeeeeeeeeeeeeeeeeeeeeesting?\n";
	Main();
	std::cin.get();
}