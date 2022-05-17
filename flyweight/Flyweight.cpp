#include <iostream>
#include <map>
using namespace std;

// Flyweight声明了一个接口，flyweights可以通过该接口接收并作用于外部状态
class Flyweight {
public:
    virtual ~Flyweight() {}
    virtual void operation() = 0;
    //...
};

// UnsharedConcreteFlyweight不用共享的子类，并非所有子类都需要共享
class UnsharedConcreteFlyweight : public Flyweight {
private:
    int state;
    //... 
public:
    UnsharedConcreteFlyweight(const int extrinsic_state) : state(extrinsic_state) {}
    ~UnsharedConcreteFlyweight() {}

    virtual void operation(){
        cout << "Unshared Flyweight with State " << state << endl;
    }
    //... 
};

// ConcreteFlyweight 实现 Flyweight 接口并为内部状态添加存储
class ConcreteFlyweight : public Flyweight {
private:
    int state;
    //...
public:
    ConcreteFlyweight(const int all_state) : state(all_state) {}
    ~ConcreteFlyweight() {}
    virtual void operation(){
        cout << "Concrete Flyweight with State " << state << endl;
    }
};

// FlyweightFactory 创建和管理享元对象并确保享元被正确共享
class FlyweightFactory {
private:
    map<int, Flyweight*> flies;
public:
    FlyweightFactory() { }
    ~FlyweightFactory(){
        for(auto it = flies.begin(); it != flies.end(); it++){
            delete it->second;
        }
        flies.clear();
    }
    Flyweight* getFlyweight(const int key){
        if(flies.find(key) != flies.end()){
            return flies[key];
        }
        Flyweight *fly = new ConcreteFlyweight(key);
        flies.insert(pair<int, Flyweight*> (key, fly));
        return fly;
    }
};

int main(){
    FlyweightFactory *factory = new FlyweightFactory();
    factory->getFlyweight(1)->operation();
    factory->getFlyweight(2)->operation();
    delete factory;
    return 0;
}