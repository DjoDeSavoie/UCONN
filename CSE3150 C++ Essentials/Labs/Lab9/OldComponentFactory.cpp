// OldComponentFactory.cpp
#include "ComponentFactory.h"
#include "DocumentComponent.h"
#include <iostream>

DocumentComponent* OldComponentFactory::createText() {
    return new Text("Old");
}

DocumentComponent* OldComponentFactory::createImage() {
    return new Image("Old");
}

DocumentComponent* OldComponentFactory::createTable() {
    return new Table("Old");
}
