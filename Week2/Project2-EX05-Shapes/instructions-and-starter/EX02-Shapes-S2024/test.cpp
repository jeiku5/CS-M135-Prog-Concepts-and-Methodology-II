// Copyright 2018, Allan Knight.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Allan Knight nor the names of other
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A unit tester for EX05-String in CS140 at Santa Barbara City College.
//
// Author: ahknight@pipeline.sbcc.edu (Allan Knight)


// Includes for google test and the unit under test.

#include <climits>
#include <numbers>
#include <random>
#include <fstream>

#include "shapes.h"

#include "gtest/gtest.h"
namespace {

    using edu::vcccd::vc::csv30::Shape;
    using edu::vcccd::vc::csv30::Rectangle;
    using edu::vcccd::vc::csv30::Square;
    using edu::vcccd::vc::csv30::Circle;

    using std::string;

    using namespace ::testing_internal;

    class ShapesTests : public ::testing::Test {
    protected:
        static const uint64_t MAX_TESTED_SCORE = 20;
        static const uint64_t MAX_OVERALL_SCORE = 25;
        static uint64_t _testScore;

    protected:
        static void TearDownTestCase() {
            if (_testScore == MAX_TESTED_SCORE) {
                std::cout << std::endl << "Your unit test score is "
                    << _testScore << " out of "
                    << MAX_TESTED_SCORE << std::endl;
            }
            else {
                std::cout << "Your unit test score is "
                    << _testScore << " out of "
                    << MAX_TESTED_SCORE << " (" << (int)(_testScore - MAX_TESTED_SCORE)
                    << ")" << std::endl;
            }

            std::cout << "The assignment is worth a total of " << MAX_OVERALL_SCORE
                << " where the remaining points" << std::endl;
            std::cout << "comes from grading related to documentation, algorithms, and other"
                << std::endl;
            std::cout << "criteria." << std::endl << std::endl;
        }
    };

    uint64_t ShapesTests::_testScore = 0;

    TEST_F(ShapesTests, Construction) {
        Circle origin;
        ASSERT_DOUBLE_EQ(0.0, origin.getX());
        ASSERT_DOUBLE_EQ(0.0, origin.getY());

        Circle random(1.0, 3.0, 4.0);
        ASSERT_DOUBLE_EQ(3.0, random.getX());
        ASSERT_DOUBLE_EQ(4.0, random.getY());
        _testScore += 1;
    }

    TEST_F(ShapesTests, Translate) {
        Circle origin;
        ASSERT_DOUBLE_EQ(0.0, origin.getX());
        ASSERT_DOUBLE_EQ(0.0, origin.getY());

        origin.translate(5, 6);
        ASSERT_DOUBLE_EQ(5.0, origin.getX());
        ASSERT_DOUBLE_EQ(6.0, origin.getY());

        origin.translate(-6, -7);
        ASSERT_DOUBLE_EQ(-1.0, origin.getX());
        ASSERT_DOUBLE_EQ(-1.0, origin.getY());
        _testScore += 1;
    }

    TEST_F(ShapesTests, Scale) {
        Circle origin;
        ASSERT_DOUBLE_EQ(0.0, origin.getX());
        ASSERT_DOUBLE_EQ(0.0, origin.getY());

        origin.scale(6);
        ASSERT_DOUBLE_EQ(0.0, origin.getX());
        ASSERT_DOUBLE_EQ(0.0, origin.getY());

        origin.translate(3, 6);
        origin.scale(4, 2);
        ASSERT_DOUBLE_EQ(12.0, origin.getX());
        ASSERT_DOUBLE_EQ(12.0, origin.getY());

        origin.scale(0.5);
        ASSERT_TRUE(!origin.scale(-2));
        ASSERT_DOUBLE_EQ(6.0, origin.getX());
        ASSERT_DOUBLE_EQ(6.0, origin.getY());
        _testScore += 1;
    }

    TEST_F(ShapesTests, ComputeDistance) {
        Circle s1(1.0, -3, 4);

        ASSERT_DOUBLE_EQ(0.0, s1.computeDistance(s1));

        Square s2;
        ASSERT_DOUBLE_EQ(5.0, s1.computeDistance(s2));
        ASSERT_DOUBLE_EQ(5.0, s2.computeDistance(s1));
        _testScore += 1;
    }

    TEST_F(ShapesTests, Rectangle) {
        Rectangle r(2.0, 3.0, 1, 2);
        ASSERT_DOUBLE_EQ(2.0, r.getWidth());
        ASSERT_DOUBLE_EQ(3.0, r.getHeight());
        ASSERT_DOUBLE_EQ(6.0, r.computeArea());
        _testScore += 4;
    }

    TEST_F(ShapesTests, Square) {
        Square s(2.0, 1, 2);
        ASSERT_DOUBLE_EQ(2.0, s.getWidth());
        ASSERT_DOUBLE_EQ(2.0, s.getHeight());
        ASSERT_DOUBLE_EQ(4.0, s.computeArea());
        _testScore += 4;
    }

    TEST_F(ShapesTests, Circle) {
        Circle c(2.0, 1, 2);
        ASSERT_DOUBLE_EQ(2.0, c.getRadius());
        ASSERT_DOUBLE_EQ(4.0 * std::numbers::pi, c.computeArea());
        _testScore += 4;
    }

    TEST_F(ShapesTests, ShapeEquality) {
        Circle c1(1.0);
        Circle c2(2.0);
        Circle c3(2.0, 1, 2);

        ASSERT_TRUE(c1 == c1);
        ASSERT_TRUE(c2 == c2);
        ASSERT_FALSE(c1 == c2);
        ASSERT_FALSE(c2 == c3);
        _testScore += 1;

        Square s1(2.0);
        Square s2(2.0, 1.0, 2.0);
        Rectangle r1(2.0, 2.0);
        Rectangle r2(2.0, 3.0);
        ASSERT_TRUE(s1 == s1);
        ASSERT_TRUE(r1 == r1);
        ASSERT_TRUE(s1 == r1);
        _testScore += 1;

        ASSERT_FALSE(s1 == s2);
        ASSERT_FALSE(r1 == r2);
        ASSERT_FALSE(s2 == r2);
        _testScore += 1;

        Shape* sp1 = &c1;
        Shape* sp2 = &r2;
        ASSERT_FALSE(*sp1 == *sp2);
        _testScore += 1;
    }

}
