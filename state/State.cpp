#include <iostream>
#include <string>
using namespace std;

class Context;// 前置定义

//State 定义了一个接口，用于封装与 Context 的特定状态相关的行为
class State {
public:
    virtual ~State(){}
    virtual void handle() = 0;// 行为实现的函数,不传入Context的参数
    virtual void handleByCtx(Context* ctx) = 0; // 根据ctx的状态进行不同操作，传入操作对象的参数
    //...
};

// Context定义客户感兴趣的接口，拥有一个State类型成员
class Context {
private:
    State *cur_state;
    string name;
    //...
public:
    Context(const string &n) : cur_state(), name(n) { };
    ~Context(){
        delete cur_state;
    }
    string getName(){
        return name;
    }
    void setState(State* const s){
        if(cur_state){
            delete cur_state;
        }
        cur_state = s;
    }
    void request(){
        cur_state->handle();
    }
    void requestByValue(){
        cur_state->handleByCtx(this);
    }
    //...
};

// ConcreteStateX实现与上下文状态相关联的行为
class ConcreteStateA: public State {
public:
    ~ConcreteStateA() {}
    void handle(){
        cout << "State A handled" << endl;
    }
    void handleByCtx(Context* ctx){
        cout << ctx->getName() << " handled State A" << endl;
    }
};

class ConcreteStateB: public State {
public:
    ~ConcreteStateB() {}
    void handle(){
        cout << "State B handled" << endl;
    }
    void handleByCtx(Context* ctx){
        cout << ctx->getName() << " handled State B" << endl;
    }
};


int main(){
    Context *ctx = new Context("yyds");
    ctx->setState(new ConcreteStateA());// 更改状态
    ctx->request();// 基于当前状态处理上下文数据
    ctx->requestByValue();

    ctx->setState(new ConcreteStateB());// 更改状态
    ctx->request();// 基于当前状态处理上下文数据
    
    delete ctx;
    return 0;
}