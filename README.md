# Proiect PAOO - Demonstrare Concepte OOP în C++

## 📋 Descriere

Acest proiect demonstrează conceptele fundamentale de programare orientată pe obiecte în C++:

1. ✅ **Build folosind CMake** - structura laborator (include/, src/, build/)
2. ✅ **Încapsulare** - membri privați, interfață publică
3. ✅ **Inițializare membri în constructor** - member initializer list, alocare heap
4. ✅ **Eliberare heap în destructor** - prevenire memory leaks
5. ✅ **Copy constructor** - deep copy pentru evitare double free
6. ✅ **Move constructor** - transfer eficient de resurse

## 🏗️ Structura Proiectului

```
PAOO/
├── CMakeLists.txt          # Configurare CMake
├── README.md               # Documentație
├── include/
│   └── DynamicArray.h      # Header cu declarații clase
└── src/
    ├── DynamicArray.cpp    # Implementare clasă
    └── main.cpp            # Demonstrații
```

## 🎯 Clasa Principală: DynamicArray

Am implementat o clasă `DynamicArray` care gestionează un array dinamic. Aceasta demonstrează clar **de ce** sunt necesare fiecare din conceptele cerute:

### De ce DynamicArray?
- **Gestionează memorie dinamică** → nevoia de destructor
- **Conține pointeri** → nevoia de copy constructor (deep copy)
- **Poate fi mișcată eficient** → nevoia de move constructor
- **Are invarianți** → nevoia de încapsulare

## 🔍 Demonstrații Incluse

### 1. Constructor cu Inițializare Membri
```cpp
DynamicArray::DynamicArray(const std::string& arrayName, size_t initialCapacity)
    : data(new int[initialCapacity]),  // Alocare pe HEAP
      size(0),
      capacity(initialCapacity),
      name(arrayName)
{
    std::cout << "[CONSTRUCTOR] Creat array..." << std::endl;
}
```
**Demonstrează**: Alocarea pe heap, member initializer list, mesaje console

### 2. Destructor cu Eliberare Heap
```cpp
~DynamicArray() {
    std::cout << "[DESTRUCTOR] Eliberez heap..." << std::endl;
    delete[] data;  // CRUCIAL: fără asta -> MEMORY LEAK!
}
```
**Demonstrează**: De ce este necesar (fără el → memory leak permanent)

### 3. Copy Constructor (Deep Copy)
```cpp
DynamicArray::DynamicArray(const DynamicArray& other)
    : data(new int[other.capacity]),  // Alocare NOUĂ memorie
      size(other.size),
      capacity(other.capacity)
{
    std::memcpy(data, other.data, size * sizeof(int));  // DEEP COPY
}
```
**Demonstrează**: 
- **Fără copy constructor** → shallow copy → double free → **CRASH**
- **Cu copy constructor** → deep copy → fiecare obiect are propria memorie

### 4. Move Constructor (Transfer Resurse)
```cpp
DynamicArray::DynamicArray(DynamicArray&& other) noexcept
    : data(other.data),        // TRANSFER pointer
      size(other.size),
      capacity(other.capacity)
{
    other.data = nullptr;  // Invalidare sursă
    other.size = 0;
}
```
**Demonstrează**: Transfer eficient (fără copiere) pentru obiecte temporare

### 5. Încapsulare
- Membri privați: `data`, `size`, `capacity`
- Interfață publică: `push_back()`, `get()`, `print()`, etc.
- **Beneficii**: protecție date, validare input, flexibilitate

## 🚀 Compilare și Rulare

### Pe Windows (cu CMake și Visual Studio)

```batch
# Creează directorul build
mkdir build
cd build

# Generează fișierele de build
cmake ..

# Compilează
cmake --build .

# Rulează
Debug\paoo_demo.exe
```

### Pe Windows (cu MinGW)

```batch
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
paoo_demo.exe
```

### Pe Linux/Mac

```bash
mkdir build
cd build
cmake ..
make
./paoo_demo
```

## 📊 Output Așteptat

Programul va afișa mesaje detaliate pentru fiecare operație:

```
╔════════════════════════════════════════════════════════╗
║     PROIECT PAOO - DEMONSTRATIE CONCEPTE OOP C++      ║
╚════════════════════════════════════════════════════════╝

========================================
DEMONSTRATIE 1: CONSTRUCTOR
========================================
[CONSTRUCTOR] Creat array 'arr1' cu capacitate 5 (alocat 20 bytes pe heap)
...

========================================
DEMONSTRATIE 3: COPY CONSTRUCTOR
========================================
[CONSTRUCTOR] Creat array 'original'...
[COPY CONSTRUCTOR] Copiez array 'original' -> 'original_copy' (deep copy)
-> Original NU a fost afectat de modificarea copiei!
...

[DESTRUCTOR] Distrus array 'original_copy' - eliberez 20 bytes de pe heap
[DESTRUCTOR] Distrus array 'original' - eliberez 20 bytes de pe heap
```

## 📝 Punctaj Acoperit

- ✅ **(3p)** Build CMake cu structura laborator
- ✅ **(1p)** Încapsulare - membri privați, interfață publică
- ✅ **(1p)** Inițializare membri în constructor
- ✅ **(1p)** Eliberare heap în destructor
- ✅ **(2p)** Copy constructor cu deep copy
- ✅ **(2p)** Move constructor cu transfer resurse

**Total: 10 puncte**

## 💡 De Ce Sunt Necesare Aceste Concepte?

Programul demonstrează **explicit** consecințele lipsei fiecărui concept:

1. **Fără destructor** → Memory leak permanent
2. **Fără copy constructor** → Shallow copy → double free → crash la runtime
3. **Fără move constructor** → Copieri inutile → performanță slabă
4. **Fără încapsulare** → Date expuse → imposibil de validat → bugs

## 🎓 Concepte Avansate Demonstrate

- **RAII** (Resource Acquisition Is Initialization)
- **Rule of Five** (destructor, copy constructor, copy assignment, move constructor, move assignment)
- **Deep copy vs Shallow copy**
- **Lvalue vs Rvalue**
- **std::move** pentru conversie explicită la rvalue

## 📚 Referințe

- C++ Core Guidelines
- Effective Modern C++ (Scott Meyers)
- CMake Best Practices

---

**Autor**: Alexandru Tulbure  
**Curs**: PAOO (Programare Avansată Orientată pe Obiecte)  
**Data**: Octombrie 2025
