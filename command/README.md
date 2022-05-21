## 命令模式

Command模式也叫命令模式 ，是行为设计模式的一种。Command模式通过被称为
Command的类封装了对目标对象的调用行为以及调用参数。

在面向对象的程序设计中，一个对象调用另一个对象，一般情况下的调用过程是：创建目标对象实例；设置调用参数；调用目标对象的方法。但在有些情况下有必要使用一个专门的类对这种调用过程加以封装，我们把这种专门的类称作command类。
整个调用过程比较繁杂，或者存在多处这种调用。这时，使用Command类对该调用加以封装，便于功能的再利用。
调用前后需要对调用参数进行某些处理。调用前后需要进行某些额外处理，比如日志，缓存，记录历史操作等。

### 角色和职责

- Command：Command命令的抽象类。
- ConcreteCommand：Command的具体实现类。
- Receiver：需要被调用的目标对象。
- Invorker：通过Invorker（调用者）执行Command对象。

适用于：是将一个请求封装为一个对象，从而使你可用不同的请求对客户端进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作。

### 应用场景 

* 想通过一个动作来参数化对象
* 想在不同时间指定、排队和执行请求
* 支持撤销
* 支持记录更改，以便在系统崩溃时重新应用它们
* 围绕基于原语操作的高级操作构建系统

### 案例

推演一：对类对象的基本使用方式、对类对象的封装使用方式
```C++
#include <iostream>
using namespace std;

class Doctor{
public:
    void treat_eye(){
        cout << "医生 治疗 眼科病" << endl;
    }

    void treat_nose(){
        cout << "医生 治疗 鼻科病" << endl;
    }
};
// 定义两个命令类，对医生对象的使用过程进行封装  
class CommandTreatEye{
public:
    CommandTreatEye(Doctor *doctor) : m_doctor(doctor) { }
    void treat(){
        m_doctor->treat_eye();
    }
private:
    Doctor *m_doctor;
};

class CommandTreatNose {
public:
    CommandTreatNose(Doctor *doctor) : m_doctor(doctor){ }
    void treat() {
        m_doctor->treat_nose();
    }
private:
    Doctor *m_doctor;
};

int main() {
    //1.一般的调用过程：医生直接看病
    /*
    Doctor *doctor = new Doctor ;
    doctor->treat_eye();
    delete doctor;
    */
    //2.通过一个命令 医生通过命令治病
    Doctor *doctor = new Doctor() ;
    CommandTreatEye * commandtreateye = new CommandTreatEye(doctor); //shift +u //转小写 shift+ctl + u转大写
    commandtreateye->treat();
    delete commandtreateye;
    delete doctor;
    return 0;
}
```

推演二：
```C++
#include <iostream>
#include <list>
#define __HEAD_NURSE__
using namespace std;

class Doctor{
public:
    void treat_eye(){
        cout << "医生 治疗 眼科病" << endl;
    }
    void treat_nose(){
        cout << "医生 治疗 鼻科病" << endl;
    }
};

class Command{
public:
    virtual void treat() = 0;
};

class CommandTreatEye : public Command {
public:
    CommandTreatEye(Doctor *doctor) :m_doctor(doctor) { }
    void treat() {
        m_doctor->treat_eye();
    }
private:
    Doctor *m_doctor;
};

class CommandTreatNose : public Command {
public:
    CommandTreatNose(Doctor *doctor) :m_doctor(doctor) { }
    void treat() {
        m_doctor->treat_nose();
    }
private:
    Doctor *m_doctor;
};

// 护士
class BeautyNurse {
public:
    BeautyNurse(Command *c) : command(c) { }
public:
    //提交病例 下单命令
    void SubmittedCase() {
        command->treat();
    }
private:
    Command *command;
};

//护士长
class HeadNurse {
public:
    HeadNurse(){
        m_list.clear();
    }
public:
    void setCommand(Command *command) {
        m_list.push_back(command);
    }
    //提交病例 下单命令
    void SubmittedCase(){
        for (list<Command *>::iterator it=m_list.begin(); it!=m_list.end(); it++){
            (*it)->treat();
        }
    }
private:
    list<Command *> m_list;
};

#ifndef __HEAD_NURSE__
int main(void)
{
    //护士提交需求 然后让医生看病，实现了客户端和需求命令的解耦 
    BeautyNurse		*beautynurse = NULL;
    Doctor			*doctor = NULL;
    Command			*command  = NULL;

    doctor = new Doctor() ;

    //command = new CommandTreatEye(doctor); //shift +u //转小写 shift+ctrl + u转大写
    command = new CommandTreatNose(doctor); //shift +u //转小写 shift+ctrl + u转大写
    beautynurse = new BeautyNurse(command);
    beautynurse->SubmittedCase();
    
    delete doctor;
    delete command; 
    delete beautynurse;
    return 0;
}
#else
// 通过护士长 批量的下单命令
int main(void)
{
    //护士长提交需求、然后让医生看病
    HeadNurse		*headnurse = NULL;
    Doctor			*doctor = NULL;
    Command			*command1  = NULL;
    Command			*command2  = NULL;

    doctor = new Doctor() ;

    command1 = new CommandTreatEye(doctor); 
    command2 = new CommandTreatNose(doctor); 

    headnurse = new HeadNurse(); //new 护士长
    headnurse->setCommand(command1);
    headnurse->setCommand(command2);

    headnurse->SubmittedCase(); // 护士长 批量下单命令

    delete doctor;
    delete command1;
    delete command2;
    delete headnurse;
    return 0;
}
#endif
```

### 扩展案例 

首先创建作为命令的接口 Order，然后创建作为请求的 Stock 类。实体命令类 BuyStock 和 SellStock，实现了 Order 接口，将执行实际的命令处理。创建作为调用对象的类 Broker，它接受订单并能下订单。

Broker 对象使用命令模式，基于命令的类型确定哪个对象执行哪个命令。CommandPatternDemo，演示类使用 Broker 类来演示命令模式。
