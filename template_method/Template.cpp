#include <iostream>
#include <string>
using namespace std;

// Abstractclass实现模板模式，定义一个算法的框架
class AbstractClass {
public:
    virtual ~AbstractClass() {}
    virtual void primitiveOperation1() = 0;
    virtual void primitiveOperation2() = 0;
    // ...
    void templateMethod(){
        // ...
        primitiveOperation1();
        primitiveOperation2();   
    }
};

// ConcreteClass 实现原始操作以执行算法的特定步骤。
// 可能有许多ConcreteClass类，每个类都实现所需操作的全套。
class ConcreteClassA : public AbstractClass {
public:
    ~ConcreteClassA () {}
    virtual void primitiveOperation1(){
        cout << "A's Primitive operation 1" << endl;
        //...
    }
    virtual void primitiveOperation2(){
        cout << "A's Primitive operation 2" << endl;
        //...
    }
    //...
};

class ConcreteClassB : public AbstractClass {
public:
    ~ConcreteClassB () {}
    virtual void primitiveOperation1(){
        cout << "B's Primitive operation 1" << endl;
        //...
    }
    virtual void primitiveOperation2(){
        cout << "B's Primitive operation 2" << endl;
        //...
    }
    //...
};

int main()
{
  AbstractClass *tm = new ConcreteClassA;
  tm->templateMethod();
  
  delete tm;
  return 0;
}
