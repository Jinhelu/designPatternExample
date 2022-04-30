#include <iostream>
#include <string>
using namespace std;

// Target 定义客户端使用的特定接口
class Target {
public:
    virtual ~Target() {}
    virtual void request() = 0;
    //...
};

// Adaptee 所有请求都被委托给Adaptee，定义了需要调整的现有接口
class Adaptee {
public:
    ~Adaptee() {}
    void specificRequest(){
        cout << "specific request" << endl;
    }
};

// Adapter 实现了 Target 接口并让 Adaptee 通过扩展这两个类来响应 Target 上的请求，
// 即将 Adaptee 的接口适配到 Target 接口
// 使用继承方式实现的适配器
class Adapter : public Target {
public:
    Adapter() : m_adaptee(){} 
    ~Adapter(){
        delete m_adaptee;
    }
    virtual void request(){
        m_adaptee->specificRequest();
        //...
    }
private:
    Adaptee *m_adaptee;
    //...
};

int main(){
    // 组合方式（实现has a关系）实现适配器测试
    Target *t = new Adapter();
    t->request();
    delete t;
    return 0;
}


