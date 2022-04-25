#include <iostream>
#include <string>

/*
 * Product
 * products implement the same interface so that the classes can refer
 * to the interface not the concrete product
 */
// Product 抽象产品角色，定义为一个抽象类
class Product{
public:
    virtual ~Product() {}
    
    virtual std::string getName() = 0; // 纯虚函数
    // ...
};

// 具体产品类，定义要生产的产品
class ConcreteProductA : public Product
{
public:
    ~ConcreteProductA() {}
    
    std::string getName()
    {
        return "type A";
    }
    // ...
};

class ConcreteProductB : public Product
{
public:
    ~ConcreteProductB() {}
    
    std::string getName()
    {
        return "type B";
    }
    // ...
};

/************  简单工厂模式 ****************/
class SimpleFactory
{
public:
    SimpleFactory() {}
    ~SimpleFactory() {}
    // 不符合开闭原则，当增加新的对象时，需要修改createProduct()函数的代码
    Product* createProduct(const std::string& p){
        if(p == "A"){
            return new ConcreteProductA;
        }else if(p == "B"){
            return new ConcreteProductB;
        }else {
            std::cout << "product is not exsiting" << std::endl;
            return NULL;
        }
    }
    void removeProduct(Product* p){
        delete p;
    }
};


/******************************************/

/********** 工厂模式：对简单工厂模式的改进，增加了对工厂的抽象 ********/
// 当需要添加新的产品时，只需要添加相应的函数，不会对原代码进行修改
// Creator工厂模式类
class Creator
{
public:
    virtual ~Creator() {}
    
    virtual Product* createProductA() = 0;
    virtual Product* createProductB() = 0;
    
    virtual void removeProduct( Product *product ) = 0;
    
    // ...
};

// 具体的工厂类实现
class ConcreteCreator : public Creator
{
public:
    ~ConcreteCreator() {}
    
    Product* createProductA()
    {
        return new ConcreteProductA;
    }
    
    Product* createProductB()
    {
        return new ConcreteProductB;
    }
    
    void removeProduct( Product *product )
    {
        delete product;
    }
    // ...
};


int main()
{
    // 简单工厂模式测试
    SimpleFactory *creator = new SimpleFactory;
    Product *p1 = creator->createProduct("A");
    std::cout << "Product: " << p1->getName() << std::endl;
    creator->removeProduct(p1);
    
    Product *p2 = creator->createProduct("B");
    std::cout << "Product: " << p2->getName() << std::endl;
    creator->removeProduct(p2);

    delete creator;

    
    // 工厂模式测试
    // Creator *creator = new ConcreteCreator();// 父类指针指向子类对象，多态
    
    // Product *p1 = creator->createProductA();
    // std::cout << "Product: " << p1->getName() << std::endl;
    // creator->removeProduct( p1 );
    
    // Product *p2 = creator->createProductB();
    // std::cout << "Product: " << p2->getName() << std::endl;
    // creator->removeProduct( p2 );
    
    // delete creator;
    return 0;
}
