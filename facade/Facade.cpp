#include <iostream>
#include <string>
using namespace std;

// 子系统的实现
class SubsystemA
{
public:
    void subOperation(){
        cout << "Subsystem A method" << endl;
        //...
    }
    //...
};

class SubsystemB
{
public:
    void subOperation(){
        cout << "Subsystem B method" << endl;
        //...
    }
    //...
};

class SubsystemC
{
public:
    void subOperation(){
        cout << "Subsystem C method" << endl;
        //...
    }
    //...
};

// 对子系统的封装
class Facade
{
private:
    SubsystemA *subA;
    SubsystemB *subB;
    SubsystemC *subC;
public:
    Facade() : subA(), subB(), subC() {}

    void operation1(){
        subA->subOperation();
        subB->subOperation();
        //...
    }
    void operation2(){
        subC->subOperation();
    }
    //...
};


int main(){
    Facade* facade = new Facade();
    facade->operation1();
    facade->operation2();
    delete facade;
    return 0;
}