#include <iostream>
#include <string>
using namespace std;

//Component 为可以动态添加职责的对象一个接口
class Component{
public:
    virtual ~Component() { }
    virtual void operation() = 0;
    //...
};

// ConcreteComponent 定义一个可以附加额外职责的具体对象
class ConcreteComponent : public Component {
public:
    virtual ~ConcreteComponent() {}
    virtual void operation(){
        cout << "Concrete Component operation" << endl;
    }
};

// Decorator 维护一个对组件对象的引用并定义一个符合组件接口的接口
class Decorator : public Component
{
private:
    Component *comp;
public:
    Decorator(Component* c) : comp(c) {};
    ~Decorator() {}
    virtual void operation(){
        comp->operation();
    }
};

// Concrete Decorator 对组件添加职责（能够扩大组件的状态）
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component *c) : Decorator(c) {};
    ~ConcreteDecoratorA(){}
    
    virtual void operation(){
        Decorator::operation();
        cout << "Decorator A" << endl;// 添加的职责
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component *c) : Decorator(c) {};
    ~ConcreteDecoratorB(){}
    
    virtual void operation(){
        Decorator::operation();
        cout << "Decorator B" << endl;// 添加的职责
    }
};

/*********** 不使用多重继承的简单实现方式 **********/
class DecoratorA : public Component
{
private:
    Component *comp;
public:
    DecoratorA(Component* c) : comp(c) {};
    ~DecoratorA() {}
    // 给基础的Component添加了装饰A
    void addFunction(){
        cout << "Add Decorator A" << endl;
    }
    virtual void operation(){
        comp->operation();
        addFunction();
    }
};


int main(){
    ConcreteComponent  *cc = new ConcreteComponent();
    ConcreteDecoratorB *db = new ConcreteDecoratorB( cc );
    ConcreteDecoratorA *da = new ConcreteDecoratorA( db );
    
    // Component *component = da;
    // component->operation();

    Component *comp2 = db;
    comp2->operation();
    
    delete da;
    delete db;
    delete cc;
    
    return 0;
}