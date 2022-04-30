## 装饰模式

装饰（ Decorator ）模式又叫做包装模式。通过一种对客户端透明的方式来扩展对象的功能，是继承关系的一个替换方案。

装饰模式就是把要添加的附加功能分别放在单独的类中，并让这个类包含它要装饰的对象，当需要执行时，客户端就可以有选择地、按顺序地使用装饰功能包装对象。

动态地将附加职责附加到对象。 装饰器为扩展功能提供子类化的灵活替代方案。该模式具有结构目的并适用于对象。
### 一、类图角色和职责

装饰者模式（Decorator Pattern）动态的给一个对象添加一些额外的职责。就增加功能来说，此模式比生成子类更为灵活。
1. 什么时候使用
   * 动态透明的为单个对象添加职责，不影响其他对象
   * 可撤销的职责
   * 当无法通过子类化拓展实现对象职责增加时

### 二、案例
<font color=red>此处案例比实例代码简单，实例代码增加了装饰类的接口，采用多重继承方式实现</font>

```C++
#include <iostream>
using namespace std;

class Car {
public:
	virtual void show() = 0;
};

class RunCar : public Car {
public:
	virtual void show() {
		cout << "可以跑" << endl;
	}
};

class SwimCarDecorator : public Car {
public:
	SwimCarDecorator(Car *car) {
		m_car = car;
	}
	void swim() {
		cout << "可以游" << endl;
	}
	virtual void show() {
		m_car->show();
		swim();
	}
private:
	Car *m_car;
};

class  FlyCarDecorator : public Car {
public:
	FlyCarDecorator(Car *car) {
		m_car = car;
	}
	void fly() {
		cout << "可以飞" << endl;
	}
	virtual void show() {
		m_car->show();
		fly();
	}
private:
	Car *m_car;
};

int main(void) {
	Car * mycar = new RunCar();
	mycar->show();
	cout << "-----------" << endl;

	FlyCarDecorator *flycar = new FlyCarDecorator(mycar);
	flycar->show();
	cout << "-----------" << endl;

	SwimCarDecorator *swimcar = new SwimCarDecorator(flycar);
	swimcar->show();
	cout << "-----------" << endl;

	delete swimcar;
	delete flycar;
	delete mycar;
	return 0;
}
```

### 三、扩展案例

创建一个 Shape 接口和实现了 Shape 接口的实体类。然后创建一个实现了 Shape 接口的抽象装饰类 ShapeDecorator，并把 Shape 对象作为它的实例变量。

RedShapeDecorator 是实现了 ShapeDecorator 的实体类。

DecoratorPatternDemo，演示类使用 RedShapeDecorator 来装饰 Shape 对象。

