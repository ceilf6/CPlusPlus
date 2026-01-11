#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include <algorithm>  // Pour std::transform
#include <cctype>     // Pour tolower

// ==================== VECTOR ====================
template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t vecSize;

public:
    // Classe iterator imbriquée
    class iterator {
    private:
        T* ptr;
    
    public:
        using value_type = T;
        
        explicit iterator(T* p = nullptr) : ptr(p) {}
        
        T& operator*() const {
            return *ptr;
        }
        
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }
        
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
        
        iterator operator+(int n) const {
            return iterator(ptr + n);
        }
        
        int operator-(const iterator& other) const {
            return ptr - other.ptr;
        }
        
        T* operator->() const {
            return ptr;
        }
    };
    
    Vector() : data(nullptr), capacity(0), vecSize(0) {}
    
    ~Vector() {
        delete[] data;
    }
    
    void push_back(const T& value) {
        if (vecSize >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < vecSize; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[vecSize++] = value;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    size_t size() const {
        return vecSize;
    }
    
    iterator begin() {
        return iterator(data);
    }
    
    iterator end() {
        return iterator(data + vecSize);
    }
};

// ==================== STACK ====================
template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    
    Node* topNode;
    size_t stackSize;

public:
    // Itérateur pour Stack
    class iterator {
    private:
        Node* current;
    
    public:
        using value_type = T;
        
        explicit iterator(Node* node = nullptr) : current(node) {}
        
        T& operator*() const {
            return current->data;
        }
        
        iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            if (current) {
                current = current->next;
            }
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
        
        T* operator->() const {
            return &(current->data);
        }
    };
    
    Stack() : topNode(nullptr), stackSize(0) {}
    
    ~Stack() {
        clear();
    }
    
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
    }
    
    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
            --stackSize;
        }
    }
    
    T& top() {
        return topNode->data;
    }
    
    bool empty() const {
        return topNode == nullptr;
    }
    
    size_t size() const {
        return stackSize;
    }
    
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
    iterator begin() {
        return iterator(topNode);
    }
    
    iterator end() {
        return iterator(nullptr);
    }
};

// ==================== FONCTION minimum_element AVEC PREDICAT ====================
template<typename Iterator, typename Compare>
Iterator minimum_element(Iterator first, Iterator last, Compare comp) {
    // Vérifier que la plage n'est pas vide
    if (first == last) {
        return last;
    }
    
    // Initialiser l'itérateur du minimum au premier élément
    Iterator min_it = first;
    ++first;
    
    // Parcourir les éléments restants en utilisant le comparateur
    for (; first != last; ++first) {
        if (comp(*first, *min_it)) {
            min_it = first;
        }
    }
    
    return min_it;
}

// Version surchargée sans comparateur (utilise operator< par défaut)
// Fonction helper pour la comparaison par défaut
template<typename T>
struct DefaultCompare {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template<typename Iterator>
Iterator minimum_element(Iterator first, Iterator last) {
    typedef typename Iterator::value_type value_type;
    return minimum_element(first, last, DefaultCompare<value_type>());
}

// ==================== FONCTIONS DE COMPARAISON ====================

// Fonction C classique
bool compareIntsAscending(int a, int b) {
    return a < b;
}

bool compareIntsDescending(int a, int b) {
    return a > b;  // Inverse de l'ordre normal
}

bool compareStringLength(const std::string& a, const std::string& b) {
    return a.length() < b.length();
}

// Foncteur (objet fonction)
class CompareByAbsoluteValue {
public:
    bool operator()(int a, int b) const {
        // Version manuelle de abs pour éviter les problèmes de compilation
        int abs_a = a < 0 ? -a : a;
        int abs_b = b < 0 ? -b : b;
        return abs_a < abs_b;
    }
};

class CompareByLastDigit {
public:
    bool operator()(int a, int b) const {
        // Gérer les nombres négatifs
        int last_a = a < 0 ? (-a) % 10 : a % 10;
        int last_b = b < 0 ? (-b) % 10 : b % 10;
        return last_a < last_b;
    }
};

// ==================== STRUCTURES POUR LES TESTS ====================

struct Person {
    std::string name;
    int age;
    double salary;
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " (" << p.age << " ans, " << p.salary << "€)";
        return os;
    }
};

// Fonction utilitaire pour convertir en minuscules (C++11 compatible)
std::string toLowerString(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// ==================== TESTS ====================

void testWithFunctionPointer() {
    std::cout << "\n=== Test avec pointeur de fonction ===" << std::endl;
    
    Vector<int> numbers;
    numbers.push_back(42);
    numbers.push_back(-17);
    numbers.push_back(89);
    numbers.push_back(-23);
    numbers.push_back(56);
    
    std::cout << "Nombres: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Test avec fonction de comparaison ascendante
    auto min_asc = minimum_element(numbers.begin(), numbers.end(), compareIntsAscending);
    if (min_asc != numbers.end()) {
        std::cout << "Minimum (ordre croissant): " << *min_asc << std::endl;
        assert(*min_asc == -23);
    }
    
    // Test avec fonction de comparaison descendante
    auto min_desc = minimum_element(numbers.begin(), numbers.end(), compareIntsDescending);
    if (min_desc != numbers.end()) {
        std::cout << "Minimum (ordre décroissant - donc max normal): " << *min_desc << std::endl;
        assert(*min_desc == 89);
    }
}

void testWithFunctor() {
    std::cout << "\n=== Test avec foncteur ===" << std::endl;
    
    Vector<int> numbers;
    numbers.push_back(42);
    numbers.push_back(-17);
    numbers.push_back(89);
    numbers.push_back(-23);
    numbers.push_back(56);
    numbers.push_back(15);
    numbers.push_back(-30);
    
    std::cout << "Nombres: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Test avec foncteur de valeur absolue
    CompareByAbsoluteValue absComp;
    auto min_abs = minimum_element(numbers.begin(), numbers.end(), absComp);
    if (min_abs != numbers.end()) {
        std::cout << "Minimum par valeur absolue: " << *min_abs << std::endl;
        assert(*min_abs == 15);
    }
    
    // Test avec foncteur de dernier chiffre
    CompareByLastDigit lastDigitComp;
    auto min_last = minimum_element(numbers.begin(), numbers.end(), lastDigitComp);
    if (min_last != numbers.end()) {
        std::cout << "Minimum par dernier chiffre: " << *min_last << std::endl;
        assert(*min_last == -30);  // 0 est le plus petit dernier chiffre
    }
}

void testWithLambda() {
    std::cout << "\n=== Test avec lambda expressions ===" << std::endl;
    
    Vector<std::string> words;
    words.push_back("chat");
    words.push_back("éléphant");
    words.push_back("souris");
    words.push_back("girafe");
    words.push_back("chien");
    
    std::cout << "Mots: ";
    for (const auto& w : words) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    
    // Lambda pour comparer par longueur
    auto min_length = minimum_element(words.begin(), words.end(),
        [](const std::string& a, const std::string& b) {
            return a.length() < b.length();
        });
    if (min_length != words.end()) {
        std::cout << "Mot le plus court: " << *min_length << std::endl;
        assert(*min_length == "chat");
    }
    
    // Lambda pour comparer par ordre alphabétique inverse
    auto min_reverse = minimum_element(words.begin(), words.end(),
        [](const std::string& a, const std::string& b) {
            return a > b;  // Ordre inverse
        });
    if (min_reverse != words.end()) {
        std::cout << "Premier mot par ordre alphabétique inverse: " << *min_reverse << std::endl;
        assert(*min_reverse == "souris");  // 's' est la plus grande lettre
    }
    
    // Lambda plus complexe: ignore la casse
    Vector<std::string> mixedCase;
    mixedCase.push_back("Pomme");
    mixedCase.push_back("banane");
    mixedCase.push_back("Abricot");
    mixedCase.push_back("ananas");
    
    auto min_nocase = minimum_element(mixedCase.begin(), mixedCase.end(),
        [](const std::string& a, const std::string& b) {
            return toLowerString(a) < toLowerString(b);
        });
    if (min_nocase != mixedCase.end()) {
        std::cout << "Premier mot (ignore case): " << *min_nocase << std::endl;
        assert(*min_nocase == "Abricot");
    }
}

void testWithCustomObjects() {
    std::cout << "\n=== Test avec objets personnalises ===" << std::endl;
    
    Vector<Person> people;
    people.push_back({"Alice", 30, 35000.0});
    people.push_back({"Bob", 25, 28000.0});
    people.push_back({"Charlie", 35, 42000.0});
    people.push_back({"David", 28, 31000.0});
    people.push_back({"Eve", 32, 38000.0});
    
    std::cout << "Personnes: " << std::endl;
    for (const auto& p : people) {
        std::cout << "  " << p << std::endl;
    }
    
    // Minimum par âge
    auto youngest = minimum_element(people.begin(), people.end(),
        [](const Person& a, const Person& b) {
            return a.age < b.age;
        });
    if (youngest != people.end()) {
        std::cout << "Plus jeune: " << *youngest << std::endl;
        assert(youngest->name == "Bob");
    }
    
    // Minimum par salaire
    auto lowest_paid = minimum_element(people.begin(), people.end(),
        [](const Person& a, const Person& b) {
            return a.salary < b.salary;
        });
    if (lowest_paid != people.end()) {
        std::cout << "Salaire le plus bas: " << *lowest_paid << std::endl;
        assert(lowest_paid->name == "Bob");
    }
    
    // Minimum par longueur du nom
    auto shortest_name = minimum_element(people.begin(), people.end(),
        [](const Person& a, const Person& b) {
            return a.name.length() < b.name.length();
        });
    if (shortest_name != people.end()) {
        std::cout << "Nom le plus court: " << *shortest_name << std::endl;
        assert(shortest_name->name == "Bob" || shortest_name->name == "Eve");
    }
}

void testWithStack() {
    std::cout << "\n=== Test avec Stack ===" << std::endl;
    
    Stack<double> values;
    values.push(3.14);
    values.push(2.71);
    values.push(1.41);
    values.push(1.62);
    values.push(2.50);
    
    std::cout << "Valeurs (haut->bas): ";
    for (double v : values) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    
    // Test avec lambda qui compare l'écart par rapport à 2.0
    auto closest_to_two = minimum_element(values.begin(), values.end(),
        [](double a, double b) {
            double diff_a = a - 2.0;
            double diff_b = b - 2.0;
            // Valeur absolue manuelle
            if (diff_a < 0) diff_a = -diff_a;
            if (diff_b < 0) diff_b = -diff_b;
            return diff_a < diff_b;
        });
    if (closest_to_two != values.end()) {
        std::cout << "Valeur la plus proche de 2.0: " << *closest_to_two << std::endl;
        // Vérification manuelle car comparaison flottante
        double diff = *closest_to_two - 2.0;
        if (diff < 0) diff = -diff;
        assert(diff < 0.51);  // 2.50 est à 0.50 de 2.0
    }
    
    // Foncteur pour avoir le maximum
    class GreaterDouble {
    public:
        bool operator()(double a, double b) const {
            return a > b;
        }
    };
    
    auto max_value = minimum_element(values.begin(), values.end(), GreaterDouble());
    if (max_value != values.end()) {
        std::cout << "Maximum (avec foncteur >): " << *max_value << std::endl;
        // Vérification avec marge d'erreur flottante
        assert(*max_value > 3.13 && *max_value < 3.15);
    }
}

void testEdgeCasesAndOverload() {
    std::cout << "\n=== Test cas limites et surcharge ===" << std::endl;
    
    Vector<int> empty;
    
    // Test plage vide avec prédicat
    auto result1 = minimum_element(empty.begin(), empty.end(), compareIntsAscending);
    std::cout << "Plage vide avec prédicat: " << (result1 == empty.end() ? "OK" : "ERREUR") << std::endl;
    assert(result1 == empty.end());
    
    // Test plage vide sans prédicat (surcharge)
    auto result2 = minimum_element(empty.begin(), empty.end());
    std::cout << "Plage vide sans prédicat: " << (result2 == empty.end() ? "OK" : "ERREUR") << std::endl;
    assert(result2 == empty.end());
    
    // Test avec un seul élément
    Vector<int> single;
    single.push_back(42);
    
    auto single_result = minimum_element(single.begin(), single.end(), 
        [](int a, int b) { return a > b; });  // Comparateur inverse
    if (single_result != single.end()) {
        std::cout << "Seul élément avec comparateur inverse: " << *single_result << std::endl;
        assert(*single_result == 42);
    }
    
    // Test de la surcharge sans prédicat
    Vector<int> nums;
    nums.push_back(5);
    nums.push_back(2);
    nums.push_back(8);
    nums.push_back(1);
    nums.push_back(4);
    
    auto default_min = minimum_element(nums.begin(), nums.end());  // Utilise operator< par défaut
    if (default_min != nums.end()) {
        std::cout << "Minimum avec surcharge par défaut: " << *default_min << std::endl;
        assert(*default_min == 1);
    }
}

void testPartialRanges() {
    std::cout << "\n=== Test avec plages partielles ===" << std::endl;
    
    Vector<int> numbers;
    for (int i = 0; i < 10; ++i) {
        numbers.push_back(i * i);  // Carrés: 0, 1, 4, 9, 16, 25, 36, 49, 64, 81
    }
    
    std::cout << "Carrés: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Premier tiers (0, 1, 4, 9) - minimum par défaut
    auto start1 = numbers.begin();
    auto end1 = numbers.begin() + 4;
    auto min1 = minimum_element(start1, end1);
    if (min1 != end1) {
        std::cout << "Minimum premier tiers: " << *min1 << std::endl;
        assert(*min1 == 0);
    }
    
    // Deuxième tiers (16, 25, 36) - comparateur personnalisé (reste modulo 10)
    auto start2 = numbers.begin() + 4;
    auto end2 = numbers.begin() + 7;
    auto min2 = minimum_element(start2, end2,
        [](int a, int b) { return (a % 10) < (b % 10); });
    if (min2 != end2) {
        std::cout << "Minimum deuxième tiers (par dernier chiffre): " << *min2 << std::endl;
        assert(*min2 == 25);  // 5 < 6
    }
}

int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "EXERCICE 37 - QUESTION 3" << std::endl;
    std::cout << "Fonction minimum_element avec prédicat (Strategy)" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    try {
        testWithFunctionPointer();
        testWithFunctor();
        testWithLambda();
        testWithCustomObjects();
        testWithStack();
        testEdgeCasesAndOverload();
        testPartialRanges();
        
        std::cout << "\n=========================================" << std::endl;
        std::cout << "TOUS LES TESTS ONT REUSSI !" << std::endl;
        std::cout << "=========================================" << std::endl;
        
        // Démonstration finale
        std::cout << "\n=== DEMONSTRATION FINALE ===" << std::endl;
        
        Vector<int> demo;
        for (int i = 0; i < 10; ++i) {
            demo.push_back((i * 13) % 7);  // Valeurs variées
        }
        
        std::cout << "Données de démo: ";
        for (int val : demo) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        // Différentes stratégies de comparaison
        std::cout << "\nDifférentes stratégies:" << std::endl;
        
        // 1. Ordre naturel
        auto natural = minimum_element(demo.begin(), demo.end());
        std::cout << "1. Ordre naturel: " << *natural << std::endl;
        
        // 2. Ordre inverse
        auto reverse = minimum_element(demo.begin(), demo.end(),
            [](int a, int b) { return a > b; });
        std::cout << "2. Ordre inverse (max): " << *reverse << std::endl;
        
        // 3. Par distance à 3
        auto closest_to_three = minimum_element(demo.begin(), demo.end(),
            [](int a, int b) {
                int diff_a = a - 3;
                int diff_b = b - 3;
                if (diff_a < 0) diff_a = -diff_a;
                if (diff_b < 0) diff_b = -diff_b;
                return diff_a < diff_b;
            });
        std::cout << "3. Plus proche de 3: " << *closest_to_three << std::endl;
        
        // 4. Par parité (pairs d'abord)
        auto parity = minimum_element(demo.begin(), demo.end(),
            [](int a, int b) {
                bool a_even = (a % 2 == 0);
                bool b_even = (b % 2 == 0);
                if (a_even != b_even) {
                    return a_even;  // Les pairs sont "plus petits"
                }
                return a < b;  // En cas d'égalité de parité
            });
        std::cout << "4. Par parité (pairs d'abord): " << *parity << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}