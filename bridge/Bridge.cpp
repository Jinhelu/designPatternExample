#include <iostream>
#include <string>
using namespace std;

// 行为类的接口
class Implementor{
public:
    virtual ~Implementor() {}
    virtual void action() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    ~ConcreteImplementorA() {}
    virtual void action(){
        std::cout << "Concrete Implementor A" << std::endl;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    ~ConcreteImplementorB() {}
    virtual void action(){
        std::cout << "Concrete Implementor B" << std::endl;
    }
};

// 抽象类
class Abstraction {
public:
    virtual ~Abstraction() {}
    virtual void operation() = 0;
};

// 抽象类的拓展
class RefinedAbstraction : public Abstraction
{
    public:
    ~RefinedAbstraction() {}
    // 构造函数中把
    RefinedAbstraction(Implementor *impl) : implementor(impl) {}
    
    void operation()
    {
        implementor->action();
    }
    // ...

    private:
    //子类中保存行为信息，不选择从父类中继承
    Implementor *implementor;
};


class Engine
{
public:
    virtual void InstallEngine() = 0;
};

class Engine4400cc : public Engine
{
public:
    virtual void InstallEngine()
    {
        cout << " 4400cc finish " << endl;
    }
};


class Engine4500cc : public Engine
{
public:
    virtual void InstallEngine()
    {
        cout << " 4500cc finish " << endl;
    }
};

class Car
{
public:
    Car(Engine *engine) :m_engine(engine)
    {
        cout<<"this is Car Construct Function"<<endl;
    }
    virtual void installEngine() = 0;

protected:
    Engine *m_engine;
};

class WBM5 : public Car
{
public:
    WBM5(Engine *engine) : Car(engine)
    {
    }

    virtual void installEngine()
    {
        m_engine->InstallEngine();
    }
};

class WBM6 : public Car
{
public:
    // 构造函数不能被子类继承，所以创建子类对象时，为了初始化从父类中继承的成员变量，需要调用其父类的构造函数
    WBM6(Engine *engine) : Car(engine)
    {
        cout<<"this is WBM6 Construct Function"<<endl;
    }

    virtual void installEngine()
    {
        m_engine->InstallEngine();
    }
};

int main(void)
{
    // 汽车安装发动机示例
    // Engine	*engine = new Engine4400cc();
    // Engine	*engine2 = new Engine4500cc();
    // WBM6	*wbm6 = new WBM6(engine);
    // WBM5    *wbm5 = new WBM5(engine2);
    // wbm6->installEngine();
    // wbm5->installEngine();
    // wbm6->installEngine();

    // delete wbm6;
    // delete engine;

    // 抽象的一种代码写法
    Implementor *impA = new ConcreteImplementorA();
    Abstraction *abs = new RefinedAbstraction(impA);
    abs->operation();

    delete impA;
    delete abs;
    return 0;
}