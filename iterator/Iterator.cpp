#include <iostream>
#include <vector>
using namespace std;

class Iterator;
class ConcreteAggregate;

// Aggregate 为聚合定义了一个接口，将 客户端 与 对象集合的实现 分离
class Aggregate {
public:
    virtual ~Aggregate() { }
    virtual Iterator *createIterator() = 0;
};

// Concrete Aggregate 有一个对象集合，并实现了为其集合返回 Iterator 的方法
class ConcreteAggregate : public Aggregate {
private:
    int *list;// 对象集合
    unsigned int count;
public:
    ConcreteAggregate(const unsigned int size){
        list = new int[size]{};// 开辟内存，并全部初始化为0
        count = size;
    }
    ~ConcreteAggregate(){
        delete[] list;
    }
    Iterator *createIterator();
    unsigned int size() const {
        return count;
    }
    int at(unsigned int index){
        return list[index];
    }
    //...
};

// Iterator迭代器提供了所有迭代器必须实现的接口和一组遍历元素的方法
class Iterator {
public:
    virtual ~Iterator(){ }

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual int currentItem() const = 0;
    //...
};


/*
 * Concrete Iterator
 * implements the interface and is responsible for managing
 * the current position of the iterator
 */
class ConcreteIterator : public Iterator {
private:
    ConcreteAggregate *list;
    unsigned int index;
public:
    ConcreteIterator(ConcreteAggregate *l) : list(l), index(0) {}
    ~ConcreteIterator(){}

    void first(){
        index = 0;
    }
    void next(){
        index++;
    }
    bool isDone() const {
        return (index >= list->size());
    }
    int currentItem() const{
        if( isDone() ){
            return -1;
        }
        return list->at(index);
    }
    //...
};

Iterator *ConcreteAggregate::createIterator(){
    return new ConcreteIterator(this); // 当具体的迭代器持有一个集合的引用
}

int main(){
    unsigned int size = 5;
    ConcreteAggregate list = ConcreteAggregate(size);
    Iterator *it = list.createIterator();
    for( ; !it->isDone(); it->next()){
        cout << "Item value: " << it->currentItem() << endl;
    }
    delete it;
    return 0;
}