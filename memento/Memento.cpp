#include <iostream>
#include <vector>
using namespace std;

// Memento 存储Originator对象的内部状态，并可防止发起者Originator以外的对象访问备忘录
class Memento {
private:
    friend class Originator;// 只有Originator类可以访问备忘录的私有成员
    Memento(const int s) : state(s) {}
    void setState(const int s){
        state = s;
    }
    int getState(){
        return state;
    }
    //...
private:
    int state;
    //...
};

// Originator需要被保存状态以便恢复的对象。
// 原生者Originator创建一个包含其当前内部状态快照的备忘录，并使用该备忘录恢复内部状态
class Originator
{
private:
    int state;
    //...
public:
    // 用于打印结果的两个函数
    void setState(const int s){
        std::cout << "Set state to " << s << "." << std::endl;
        state = s;
    }
    int getState(){
        return state;
    }
    // createMemento 创建包含内部状态的备忘录
    Memento* createMemento(){
        return new Memento(state);
    }
    // setMemento 通过备忘录回复内部状态
    void setMemento(Memento* const m){
        state = m->getState();
    }
};

// CareTaker负责保存好备忘录,在适当的时间保存/恢复Originator对象的状态
class CareTaker
{
private:
    Originator* originator;//操作的对象
    vector<Memento*> history;//存储备忘录的历史队列
public:
    CareTaker(Originator* const o) : originator(o){ }
    ~CareTaker(){
        for (unsigned int i = 0; i < history.size(); i++){
            delete history.at(i);
        }
        history.clear();
    }
    void save(){
        cout << "Save state finished" << endl;
        history.push_back(originator->createMemento());
    }
    void undo(){
        if(history.empty()){
            cout << "history is empty, Unable to undo state" << endl;
            return;
        }
        Memento* m = history.back();// 从最近的一次操作开始恢复
        originator->setMemento(m);
        cout << "Undo State" << endl;
        history.pop_back();
        delete m;
    }
    //...
};

int main(){
    // 封装了对备忘录的接口，不把原生者Originator的状态暴露给客户端
    Originator *originator = new Originator();
    CareTaker *caretaker = new CareTaker( originator );
    
    originator->setState( 1 );
    caretaker->save();
    
    originator->setState( 2 );
    caretaker->save();
    
    originator->setState( 3 );
    caretaker->undo();
    
    std::cout << "Actual state is " << originator->getState() << "." << std::endl;
    delete originator;
    delete caretaker;
    
    return 0;
}
