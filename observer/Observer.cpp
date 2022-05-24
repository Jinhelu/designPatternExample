#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Subject;

// Observer为应该被通知主题更改的观察者对象定义更新接口
class Observer {
public:
    virtual ~Observer(){}
    virtual int getState() = 0;
    virtual void update(Subject* subject) = 0;
};

// ConcreteObserver 将感兴趣的状态存储到 ConcreteObserver 对象，并在其状态更改时向其观察者发送通知
class ConcreteObserver : public Observer {
private:
    int observer_state;
public:
    ConcreteObserver( const int state ){
        observer_state = state;
    }
    ~ConcreteObserver(){ }
    int getState(){
        return observer_state;
    }
    /**
     * @brief 
     * 1.通过传递Subject对象指针，将Subject的状态改变传递到观察者（状态保存在Subject的子类对象中）
     * 2.也可以直接传递定义的状态
     * @param subject 
     */
    void update(Subject* subject);
    //...
};

// Subject 管理它的观察者并提供一个附加和分离观察者的接口
class Subject {
private:
    vector<Observer*> observers;
    //...
public:
    virtual ~Subject(){}
    void attach(Observer* observer){
        observers.push_back(observer);
    }
    void detach(const int index){
        observers.erase(observers.begin() + index);
    }
    void notify(){
        for(size_t i=0; i<observers.size(); i++){
            observers[i]->update(this);
        }
    }
    virtual int getState() = 0;
    virtual void setState(const int s) = 0;
    //...
};

// 储存应该与主题对象保持一致的状态
class ConcreteSubject : public Subject
{
private:
    int subject_state;
    //...
public:
    ~ConcreteSubject(){}
    int getState(){
        return subject_state;
    }
    void setState(const int s){
        subject_state = s;
    }
    //...
};

void ConcreteObserver::update(Subject* subject){
    observer_state = subject->getState();
    cout << "Observer State Updated" << endl;
}

int main(){
    Observer* ob1 = new ConcreteObserver(1);
    Observer* ob2 = new ConcreteObserver(2);
        
    std::cout << "Observer 1 state: " << ob1->getState() << std::endl;// output:1
    std::cout << "Observer 2 state: " << ob2->getState() << std::endl;// output:2

    Subject* subject = new ConcreteSubject();
    subject->attach(ob1);
    subject->attach(ob2);

    subject->setState(10);
    subject->notify();// 通过notify()函数修改观察者的状态
    
    std::cout << "Observer 1 state: " << ob1->getState() << std::endl;// output:10
    std::cout << "Observer 2 state: " << ob2->getState() << std::endl;// output:10

    delete ob1,ob2,subject;
    return 0;
}