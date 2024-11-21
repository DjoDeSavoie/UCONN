// NewComponentFactory.cpp
#include "ComponentFactory.h"
#include "DocumentComponent.h"
#include <iostream>

DocumentComponent* NewComponentFactory::createText() {
    return new Text("New");
}

DocumentComponent* NewComponentFactory::createImage() {
    return new Image("New");
}

DocumentComponent* NewComponentFactory::createTable() {
    return new Table("New");
}
