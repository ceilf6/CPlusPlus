#include <iostream>
#include <string>
#include "stack_class_adapter.h"
#include "stack_object_adapter.h"
#include "stack_strategy.h"

void test_basic() {
    std::cout << "=== TEST BASIQUE DES 3 IMPLEMENTATIONS ===" << std::endl;
    
    // Test StackClassAdapter
    std::cout << "\n1. StackClassAdapter:" << std::endl;
    StackClassAdapter<int> stack1;
    stack1.push(10);
    stack1.push(20);
    std::cout << "   top: " << stack1.top() << ", size: " << stack1.size() << std::endl;
    stack1.pop();
    std::cout << "   après pop - top: " << stack1.top() << std::endl;
    
    // Test StackObjectAdapter
    std::cout << "\n2. StackObjectAdapter:" << std::endl;
    StackObjectAdapter<int> stack2;
    stack2.push(100);
    stack2.push(200);
    std::cout << "   top: " << stack2.top() << ", size: " << stack2.size() << std::endl;
    
    // Test Stack avec Stratégie
    std::cout << "\n3. Stack avec Stratégie:" << std::endl;
    Stack<int> stack3;
    stack3.push(1000);
    stack3.push(2000);
    std::cout << "   top: " << stack3.top() << ", size: " << stack3.size() << std::endl;
    
    std::cout << "\n✅ Tous les tests basiques passent!" << std::endl;
}

void test_exceptions() {
    std::cout << "\n=== TEST EXCEPTIONS ===" << std::endl;
    
    try {
        StackClassAdapter<int> emptyStack;
        emptyStack.pop();
        std::cout << "❌ ERREUR: aurait dû lever une exception!" << std::endl;
    } catch (const StackException& e) {
        std::cout << "✓ StackClassAdapter: " << e.what() << std::endl;
    }
    
    try {
        StackObjectAdapter<int> emptyStack;
        emptyStack.top();
        std::cout << "❌ ERREUR: aurait dû lever une exception!" << std::endl;
    } catch (const StackException& e) {
        std::cout << "✓ StackObjectAdapter: " << e.what() << std::endl;
    }
    
    try {
        Stack<int> emptyStack;
        emptyStack.top();
        std::cout << "❌ ERREUR: aurait dû lever une exception!" << std::endl;
    } catch (const StackException& e) {
        std::cout << "✓ Stack Stratégie: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "   EXERCICE STACK - PATTERN ADAPTER      " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    test_basic();
    test_exceptions();
    
    std::cout << "\n==========================================" << std::endl;
    std::cout << "          TESTS RÉUSSIS !                 " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    return 0;
}