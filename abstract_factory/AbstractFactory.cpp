#include <iostream>
#include <string>
using namespace std;

// A系列产品的抽象类
class ProductA{
public:
    ProductA(){}
    // 析构函数声明为虚函数，为了调用时释放子类对象
    virtual ~ProductA(){}
    virtual const string getName() = 0; 
};

// 具体工厂生产的产品对象，产品AX
class ConcreteProductAX : public ProductA {
public:
    ~ConcreteProductAX() { }
    virtual const string getName(){
        return "A-X";
    }
};
// 具体工厂生产的产品对象，产品AY
class ConcreteProductAY : public ProductA {
public:
    ~ConcreteProductAY() { }
    virtual const string getName(){
        return "A-Y";
    }
};

class ProductB {
public:
    virtual ~ProductB(){}
    virtual const string getName() = 0; 
};

class ConcreteProductBX : public ProductB {
public:
    virtual ~ConcreteProductBX(){}
    virtual const string getName(){
        return "B-X";
    }
};

class ConcreteProductBY : public ProductB {
public:
    virtual ~ConcreteProductBY(){}
    virtual const string getName(){
        return "B-Y";
    }
};

// AbstractFactory类：提供抽象接口用来生成一个产品系列
class AbstractFactory {
public:
    virtual ~AbstractFactory(){}
    virtual ProductA* createProductA() = 0;
    virtual ProductB* createProductB() = 0;
};

//具体的工厂X和Y生产一系列产品，客户使用具体的工厂，因此它不需要实例化产品对象
class ConcreteFactoryX : public AbstractFactory {
public:
    ~ConcreteFactoryX(){}
    virtual ProductA* createProductA(){
        return new ConcreteProductAX();
    }
    virtual ProductB* createProductB(){
        return new ConcreteProductBX();
    }
};

class ConcreteFactoryY : public AbstractFactory {
public:
    ~ConcreteFactoryY(){}
    virtual ProductA* createProductA(){
        return new ConcreteProductAY();
    }
    virtual ProductB* createProductB(){
        return new ConcreteProductBY();
    }
    // ...
};

int main(){
    // 操作抽象类作为接口
    AbstractFactory *AF = nullptr;
    AF = new ConcreteFactoryX();
    ProductA* PA =  AF->createProductA();
    cout << "Product: " << PA->getName() << endl;
    ProductB* PB = AF->createProductB();
    cout << "Product: " << PB->getName() << endl;
    cout << &AF << endl;
    delete AF;
    cout << &AF << endl;// delete只是释放指针指向的内存空间，指针本身还存在，指针地址不变
    delete PA;
    delete PB;
    // 操作具体工厂生产产品
    // ConcreteFactoryX *factoryX = new ConcreteFactoryX();
    // ConcreteFactoryY *factoryY = new ConcreteFactoryY();

    // ProductA *p1 = factoryX->createProductA();
    // std::cout << "Product: " << p1->getName() << std::endl;
    
    // ProductA *p2 = factoryY->createProductA();
    // std::cout << "Product: " << p2->getName() << std::endl;
    
    // delete p1;
    // delete p2;
    
    // delete factoryX;
    // delete factoryY;
    return 0;
}






