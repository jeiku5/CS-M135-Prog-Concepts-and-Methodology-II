#include <cmath>
#include <numbers>
#include "shapes.h"

namespace edu {
    namespace vcccd {
        namespace vc {
            namespace csv30 {
                Shape::Shape(double x, double y) : _x(x), _y(y) {
                }

                void Shape::translate(double tx, double ty) {
                    setX(_x + tx);
                    setY(_y + ty);
                }

                bool Shape::scale(double sx, double sy) {
                    if (sx < 0.0 || sy < 0.0) return false;
                    setX(_x * sx);
                    setY(_y * sy);
                    return true; // Only return true if sx and sy are non-negative
                }

                bool Shape::scale(double s) {
                    return scale(s, s);
                }

                double Shape::computeDistance(const Shape& other) {
                    return sqrt(pow(_x - other._x, 2) + pow(_y - other._y, 2));
                }

                double Rectangle::computeArea() const {
                    return _width * _height;
                }

                bool Rectangle::operator ==(const Rectangle& rhs) const {
                    return getX() == rhs.getX() && getY() == rhs.getY() && _width == rhs._width && _height == rhs._height;
                }

                double Circle::computeArea() const {
                    return _radius * _radius * std::numbers::pi;
                }

                bool Circle::operator ==(const Circle& rhs) const {
                    return getX() == rhs.getX() && getY() == rhs.getY() && _radius == rhs._radius && _radius == rhs._radius;
                }

            }
        }
    }
}