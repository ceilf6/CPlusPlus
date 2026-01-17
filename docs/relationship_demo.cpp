#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// ==================== 关联关系示例 ====================
// 学生和课程：松散关系，互相独立
class Course
{
private:
    string name;

public:
    Course(string n) : name(n) {}
    string getName() const { return name; }
};

class Student
{
private:
    string name;
    vector<Course *> courses; // 指针，不负责创建和销毁
public:
    Student(string n) : name(n) {}

    void enrollCourse(Course *c)
    {
        courses.push_back(c);
    }

    void showCourses()
    {
        cout << name << " 的课程: ";
        for (auto c : courses)
        {
            cout << c->getName() << " ";
        }
        cout << endl;
    }
};

// ==================== 聚合关系示例 ====================
// 部门和员工：整体-部分关系，但员工可以换部门
class Employee
{
private:
    string name;

public:
    Employee(string n) : name(n) {}
    string getName() const { return name; }
};

class Department
{
private:
    string name;
    vector<Employee *> employees; // 指针，员工在外部创建
public:
    Department(string n) : name(n) {}

    void addEmployee(Employee *emp)
    {
        employees.push_back(emp);
    }

    void showEmployees()
    {
        cout << name << " 部门的员工: ";
        for (auto emp : employees)
        {
            cout << emp->getName() << " ";
        }
        cout << endl;
    }

    // 析构函数不删除员工对象
    ~Department()
    {
        cout << name << " 部门解散，但员工依然存在" << endl;
    }
};

// ==================== 组合关系示例 ====================
// 房子和房间：强整体-部分关系，房间不能脱离房子
class Room
{
private:
    string type;

public:
    Room(string t) : type(t) {}
    string getType() const { return type; }
};

class House
{
private:
    string address;
    vector<unique_ptr<Room>> rooms; // unique_ptr，独占所有权
public:
    House(string addr) : address(addr) {}

    void addRoom(string type)
    {
        rooms.push_back(make_unique<Room>(type));
    }

    void showRooms()
    {
        cout << address << " 的房间: ";
        for (const auto &room : rooms)
        {
            cout << room->getType() << " ";
        }
        cout << endl;
    }

    // 析构函数会自动删除所有房间
    ~House()
    {
        cout << address << " 被拆除，房间也不存在了" << endl;
    }
};

// ==================== 测试代码 ====================
int main()
{
    cout << "=== 关联关系示例 ===" << endl;
    {
        // 课程在外部创建，独立存在
        Course math("数学");
        Course physics("物理");

        Student stu1("张三");
        stu1.enrollCourse(&math);
        stu1.enrollCourse(&physics);
        stu1.showCourses();

        // 学生对象销毁后，课程依然存在
    }
    cout << "学生对象已销毁，但课程对象仍然存在\n"
         << endl;

    cout << "=== 聚合关系示例 ===" << endl;
    {
        // 员工在外部创建
        Employee emp1("李四");
        Employee emp2("王五");

        Department *dept = new Department("技术部");
        dept->addEmployee(&emp1);
        dept->addEmployee(&emp2);
        dept->showEmployees();

        delete dept; // 部门销毁，员工仍存在

        cout << "员工 " << emp1.getName() << " 和 "
             << emp2.getName() << " 依然存在，可以加入新部门\n"
             << endl;
    }

    cout << "=== 组合关系示例 ===" << endl;
    {
        House *house = new House("北京路100号");
        house->addRoom("客厅");
        house->addRoom("卧室");
        house->addRoom("厨房");
        house->showRooms();

        delete house; // 房子销毁，房间也被销毁
        // 房间对象已不存在，无法访问
    }

    cout << "\n=== 关键区别总结 ===" << endl;
    cout << "1. 关联: A 使用 B*，B 在外部管理，完全独立" << endl;
    cout << "2. 聚合: A 包含 B*，B 在外部管理，整体-部分但可分离" << endl;
    cout << "3. 组合: A 包含 B 或 unique_ptr<B>，A 完全拥有 B，生命周期绑定" << endl;

    return 0;
}
