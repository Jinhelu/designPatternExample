[toc]
## 建造者模式

Builder模式也叫建造者模式或者生成器模式，是由GoF提出的23种设计模式中的一种。
Builder模式是一种对象创建型模式之一，用来隐藏复合对象的创建过程，它把复合对象的创建过程加以抽象，通过子类继承和重载的方式，动态地创建具有复合属性的对象。

对象的创建：Builder模式是为对象的创建而设计的模式- 创建的是一个复合对象：被创建的对象为一个具有复合属性的复合对象- 关注对象创建的各部分的创建过程：不同的工厂（这里指builder生成器）对产品属性有不同的创建方法。

### 一、角色和职责
- 1) Builder：为创建产品各个部分，统一抽象接口。
- 2) ConcreteBuilder：具体的创建产品的各个部分，部分A， 部分B，部分C。
- 3) Director：构造一个使用Builder接口的对象，是多种不同建筑者的管理类，
- 4) Product: 表示被构造的复杂对象

ConcreteBuilder创建该产品的内部表示并定义它的装配过程，包含定义组成部件的类，包括将这些部件装配成最终产品的接口。

适用情况：一个对象的构建比较复杂，将一个对象的构建和对象的表示进行分离。
1. 对象的构建
使用Builder作为建筑者接口，
ConcreteBuilderX、ConcreteBuilderY作为具体的建筑者，建筑不同的产品，并对产品属性进行操作

2. 对象的表示
对应代码中的Product类，实现产品的属性描述以及操作（单独产品层面）

### 二、优缺点


