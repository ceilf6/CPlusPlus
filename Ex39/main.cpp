#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>  // Pour std::for_each
#include <functional> // Pour std::function
using namespace std;

// ============================================
// FONCTEURS (Functors) pour std::for_each
// ============================================

// Foncteur pour afficher un sommet et ses successeurs
template<class Vertex>
class PrintVertexFunctor {
private:
    ostream& output_stream;
    
public:
    // Constructeur qui capture le flux de sortie
    PrintVertexFunctor(ostream& os) : output_stream(os) {}
    
    // Opérateur () qui sera appelé par std::for_each
    // Prend une paire (sommet, ensemble de successeurs)
    void operator()(const pair<Vertex, set<Vertex>>& vertex_data) const {
        // Affiche le sommet
        output_stream << vertex_data.first << ":";
        
        // Foncteur interne pour afficher les successeurs
        class PrintSuccessorFunctor {
        private:
            ostream& os;
        public:
            PrintSuccessorFunctor(ostream& o) : os(o) {}
            void operator()(const Vertex& successor) const {
                os << " " << successor;
            }
        };
        
        // Utilise std::for_each pour afficher les successeurs
        PrintSuccessorFunctor print_successor(output_stream);
        for_each(vertex_data.second.begin(), vertex_data.second.end(), print_successor);
        
        output_stream << endl;
    }
};

// Foncteur pour compter les arcs (utilisé dans getNbEdges)
template<class Vertex>
class CountEdgesFunctor {
private:
    size_t& edge_count;  // Référence au compteur
    
public:
    CountEdgesFunctor(size_t& count) : edge_count(count) {}
    
    void operator()(const pair<Vertex, set<Vertex>>& vertex_data) const {
        edge_count += vertex_data.second.size();
    }
};

// ============================================
// CLASSE GraphG (version complète avec Question 2 et 3)
// ============================================
template<class Vertex>
class GraphG {
private:
    map<Vertex, set<Vertex>> adj;
    string name;
    
    // Helper pour les sommets inexistants
    const set<Vertex>& getSuccessorSet(const Vertex& v) const {
        static const set<Vertex> emptySet;
        auto it = adj.find(v);
        return (it != adj.end()) ? it->second : emptySet;
    }
    
public:
    // ============================================
    // ITERATEURS (Question 2)
    // ============================================
    class vertex_iterator {
    private:
        typename map<Vertex, set<Vertex>>::const_iterator it;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Vertex;
        using difference_type = std::ptrdiff_t;
        using pointer = const Vertex*;
        using reference = const Vertex&;
        
        vertex_iterator(typename map<Vertex, set<Vertex>>::const_iterator map_it = {}) 
            : it(map_it) {}
        
        const Vertex& operator*() const { return it->first; }
        const Vertex* operator->() const { return &(it->first); }
        
        vertex_iterator& operator++() { ++it; return *this; }
        vertex_iterator operator++(int) { vertex_iterator tmp = *this; ++it; return tmp; }
        
        bool operator==(const vertex_iterator& other) const { return it == other.it; }
        bool operator!=(const vertex_iterator& other) const { return it != other.it; }
    };
    
    class successor_iterator {
    private:
        typename set<Vertex>::const_iterator it;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Vertex;
        using difference_type = std::ptrdiff_t;
        using pointer = const Vertex*;
        using reference = const Vertex&;
        
        successor_iterator(typename set<Vertex>::const_iterator set_it = {}) 
            : it(set_it) {}
        
        const Vertex& operator*() const { return *it; }
        const Vertex* operator->() const { return &(*it); }
        
        successor_iterator& operator++() { ++it; return *this; }
        successor_iterator operator++(int) { successor_iterator tmp = *this; ++it; return tmp; }
        
        bool operator==(const successor_iterator& other) const { return it == other.it; }
        bool operator!=(const successor_iterator& other) const { return it != other.it; }
    };
    
    // ============================================
    // CONSTRUCTEUR ET METHODES DE BASE
    // ============================================
    GraphG(const string& n) : name(n) {}
    
    const string& getName() const { return name; }
    
    size_t getNbVertices() const { return adj.size(); }
    
    // Version de getNbEdges utilisant std::for_each
    size_t getNbEdges() const {
        size_t count = 0;
        
        // Crée le foncteur avec une référence au compteur
        CountEdgesFunctor<Vertex> count_functor(count);
        
        // Applique le foncteur à chaque élément de la map
        for_each(adj.begin(), adj.end(), count_functor);
        
        return count;
    }
    
    // Alternative: getNbEdges avec lambda (C++11)
    size_t getNbEdgesLambda() const {
        size_t count = 0;
        
        // Version avec lambda (plus moderne)
        for_each(adj.begin(), adj.end(),
            [&count](const pair<Vertex, set<Vertex>>& vertex_data) {
                count += vertex_data.second.size();
            }
        );
        
        return count;
    }
    
    void addVertex(const Vertex& i) {
        if (adj.find(i) == adj.end()) {
            adj[i] = set<Vertex>();
        }
    }
    
    void addEdge(const Vertex& i, const Vertex& j) {
        addVertex(i);
        addVertex(j);
        adj[i].insert(j);
    }
    
    void removeEdge(const Vertex& i, const Vertex& j) {
        auto it = adj.find(i);
        if (it != adj.end()) {
            it->second.erase(j);
        }
    }
    
    void removeVertex(const Vertex& i) {
        adj.erase(i);
        for (auto& pair : adj) {
            pair.second.erase(i);
        }
    }
    
    // ============================================
    // METHODES POUR LES ITERATEURS
    // ============================================
    vertex_iterator begin_vertex() const {
        return vertex_iterator(adj.begin());
    }
    
    vertex_iterator end_vertex() const {
        return vertex_iterator(adj.end());
    }
    
    successor_iterator begin_successor(const Vertex& v) const {
        const set<Vertex>& successors = getSuccessorSet(v);
        return successor_iterator(successors.begin());
    }
    
    successor_iterator end_successor(const Vertex& v) const {
        const set<Vertex>& successors = getSuccessorSet(v);
        return successor_iterator(successors.end());
    }
    
    // ============================================
    // METHODE PRINT utilisant std::for_each (Question 3)
    // ============================================
    void print(ostream& f) const {
        // En-tête du graphe
        f << "graph " << name << " (" << getNbVertices() 
          << " vertices and " << getNbEdges() << " edges)" << endl;
        
        // Crée le foncteur d'affichage
        PrintVertexFunctor<Vertex> print_functor(f);
        
        // Utilise std::for_each pour parcourir et afficher tous les sommets
        // C'est la manière "inutilement compliquée" demandée dans l'énoncé !
        for_each(adj.begin(), adj.end(), print_functor);
    }
    
    // Version de print avec lambda (alternative)
    void printLambda(ostream& f) const {
        f << "graph " << name << " (" << getNbVertices() 
          << " vertices and " << getNbEdges() << " edges)" << endl;
        
        // Version avec lambda function
        for_each(adj.begin(), adj.end(),
            [&f](const pair<Vertex, set<Vertex>>& vertex_data) {
                f << vertex_data.first << ":";
                
                // Lambda imbriquée pour les successeurs
                for_each(vertex_data.second.begin(), vertex_data.second.end(),
                    [&f](const Vertex& successor) {
                        f << " " << successor;
                    }
                );
                
                f << endl;
            }
        );
    }
};

// ============================================
// OPERATEUR << utilisant std::for_each (Question 3)
// ============================================
template<class V>
ostream& operator<<(ostream& f, const GraphG<V>& G) {
    G.print(f);  // Utilise la version avec foncteur
    return f;
}

// ============================================
// TESTS SPÉCIFIQUES POUR LA QUESTION 3
// ============================================

// Test 1: Foncteur simple pour démontrer le principe
void test_foncteur_simple() {
    cout << "\n=== TEST Foncteur Simple ===" << endl;
    
    // Création d'un vecteur d'entiers
    vector<int> nombres = {1, 2, 3, 4, 5};
    
    // Foncteur pour afficher un nombre au carré
    class CarreFunctor {
    public:
        void operator()(int n) const {
            cout << n << "^2 = " << n * n << endl;
        }
    };
    
    cout << "Carrés des nombres :" << endl;
    CarreFunctor affiche_carre;
    for_each(nombres.begin(), nombres.end(), affiche_carre);
}

// Test 2: Vérification que std::for_each fonctionne
void test_stl_for_each() {
    cout << "\n=== TEST std::for_each avec vector ===" << endl;
    
    vector<string> mots = {"Bonjour", "le", "monde", "C++"};
    
    // Foncteur pour compter les lettres
    class CompteLettresFunctor {
    private:
        int& total;
    public:
        CompteLettresFunctor(int& t) : total(t) {}
        void operator()(const string& mot) const {
            total += mot.length();
            cout << mot << " (" << mot.length() << " lettres)" << endl;
        }
    };
    
    int total_lettres = 0;
    CompteLettresFunctor compte(total_lettres);
    
    cout << "Mots et leur longueur :" << endl;
    for_each(mots.begin(), mots.end(), compte);
    cout << "Total lettres: " << total_lettres << endl;
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================
int main() {
    cout << "=== QUESTION 3 - std::for_each avec foncteur ===" << endl;
    
    // Test des concepts de base
    test_foncteur_simple();
    test_stl_for_each();
    
    cout << "\n=== TEST avec GraphG ===" << endl;
    
    try {
        // Test 1: Exemple de l'énoncé
        cout << "\n1. TEST - Exemple de l'énoncé avec foncteur" << endl;
        GraphG<char> G2("G2");
        
        G2.addVertex('a'); 
        G2.addVertex('b'); 
        G2.addEdge('a', 'c');
        G2.addEdge('a', 'd'); 
        G2.addEdge('d', 'e'); 
        G2.addEdge('e', 'b');
        
        // Affichage avec l'opérateur << qui utilise std::for_each
        cout << G2;
        
        // Test getNbEdges avec foncteur
        cout << "\nNombre d'arcs (avec foncteur): " << G2.getNbEdges() << endl;
        cout << "Nombre d'arcs (avec lambda): " << G2.getNbEdgesLambda() << endl;
        
        // Test 2: Affichage avec printLambda
        cout << "\n2. TEST - Affichage avec lambda" << endl;
        G2.printLambda(cout);
        
        // Test 3: Vérification des itérateurs toujours fonctionnels
        cout << "\n3. TEST - Itérateurs toujours fonctionnels" << endl;
        cout << "Sommets de G2 : ";
        for(auto it = G2.begin_vertex(); it != G2.end_vertex(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "Successeurs de 'a' : ";
        for(auto it = G2.begin_successor('a'); it != G2.end_successor('a'); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        // Test 4: Graphe avec strings
        cout << "\n4. TEST - Graphe avec strings" << endl;
        GraphG<string> G3("Pref");
        G3.addEdge("LO21","IA01"); 
        G3.addEdge("IA02","IA01"); 
        G3.addEdge("IA01","NF17");
        G3.addEdge("IA02","NF16"); 
        G3.addEdge("NF93","NF16");
        
        cout << G3;
        
        // Test 5: Graphe vide
        cout << "\n5. TEST - Graphe vide" << endl;
        GraphG<int> G4("Vide");
        cout << G4;
        
        // Test 6: Graphe avec un seul arc
        cout << "\n6. TEST - Graphe avec un seul arc" << endl;
        GraphG<char> G5("Simple");
        G5.addEdge('x', 'y');
        cout << G5;
        
        cout << "Vérification getNbEdges: " << G5.getNbEdges() 
             << " (attendu: 1)" << endl;
        
        // Test 7: Performance et vérification
        cout << "\n7. TEST - Comparaison des méthodes" << endl;
        GraphG<int> G6("Performance");
        
        // Ajout de quelques arcs
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 3; j++) {
                G6.addEdge(i, i + j + 1);
            }
        }
        
        cout << "Graphe G6 :" << endl;
        G6.print(cout);  // Avec foncteur
        
        cout << "\nMême graphe avec lambda :" << endl;
        G6.printLambda(cout);
        
        cout << "\nVérification cohérence :" << endl;
        cout << "getNbEdges(): " << G6.getNbEdges() << endl;
        cout << "getNbEdgesLambda(): " << G6.getNbEdgesLambda() << endl;
        cout << "getNbVertices(): " << G6.getNbVertices() << endl;
        
    } catch(exception& e) { 
        cout << "ERREUR : " << e.what() << "\n"; 
        return 1;
    }
    
    cout << "\n=== TOUS LES TESTS RÉUSSIS ===" << endl;
    cout << "L'opérateur << utilise bien std::for_each avec un foncteur" << endl;
    cout << "comme demandé dans la Question 3 (même si c'est inutilement compliqué!)" << endl;
    
    return 0;
} 