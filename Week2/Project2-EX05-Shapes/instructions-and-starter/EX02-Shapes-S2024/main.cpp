#include <iostream>
#include "shapes.h"
#include "gtest/gtest.h"

using edu::vcccd::vc::csv30::Shape;
using edu::vcccd::vc::csv30::Square;
using edu::vcccd::vc::csv30::Circle;

// In order to run the project itself rename it to -->>> main
int main1(int argc, char* argv[]) {
    const double SQUARE_SIZE = 2.0;
    const double CIRCLE_RADIUS = 3.0;
    Square s1(SQUARE_SIZE);
    Circle s2(CIRCLE_RADIUS, 1, 1);

    std::cout << "The distance between s1 and s2 is " << s1.computeDistance(s2) << std::endl;

    return 0;
}

// In order to run the tester rename it to -->>> main
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}