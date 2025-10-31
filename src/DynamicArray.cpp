#include "DynamicArray.h"
#include <cstring>
#include <stdexcept>

// ============================================================================
// CONSTRUCTOR (3p + 1p): Initializare membri din constructor
// ============================================================================
// Demonstreaza:
// - Alocarea pe heap (new)
// - Initializarea corecta a tuturor membrilor
// - Lista de initializare (member initializer list)
DynamicArray::DynamicArray(const std::string& arrayName, size_t initialCapacity)
    : data(new int[initialCapacity]),  // Alocare pe HEAP
      size(0),
      capacity(initialCapacity),
      name(arrayName)
{
    std::cout << "[CONSTRUCTOR] Creat array '" << name 
              << "' cu capacitate " << capacity 
              << " (alocat " << capacity * sizeof(int) << " bytes pe heap)"
              << std::endl;
}

// ============================================================================
// DESTRUCTOR (1p): Eliberare heap
// ============================================================================
// CRUCIAL: Fara destructor -> MEMORY LEAK!
// Demonstreaza nevoia de a elibera manual memoria alocata cu 'new'
DynamicArray::~DynamicArray() {
    std::cout << "[DESTRUCTOR] Distrus array '" << name 
              << "' - eliberez " << capacity * sizeof(int) 
              << " bytes de pe heap" << std::endl;
    delete[] data;  // CRUCIAL: eliberare memorie
    data = nullptr;
}

// ============================================================================
// COPY CONSTRUCTOR (2p): Deep copy
// ============================================================================
// CRUCIAL: Fara copy constructor -> SHALLOW COPY -> PROBLEME GRAVE:
// 1. Doua obiecte vor pointa la aceeasi zona de memorie
// 2. Modificarea unui obiect afecteaza celalalt
// 3. La distrugere -> DOUBLE FREE -> CRASH!
//
// Cu copy constructor -> DEEP COPY -> Fiecare obiect are propria memorie
DynamicArray::DynamicArray(const DynamicArray& other)
    : data(new int[other.capacity]),  // Alocare NOUA memorie
      size(other.size),
      capacity(other.capacity),
      name(other.name + "_copy")
{
    std::cout << "[COPY CONSTRUCTOR] Copiez array '" << other.name 
              << "' -> '" << name << "' (deep copy - alocare noua memorie)" 
              << std::endl;
    
    // Copiere efectiva a datelor (DEEP COPY)
    std::memcpy(data, other.data, size * sizeof(int));
}

// ============================================================================
// MOVE CONSTRUCTOR (2p): Transfer de resurse
// ============================================================================
// Demonstreaza:
// - Transfer eficient de resurse (fara copiere)
// - Utilizare pentru obiecte temporare (rvalue)
// - Performanta superioara fata de copy constructor
DynamicArray::DynamicArray(DynamicArray&& other) noexcept
    : data(other.data),        // TRANSFER pointer (nu copiere)
      size(other.size),
      capacity(other.capacity),
      name(other.name + "_moved")
{
    std::cout << "[MOVE CONSTRUCTOR] Mutat array '" << other.name 
              << "' -> '" << name << "' (transfer resurse, fara copiere)" 
              << std::endl;
    
    // CRUCIAL: Invalidare obiect sursa pentru a preveni double free
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// ============================================================================
// COPY ASSIGNMENT OPERATOR
// ============================================================================
DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        std::cout << "[COPY ASSIGNMENT] Copiez '" << other.name 
                  << "' in '" << name << "'" << std::endl;
        
        // Eliberare memorie veche
        delete[] data;
        
        // Alocare si copiere
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        std::memcpy(data, other.data, size * sizeof(int));
    }
    return *this;
}

// ============================================================================
// MOVE ASSIGNMENT OPERATOR
// ============================================================================
DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        std::cout << "[MOVE ASSIGNMENT] Mutat '" << other.name 
                  << "' in '" << name << "'" << std::endl;
        
        // Eliberare memorie veche
        delete[] data;
        
        // Transfer resurse
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        
        // Invalidare sursa
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

// ============================================================================
// Metode publice - INCAPSULARE
// ============================================================================

void DynamicArray::push_back(int value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = value;
}

int DynamicArray::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void DynamicArray::print() const {
    std::cout << "Array '" << name << "' [size=" << size 
              << ", capacity=" << capacity << "]: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void DynamicArray::resize() {
    size_t newCapacity = capacity * 2;
    int* newData = new int[newCapacity];
    std::memcpy(newData, data, size * sizeof(int));
    delete[] data;
    data = newData;
    capacity = newCapacity;
    
    std::cout << "[RESIZE] Array '" << name 
              << "' redimensionat la capacitate " << capacity 
              << std::endl;
}
