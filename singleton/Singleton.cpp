#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

//懒汉式
class SingeltonLazy
{
    private:
        SingeltonLazy(){
            cout << "SingeltonLazy constructor run" << endl;
        }
    public:
        // The copy constructor and assignment operator
        // are defined as deleted, which means that you
        // can't make a copy of singleton.
        //
        // Note: you can achieve the same effect by declaring
        // the constructor and the operator as private
        SingeltonLazy( SingeltonLazy const& ) = delete;
        SingeltonLazy& operator = ( SingeltonLazy const& ) = delete;
        
        static SingeltonLazy *getInstance(){
            if (instance == NULL){
                instance = new SingeltonLazy();
            }
            return instance;
        }

        static void freeInstance(){
            if (instance != NULL){
                delete instance;
                instance = NULL; 
            }
        }

        void tell(){
            cout << "This is a Lazy Singleton Pattern" << endl;
        }

    private:
        static SingeltonLazy *instance;
};

SingeltonLazy *SingeltonLazy::instance = NULL;
	
//饿汉式
class SingletonHungry
{
private:
    SingletonHungry(){
        cout << "SingeltonHungry constructor run" << endl;
    }

public:
    SingletonHungry( SingletonHungry const& ) = delete;
    SingletonHungry& operator = ( SingletonHungry const& ) = delete;

    static SingletonHungry *getInstance(){
        return instance;
    }
    static void freeInstance(){
        if(instance != NULL){
            delete instance;
            instance = NULL;
        }
    }

private:
    static SingletonHungry* instance;
};

SingletonHungry *SingletonHungry::instance = new SingletonHungry();

// 互斥锁实现的线程安全的懒汉模式
class SingletonLazy_ThreadSafe{
    private:
        SingletonLazy_ThreadSafe(){
            cout << "SingletonLazy_ThreadSafe constructor run" << endl;
        }
    public:
        SingletonLazy_ThreadSafe( SingletonLazy_ThreadSafe const& ) = delete;
        SingletonLazy_ThreadSafe& operator = ( SingletonLazy_ThreadSafe const& ) = delete;
        
        static SingletonLazy_ThreadSafe *getInstance(){
            if (instance == NULL){// double check, avoid to using lock frequently
                m.lock();
                if(instance == NULL){
                    instance = new SingletonLazy_ThreadSafe();
                }
                m.unlock();
            }
            return instance;
        }

        static void freeInstance(){
            if (instance != NULL){
                delete instance;
                instance = NULL; 
            }
        }

        void tell(){
            cout << "This is a Thread-Safe Lazy Singleton Pattern" << endl;
        }

    private:
        static SingletonLazy_ThreadSafe *instance;
        static mutex m;
};

// 初始化静态成员变量
SingletonLazy_ThreadSafe *SingletonLazy_ThreadSafe::instance = NULL;
mutex SingletonLazy_ThreadSafe::m;

// 局部静态变量实现的线程安全的懒汉模式
class SingletonLazy_ThreadSafe_LocalStatic{
    private:
        SingletonLazy_ThreadSafe_LocalStatic(){
            cout << "SingletonLazy_ThreadSafe_LocalStatic constructor run" << endl;
        }
    public:
        static SingletonLazy_ThreadSafe_LocalStatic *getInstance(){
            static SingletonLazy_ThreadSafe_LocalStatic *instance;
            return instance;
        }
        static void freeInstance(){
            if (instance != NULL){
                delete instance;
                instance = NULL; 
            }
        }
        void tell(){
            cout << "This is a local-static Thread-Safe Lazy Singleton Pattern" << endl;
        }

    private:
        static SingletonLazy_ThreadSafe_LocalStatic *instance;
};

// 懒汉模式测试
void LazyTest(){
    // 懒汉模式下一直到调用getInstance()才对单例对象进行实例化，但是存在多线程下线程不安全问题
    SingeltonLazy *p1 = SingeltonLazy::getInstance();
    SingeltonLazy *p2 = SingeltonLazy::getInstance();

    if (p1 == p2){
        cout << "是同一个对象" << endl;
    }
    else{
        cout << "不是同一个对象" << endl;
    }
    p1->tell();// 正常执行类中的成员函数
    SingeltonLazy::freeInstance();
}
 
// 饿汉模式测试
void HungryTest(){
    // 饿汉模式下先执行全局变量SingletonHungry *SingletonHungry::instance = new SingletonHungry();
    // 然后才会进入主函数进行单例对象的使用
    SingletonHungry *p1 = SingletonHungry::getInstance();
    SingletonHungry *p2 = SingletonHungry::getInstance();

    if (p1 == p2){
        cout << "是同一个对象" << endl;
    }
    else{
        cout << "不是同一个对象" << endl;
    }
    SingletonHungry::freeInstance();
}

// 多线程下的线程函数
void ThreadFunc(){
    cout << "this is a threadfunc" << endl;
    // 在多线程情况下，懒汉式会执行多次构造函数，将不再是单例
    SingletonLazy_ThreadSafe_LocalStatic::getInstance()->tell();
}

// 懒汉式在多线程情况下
void Lazy_MultiThread(){
    thread threads[10]; //空线程变量
    for(int i=0; i<3; i++){
        // 移动语义赋值，thread(ThreadFunc)为右值
        threads[i] = thread(ThreadFunc);
    }
    for(int i=0; i<3; i++){
        threads[i].join();
    }
}

int main()
{
    Lazy_MultiThread();
    return 0;
}