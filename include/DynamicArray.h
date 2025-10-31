#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <string>

/**
 * Clasa DynamicArray - demonstreaza toate conceptele PAOO cerute:
 * 1. Incapsulare - membri privati, interfata publica
 * 2. Initializare membri in constructor
 * 3. Eliberare heap in destructor
 * 4. Copy constructor pentru deep copy
 * 5. Move constructor pentru transfer de resurse
 */
class DynamicArray {
private:
    // INCAPSULARE (1p): Membrii privati - ascunderea datelor
    int* data;           // Pointer la datele alocate pe heap
    size_t size;         // Dimensiunea array-ului
    size_t capacity;     // Capacitatea alocata
    std::string name;    // Nume pentru identificare

public:
    // CONSTRUCTOR cu initializare membri (1p + 1p)
    // Demonstreaza alocarea pe heap si initializarea corecta
    DynamicArray(const std::string& arrayName, size_t initialCapacity = 10);
    
    // DESTRUCTOR pentru eliberare heap (1p)
    // CRUCIAL: fara destructor -> memory leak!
    ~DynamicArray();
    
    // COPY CONSTRUCTOR (2p)
    // CRUCIAL: fara el -> shallow copy -> double free -> crash!
    DynamicArray(const DynamicArray& other);
    
    // MOVE CONSTRUCTOR (2p)
    // Demonstreaza transfer eficient de resurse (fara copiere)
    DynamicArray(DynamicArray&& other) noexcept;
    
    // Copy assignment operator (pentru completitudine)
    DynamicArray& operator=(const DynamicArray& other);
    
    // Move assignment operator (pentru completitudine)
    DynamicArray& operator=(DynamicArray&& other) noexcept;
    
    // Interfata publica - INCAPSULARE
    void push_back(int value);
    int get(size_t index) const;
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    std::string getName() const { return name; }
    void print() const;
    
private:
    // Functie helper pentru redimensionare
    void resize();
};

#endif // DYNAMIC_ARRAY_H
