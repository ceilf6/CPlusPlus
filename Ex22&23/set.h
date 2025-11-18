#ifndef _SET_H
#define _SET_H

#include "config.hpp"
#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>

using namespace std;

/**
 * ============================================================================
 * SET 游戏命名空间 (SET Game Namespace)
 * ============================================================================
 *
 * 本文件实现了 SET 纸牌游戏的核心数据结构和类。
 * SET 是一款观察力游戏，玩家需要从桌面上的卡牌中找出满足特定规则的三张卡组合。
 *
 * 主要类的关系：
 * - Carte: 表示单张卡牌（组合关系 - 由 Jeu 创建和拥有）
 * - Jeu: 单例模式，管理所有 81 张卡牌（组合关系 - 拥有所有 Carte）
 * - Pioche: 牌堆，管理待发的卡牌（聚合关系 - 指向 Carte，不拥有）
 * - Plateau: 桌面，显示当前可见的卡牌（聚合关系 - 指向 Carte，不拥有）
 * - Combinaison: 三张卡的组合（聚合关系 - 指向 Carte，不拥有）
 * - Controleur: 游戏控制器（组合关系 - 拥有 Jeu、Pioche、Plateau）
 */
namespace Set
{
	// ========================================================================
	// 异常处理类 (Exception Handling)
	// ========================================================================

	/**
	 * SetException: SET 游戏中的异常类
	 *
	 * 设计说明：
	 * - 用于处理游戏中的各种异常情况（如牌堆为空、索引越界等）
	 * - 存储错误信息字符串，便于调试和错误提示
	 *
	 * 使用场景：
	 * - 访问不存在的卡牌索引
	 * - 从空牌堆中抽牌
	 * - 迭代器越界
	 */
	class SetException
	{
	public:
		// 构造函数：接收错误信息
		SetException(const string &i) : info(i) {}

		// 获取错误信息
		string getInfo() const { return info; }

	private:
		string info; // 存储错误描述信息
	};

	// ========================================================================
	// 卡牌特征枚举 (Card Characteristics Enumerations)
	// ========================================================================

	/**
	 * 设计理念：使用强类型枚举（enum class）
	 *
	 * 为什么使用 enum class 而不是普通 enum？
	 * 1. 类型安全：不会隐式转换为整数，避免误用
	 * 2. 作用域限定：枚举值在枚举类型内部，避免命名冲突
	 * 3. 前向声明：可以前向声明，提高编译效率（像JS的变量提升是自动的）
	 *
	 * 例如：Couleur::rouge 而不是 rouge（避免与其他地方的 rouge 冲突）
	 */

	/**
	 * Couleur: 卡牌符号的颜色
	 * - rouge: 红色
	 * - mauve: 紫色（或称紫红色）
	 * - vert: 绿色
	 */
	enum class Couleur
	{
		rouge, // 红色
		mauve, // 紫色
		vert   // 绿色
	};

	/**
	 * Nombre: 卡牌上符号的数量
	 * - un: 1 个符号
	 * - deux: 2 个符号
	 * - trois: 3 个符号
	 *
	 * 注意：显式指定值便于后续逻辑判断和输出
	 */
	enum class Nombre
	{
		un = 1,	  // 1 个
		deux = 2, // 2 个
		trois = 3 // 3 个
	};

	/**
	 * Forme: 卡牌符号的形状
	 * - ovale: 椭圆形
	 * - vague: 波浪形
	 * - losange: 菱形
	 */
	enum class Forme
	{
		ovale,	// 椭圆形
		vague,	// 波浪形
		losange // 菱形
	};

	/**
	 * Remplissage: 卡牌符号的填充方式
	 * - plein: 实心填充
	 * - vide: 空心（只有轮廓）
	 * - hachure: 阴影填充（斜线纹理）
	 */
	enum class Remplissage
	{
		plein,	// 实心
		vide,	// 空心
		hachure // 阴影
	};

	// ========================================================================
	// 枚举转换与输出函数 (Enum Conversion and Output Functions)
	// ========================================================================

	/**
	 * toString 系列函数：将枚举值转换为字符串表示
	 * 用途：便于调试和显示卡牌信息
	 */
	string toString(Couleur c);
	string toString(Nombre v);
	string toString(Forme f);
	string toString(Remplissage v);

	/**
	 * operator<< 重载：支持直接输出枚举值到流
	 * 使用方式：cout << Couleur::rouge << endl;
	 */
	ostream &operator<<(ostream &f, Couleur c);
	ostream &operator<<(ostream &f, Nombre v);
	ostream &operator<<(ostream &f, Forme x);
	ostream &operator<<(ostream &f, Remplissage r);

	// ========================================================================
	// 枚举值列表 (Enum Value Lists)
	// ========================================================================

	/**
	 * 全局常量列表：包含每个特征的所有可能值
	 *
	 * 设计说明：
	 * - 使用 initializer_list 允许在循环中遍历所有可能的值
	 * - extern 声明表示在 set.cpp 中定义
	 *
	 * 用途：
	 * 1. 生成所有 81 张卡牌（4 层嵌套循环）
	 * 2. 显示所有可能的特征值
	 * 3. 验证和测试
	 */
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;
	extern std::initializer_list<Forme> Formes;
	extern std::initializer_list<Remplissage> Remplissages;

	/**
	 * print 系列函数：打印所有可能的特征值
	 * 参数 f: 输出流，默认为标准输出 cout
	 */
	void printCouleurs(std::ostream &f = cout);
	void printNombres(std::ostream &f = cout);
	void printFormes(std::ostream &f = cout);
	void printRemplissages(std::ostream &f = cout);

	// ========================================================================
	// Carte 类：表示单张卡牌 (Card Class)
	// ========================================================================

	/**
	 * Carte: 代表游戏中的一张卡牌
	 *
	 * 设计要点（回答题目问题1）：
	 *
	 * 1. 为什么构造函数是私有的？
	 *    - 封装性：只有 Jeu 类能创建卡牌，外部无法随意创建
	 *    - 单一职责：卡牌的生命周期由 Jeu 统一管理
	 *    - 避免重复：确保每张卡牌唯一，不会有重复创建
	 *
	 * 2. 为什么使用 = default？
	 *    - Carte 只包含基本类型成员（4个枚举值）
	 *    - 没有动态分配的资源（指针、数组等）
	 *    - 编译器生成的默认版本已经足够（浅拷贝即可）
	 *    - = default 明确表达设计意图，提高代码可读性
	 *
	 * 3. 何时需要自定义这些函数？
	 *    - 当类包含指针成员时（需要深拷贝）
	 *    - 当类管理外部资源时（文件、内存等）
	 *    - 遵循"三五法则"：如果需要自定义析构函数，
	 *      通常也需要自定义拷贝构造函数和赋值运算符
	 *
	 * 类间关系：
	 * - Carte 与 Jeu：组合关系（Composition）
	 *   Jeu 创建并拥有所有 Carte 对象，负责其生命周期
	 */
	class Carte
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		Couleur couleur;		 // 卡牌符号的颜色
		Nombre nombre;			 // 卡牌上符号的数量
		Forme forme;			 // 卡牌符号的形状
		Remplissage remplissage; // 卡牌符号的填充方式

		// ====================================================================
		// 私有构造函数 (Private Constructor)
		// ====================================================================

		/**
		 * 构造函数：初始化卡牌的四个特征
		 *
		 * 为什么私有？
		 * - 只允许 Jeu 类创建卡牌实例
		 * - 防止外部代码随意创建卡牌
		 * - 确保所有卡牌都由 Jeu 统一管理
		 *
		 * 使用初始化列表的好处：
		 * - 直接初始化成员，效率高于赋值
		 * - 对于 const 成员和引用成员，必须使用初始化列表
		 */
		Carte(Couleur c, Nombre n, Forme f, Remplissage r)
			: couleur(c), nombre(n), forme(f), remplissage(r) {}

		// ====================================================================
		// 特殊成员函数 (Special Member Functions)
		// ====================================================================

		/**
		 * 拷贝构造函数：使用默认实现
		 *
		 * 为什么 = default 足够？
		 * - Carte 的所有成员都是枚举类型（值类型）
		 * - 没有指针或动态分配的内存
		 * - 编译器生成的成员逐个拷贝已经满足需求
		 */
		Carte(const Carte &) = default;

		/**
		 * 赋值运算符：使用默认实现
		 *
		 * 默认行为：逐成员赋值
		 * 对于 Carte 来说已经足够
		 */
		Carte &operator=(const Carte &) = default;

		/**
		 * 析构函数：使用默认实现
		 *
		 * 为什么不需要自定义？
		 * - Carte 没有管理任何需要手动释放的资源
		 * - 没有动态分配的内存
		 * - 没有打开的文件或网络连接
		 * - 枚举类型的销毁由编译器自动处理
		 */
		~Carte() = default;

		// ====================================================================
		// 友元声明 (Friend Declaration)
		// ====================================================================

		/**
		 * 友元类：允许 Jeu 访问 Carte 的私有成员
		 *
		 * 为什么需要？
		 * - Jeu 需要调用 Carte 的私有构造函数来创建卡牌
		 * - 体现了 Carte 与 Jeu 之间的紧密组合关系
		 * - Jeu 负责 Carte 的整个生命周期
		 */
		friend class Jeu;

	public:
		// ====================================================================
		// 公有访问器方法 (Public Accessor Methods)
		// ====================================================================

		/**
		 * Getter 方法：获取卡牌的各个特征
		 *
		 * 设计说明：
		 * - const 成员函数：不修改对象状态
		 * - 返回值类型：直接返回枚举值（值类型，开销小）
		 * - 命名规范：遵循 getCamelCase 风格
		 */
		Couleur getCouleur() const { return couleur; }
		Nombre getNombre() const { return nombre; }
		Forme getForme() const { return forme; }
		Remplissage getRemplissage() const { return remplissage; }
	};

	/**
	 * 输出运算符重载：支持直接输出 Carte 对象
	 * 格式：[颜色形状数量填充]，例如 [RO2P] 表示红色椭圆2个实心
	 */
	ostream &operator<<(ostream &f, const Carte &c);

	// ========================================================================
	// Jeu 类：管理所有卡牌的单例类 (Game Singleton Class)
	// ========================================================================

	/**
	 * Jeu: 游戏类，管理所有 81 张卡牌
	 *
	 * 设计要点（回答题目问题2、3、4、5）：
	 *
	 * 问题2：关于数组初始化
	 * - Carte cartes[81]; 如果是对象数组就必须有初始化器，否则编译器不知道该如何创建这个数组
	 *   ru提供初始化器：Carte cartes[3] = {c1, c2, c3};
	 * - const Carte* cartes[81]; 指针数组可以不初始化
	 *   指针本身可以稍后赋值
	 *
	 * 问题3：Carte 与 Jeu 的关系
	 * - 组合关系（Composition，实心菱形）
	 * - Jeu 拥有并管理所有 Carte 对象的生命周期
	 * - Carte 不能独立于 Jeu 存在
	 * - UML表示：Jeu ◆——> Carte (1对81的组合)
	 *
	 * 问题4：为什么使用 const Carte*？
	 * - 常量指针保护：防止意外修改卡牌内容
	 * - 卡牌一旦创建就不应该改变（符合 SET 游戏规则）
	 * - 类型安全：编译器会阻止通过指针修改 Carte
	 * - 对比：Carte* 允许修改，const Carte* 只读
	 *
	 * 问题5：为什么禁止拷贝？
	 * - 单例模式：全局只应该有一个 Jeu 实例
	 * - 资源管理：避免多个 Jeu 对象管理同一批卡牌
	 * - 防止悬空指针：拷贝会导致指针管理混乱
	 *
	 * 单例模式说明：
	 * - 保证全局只有一个 Jeu 实例
	 * - 通过 getInstance() 获取实例
	 * - 私有构造函数防止外部创建
	 */
	class Jeu
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * cartes: 存储所有 81 张卡牌的指针数组
		 *
		 * 设计细节：
		 * - const Carte*：指向常量 Carte 的指针，卡牌内容不可修改
		 * - 固定大小数组：81 = 3^4（4个特征各3种可能）
		 * - 使用配置常量：config::NB_CARTES，便于统一管理
		 *
		 * 为什么是指针数组而不是对象数组？
		 * 1. Carte 构造函数私有，无法直接创建对象数组
		 * 2. 指针允许动态分配（new），在运行时创建
		 * 3. 灵活性：可以在构造函数中逐个创建卡牌
		 */
		const Carte *cartes[config::NB_CARTES];

		// ====================================================================
		// 禁用拷贝和赋值 (Deleted Copy and Assignment)
		// ====================================================================

		/**
		 * 拷贝构造函数：已删除
		 *
		 * 为什么删除？
		 * - 单例模式：不允许创建多个 Jeu 实例
		 * - 资源管理：避免多个对象管理同一批动态分配的 Carte
		 * - 防止错误：拷贝会导致两个 Jeu 对象指向相同的 Carte，
		 *   销毁时会重复释放内存（double free）
		 */
		Jeu(const Jeu &) = delete;

		/**
		 * 赋值运算符：已删除
		 * 原因同上，维护单例模式
		 */
		Jeu &operator=(const Jeu &) = delete;

		// ====================================================================
		// 私有构造和析构函数 (Private Constructor and Destructor)
		// ====================================================================

		/**
		 * 构造函数：创建所有 81 张卡牌
		 *
		 * 为什么私有？
		 * - 单例模式要求：外部无法直接创建实例
		 * - 只能通过 getInstance() 获取唯一实例
		 *
		 * 为什么不用 = default？
		 * - 需要自定义逻辑：生成所有 81 张不同的卡牌
		 * - 4层嵌套循环遍历所有特征组合
		 * - 为每张卡牌分配内存（new Carte(...)）
		 */
		Jeu();

		/**
		 * 析构函数：释放所有卡牌的内存
		 *
		 * 为什么不用 = default？
		 * - 需要自定义清理：释放 81 张动态分配的 Carte
		 * - 遵循"谁分配谁释放"原则
		 * - 防止内存泄漏：必须 delete 每个 new 出来的 Carte
		 */
		~Jeu();

	public:
		// ====================================================================
		// 单例访问方法 (Singleton Access Method)
		// ====================================================================

		/**
		 * getInstance: 获取 Jeu 的唯一实例（单例模式）
		 *
		 * 实现原理：
		 * - static 局部变量：在第一次调用时创建，程序结束时销毁
		 * - 线程安全：C++11 保证 static 局部变量的初始化是线程安全的
		 * - 延迟初始化：只有在第一次调用时才创建实例
		 *
		 * 单例模式的优点：
		 * - 全局访问点：任何地方都可以获取 Jeu 实例
		 * - 资源共享：所有代码共享同一套卡牌数据
		 * - 内存高效：只创建一次，避免重复创建
		 *
		 * 使用方式：
		 *   Jeu& jeu = Jeu::getInstance();
		 *   const Carte& card = jeu.getCarte(0);
		 */
		static Jeu &getInstance()
		{
			static Jeu instance; // 局部静态变量，只初始化一次
			return instance;	 // 返回引用，避免拷贝
		}

		// ====================================================================
		// 公有访问方法 (Public Access Methods)
		// ====================================================================

		/**
		 * getCarte: 获取指定索引的卡牌
		 *
		 * 参数：
		 * - i: 卡牌索引（0-80）
		 *   size_t 是无符号整数类型，表示大小和索引
		 *   在 64 位系统上通常是 unsigned long (8 字节)
		 *   在 32 位系统上通常是 unsigned int (4 字节)
		 *
		 * 返回值：const Carte&
		 * - 引用：避免拷贝，提高效率
		 * - const：保证外部无法修改卡牌
		 *
		 * 异常：如果 i >= 81，抛出 SetException
		 *
		 * 前面的 const 确保函数返回对象后这个对象不会变
		 * 后面的 const 确保成员函数内部不会修改当前类的成员
		 * 通过 const 加固封装的密闭性
		 */
		const Carte &getCarte(size_t i) const;

		/**
		 * getNbCartes: 获取卡牌总数
		 *
		 * 返回值：81（通过配置文件统一管理）
		 *
		 * 设计优势：
		 * - 使用 config::NB_CARTES 而不是硬编码 81
		 * - 集中管理常量，便于维护和修改
		 * - 提高代码可读性和可维护性
		 */
		size_t getNbCartes() const { return config::NB_CARTES; }

		// ================================================================
		// 迭代器类：遍历所有卡牌 (Iterator Classes)
		// ================================================================

		/**
		 * 将迭代器类写在 Jeu 类的内部：
		 * - 1. 只能Jeu遍历其管理的卡牌（若是公共API的话可能会被滥用）
		 * - 2. 这样迭代器类访问私有成员就不受限制了
		 * - 3. 后续拓展代码支持多版本迭代（如普通遍历、索引遍历、按 Forme 过滤遍历等）的时候都能共享相同的上下文而不冲突，还可以访问相同的私有资源。
		 *
		 * Iterator: 基于指针的迭代器（方式一）
		 *
		 * 设计模式：迭代器模式 (Iterator Pattern)
		 * 目的：提供一种方法顺序访问聚合对象中的元素，
		 *      而不暴露其内部表示
		 *
		 * 实现方式：使用指向指针的指针
		 * - currentCarte: 指向 cartes 数组中当前元素的指针
		 * - nb: 剩余可迭代的元素数量
		 *
		 * 为什么是 const Carte**？
		 * - cartes 是 const Carte* 类型的数组
		 * - currentCarte 需要指向数组元素（指针的指针）
		 * - 保持 const 约束，防止修改卡牌
		 *
		 * 使用示例：
		 *   Jeu::Iterator it = jeu.first();
		 *   while (!it.isDone()) {
		 *       cout << it.getCurrentItem();
		 *       it.next();
		 *   }
		 *
		 * (迭代器的作用远不止于此：像在JS中co库实现异步管理的本质就是迭代器)
		 */
		class Iterator
		{
		private:
			const Carte **currentCarte; // 指向当前卡牌指针的指针
			size_t nb;					// 剩余待遍历的卡牌数量

			/**
			 * 私有构造函数：只允许 Jeu 创建迭代器
			 *
			 * 参数：
			 * - c: 指向数组起始位置的指针
			 * - n: 可迭代的元素数量
			 */
			Iterator(const Carte **c, size_t n) : currentCarte(c), nb(n) {}

			friend class Jeu; // 允许 Jeu 访问私有构造函数

		public:
			/**
			 * next: 移动到下一张卡牌
			 *
			 * 操作：
			 * 1. currentCarte++ : 指针向后移动一位
			 * 2. nb-- : 剩余数量减一
			 */
			void next()
			{
				currentCarte++; // 移动指针到下一个元素
				nb--;			// 减少剩余计数
			}

			/**
			 * isDone: 检查是否遍历完成
			 *
			 * 返回：true 表示已遍历完所有元素
			 */
			bool isDone() const { return nb == 0; }

			/**
			 * getCurrentItem: 获取当前卡牌
			 *
			 * 返回：当前指向的 Carte 对象的引用（返回的是复制的对象还是引用是看函数上面有没有 & ）
			 *
			 * 为什么是 **currentCarte？
			 * - currentCarte 是指向指针的指针（Carte**）
			 * - *currentCarte 得到 Carte*（指向 Carte 的指针）
			 * - **currentCarte 得到 Carte 对象本身
			 */
			const Carte &getCurrentItem() const
			{
				return **currentCarte; // 双重解引用获取 Carte 对象
			}
		};

		/**
		 * first: 创建指向第一张卡牌的迭代器
		 *
		 * 返回：指向数组开头的 Iterator
		 *
		 * 实现细节：
		 * - &cartes[0] 获取数组第一个元素的地址
		 * - 初始化 nb 为总卡牌数
		 */
		Iterator first()
		{
			const Carte **c = &cartes[0]; // 获取数组首地址
			return Iterator(c, config::NB_CARTES);
		}

		/**
		 * IteratorBis: 基于索引的迭代器（方式二）
		 *
		 * 对比 Iterator 的不同：
		 * - Iterator 使用指针遍历：currentCarte++
		 * - IteratorBis 使用索引遍历：i++
		 *
		 * 优缺点对比：
		 * Iterator（指针方式）：
		 *   优点：直接操作指针，效率略高
		 *   缺点：需要理解指针的指针，较复杂
		 *
		 * IteratorBis（索引方式）：
		 *   优点：逻辑更清晰，易于理解
		 *   缺点：每次需要通过 getCarte(i) 访问，多一次函数调用
		 *
		 * 设计意图：
		 * 展示两种不同的迭代器实现方式，让学习者理解：
		 * - 迭代器模式的本质是提供统一的遍历接口
		 * - 底层实现可以有多种方式
		 */
		class IteratorBis
		{
		private:
			Jeu &instance; // Jeu 实例的引用
			size_t i;	   // 当前卡牌的索引

			/**
			 * 构造函数：初始化迭代器
			 *
			 * 参数：
			 * - j: Jeu 对象的引用
			 * - index: 起始索引
			 */
			IteratorBis(Jeu &j, size_t index) : instance(j), i(index) {}

			friend class Jeu;

		public:
			/**
			 * next: 移动到下一张卡牌
			 *
			 * 安全检查：如果已经遍历完成，抛出异常
			 * 这是一种防御性编程的体现
			 */
			void next()
			{
				if (isDone())
					throw SetException("end of iteration");
				i++; // 索引递增
			}

			/**
			 * isDone: 检查是否遍历完成
			 *
			 * 判断：当前索引是否达到总数
			 */
			bool isDone() const { return i == instance.getNbCartes(); }

			/**
			 * getCurrentItem: 获取当前卡牌
			 *
			 * 实现：通过索引调用 getCarte(i)
			 * 包含安全检查，防止越界访问
			 */
			const Carte &getCurrentItem() const
			{
				if (isDone())
					throw SetException("end of iteration");
				return instance.getCarte(i); // 通过索引获取卡牌
			}
		};

		/**
		 * firstBis: 创建指向第一张卡牌的 IteratorBis
		 *
		 * 参数：*this 传递当前 Jeu 对象的引用
		 * 索引从 0 开始
		 */
		IteratorBis firstBis()
		{
			return IteratorBis(*this, 0);
		}

		/**
		 * const_iterator: 符合 C++ 标准库风格的迭代器
		 *
		 * 设计目标：
		 * - 兼容 C++11 的 range-based for 循环
		 * - 遵循 STL 容器的迭代器接口规范
		 *
		 * 必须实现的操作符：
		 * - operator++: 前缀递增运算符
		 * - operator!=: 不等于比较运算符
		 * - operator*: 解引用运算符
		 *
		 * 配合 begin() 和 end()，支持以下语法：
		 *   for (const Carte& c : jeu) {
		 *       cout << c << endl;
		 *   }
		 *
		 * 为什么叫 const_iterator？
		 * - 返回的是 const Carte&，不允许修改卡牌
		 * - 对应 STL 中的 const_iterator 概念
		 * - 与 iterator（非 const）区分开
		 */
		class const_iterator
		{
		private:
			const Jeu &instance; // Jeu 实例的 const 引用
			size_t i;			 // 当前索引

			/**
			 * 构造函数：初始化迭代器位置
			 *
			 * 参数：
			 * - j: const Jeu 引用（保证不修改 Jeu）
			 * - index: 起始索引
			 */
			const_iterator(const Jeu &j, size_t index) : instance(j), i(index) {}

			friend class Jeu;

		public:
			/**
			 * operator++: 前缀递增运算符
			 *
			 * 用法：++it
			 *
			 * 为什么不返回值？
			 * - 简化实现，满足基本 range-based for 需求
			 * - 标准实现应返回 const_iterator&
			 */
			void operator++()
			{
				i++;
			}

			/**
			 * operator!=: 不等于比较运算符
			 *
			 * 用途：range-based for 循环判断是否到达 end()
			 *
			 * 实现：比较索引是否不同
			 *
			 * 注意：通常还应该检查是否比较的是同一个容器的迭代器
			 *      这里简化处理，只比较索引
			 */
			bool operator!=(const_iterator other) const
			{
				return i != other.i;
			}

			/**
			 * operator*: 解引用运算符
			 *
			 * 用法：*it 或 auto& card = *it
			 *
			 * 返回：当前位置的 Carte 引用
			 *
			 * 模拟指针行为：就像 *ptr 获取指针指向的值
			 */
			const Carte &operator*() const
			{
				return instance.getCarte(i);
			}
		};

		/**
		 * begin: 返回指向第一个元素的迭代器
		 *
		 * 必须是 const 成员函数，配合 range-based for
		 */
		const_iterator begin() const { return const_iterator(*this, 0); }

		/**
		 * end: 返回指向"最后一个元素之后"的迭代器
		 *
		 * 注意：end() 不指向有效元素，仅用于判断结束
		 * 经典的"哨兵"模式，[begin, end) 左闭右开区间
		 */
		const_iterator end() const { return const_iterator(*this, config::NB_CARTES); }

		/**
		 * FormeIterator: 条件过滤迭代器
		 *
		 * 设计目的：
		 * - 只遍历特定形状（Forme）的卡牌
		 * - 展示迭代器的扩展应用：带过滤条件的遍历
		 *
		 * 应用场景：
		 * - 需要查找所有椭圆形卡牌
		 * - 需要查找所有波浪形卡牌
		 * - 任何基于形状的过滤查询
		 *
		 * 实现原理：
		 * - 在 next() 中跳过不符合条件的卡牌
		 * - 持续递增索引直到找到匹配的形状或遍历完成
		 *
		 * 扩展思路：
		 * - 可以实现 CouleurIterator（按颜色过滤）
		 * - 可以实现 NombreIterator（按数量过滤）
		 * - 可以实现通用的 FilterIterator（传入谓词函数）
		 *
		 * 使用示例：
		 *   // 遍历所有椭圆形卡牌
		 *   FormeIterator it = jeu.firstFormeIterator(Forme::ovale);
		 *   while (!it.isDone()) {
		 *       cout << it.getCurrentItem();
		 *       it.next();
		 *   }
		 */
		class FormeIterator
		{
		private:
			Forme forme;   // 要过滤的形状
			Jeu &instance; // Jeu 实例引用
			size_t i;	   // 当前索引

			/**
			 * 构造函数：初始化过滤迭代器
			 *
			 * 参数：
			 * - j: Jeu 对象引用
			 * - index: 起始索引
			 * - f: 要过滤的形状
			 */
			FormeIterator(Jeu &j, size_t index, Forme f)
				: forme(f), instance(j), i(index) {}

			friend class Jeu;

		public:
			/**
			 * next: 移动到下一张符合条件的卡牌
			 *
			 * 算法：
			 * 1. 先递增索引（i++）
			 * 2. 如果未完成且当前卡牌形状不匹配，继续递增
			 * 3. 直到找到匹配的卡牌或遍历完成
			 *
			 * 时间复杂度：
			 * - 最坏 O(n)，需要遍历所有卡牌
			 * - 平均 O(1)，因为每种形状约占 1/3
			 */
			void next()
			{
				i++; // 移动到下一张卡
				// 跳过不符合条件的卡牌
				while (!isDone() &&
					   instance.getCarte(i).getForme() != forme)
					i++;
			}

			/**
			 * isDone: 检查是否遍历完成
			 */
			bool isDone() const { return i == instance.getNbCartes(); }

			/**
			 * getCurrentItem: 获取当前卡牌
			 *
			 * 前提：当前索引指向的卡牌形状匹配 forme
			 */
			const Carte &getCurrentItem() const
			{
				return instance.getCarte(i);
			}
		};

		/**
		 * firstFormeIterator: 创建形状过滤迭代器
		 *
		 * 参数：
		 * - f: 要过滤的形状
		 *
		 * 返回：指向第一张该形状卡牌的迭代器
		 *
		 * 注意：如果第一张卡不是目标形状，
		 *      用户需要先调用 next() 才能找到第一张匹配的卡
		 */
		FormeIterator firstFormeIterator(Forme f)
		{
			return FormeIterator(*this, 0, f);
		}
	}; // end of class Jeu

	// ========================================================================
	// Pioche 类：牌堆管理类 (Draw Pile Class)
	// ========================================================================

	/**
	 * Pioche: 管理待发的卡牌（牌堆）
	 *
	 * 设计要点（回答题目问题6、7）：
	 *
	 * 问题6：Carte 与 Pioche 的关系
	 * - 聚合关系（Aggregation，空心菱形）
	 * - Pioche 持有指向 Carte 的指针，但不拥有 Carte
	 * - Carte 的生命周期由 Jeu 管理，不受 Pioche 影响
	 * - Pioche 销毁时不应该删除 Carte 对象
	 * - UML表示：Pioche ◇——> Carte (1对多的聚合)
	 *
	 * 组合 vs 聚合的区别：
	 * - Jeu ◆——> Carte: 组合，Jeu 拥有 Carte，负责创建和销毁
	 * - Pioche ◇——> Carte: 聚合，Pioche 引用 Carte，不负责生命周期
	 *
	 * 问题7：explicit 关键字的意义
	 * - 防止隐式类型转换
	 * - explicit Pioche(const Jeu& j) 禁止：Pioche p = jeu;
	 * - 必须显式调用：Pioche p(jeu);
	 * - 避免意外的类型转换导致的错误
	 *
	 * 为什么禁止拷贝？
	 * - 资源管理：避免多个 Pioche 管理同一个动态数组
	 * - 防止悬空指针：拷贝会导致两个对象共享指针数组
	 * - 明确语义：一个游戏只应该有一个牌堆
	 *
	 * 功能说明：
	 * - 初始化时包含所有 81 张卡牌
	 * - piocher() 随机抽取一张卡并将其从牌堆移除
	 * - 支持查询剩余卡牌数量和是否为空
	 */
	class Pioche
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * cartes: 指向卡牌指针的动态数组
		 *
		 * 类型分析：const Carte**
		 * - 最内层：Carte 对象
		 * - 中间层：const Carte* （指向 Carte 的常量指针）
		 * - 外层：const Carte** （指向指针的指针，即指针数组）
		 *
		 * 为什么是动态数组？
		 * - 初始化时从 Jeu 复制所有卡牌的地址
		 * - 需要可修改的数组来实现"抽牌"操作
		 * - 抽到的牌会从数组中移除（交换到末尾）
		 */
		const Carte **cartes;

		/**
		 * nb: 当前牌堆中剩余的卡牌数量
		 *
		 * 初始值：81（所有卡牌）
		 * 每次 piocher() 后递减
		 * 当 nb == 0 时牌堆为空
		 */
		size_t nb;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 构造函数：从 Jeu 创建牌堆
		 *
		 * 参数：
		 * - j: Jeu 对象的引用（不是 const，因为可能需要获取非 const 引用）
		 *
		 * 注意：虽然参数不是 explicit，但建议加上以防止隐式转换
		 *
		 * 初始化步骤：
		 * 1. 分配大小为 NB_CARTES 的指针数组
		 * 2. 将 Jeu 中所有卡牌的地址复制到数组
		 * 3. 初始化 nb 为总卡牌数
		 *
		 * 时间复杂度：O(n)，n = 81
		 * 空间复杂度：O(n)，分配 81 个指针
		 */
		Pioche(Jeu &j) : nb(config::NB_CARTES)
		{
			// 动态分配指针数组
			cartes = new const Carte *[config::NB_CARTES];

			// 复制所有卡牌的地址
			// 注意：这里只复制地址（浅拷贝），不复制 Carte 对象
			for (size_t i = 0; i < j.getNbCartes(); i++)
				cartes[i] = &j.getCarte(i);
		}

		// ====================================================================
		// 析构函数 (Destructor)
		// ====================================================================

		/**
		 * 析构函数：释放动态分配的指针数组
		 *
		 * 重要：只删除数组本身，不删除 Carte 对象
		 *
		 * 为什么不删除 Carte？
		 * - 聚合关系：Pioche 不拥有 Carte
		 * - Carte 的生命周期由 Jeu 管理
		 * - 删除 Carte 会导致 Jeu 中的指针悬空（dangling pointer）
		 *
		 * 对比：
		 * - delete[] cartes;     ✅ 删除指针数组
		 * - delete[] cartes[i];  ❌ 错误！不应该删除 Carte
		 */
		~Pioche()
		{
			delete[] cartes; // 只释放指针数组，不删除 Carte 对象
		}

		// ====================================================================
		// 公有方法 (Public Methods)
		// ====================================================================

		/**
		 * piocher: 随机抽取一张卡牌
		 *
		 * 算法：
		 * 1. 检查牌堆是否为空，空则抛出异常
		 * 2. 生成随机索引 i（0 到 nb-1）
		 * 3. 保存 cartes[i]（要返回的卡牌）
		 * 4. 将 cartes[nb-1]（最后一张）移到位置 i
		 * 5. nb--（减少牌堆大小）
		 * 6. 返回被抽中的卡牌
		 *
		 * 时间复杂度：O(1)
		 *
		 * 为什么交换而不是删除？
		 * - 避免数组元素移动（O(n)操作）
		 * - 利用"最后一张卡填补空位"技巧
		 * - 保持剩余卡牌在数组前 nb 个位置
		 *
		 * 实现在 set.cpp 中
		 */
		const Carte &piocher();

		/**
		 * getNbCartes: 获取剩余卡牌数量
		 */
		size_t getNbCartes() const { return nb; }

		/**
		 * estVide: 检查牌堆是否为空
		 */
		bool estVide() const { return nb == 0; }

		// ====================================================================
		// 禁用拷贝和赋值 (Deleted Copy and Assignment)
		// ====================================================================

		/**
		 * 拷贝构造函数：已删除
		 *
		 * 为什么禁止？
		 * - 避免浅拷贝问题：两个 Pioche 会共享同一个 cartes 数组
		 * - 防止双重释放：两个对象的析构函数会删除同一个数组
		 * - 语义不明：复制牌堆的意义不清晰
		 */
		Pioche(const Pioche &p) = delete;

		/**
		 * 赋值运算符：已删除
		 * 原因同上
		 */
		Pioche &operator=(const Pioche &p) = delete;
	};

	// ========================================================================
	// Plateau 类：游戏桌面类 (Game Board Class)
	// ========================================================================

	/**
	 * Plateau: 表示游戏桌面，存放当前可见的卡牌
	 *
	 * 设计要点（回答题目问题8、9）：
	 *
	 * 问题8：Carte 与 Plateau 的关系
	 * - 聚合关系（Aggregation，空心菱形）
	 * - Plateau 持有指向 Carte 的指针，但不拥有 Carte
	 * - Carte 的生命周期由 Jeu 管理
	 * - Plateau 销毁时不删除 Carte 对象
	 * - UML表示：Plateau ◇——> Carte (1对多的聚合)
	 *
	 * 问题9：为什么需要自定义拷贝构造和赋值运算符？
	 *
	 * 如果使用默认版本会发生什么？
	 * - 浅拷贝：两个 Plateau 对象的 cartes 指针指向同一个数组
	 * - 修改一个会影响另一个
	 * - 析构时会双重释放同一块内存（double free）→ 崩溃
	 *
	 * 正确做法：
	 * - 深拷贝：分配新的数组，复制所有指针
	 * - 每个 Plateau 拥有独立的数组
	 * - 但数组中的指针仍指向 Jeu 中的 Carte（聚合关系）
	 *
	 * 动态数组设计：
	 * - cartes: 动态分配的指针数组
	 * - nbMax: 数组的容量（已分配的大小）
	 * - nb: 当前实际使用的元素数量
	 * - 当 nb == nbMax 时需要扩容
	 *
	 * 扩容策略：
	 * - 每次增加固定大小（如 5）
	 * - 类似于 std::vector 的动态增长
	 * - 也可以采用倍增策略（如 *2）以均摊 O(1)
	 */
	class Plateau
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * cartes: 指向卡牌指针的动态数组
		 *
		 * 类型：const Carte**
		 * - 动态分配，支持扩容
		 * - 存储指向 Carte 的指针（聚合）
		 */
		const Carte **cartes;

		/**
		 * nbMax: 数组的最大容量
		 *
		 * 表示当前已分配的数组大小
		 * 当 nb 达到 nbMax 时需要扩容
		 */
		size_t nbMax;

		/**
		 * nb: 当前桌面上的卡牌数量
		 *
		 * 表示数组中实际使用的元素数量
		 * 范围：0 <= nb <= nbMax
		 */
		size_t nb;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 默认构造函数：创建空的桌面
		 *
		 * 初始化策略：
		 * - 分配初始容量（5 个位置）
		 * - 初始时没有卡牌（nb = 0）
		 *
		 * 为什么初始容量是 5？
		 * - 避免频繁扩容
		 * - 不要太大（浪费内存）
		 * - 可以通过配置文件调整
		 */
		Plateau()
		{
			cartes = new const Carte *[5]; // 分配初始数组
			nbMax = 5;					   // 设置容量
			nb = 0;						   // 初始为空
		}

		// ====================================================================
		// 析构函数 (Destructor)
		// ====================================================================

		/**
		 * 析构函数：释放动态分配的数组
		 *
		 * 注意：只删除指针数组，不删除 Carte 对象
		 * 原因：聚合关系，Carte 由 Jeu 管理
		 */
		~Plateau() { delete[] cartes; }

		// ====================================================================
		// 公有方法 (Public Methods)
		// ====================================================================

		/**
		 * getNbCartes: 获取桌面上的卡牌数量
		 */
		size_t getNbCartes() const { return nb; }

		/**
		 * ajouter: 向桌面添加一张卡牌
		 *
		 * 参数：c - 要添加的卡牌引用
		 *
		 * 算法：
		 * 1. 检查是否需要扩容（nb == nbMax）
		 * 2. 如果需要，分配更大的数组并复制
		 * 3. 将卡牌指针添加到数组末尾
		 * 4. nb++
		 *
		 * 扩容策略：
		 * - 创建大小为 (nbMax + 5) 的新数组
		 * - 复制所有现有指针
		 * - 删除旧数组
		 * - 更新 cartes 和 nbMax
		 *
		 * 时间复杂度：
		 * - 不扩容：O(1)
		 * - 扩容：O(n)
		 *
		 * 实现在 set.cpp 中
		 */
		void ajouter(const Carte &c);

		/**
		 * retirer: 从桌面移除一张卡牌
		 *
		 * 参数：c - 要移除的卡牌引用
		 *
		 * 算法：
		 * 1. 遍历数组查找卡牌地址
		 * 2. 如果找到，用最后一张卡填补空位
		 * 3. nb--
		 * 4. 如果未找到，抛出异常
		 *
		 * 时间复杂度：O(n)
		 *
		 * 实现在 set.cpp 中
		 */
		void retirer(const Carte &c);

		/**
		 * 拷贝构造函数：深拷贝 Plateau
		 *
		 * 为什么需要？
		 * - 避免浅拷贝导致的双重释放
		 * - 每个 Plateau 需要独立的数组
		 *
		 * 实现：
		 * 1. 分配新的数组（大小为 p.nbMax）
		 * 2. 复制所有卡牌指针
		 * 3. 复制 nb 和 nbMax
		 *
		 * 实现在 set.cpp 中
		 */
		Plateau(const Plateau &p);

		/**
		 * 赋值运算符：深拷贝赋值
		 *
		 * 必须处理：
		 * 1. 自赋值检查（if (this != &p)）
		 * 2. 释放当前资源或重用现有数组
		 * 3. 复制新数据
		 *
		 * 实现策略：
		 * - 清空当前内容（nb = 0）
		 * - 逐个添加源对象的卡牌（调用 ajouter）
		 * - 利用 ajouter 的扩容机制
		 *
		 * 实现在 set.cpp 中
		 */
		Plateau &operator=(const Plateau &p);

		/**
		 * print: 打印桌面上的所有卡牌
		 *
		 * 参数：f - 输出流
		 *
		 * 格式：每行显示若干张卡牌，便于阅读
		 *
		 * 实现在 set.cpp 中
		 */
		void print(ostream &f) const;

		// ====================================================================
		// Ex23: STL 风格迭代器 (STL-style Iterator)
		// ====================================================================

		/**
		 * const_iterator: 符合 C++ 标准库风格的迭代器
		 *
		 * 设计目标：
		 * - 兼容 C++11 的 range-based for 循环
		 * - 遵循 STL 容器的迭代器接口规范
		 *
		 * 使用示例：
		 *   for(Plateau::const_iterator it = plateau.begin(); it != plateau.end(); ++it)
		 *       std::cout << *it << "\n";
		 *
		 *   // 或使用 range-based for
		 *   for(const Carte& c : plateau)
		 *       std::cout << c << "\n";
		 */
		class const_iterator
		{
		private:
			const Plateau &plateau; // Plateau 实例的 const 引用
			size_t index;			// 当前索引

			/**
			 * 构造函数：初始化迭代器位置
			 */
			const_iterator(const Plateau &p, size_t i) : plateau(p), index(i) {}

			friend class Plateau;

		public:
			/**
			 * operator++: 前缀递增运算符
			 *
			 * 用法：++it
			 * 返回：引用支持链式操作
			 */
			const_iterator &operator++()
			{
				index++;
				return *this;
			}

			/**
			 * operator!=: 不等于比较运算符
			 *
			 * 用途：range-based for 循环判断是否到达 end()
			 */
			bool operator!=(const const_iterator &other) const
			{
				return index != other.index;
			}

			/**
			 * operator==: 等于比较运算符
			 */
			bool operator==(const const_iterator &other) const
			{
				return index == other.index;
			}

			/**
			 * operator*: 解引用运算符
			 *
			 * 用法：*it
			 * 返回：当前位置的 Carte 引用
			 */
			const Carte &operator*() const
			{
				if (index >= plateau.nb)
					throw SetException("Iterator out of bounds");
				return *plateau.cartes[index];
			}
		};

		/**
		 * begin: 返回指向第一个元素的迭代器
		 */
		const_iterator begin() const { return const_iterator(*this, 0); }

		/**
		 * end: 返回指向"最后一个元素之后"的迭代器
		 */
		const_iterator end() const { return const_iterator(*this, nb); }

		/**
		 * cbegin: 返回 const 迭代器（C++11 标准）
		 */
		const_iterator cbegin() const { return begin(); }

		/**
		 * cend: 返回 const 迭代器（C++11 标准）
		 */
		const_iterator cend() const { return end(); }
	};

	/**
	 * 输出运算符重载：支持直接输出 Plateau 对象
	 * 使用方式：cout << plateau << endl;
	 */
	ostream &operator<<(ostream &f, const Plateau &c);

	// ========================================================================
	// Combinaison 类：三卡组合类 (Three-Card Combination Class)
	// ========================================================================

	/**
	 * Combinaison: 表示玩家选择的三张卡牌组合
	 *
	 * 设计要点（回答题目问题10、11）：
	 *
	 * 问题10：Carte 与 Combinaison 的关系
	 * - 聚合关系（Aggregation，空心菱形）
	 * - Combinaison 持有指向 Carte 的指针，但不拥有 Carte
	 * - Carte 的生命周期由 Jeu 管理
	 * - UML表示：Combinaison ◇——> Carte (1对3的聚合)
	 *
	 * 问题11：为什么可以使用 = default？
	 *
	 * 成员变量分析：
	 * - c1, c2, c3: 三个指针（const Carte*）
	 * - 指针是基本类型，可以安全地浅拷贝
	 * - 没有动态分配的资源需要管理
	 *
	 * = default 适用条件：
	 * - 所有成员都是值类型或指针
	 * - 不需要深拷贝（没有拥有的资源）
	 * - 编译器生成的版本满足需求
	 *
	 * 对比 Plateau：
	 * - Plateau 有动态数组，需要深拷贝
	 * - Combinaison 只有三个指针，浅拷贝即可
	 *
	 * 核心功能：
	 * - 存储三张卡牌的引用
	 * - 判断这三张卡是否构成有效的 SET
	 *
	 * SET 规则回顾：
	 * 对于每个特征（颜色、数量、形状、填充）：
	 * - 要么三张卡完全相同
	 * - 要么三张卡完全不同
	 * - 不允许"两同一异"的情况
	 */
	class Combinaison
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * c1, c2, c3: 指向三张卡牌的指针
		 *
		 * 类型：const Carte*
		 * - const: 不能通过指针修改卡牌
		 * - 指针: 不拥有卡牌，只是引用
		 *
		 * 为什么不用引用（const Carte&）？
		 * - 引用必须在构造时初始化，无法重新赋值
		 * - 指针更灵活，支持后续修改（虽然这里不需要）
		 * - 指针可以为 nullptr（虽然这里不会）
		 */
		const Carte *c1;
		const Carte *c2;
		const Carte *c3;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 构造函数：从三张卡牌创建组合
		 *
		 * 参数：C1, C2, C3 - 三张卡牌的引用
		 *
		 * 实现：使用初始化列表
		 * - c1(&C1): 获取 C1 的地址并赋给 c1
		 * - 存储的是地址，不是拷贝对象
		 *
		 * 设计选择：
		 * - 参数是引用：避免不必要的拷贝
		 * - 成员是指针：支持后续可能的修改
		 */
		Combinaison(const Carte &C1, const Carte &C2, const Carte &C3)
			: c1(&C1), c2(&C2), c3(&C3) {}

		// ====================================================================
		// 访问器方法 (Accessor Methods)
		// ====================================================================

		/**
		 * getCarte 系列：获取各张卡牌的引用
		 *
		 * 返回：*c1 解引用指针得到 Carte 对象
		 */
		const Carte &getCarte1() const { return *c1; }
		const Carte &getCarte2() const { return *c2; }
		const Carte &getCarte3() const { return *c3; }

		/**
		 * estUnSet: 判断这三张卡是否构成有效的 SET
		 *
		 * 规则：对于每个特征（颜色、形状、数量、填充）
		 * - 要么三个完全相同
		 * - 要么三个完全不同
		 *
		 * 数学表达：
		 * 对于特征 X：
		 * - 全同：X1 == X2 && X1 == X3
		 * - 全异：X1 != X2 && X1 != X3 && X2 != X3
		 *
		 * 实现算法：
		 * 1. 对四个特征分别检查
		 * 2. 每个特征返回 true/false
		 * 3. 四个结果进行 AND 运算
		 *
		 * 时间复杂度：O(1)（固定的4个特征检查）
		 *
		 * 实现在 set.cpp 中
		 */
		bool estUnSet() const;

		// ====================================================================
		// 特殊成员函数 (Special Member Functions)
		// ====================================================================

		/**
		 * 析构函数：使用默认实现
		 *
		 * 为什么 = default 足够？
		 * - 只有三个指针成员
		 * - 不拥有任何需要手动释放的资源
		 * - 指针指向的 Carte 由 Jeu 管理
		 */
		~Combinaison() = default;

		/**
		 * 拷贝构造函数：使用默认实现
		 *
		 * 默认行为：逐成员拷贝（浅拷贝）
		 * - c1, c2, c3 是指针，拷贝指针值
		 * - 两个 Combinaison 会指向相同的 Carte
		 * - 这是合理的，因为不拥有 Carte
		 */
		Combinaison(const Combinaison &c) = default;

		/**
		 * 赋值运算符：使用默认实现
		 *
		 * 默认行为：逐成员赋值
		 * 对于 Combinaison 来说已经足够
		 */
		Combinaison &operator=(const Combinaison &c) = default;
	};

	/**
	 * 输出运算符重载：格式化输出组合
	 * 格式：[卡1 ; 卡2 ; 卡3]
	 */
	ostream &operator<<(ostream &f, const Combinaison &c);

	// ========================================================================
	// Controleur 类：游戏控制器类 (Game Controller Class)
	// ========================================================================

	/**
	 * Controleur: 游戏控制器，管理游戏流程
	 *
	 * 设计要点（回答题目问题12、13）：
	 *
	 * 问题12：Controleur 与其他类的关系
	 *
	 * 1. Controleur ——> Jeu: 关联关系（引用）
	 *    - jeu 是引用成员，指向单例
	 *    - 不拥有 Jeu，Jeu 是全局单例
	 *    - UML: Controleur -----> Jeu
	 *
	 * 2. Controleur ◆——> Plateau: 组合关系
	 *    - plateau 是值成员（不是指针）
	 *    - Controleur 拥有并管理 Plateau 的生命周期
	 *    - Plateau 随 Controleur 创建和销毁
	 *    - UML: Controleur ◆——> Plateau
	 *
	 * 3. Controleur ◆——> Pioche: 组合关系
	 *    - pioche 是指针，指向动态分配的对象
	 *    - Controleur 负责 Pioche 的创建（new）和销毁（delete）
	 *    - Pioche 的生命周期完全由 Controleur 管理
	 *    - UML: Controleur ◆——> Pioche
	 *
	 * 为什么 Plateau 是值，Pioche 是指针？
	 * - Plateau: 可以在栈上创建，构造简单，无需指针
	 * - Pioche: 需要 Jeu 引用来初始化，构造函数调用在 Controleur
	 *          构造函数体内，必须用指针
	 *
	 * 问题13：为什么禁止拷贝？
	 * - 资源管理：pioche 是动态分配的，拷贝会导致问题
	 * - 语义不明：复制游戏控制器的含义不清
	 * - 单一控制：一个游戏应该只有一个控制器
	 *
	 * 职责说明：
	 * - 初始化游戏（创建牌堆、桌面）
	 * - 管理游戏流程（发牌等）
	 * - 提供访问游戏状态的接口
	 */
	class Controleur
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * jeu: Jeu 单例的引用
		 *
		 * 类型：Jeu& （引用）
		 * - 必须在初始化列表中初始化
		 * - 引用一旦绑定就不能改变
		 * - 指向全局唯一的 Jeu 实例
		 *
		 * 关系类型：关联（Association）
		 * - Controleur 使用 Jeu，但不拥有它
		 * - Jeu 的生命周期独立于 Controleur
		 */
		Jeu &jeu;

		/**
		 * plateau: 游戏桌面对象
		 *
		 * 类型：Plateau （值成员）
		 * - 不是指针，直接嵌入在 Controleur 中
		 * - 随 Controleur 自动创建和销毁
		 * - 使用 Plateau 的默认构造函数初始化
		 *
		 * 关系类型：组合（Composition）
		 * - Controleur 拥有 Plateau
		 * - Plateau 的生命周期与 Controleur 相同
		 * - Plateau 不能独立于 Controleur 存在
		 */
		Plateau plateau;

		/**
		 * pioche: 牌堆对象的指针
		 *
		 * 类型：Pioche* （指针）
		 * - 指向动态分配的 Pioche 对象
		 * - 在构造函数体内创建（new Pioche(jeu)）
		 * - 在析构函数中销毁（delete pioche）
		 *
		 * 为什么是指针而不是值？
		 * 1. Pioche 构造函数需要 jeu 参数
		 * 2. jeu 在初始化列表中才能获取
		 * 3. plateau 可以默认构造，所以可以是值
		 * 4. pioche 需要参数，必须在构造函数体内 new
		 *
		 * 关系类型：组合（Composition）
		 * - Controleur 拥有并管理 Pioche
		 * - Controleur 负责创建和销毁 Pioche
		 * - Pioche 的生命周期由 Controleur 控制
		 */
		Pioche *pioche;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 构造函数：初始化游戏控制器
		 *
		 * 初始化顺序：
		 * 1. 初始化列表：jeu(Jeu::getInstance())
		 *    - 获取 Jeu 单例的引用
		 *    - 必须在此处初始化（引用成员的要求）
		 *
		 * 2. 隐式调用：plateau 的默认构造函数
		 *    - Plateau() 会自动调用
		 *    - 创建空的桌面
		 *
		 * 3. 构造函数体：pioche = new Pioche(jeu)
		 *    - 动态分配 Pioche 对象
		 *    - 传入 jeu 引用初始化牌堆
		 *
		 * 为什么这样设计？
		 * - jeu 必须先初始化（引用的要求）
		 * - pioche 依赖 jeu（需要 jeu 作为参数）
		 * - plateau 独立，可以自动初始化
		 *
		 * 内存布局：
		 * - jeu: 引用（8字节，64位系统）
		 * - plateau: Plateau 对象（直接嵌入）
		 * - pioche: 指针（8字节，64位系统）
		 */
		Controleur() : jeu(Jeu::getInstance())
		{
			pioche = new Pioche(jeu); // 动态创建牌堆
		}

		// ====================================================================
		// 访问器方法 (Accessor Methods)
		// ====================================================================

		/**
		 * getPlateau: 获取桌面的常量引用
		 *
		 * 返回：const Plateau&
		 * - 避免拷贝
		 * - 保护桌面不被外部修改（const）
		 */
		const Plateau &getPlateau() const { return plateau; }

		/**
		 * getPioche: 获取牌堆的常量引用
		 *
		 * 返回：const Pioche&
		 * - *pioche 解引用指针得到对象
		 * - 返回引用避免拷贝
		 */
		const Pioche &getPioche() const { return *pioche; }

		// ====================================================================
		// 游戏逻辑方法 (Game Logic Methods)
		// ====================================================================

		/**
		 * distribuer: 将牌堆中的卡牌发到桌面
		 *
		 * 游戏规则：
		 * - 如果桌面卡牌数 < 12：补到 12 张
		 * - 如果桌面卡牌数 >= 12：只加 1 张
		 * - 如果牌堆为空：不做任何操作
		 *
		 * 算法：
		 * 1. 检查牌堆是否为空
		 * 2. 如果桌面 < 12，循环抽牌直到达到 12 或牌堆空
		 * 3. 否则，只抽一张牌
		 *
		 * 实现在 set.cpp 中
		 */
		void distribuer();

		// ====================================================================
		// 析构函数 (Destructor)
		// ====================================================================

		/**
		 * 析构函数：清理资源
		 *
		 * 必须做的事：
		 * - delete pioche: 释放动态分配的 Pioche 对象
		 *
		 * 自动完成的事：
		 * - plateau 的析构函数自动调用（值成员）
		 * - jeu 是引用，不需要销毁
		 *
		 * 三五法则（Rule of Three/Five）：
		 * - 如果需要自定义析构函数（因为 pioche）
		 * - 通常也需要自定义拷贝构造和赋值运算符
		 * - 这里选择禁用拷贝和赋值（= delete）
		 */
		~Controleur() { delete pioche; }

		// ====================================================================
		// 禁用拷贝和赋值 (Deleted Copy and Assignment)
		// ====================================================================

		/**
		 * 拷贝构造函数：已删除
		 *
		 * 为什么禁止？
		 * 1. pioche 是指针，浅拷贝会导致两个对象共享同一个 Pioche
		 * 2. 析构时会双重释放（double free）
		 * 3. jeu 是引用，拷贝后仍指向同一个 Jeu（可能不是问题）
		 * 4. plateau 可以拷贝，但整体语义不明确
		 * 5. 游戏控制器应该唯一，不应该复制
		 */
		Controleur(const Controleur &c) = delete;

		/**
		 * 赋值运算符：已删除
		 * 原因同上
		 */
		Controleur &operator=(const Controleur &c) = delete;
	};

}; // end of namespace Set

#endif // _SET_H
