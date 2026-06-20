#ifndef EX04_SHAPE_SHAPES_H
#define EX04_SHAPE_SHAPES_H

namespace edu {
    namespace vcccd {
        namespace vc {
            namespace csv30 {

                class Shape {
                    static constexpr double DEFAULT_COORD = 0.0;
                    double _x; // X-axis coordinate
                    double _y; // Y-axis coordinate

                protected:
                    void setX(double x) { _x = x; }
                    void setY(double y) { _y = y; }

                public:
                    Shape() : _x(DEFAULT_COORD), _y(DEFAULT_COORD) {}
                    Shape(double x, double y);

                    double getX() const { return _x; }
                    double getY() const { return _y; }

                    void translate(double tx, double ty);
                    bool scale(double sx, double sy);
                    bool scale(double s);
                    double computeDistance(const Shape& other);
                    bool operator ==(const Shape& rhs) { (void)rhs; return false; }
                    bool operator !=(const Shape& rhs) { return !(*this == rhs); }
                };

                class Rectangle : public Shape {
                    double _width;
                    double _height;

                public:
                    Rectangle(double w, double h, double x = 0.0, double y = 0.0) : Shape(x, y), _width(w), _height(h) {
                    }

                    double getWidth() const { return _width; }
                    double getHeight() const { return _height; }

                    double computeArea() const;

                    bool operator ==(const Rectangle& rhs) const;
                };

                class Square : public Rectangle {
                public:
                    Square(double size = 1.0, double x = 0.0, double y = 0.0) : Rectangle(size, size, x, y) {
                    }
                };

                class Circle : public Shape {
                    double _radius;

                public:
                    Circle(double radius = 1.0, double x = 0.0, double y = 0.0) : Shape(x, y), _radius(radius) {
                    }

                    double getRadius() const { return _radius; }

                    double computeArea() const;

                    bool operator ==(const Circle& rhs) const;
                };

            }
        }
    }
}
#endif //EX04_SHAPE_SHAPES_H