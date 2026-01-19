Exercice 37 - Conteneurs - Design pattern Iterator et algorithmes
Question 1
Implémenter le design pattern "itérateur" en créant le type iterator pour les classes Vector et Stack :

— Pour accéder 4 l’élément désigné par un itérateur, on utilisera l’opérateur operator«.

— Pour qu’un itérateur désigne |’élément suivant, on lui appliquera l’opérateur operator++.

— Afin de comparer deux itérateurs, on surchargera les opérateurs operator== et operator! = : on suppose
que deux itérateurs sont égaux s’ils désignent le méme élément.

— Pour les classes Vector et Stack, on implémentera la fonction begin () qui renvoie un itérateur désignant
le premier élément.

— Pour les classes Vector et Stack, on implémentera aussi la fonction end() qui renvoie un itérateur d@
signant |’élément (fictif) qui suit le dernier élément, c’est 4 dire ’itérateur que |’on obtient si on applique
Vopérateur ++ sur un itérateur désignant le dernier élément.

— Pour le type Stack::iterator, préciser les différentes possibilités d’implémentation.

— Avec un simple copier/coller et quelques modifications, on implémentera aussi un type const_iterator
ainsi que les méthodes begin() et end() correspondantes.

Question 2

Implémenter la fonction minimum_element qui prend en arguments deux itérateurs it1 et it2 de n’importe
quel conteneur et qui permet de renvoyer un itérateur désignant |’éleément minimum dans le conteneur entre les
itérateurs it1 et it2 (it2 non compris), par rapport a l’opérateur operator<. On supposera pour cela que cet
opérateur a été surchargé pour le type d’élément contenu dans le conteneur.

Question 3

Implémenter la fonction minimum_element qui prend en arguments deux itérateurs it1 et it2 de n’importe
quel conteneur, ainsi qu’un prédicat binaire définissant un ordre sur les éléments (design pattern "Strategy"). La
fonction permet de renvoyer un itérateur désignant |’élément minimum par rapport au prédicat binaire dans le
conteneur entre les itérateurs ‘it 1 et it2 (it2 non compris). Le prédicat binaire doit renvoyer true ou false.
Il pourra étre soit une fonction prenant en arguments deux objets du type de ceux contenus dans le conteneur, soit
un objet fonction dont l’opérateur operator () prend en arguments deux objets du type de ceux contenus dans le
conteneur, soit une lambda-expression équivalente.

⸻

练习 37 —— 容器（Containers）—— 设计模式：迭代器（Iterator）与算法（Algorithmes）

⸻

问题 1 —— 设计模式：迭代器（Iterator）

为 Vector 和 Stack 两个类实现 迭代器（iterator）设计模式，具体要求如下：

⸻

1️⃣ 访问迭代器所指向的元素
	•	使用 解引用运算符 operator*
	•	通过 *it 的形式访问迭代器当前指向的元素

⸻

2️⃣ 移动到下一个元素
	•	对迭代器应用 自增运算符 operator++
	•	使迭代器指向 下一个元素

⸻

3️⃣ 迭代器比较
	•	重载：
	•	operator==
	•	operator!=
	•	约定：
当两个迭代器指向同一个元素时，它们被认为是相等的

⸻

4️⃣ begin() 方法
	•	在 Vector 和 Stack 中实现 begin()
	•	该方法返回一个迭代器，指向 容器中的第一个元素

⸻

5️⃣ end() 方法
	•	在 Vector 和 Stack 中实现 end()
	•	返回一个 “虚拟的迭代器”，指向：
最后一个元素之后的位置

也就是说：
	•	如果对一个指向最后一个元素的迭代器应用 operator++
	•	得到的迭代器应当等于 end()

⸻

6️⃣ 关于 Stack::iterator 的实现方式
	•	请说明 Stack::iterator 的不同实现可能性
（例如：直接基于底层容器的迭代器，或自行实现等）

⸻

7️⃣ const_iterator
	•	通过简单的 复制 + 少量修改
	•	再实现一个：
	•	const_iterator 类型
	•	以及对应的 begin() const / end() const

⸻

问题 2 —— 泛型算法：minimum_element

实现一个函数 minimum_element，要求：
	•	接收两个迭代器 it1 和 it2
	•	适用于 任意容器
	•	返回一个迭代器，指向区间 [it1, it2)（不包含 it2）中：
最小的元素

比较规则：
	•	使用元素类型已经重载的 operator<
	•	假设该运算符已正确实现

⸻

问题 3 —— 泛型算法 + Strategy 模式

实现 另一个版本的 minimum_element，要求：
	•	接收：
	•	两个迭代器 it1、it2
	•	一个 二元谓词（binary predicate）
	•	返回区间 [it1, it2) 中：
按该谓词定义的顺序下的最小元素对应的迭代器

⸻

关于二元谓词（非常重要）

该谓词应返回 true 或 false，可以是以下任意形式：
	1.	普通函数

bool cmp(const T& a, const T& b);


	2.	函数对象（仿函数）

struct Cmp {
    bool operator()(const T& a, const T& b) const;
};


	3.	lambda 表达式

[](const T& a, const T& b) { return a < b; }



👉 这正是 Strategy 设计模式 在算法中的体现。

⸻

考点
	•	Iterator 设计模式
	•	容器的统一遍历接口
	•	begin / end 语义
	•	const_iterator
	•	泛型算法设计
	•	STL 风格算法
	•	Strategy 模式（通过比较谓词）

⸻