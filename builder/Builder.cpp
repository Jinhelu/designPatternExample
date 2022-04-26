#include <iostream>
#include <string>
using namespace std;

// Product：建造者最终会生成的对象(对对象的描述，属性+方法)
class Product {
public:
    void makeA(const string& part){
        partA = part;
    }
    void makeB(const string& part){
        partB = part;
    }
    void makeC(const string& part){
        partC = part;
    }
    string getComposite(){
        return (partA + " " + partB + " " + partC);
    }
private:
    string partA;
    string partB;
    string partC;
};

// Builder建造者类：生产产品的抽象接口
class Builder {
public:
    virtual ~Builder() { }

    Product get(){
        return product;
    }
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
protected:
    Product product;
};

// 具体建造者X和Y，生产具体产品并且存储在组合结构中
class ConcreteBuilderX : public Builder {
public:
    ~ConcreteBuilderX() { }
    virtual void buildPartA(){
        product.makeA("A-X");
    }
    virtual void buildPartB(){
        product.makeB("B-X");
    }
    virtual void buildPartC(){
        product.makeC("C-X");
    }
};

class ConcreteBuilderY : public Builder {
public:
    ~ConcreteBuilderY() { }
    virtual void buildPartA(){
        product.makeA("A-Y");
    }
    virtual void buildPartB(){
        product.makeB("B-Y");
    }
    virtual void buildPartC(){
        product.makeC("C-Y");
    }
};

// Director: 管理正确的产品生成序列
class Director
{
private:
    Builder *builder;
public:
    // 构造函数将builder指针初始化为空
    Director() : builder() {}
    ~Director(){
        if(builder){
            delete builder;
        }
    }

    void set(Builder* b){
        // 删除指向的内存空间，防止内存泄漏
        if(builder){
            delete builder;
        }
        builder = b;
    }
    // get获取生产的产品
    Product get(){
        return builder->get();
    }

    void construct(){
        builder->buildPartA();
        builder->buildPartB();
        builder->buildPartC();
        // ...
    }
    // ...
};

int main(){
    Director director;
    director.set(new ConcreteBuilderX);
    director.construct();

    Product p1 = director.get();
    cout << "1st product parts: " << p1.getComposite() << endl;
    
    director.set(new ConcreteBuilderY);
    director.construct();
    Product p2 = director.get();
    cout << "2st product parts: " << p2.getComposite() << endl;
}

