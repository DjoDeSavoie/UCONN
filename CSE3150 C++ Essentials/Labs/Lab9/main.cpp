// main.cpp

// Compile the code with "g++ main.cpp DocumentComponent.cpp NewComponentFactory.cpp OldComponentFactory.cpp -o stuff"

#include "ComponentFactory.h"
#include "DocumentComponent.h"
#include <iostream>

int main() {
    // Using New Style
    NewComponentFactory NewFactory;
    CompositeDocument* NewDocument = new CompositeDocument();

    NewDocument->add(NewFactory.createText());
    NewDocument->add(NewFactory.createImage());
    NewDocument->add(NewFactory.createTable());

    std::cout << "New Document Structure:\n";
    NewDocument->display();

    // Clean up dynamically allocated objects in NewDocument
    delete NewDocument;

    // Using Old Style
    OldComponentFactory OldFactory;
    CompositeDocument* OldDocument = new CompositeDocument();

    OldDocument->add(OldFactory.createText());
    OldDocument->add(OldFactory.createImage());
    OldDocument->add(OldFactory.createTable());

    std::cout << "\nOld Document Structure:\n";
    OldDocument->display();

    // Clean up dynamically allocated objects in OldDocument
    delete OldDocument;

    return 0;
}

