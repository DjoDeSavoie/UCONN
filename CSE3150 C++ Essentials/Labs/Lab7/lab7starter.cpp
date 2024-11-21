

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

// Base class: Shape
class Shape
{
protected:
    std::string color;

public:
    Shape(const std::string &c) : color(c) {}

    // TODO: Declare a virtual destructor
    virtual ~Shape() {}

    // TODO: Declare a pure virtual function called area()
    virtual double area() const = 0;

    // TODO: Declare a pure virtual function called perimeter()
    virtual double perimeter() const = 0;

    // TODO: Implement a non-virtual function called getColor() that returns the color
    std::string getColor() const
    {
        return color;
    }
    // TODO: Declare a virtual function called display()
    virtual void display() const
    {
        std::cout << "Shape color: " << getColor() << std::endl;
    }
};

// TODO: Implement a derived class called Circle
// It should have a private member variable for radius
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(const std::string &c, double r) : Shape(c), radius(r) {}

    // Override the area function for Circle
    double area() const override
    {
        return M_PI * radius * radius;
    }

    // Override the perimeter function for Circle
    double perimeter() const override
    {
        return 2 * M_PI * radius;
    }

    // Override the display function for Circle
    void display() const override
    {
        Shape::display();
        std::cout << "Circle radius: " << radius << std::endl;
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
};

// TODO: Implement a derived class called Rectangle
// It should have private member variables for width and height

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(const std::string& c, double w, double h) : Shape(c), width(w), height(h) {}

    // Override the area function for Rectangle
    double area() const override {
        return width * height;
    }

    // Override the perimeter function for Rectangle
    double perimeter() const override {
        return 2 * (width + height);
    }

    // Override the display function for Rectangle
    void display() const override {
        Shape::display();
        std::cout << "Rectangle width: " << width << ", height: " << height << std::endl;
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
};


// TODO: Implement a derived class called Square that inherits from Rectangle
// Override necessary functions to ensure a square always has equal sides

class Square : public Rectangle {
public:
    Square(const std::string& c, double side) : Rectangle(c, side, side) {}

    // Override the display function for Square
    void display() const override {
        Shape::display();
        std::cout << "Square side: " << Rectangle::area() / Rectangle::perimeter() << std::endl; // Since a square has equal sides
        std::cout << "Area: " << area() << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
    }
};

int main()
{
    std::vector<Shape *> shapes;

    shapes.push_back(new Circle("Red", 5.0));
    shapes.push_back(new Rectangle("Blue", 4.0, 6.0));
    shapes.push_back(new Square("Green", 3.0));

    for (const auto &shape : shapes)
    {
        shape->display();
        std::cout << std::endl;
    }

    // Clean up
    for (auto &shape : shapes)
    {
        delete shape;
    }

    return 0;
}