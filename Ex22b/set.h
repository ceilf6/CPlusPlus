#ifndef _SET_H
#define _SET_H

#include "config.hpp"
#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>

using namespace std;
namespace Set
{
	// classe pour g�rer les exceptions dans le set
	class SetException
	{
	public:
		SetException(const string &i) : info(i) {}
		string getInfo() const { return info; }

	private:
		string info;
	};

	// caract�ristiques
	// 设立枚举，限制确保数据的安全性
	enum class Couleur
	{
		rouge,
		mauve,
		vert
	};
	enum class Nombre
	{
		un = 1,
		deux = 2,
		trois = 3
	};
	enum class Forme
	{
		ovale,
		vague,
		losange
	};
	enum class Remplissage
	{
		plein,
		vide,
		hachure
	};

	// conversion d'une caract�ristique en string
	string toString(Couleur c);
	string toString(Nombre v);
	string toString(Forme f);
	string toString(Remplissage v);

	// �criture d'une caract�ristique sur un flux ostream
	ostream &operator<<(ostream &f, Couleur c);
	ostream &operator<<(ostream &f, Nombre v);
	ostream &operator<<(ostream &f, Forme x);
	ostream &operator<<(ostream &f, Remplissage r);

	// listes contenant les valeurs possibles pour chacune des caract�ristiques
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;
	extern std::initializer_list<Forme> Formes;
	extern std::initializer_list<Remplissage> Remplissages;

	// affichage des valeurs possibles pour chaque caract�ristiques
	void printCouleurs(std::ostream &f = cout);
	void printNombres(std::ostream &f = cout);
	void printFormes(std::ostream &f = cout);
	void printRemplissages(std::ostream &f = cout);

	class Carte
	{
	private:
		// 四个属性
		Couleur couleur;
		Nombre nombre;
		Forme forme;
		Remplissage remplissage;
		// 构造函数
		Carte(Couleur c, Nombre n, Forme f, Remplissage r) : couleur(c), nombre(n), forme(f), remplissage(r) {}
		// les op�rations de construction par recopie, d'affectation,
		// de destruction par d�faut conviennent
		// 深拷贝构造函数
		Carte(const Carte &) = default;
		// 赋值重载函数
		Carte &operator=(const Carte &) = default;
		// 卡牌没有数组等外部资源，所以析构函数直接用 C++ 的最基础版本就好
		~Carte() = default;
		// 只允许 Jeu 有权限
		friend class Jeu; // now, Jeu access
						  // to the builder and destructors
						  // of Carte

	public:
		Couleur getCouleur() const { return couleur; }
		Nombre getNombre() const { return nombre; }
		Forme getForme() const { return forme; }
		Remplissage getRemplissage() const { return remplissage; }
	};
	ostream &operator<<(ostream &f, const Carte &c);

	class Jeu
	{
		// 注意：这里构造的是对象指针数组没问题，但如果构造的是对象数组就需要初始化器语法，否则编译器不知道该如何创建这个数组
		const Carte *cartes[config::NB_CARTES];
		/* d�sactivation du constructeur de recopie et
		et de l'op�rateur d'affectation */
		// 禁止了 Jeu 的拷贝和赋值，确保场上只有一个 Jeu 实例
		Jeu(const Jeu &) = delete;
		Jeu &operator=(const Jeu &) = delete;

		// transformation en singleton
		// 不用 default 的，得根据题目要求去 cpp 里面具体实现构造功能以及析构（因为开了一个数组资源）
		Jeu();
		~Jeu();

	public:
		// obtention de l'instance unique de Jeu
		static Jeu &getInstance()
		{
			static Jeu instance;
			return instance;
		}

		// size_t 无符号整数类型，用于表示永远不会为负的值（与底层操作系统有关，例如64位系统那么 size_t 即unsigned long（64 bit））
		const Carte &getCarte(size_t i) const;
		// 通过 config 去统一管理
		size_t getNbCartes() const { return config::NB_CARTES; }

		class Iterator
		{
			// a pointer over a specific Carte
			const Carte **currentCarte;
			size_t nb; // number of times I have the right
					   // to iterate
			Iterator(const Carte **c, size_t n) : currentCarte(c), nb(n) {}
			friend class Jeu;

		public:
			void next()
			{
				currentCarte++; // deplacement over the next Carte
				nb--;
			}
			bool isDone() const { return nb == 0; }
			const Carte &getCurrentItem() const
			{
				return **currentCarte;
			}
		};
		Iterator first()
		{
			const Carte **c = &cartes[0];
			return Iterator(c, config::NB_CARTES);
		}

		class IteratorBis
		{
			Jeu &instance; // an instance of the class Jeu
			size_t i;	   // the index of the current Carte
			IteratorBis(Jeu &j, size_t index) : instance(j), i(index) {}
			friend class Jeu;

		public:
			void next()
			{
				if (isDone())
					throw SetException("end of iteration");
				i++;
			}
			bool isDone() const { return i == instance.getNbCartes(); }
			const Carte &getCurrentItem() const
			{
				if (isDone())
					throw SetException("end of iteration");
				return instance.getCarte(i);
			}
		};
		IteratorBis firstBis()
		{
			return IteratorBis(*this, 0);
		}

		class const_iterator
		{
			const Jeu &instance; // an instance of the class Jeu
			size_t i;			 // the index of the current Carte
			const_iterator(const Jeu &j, size_t index) : instance(j), i(index) {}
			friend class Jeu;

		public:
			void operator++()
			{
				i++;
			}
			bool operator!=(const_iterator other) const
			{
				return i != other.i;
			}
			const Carte &operator*() const
			{
				return instance.getCarte(i);
			}
		};
		const_iterator begin() const { return const_iterator(*this, 0); }
		const_iterator end() const { return const_iterator(*this, config::NB_CARTES); }

		class FormeIterator
		{
			Forme forme;
			Jeu &instance; // an instance of the class Jeu
			size_t i;	   // the index of the current Carte
			FormeIterator(Jeu &j, size_t index, Forme f) : instance(j), i(index), forme(f) {}
			friend class Jeu;

		public:
			void next()
			{
				i++; // aller sur la carte suivante
				while (!isDone() &&
					   instance.getCarte(i).getForme() != forme)
					i++;
			}
			bool isDone() const { return i == instance.getNbCartes(); }
			const Carte &getCurrentItem() const
			{
				return instance.getCarte(i);
			}
		};
		FormeIterator firstFormeIterator(Forme f)
		{
			return FormeIterator(*this, 0, f);
		}
	};

	class Pioche
	{
	private:
		const Carte **cartes; // points over a dynamically allocated array
		size_t nb;			  // number of elements to consider in the array
	public:
		Pioche(Jeu &j) : nb(config::NB_CARTES)
		{
			cartes = new const Carte *[config::NB_CARTES]; // dynamically allocate an array of pointers
			// copy the adresses of the Carte which are contained in Jeu j
			for (size_t i = 0; i < j.getNbCartes(); i++)
				cartes[i] = &j.getCarte(i);
		}

		~Pioche()
		{
			delete[] cartes; // we have to deallocate the array of pointers
							 // but we don't have to destroy the cartes : it is the responsability of Jeu
		}

		const Carte &piocher(); // get a random carte from the pioche
		size_t getNbCartes() const { return nb; }
		bool estVide() const { return nb == 0; }
		// assignment and copy-construction are forbidden
		Pioche(const Pioche &p) = delete;			 // delete the default copy-constructor
		Pioche &operator=(const Pioche &p) = delete; // delete the default assignment operator
	};

	class Plateau
	{
		const Carte **cartes; // dynamically allocated array of pointers
		size_t nbMax;
		size_t nb;

	public:
		Plateau()
		{
			cartes = new const Carte *[5];
			nbMax = 5; // at first, we consider 5 places to record cartes
			nb = 0;	   // at te beginning, we don't have carte
		}
		~Plateau() { delete[] cartes; }
		size_t getNbCartes() const { return nb; }
		void ajouter(const Carte &c); // add a carte
		void retirer(const Carte &c); // remove a carte
		Plateau(const Plateau &p);
		Plateau &operator=(const Plateau &p);
		void print(ostream &f) const;
	};

	ostream &operator<<(ostream &f, const Plateau &c);

	class Combinaison
	{
		const Carte *c1;
		const Carte *c2;
		const Carte *c3;

	public:
		Combinaison(const Carte &C1, const Carte &C2, const Carte &C3) : c1(&C1), c2(&C2), c3(&C3) {}
		const Carte &getCarte1() const { return *c1; }
		const Carte &getCarte2() const { return *c2; }
		const Carte &getCarte3() const { return *c3; }
		bool estUnSet() const;
		~Combinaison() = default;								// the default-destructor is enough because we have nothing to do
		Combinaison(const Combinaison &c) = default;			// the default copy-constructor is also ok
		Combinaison &operator=(const Combinaison &c) = default; // and the default assignment operator too
	};

	ostream &operator<<(ostream &f, const Combinaison &c);

	class Controleur
	{
		Jeu &jeu;		 // r�f�rence sur le singleton de Jeu
		Plateau plateau; // composition : une classe compose toujours ses attributs
		Pioche *pioche;	 // Controleur compose son attribut pioche
						 // mais il compose aussi l'objet qui sera point� par pioche
						 // il est responsable du cycle de vie de cet objet
	public:
		Controleur() : jeu(Jeu::getInstance()) { pioche = new Pioche(jeu); }
		const Plateau &getPlateau() const { return plateau; }
		const Pioche &getPioche() const { return *pioche; }
		void distribuer();
		~Controleur() { delete pioche; }					 // il faut d�truire la pioche � cause de la composition
		Controleur(const Controleur &c) = delete;			 // interdiction de la construction par recopie
		Controleur &operator=(const Controleur &c) = delete; // et de l'affectation entre objets
	};
};
#endif
