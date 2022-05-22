#include <iostream>
#include <string>
using namespace std;

// Strategy为所有支持的算法声明一个通用接口
class Strategy {
public:
    virtual ~Strategy() {}
    virtual void algorithmInterface() = 0;
};

// Concrete Strategies使用Strategy接口实现具体算法
class ConcreteStrategyA : public Strategy {
public:
    ~ConcreteStrategyA() {}
    virtual void algorithmInterface(){
        cout << "Concrete Stratrgy A" << endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    ~ConcreteStrategyB() {}
    virtual void algorithmInterface(){
        cout << "Concrete Stratrgy B" << endl;
    }
};

// Context相当于Strategy的容器类，维护对 Strategy 对象的引用
class Context {
private:
    Strategy* stratrgy;
    //...
public:
    Context(Strategy* const s) : stratrgy(s) {}
    ~Context(){
        delete stratrgy;
    }
    void contextInterface(){
        stratrgy->algorithmInterface();
    }
    //... 
};

int main(){
    Context context(new ConcreteStrategyB());
    context.contextInterface();

    return 0;
}   