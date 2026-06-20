## Exercise: Shapes (25 Points)

The project name of this exercise is **Shapes**.

The purpose of this assignment is for you to write code that uses inheritance. 

### Problem Description

From our conversations in class, we have discussed the `Shape` class. We implemented several methods for this 
class in the previous assignment. In this assignment we'll add some new classes that inherit from the `Shape`
class we implemented previously. Specifically, we will create 3 new classes, `Rectangle`, `Square` and `Circle`.
All three of these classes are ancestors of `Shape`. While both `Rectangle` and `Cirlce` inherit directly from
`Shape`, `Square` inherits directly from `Rectangle` since squares are rectangles.

In addition to inheritance, we will implement a few new methods, `computeArea` and `operator ==` for each of the
three new classes. Since the computation of area is different for circles and rectangles, they will have different
implementations. Similarly, determining the equality of different shapes is also a different process. For example,
two circles are the same if they are at the same position in the Cartesian plane and their radii are the same. For
Rectangles, however, they also must have the same position, but they must have the same height and width. Therefore,
it is necessary to implement, or override, these functions in `Circle` and `Rectangle`.

In this assignment, you will implement the methods mentioned above in `shapes.cc`. If you wish to see the declrations
for all the shapes used in this assignment, look in `shapes.h`.

### Getting Started

Unlike other assignments, you don't need to create any files. You only need to update the **shapes.cc** file.
Where ever you see the comment `// Put your code here`, replace that comment with the appropriate code. 
  
##### shape.h

**shapes.h** is provided for you and should require no changes.  

##### Implementation

Next you'll add your code to the implementation, separately from the declaration, in the **shapes.cc** file, which is provided.

Where ever you see the comment `// Put your code here`, replace it with your own code.

Here's what the `Rectangle` and `Circle` classes looks like before you add your code:

```cpp
    double Rectangle::computeArea() const {
        return 0.0; // Put your code here
    }

    bool Rectangle::operator ==(const Rectangle &rhs) const {
        return true; // Put your code here
    }

    double Circle::computeArea() const {
            return 0.0; // Put your code here
    }

    bool Circle::operator ==(const Circle &rhs) const {
        return true; // Put your code here
    }

```

Where you see `// Put your code here`, your are going to add your code to make the functions work as
needed. For example, you'll replace `return 0.0;` with code that computes the area, and `return true` with
code that determines if shapes are equal to each other.
 
#### main()



Your `main` function look like this:

```cpp
  
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

```

As you know you MUST have just one "main" in your project. 
So, as it says "main1" is unactive now, it is reposnsible for the project itself. 
Rename it to "main" if you want to do so. 

The main(int argc, char* argv[]) is active now. It runs the tester. Rename it to main2 if you want to switch to do the coding. 


### Running the code for this project

Running this code should be straightforward. You shoudl have your main.cpp file look exactly as it does above. 

```bash
/home/user/ex04-shape/bin/Shape
The distance between s1 and s2 is 1.41421

Process finished with exit code 0
```
Success! Now you can move on to testing your code.

### Testing the code for this project

Testing the code for this project is your goal for this project. 
Try to read the test.cpp file and figure out what does test and how. 
Look at the functions and methods and note the "Assert" function always compares 
an expected result with actual one. 



```bash
[==========] Running 8 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 8 tests from ShapesTests
[ RUN      ] ShapesTests.Construction
[       OK ] ShapesTests.Construction (0 ms)
[ RUN      ] ShapesTests.Translate
[       OK ] ShapesTests.Translate (0 ms)
[ RUN      ] ShapesTests.Scale
[       OK ] ShapesTests.Scale (0 ms)
[ RUN      ] ShapesTests.ComputeDistance
[       OK ] ShapesTests.ComputeDistance (0 ms)
[ RUN      ] ShapesTests.Rectangle
[       OK ] ShapesTests.Rectangle (0 ms)
[ RUN      ] ShapesTests.Square
[       OK ] ShapesTests.Square (0 ms)
[ RUN      ] ShapesTests.Circle
[       OK ] ShapesTests.Circle (0 ms)
[ RUN      ] ShapesTests.ShapeEquality
[       OK ] ShapesTests.ShapeEquality (0 ms)

Your unit test score is 20 out of 20
The assignment is worth a total of 25 where the remaining points
comes from grading related to documentation, algorithms, and other
criteria.

[----------] 8 tests from ShapesTests (2 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test case ran. (3 ms total)
[  PASSED  ] 8 tests.

C:\Users\Kira Minkova\source\repos\EX02-Shapes-S24\x64\Debug\EX02-Shapes-S24.exe (process 10072) exited with code 0.
Press any key to close this window . . .
```

Remember, You should also see your score for this
assignment minus code styling points which I will add later.




#### Turning in and Grading your code
Submit 
- your shapes.cpp code to canvas. 
- a screenshot of the testing scores. It should look `Testing the code for this project` above. 
Rememer, no screenshot --->>> no credit.  

