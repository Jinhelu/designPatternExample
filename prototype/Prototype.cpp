#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Prototype:复制实例本身的接口
class Prototype{
public:
    virtual ~Prototype() { }
    virtual Prototype* clone() = 0;
    virtual string type() = 0;
    // ... 
};

class ConcretePrototypeA : public Prototype {
public:
    ~ConcretePrototypeA() { }
    virtual Prototype* clone(){
        return new ConcretePrototypeA;
    }
    virtual string type(){
        return "type A";
    }
};

class ConcretePrototypeB : public Prototype {
public:
    ~ConcretePrototypeB() { }
    virtual Prototype* clone(){
        return new ConcretePrototypeB;
    }
    virtual string type(){
        return "type B";
    }
};

class Client {
private:
    static Prototype* types[2];
    static int n_types;
public:
    static void init(){
        types[0] = new ConcretePrototypeA;
        types[1] = new ConcretePrototypeB;
    }
    static void remove() {
        delete[] types;
    }
    static Prototype* make(const int index){
        if(index >= n_types){
            return nullptr;
        }
        return types[index]->clone();
    }
};

// 静态成员变量在类外初始化
Prototype* Client::types[2];
int Client::n_types = 2;

/************ 另一种原型模式的实例 **********/
class Person
{
public:
    virtual Person* clone() = 0;
    virtual void printT() = 0;
};

class  CPlusPlusProgrammer : public Person
{
public:
    CPlusPlusProgrammer() :m_name(""), m_age(0), m_resume(NULL)
    {
        setResume("aaaa");
    }

    CPlusPlusProgrammer(string name, int age) :m_name(name), m_age(age), m_resume(NULL)
    {
        setResume("aaaa");
    }

    void setResume(char *p)
    {
        if (m_resume != NULL)
        {
            delete m_resume;
        }
        m_resume = new char[strlen(p) + 1];
        strcpy(m_resume, p);
    }

    virtual void printT()
    {
        cout << "m_name: " << m_name << " m_age: " << m_age << "m_resume: " << m_resume <<  endl;
        // 指针m_resume指向的地址空间的首地址
        // 浅拷贝下相同
        // 深拷贝下不同
        cout << "addr of pointer m-resume refer to: " << static_cast<const void*>(m_resume) << endl;
    }
    virtual Person* clone()
    {
        CPlusPlusProgrammer *tmp = new CPlusPlusProgrammer;
        //*tmp = *this; // =  浅拷贝
        // 深拷贝
        tmp->m_name = this->m_name;
        tmp->m_age = this->m_age;
        tmp->m_resume = new char[strlen(this->m_resume) + 1];
        strcpy(tmp->m_resume, this->m_resume);
        return tmp;
    }
private:
    string	m_name;
    int		m_age ;
    char	*m_resume;
        
};

int main(){
    // Client::init();
    // Prototype *prototype1 = Client::make( 0 );
    // std::cout << "Prototype: " << prototype1->type() << std::endl;
    // delete prototype1;
    // Prototype *prototype2 = Client::make( 1 );
    // std::cout << "Prototype: " << prototype2->type() << std::endl;
    // delete prototype2;
    
    // Client::remove();

    // 一种克隆实现
    Person *c1 = new CPlusPlusProgrammer("holi", 32);
    c1->printT(); 

    Person *c2 = c1->clone();
    c2->printT();
    return 0;
    
    return 0;
}