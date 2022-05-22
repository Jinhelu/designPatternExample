#include <iostream>
#include <string>
using namespace std;
/*
 * Handler
 * defines an interface for handling requests and
 * optionally implements the successor link
 */
// Handler定义处理请求的接口，可选择的实现继承链（A-B-...-N的处理链路）
class Handler {
public:
    virtual ~Handler(){}
    void setNextHandler(Handler* h){
        successor = h;
    }
    virtual void handleRequest(){
        if(successor){
            successor->handleRequest();
        }
    }
private:
    Handler* successor;
};

// Concrete Handlers处理它们能够处理的请求
class ConcreteHandlerA : public Handler {
public:
    virtual ~ConcreteHandlerA(){}
    bool canHandle(){
        //...
        return false;
    }
    virtual void handleRequest(){
        if ( canHandle() ){
            std::cout << "Handled by Concrete Handler A" << std::endl;
        }
        else{
            std::cout << "Cannot be handled by Handler A" << std::endl;
            Handler::handleRequest();
        }
        // ...
    }
    //...
};

class ConcreteHandlerB : public Handler {
public:
    virtual ~ConcreteHandlerB(){}
    bool canHandle(){
        //...
        return true;
    }
    virtual void handleRequest(){
        if ( canHandle() ){
            std::cout << "Handled by Concrete Handler B" << std::endl;
        }
        else{
            std::cout << "Cannot be handled by Handler B" << std::endl;
            Handler::handleRequest();
        }
        // ...
    }
    //...
};

int main(){
    ConcreteHandlerA handlerA;
    ConcreteHandlerB handlerB;

    handlerA.setNextHandler(&handlerB);
    handlerA.handleRequest();

    return 0;
}