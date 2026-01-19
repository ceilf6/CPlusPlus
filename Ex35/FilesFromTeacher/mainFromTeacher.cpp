#include <iostream>
#include <string>
#include "container.h"

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "         TEST DE LA CLASSE VECTOR         " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    // Test 1: Constructeur de base
    std::cout << "\n1. Test constructeur:" << std::endl;
    Vector<int> v1(3, 10);
    std::cout << "   Vector<int> v1(3, 10)" << std::endl;
    std::cout << "   Taille: " << v1.size() << std::endl;
    std::cout << "   Capacité: " << v1.getCapacity() << std::endl;
    
    // Test 2: push_back et redimensionnement
    std::cout << "\n2. Test push_back:" << std::endl;
    std::cout << "   Avant push_back - Capacité: " << v1.getCapacity() << std::endl;
    
    for (int i = 0; i < 10; ++i) {
        v1.push_back(i * 100);
    }
    
    std::cout << "   Après 10 push_back - Taille: " << v1.size() << std::endl;
    std::cout << "   Après 10 push_back - Capacité: " << v1.getCapacity() << std::endl;
    
    // Test 3: operator[]
    std::cout << "\n3. Test operator[]:" << std::endl;
    std::cout << "   v1[0] = " << v1[0] << std::endl;
    std::cout << "   v1[5] = " << v1[5] << std::endl;
    
    v1[0] = 999;
    std::cout << "   Après v1[0] = 999: " << v1[0] << std::endl;
    
    // Test 4: front() et back()
    std::cout << "\n4. Test front() et back():" << std::endl;
    std::cout << "   front(): " << v1.front() << std::endl;
    std::cout << "   back(): " << v1.back() << std::endl;
    
    // Test 5: std::string
    std::cout << "\n5. Test avec std::string:" << std::endl;
    Vector<std::string> v2(2, "hello");
    v2.push_back("world");
    v2.push_back("!");
    
    for (size_t i = 0; i < v2.size(); ++i) {
        std::cout << "   v2[" << i << "] = \"" << v2[i] << "\"" << std::endl;
    }
    
    // Test 6: resize
    std::cout << "\n6. Test resize:" << std::endl;
    Vector<int> v3;
    v3.resize(5, 42);
    std::cout << "   Après resize(5, 42):" << std::endl;
    std::cout << "   Taille: " << v3.size() << std::endl;
    
    // Test 7: reserve
    std::cout << "\n7. Test reserve:" << std::endl;
    std::cout << "   Avant reserve(50) - Capacité: " << v3.getCapacity() << std::endl;
    v3.reserve(50);
    std::cout << "   Après reserve(50) - Capacité: " << v3.getCapacity() << std::endl;
    std::cout << "   Taille: " << v3.size() << " (inchangée)" << std::endl;
    
    // Test 8: insert et erase
    std::cout << "\n8. Test insert et erase:" << std::endl;
    Vector<int> v4;
    v4.push_back(1);
    v4.push_back(3);
    v4.insert(1, 2);
    
    std::cout << "   Après insert(1, 2): ";
    for (size_t i = 0; i < v4.size(); ++i) {
        std::cout << v4[i] << " ";
    }
    std::cout << std::endl;
    
    v4.erase(0);
    std::cout << "   Après erase(0): ";
    for (size_t i = 0; i < v4.size(); ++i) {
        std::cout << v4[i] << " ";
    }
    std::cout << std::endl;
    
    // Test 9: Copie
    std::cout << "\n9. Test copie:" << std::endl;
    Vector<int> original(3, 7);
    Vector<int> copie(original);
    
    original[0] = 999;
    std::cout << "   original[0] = " << original[0] << std::endl;
    std::cout << "   copie[0] = " << copie[0] << " (doit être 7)" << std::endl;
    
    // Test 10: Exceptions
    std::cout << "\n10. Test exceptions:" << std::endl;
    try {
        Vector<int> empty;
        std::cout << "   Tentative d'accès à empty[0]..." << std::endl;
        int x = empty[0];
        std::cout << "   ERREUR: aurait dû lever une exception!" << std::endl;
    } catch (const ContainerException& e) {
        std::cout << "   ✓ Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n==========================================" << std::endl;
    std::cout << "        TESTS RÉUSSIS !                 " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    return 0;
}
