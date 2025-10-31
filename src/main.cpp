#include "DynamicArray.h"
#include <iostream>

using namespace std;

// Functie helper pentru a crea un array temporar (rvalue)
// Demonstreaza move constructor
DynamicArray createTempArray(const string& name) {
    DynamicArray temp(name, 5);
    temp.push_back(100);
    temp.push_back(200);
    return temp;  // Aici se va apela MOVE CONSTRUCTOR (nu copy)
}

void demonstrateConstructor() {
    cout << "\n========================================" << endl;
    cout << "DEMONSTRATIE 1: CONSTRUCTOR" << endl;
    cout << "========================================" << endl;
    cout << "Creare array cu initializare membri si alocare heap..." << endl;
    DynamicArray arr1("arr1", 5);
    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);
    arr1.print();
    cout << "-> Membrii sunt corect initializati in constructor" << endl;
    cout << "-> Memoria este alocata pe heap cu 'new'" << endl;
}

void demonstrateDestructor() {
    cout << "\n========================================" << endl;
    cout << "DEMONSTRATIE 2: DESTRUCTOR" << endl;
    cout << "========================================" << endl;
    cout << "Creez un array in scope local..." << endl;
    {
        DynamicArray arr2("arr2_local", 3);
        arr2.push_back(1);
        arr2.push_back(2);
        arr2.print();
        cout << "-> La iesirea din scope, destructorul va elibera heap-ul..." << endl;
    } // Aici se apeleaza DESTRUCTORUL automat
    cout << "-> Destructorul a fost apelat si memoria a fost eliberata!" << endl;
    cout << "-> FARA destructor -> MEMORY LEAK!" << endl;
}

void demonstrateCopyConstructor() {
    cout << "\n========================================" << endl;
    cout << "DEMONSTRATIE 3: COPY CONSTRUCTOR" << endl;
    cout << "========================================" << endl;
    
    cout << "\nCreare array original..." << endl;
    DynamicArray original("original", 5);
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);
    original.print();
    
    cout << "\nCopiere array (va apela copy constructor)..." << endl;
    DynamicArray copy = original;  // COPY CONSTRUCTOR
    copy.print();
    
    cout << "\nModific copia (adaug 99)..." << endl;
    copy.push_back(99);
    
    cout << "\nAfisez ambele array-uri:" << endl;
    original.print();
    copy.print();
    
    cout << "\n-> OBSERVATIE IMPORTANTA:" << endl;
    cout << "-> Original NU a fost afectat de modificarea copiei!" << endl;
    cout << "-> Acest lucru e posibil DOAR cu COPY CONSTRUCTOR (deep copy)" << endl;
    cout << "\n-> FARA copy constructor:" << endl;
    cout << "   - Shallow copy -> ambele obiecte ar pointa la aceeasi memorie" << endl;
    cout << "   - Modificarea unuia ar afecta celalalt" << endl;
    cout << "   - La distrugere -> DOUBLE FREE -> CRASH!" << endl;
}

void demonstrateMoveConstructor() {
    cout << "\n========================================" << endl;
    cout << "DEMONSTRATIE 4: MOVE CONSTRUCTOR" << endl;
    cout << "========================================" << endl;
    
    cout << "\nCreez array temporar (functia returneaza prin valoare)..." << endl;
    DynamicArray moved = createTempArray("temp");  // MOVE CONSTRUCTOR
    moved.print();
    
    cout << "\n-> OBSERVATIE IMPORTANTA:" << endl;
    cout << "-> Move constructor a TRANSFERAT resursele (nu le-a copiat)" << endl;
    cout << "-> Mult mai EFICIENT decat copy constructor" << endl;
    cout << "-> Util pentru obiecte temporare (rvalue)" << endl;
    
    cout << "\nDemonstratie explicita cu std::move..." << endl;
    DynamicArray arr3("arr3", 5);
    arr3.push_back(111);
    arr3.push_back(222);
    arr3.print();
    
    cout << "\nMut explicit arr3 in arr4..." << endl;
    DynamicArray arr4(std::move(arr3));  // MOVE CONSTRUCTOR explicit
    arr4.print();
    cout << "-> arr3 a fost invalidat (resursele au fost transferate)" << endl;
}

void demonstrateEncapsulation() {
    cout << "\n========================================" << endl;
    cout << "DEMONSTRATIE 5: INCAPSULARE" << endl;
    cout << "========================================" << endl;
    
    DynamicArray arr("arr_encapsulation", 5);
    
    cout << "\n-> Membri privati (data, size, capacity) NU sunt accesibili direct" << endl;
    cout << "-> Accesul se face DOAR prin interfata publica (metode)" << endl;
    cout << "\nUtilizare interfata publica:" << endl;
    
    arr.push_back(5);
    arr.push_back(10);
    arr.push_back(15);
    
    cout << "  - push_back() pentru adaugare elemente" << endl;
    cout << "  - get() pentru citire element: arr[1] = " << arr.get(1) << endl;
    cout << "  - getSize() pentru dimensiune: " << arr.getSize() << endl;
    cout << "  - getCapacity() pentru capacitate: " << arr.getCapacity() << endl;
    cout << "  - print() pentru afisare" << endl;
    
    arr.print();
    
    cout << "\n-> BENEFICII INCAPSULARE:" << endl;
    cout << "   - Protectie date (nu se pot modifica direct membri privati)" << endl;
    cout << "   - Validare input (ex: verificare index in get())" << endl;
    cout << "   - Flexibilitate (implementarea poate fi schimbata fara a afecta codul client)" << endl;
}

int main() {
    cout << "╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║     PROIECT PAOO - DEMONSTRATIE CONCEPTE OOP C++      ║" << endl;
    cout << "║                                                        ║" << endl;
    cout << "║  Concepte demonstrate:                                ║" << endl;
    cout << "║  1. Build cu CMake (structura laborator)              ║" << endl;
    cout << "║  2. Incapsulare                                       ║" << endl;
    cout << "║  3. Initializare membri in constructor                ║" << endl;
    cout << "║  4. Eliberare heap in destructor                      ║" << endl;
    cout << "║  5. Copy constructor (deep copy)                      ║" << endl;
    cout << "║  6. Move constructor (transfer resurse)               ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    
    try {
        demonstrateConstructor();
        demonstrateDestructor();
        demonstrateCopyConstructor();
        demonstrateMoveConstructor();
        demonstrateEncapsulation();
        
        cout << "\n========================================" << endl;
        cout << "FINALIZARE PROGRAM" << endl;
        cout << "========================================" << endl;
        cout << "Toate obiectele vor fi distruse automat..." << endl;
        cout << "Urmariti mesajele de la destructori!\n" << endl;
        
    } catch (const exception& e) {
        cerr << "Eroare: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
