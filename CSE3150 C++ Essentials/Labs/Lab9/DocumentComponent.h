// DocumentComponent.h
#pragma once
#include <vector>
#include <string>
#include <iostream>

class DocumentComponent {
public:
    virtual ~DocumentComponent() = default;
    virtual void add(DocumentComponent* component) {}
    virtual void display() const = 0;
};

// Concrete Text Component
class Text : public DocumentComponent {
    std::string style;
public:
    Text(const std::string& style) : style(style) {}
    void display() const override {
        std::cout << style << " Text Component\n";
    }
};

// Concrete Image Component
class Image : public DocumentComponent {
    std::string style;
public:
    Image(const std::string& style) : style(style) {}
    void display() const override {
        std::cout << style << " Image Component\n";
    }
};

// Concrete Table Component
class Table : public DocumentComponent {
    std::string style;
public:
    Table(const std::string& style) : style(style) {}
    void display() const override {
        std::cout << style << " Table Component\n";
    }
};

// Composite Document to hold multiple components
class CompositeDocument : public DocumentComponent {
    std::vector<DocumentComponent*> children;  
public:
    void add(DocumentComponent* component) override {
        children.push_back(component);
    }
    void display() const override {
        for (const auto& child : children) {
            child->display();
        }
    }
    ~CompositeDocument() {
        for (auto* child : children) {
            delete child;
        }
    }
};
