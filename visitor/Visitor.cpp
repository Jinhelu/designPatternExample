#include <iostream>
using namespace std;

class Element;
class ConcreteElementA;
class ConcreteElementB;

// Visitor 为每个 ConcreteElement 类声明一个 Visit 操作在对象结构中
class Visitor {
public:
    virtual ~Visitor(){}

    virtual void visitElementA(ConcreteElementA* const element) = 0;
    virtual void visitElementB(ConcreteElementB* const element) = 0;
};

// 具体的访问者实现了访问者声明的每个操作，它实现了为结构中对应的对象类定义的算法片段
class ConcreteVisitor1 : public Visitor {
public:
    ~ConcreteVisitor1() {}
    void visitElementA(ConcreteElementA* const element){
        cout << "Concrete Visitor 1: Element A visited" << endl;
    }
    void visitElementB(ConcreteElementB* const element){
        cout << "Concrete Visitor 1: Element B visited" << endl;
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    ~ConcreteVisitor2() {}
    void visitElementA(ConcreteElementA* const element){
        cout << "Concrete Visitor 2: Element A visited" << endl;
    }
    void visitElementB(ConcreteElementB* const element){
        cout << "Concrete Visitor 2: Element B visited" << endl;
    }
};

// Element定义了一个以访问者为参数的接受操作
class Element {
public:
    virtual ~Element(){ }

    virtual void accept(Visitor &visitor) = 0;
    //...
};

// ConcreteElements 实现一个以访问者为参数的接受操作
class ConcreteElementA : public Element {
public:
    ~ConcreteElementA() { }
    void accept(Visitor &visitor){
        visitor.visitElementA(this);
    }
    //...
};

class ConcreteElementB : public Element {
public:
    ~ConcreteElementB() { }
    void accept(Visitor &visitor){
        visitor.visitElementB(this);
    }
    //...
};

int main(){
    ConcreteElementA elementA;
    ConcreteElementB elementB;
    ConcreteVisitor1 visitor1;
    ConcreteVisitor2 visitor2;
    elementA.accept(visitor1);
    elementB.accept(visitor2);
    
    return 0;
}