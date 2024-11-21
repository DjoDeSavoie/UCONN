// ComponentFactory.h
#pragma once
#include "DocumentComponent.h"

// Abstract Factory Interface
class ComponentFactory {
public:
    virtual ~ComponentFactory() = default;
    virtual DocumentComponent* createText() = 0;
    virtual DocumentComponent* createImage() = 0;
    virtual DocumentComponent* createTable() = 0;
};

// Old Factory Implementation
class OldComponentFactory : public ComponentFactory {
public:
    DocumentComponent* createText() override;
    DocumentComponent* createImage() override;
    DocumentComponent* createTable() override;
};

// New Factory Implementation
class NewComponentFactory : public ComponentFactory {
public:
    DocumentComponent* createText() override;
    DocumentComponent* createImage() override;
    DocumentComponent* createTable() override;
};
