#include <iostream>
#include <string>
#include <list>
using namespace std;

// Receiver知道如何执行与执行请求相关的操作，请求的处理方
class Receiver {
public:
    void action(){
        cout << "Receiver: execute action" << endl;
    }
    //...
};

// Command 处理命令的接口
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// ConcreteCommand 通过调用Receiver的相关操作实现处理过程
class ConcreteCommand : public Command {
private:
    Receiver* receiver;
    //...
public:
    ConcreteCommand(Receiver* r) : receiver(r) {}
    virtual ~ConcreteCommand(){
        if(receiver){
            delete receiver;
        }
    }
    virtual void execute(){
        receiver->action();
    }
    //...
};

// Invoker分配Command去执行请求,一个invoker处理一个请求
class Invoker {
private:
    Command* command;
public:
    void setCommand(Command* c){
        command = c;
    }
    void confirm(){
        if(command){
            command->execute();
        }
    }
    ~Invoker(){
        if(command){
            delete command;
        }
    }
};

// InvokerBatch 批量处理请求，可以先保存请求，再一并提交执行
class InvokerBatch {
private:
    list<Command*> commmand_list;
    //reset 参数重置函数
    void reset(){
        commmand_list.clear();
    }
public:
    InvokerBatch(){
        reset();
    }
    void setCommand(Command* c){
        commmand_list.push_back(c);
    }
    void confirm(){
        for(list<Command*>::iterator it=commmand_list.begin(); it!=commmand_list.end(); it++){
            if(*it != nullptr){
                (*it)->execute();
            }
        }
        reset();
    }
    ~InvokerBatch(){
        for(list<Command*>::iterator it=commmand_list.begin(); it!=commmand_list.end(); it++){
            if(*it != nullptr){
                delete (*it);
            }
        }
    }
};


int main() {
    // 单个调用者的演示
    ConcreteCommand command( new Receiver() );
    Invoker invoker;
    invoker.setCommand( &command );
    invoker.confirm();
    // 批量调用者的演示
    InvokerBatch invokerBatch;
    invokerBatch.setCommand(&command);
    invokerBatch.setCommand(&command);
    invokerBatch.confirm();
    return 0;
}