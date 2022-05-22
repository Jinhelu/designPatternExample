#include <iostream>
#include <string>
#include <vector>
using  namespace std;

class Mediator;
// Colleague类 无论何时同事想要和其他同事通信时，都通过中介者
class Colleague {
public:
    Colleague(Mediator* const m, const int i) : mediator(m), id(i) {}
    virtual ~Colleague(){}
    int getID(){
        return id;
    }
    virtual void send(string) = 0;
    virtual void receive(string) = 0;
protected:
    Mediator* mediator;
    int id;
};

class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* const m, const int i) : Colleague(m, i) {}
    ~ConcreteColleague(){}
    void send(string msg);
    void receive(string msg){
        std::cout << "Message '" << msg << "' received by Colleague " << id << std::endl;
    }
};

class Mediator {
public:
    Mediator(){}
    virtual ~Mediator(){}
    virtual void add(Colleague* const c) = 0;
    virtual void distribute(Colleague* const sender, string msg) = 0;
};

class ConcreteMediator : public Mediator
{
private:
    vector<Colleague*> colleagues;
public:
    ~ConcreteMediator(){
        for(size_t i=0; i<colleagues.size(); i++){
            delete colleagues[i];
        }
        colleagues.clear();
    }
    void add(Colleague* const c){
        colleagues.push_back(c);
    }
    void distribute(Colleague* const sender, string msg){
        for(size_t i=0; i<colleagues.size(); i++){
            // 除了sender以外的其他对象接收消息，通过中介
            if(colleagues[i]->getID() != sender->getID()){
                colleagues[i]->receive(msg);
            }
        }
    }
};

void ConcreteColleague::send(string msg){
    // 函数中使用了Mediator类中的方法，所以第一次出现时候只声明，在此处实现
    cout << "Message: " << msg << " sent by Colleague " << id << endl;
    // 通过中介者对象发布消息
    mediator->distribute(this, msg);
}

int main(){
    Mediator *mediator = new ConcreteMediator();
    
    Colleague *c1 = new ConcreteColleague( mediator, 1 );
    Colleague *c2 = new ConcreteColleague( mediator, 2 );
    Colleague *c3 = new ConcreteColleague( mediator, 3 );
    
    mediator->add( c1 );
    mediator->add( c2 );
    mediator->add( c3 );
    
    c1->send( "Hi!" );
    c3->send( "Hello!" );
    
    delete mediator;
    return 0;
}