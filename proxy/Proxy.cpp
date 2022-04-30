#include <iostream>
#include <string>
using namespace std;

class Subject
{
private:
    /* data */
public:
    virtual ~Subject() {}
    virtual void request() = 0;
    //...
};

// RealSubjet定义代理角色表示的真实对象
class RealSubjet : public Subject {
public:
    ~RealSubjet() {}
    virtual void request(){
        cout << "Real Subject request" << endl;
    }
};

// 代理角色：含有对真实对象角色的引用，
class Proxy : public Subject {
public:
    Proxy(){
        subject = new RealSubjet();
    }
    ~Proxy(){
        delete subject;
    }
    virtual void request(){
        subject->request();
    }
private:
    RealSubjet *subject;
};

int main(){
    Subject *proxy = new Proxy();
    proxy->request();
    delete proxy;
    return 0;
}