#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

// Component：组合中节点的接口
class Component {
public:
    virtual ~Component() {}
    virtual Component* getchild(int){ return 0;}
    virtual void add(Component*) {}
    virtual void remove(int) {}
    virtual void operation() = 0;
};
/*
 * Composite
 * defines behavior of the components having children
 * and store child components
 */
class Composite : public Component {
private:
    vector<Component*> children;
public:
    ~Composite () {
        for(size_t i=0; i<children.size(); i++){
            delete children[i];
        }
    }
    virtual Component* getchild(const int index) { 
        return children[index];
    }
    virtual void add(Component* component) {
        children.push_back(component);
    }
    virtual void remove(const int index) {
        Component* child = children[index];
        children.erase(children.begin() + index);
        delete child;
    }
    virtual void operation() {
        for(size_t i=0; i<children.size(); i++){
            children[i]->operation();
        }
    }
};

/*
 * Leaf
 * defines the behavior for the elements in the composition,
 * it has no children
 */
class Leaf : public Component {
private:
    int id;
public:
    Leaf(const int i) : id(i) {}
    ~Leaf() {}
    virtual void operation(){
        cout << "Leaf " << id <<" operation" << endl;
    }
};

int main(){  
    Composite composite;
    for(int i=0; i<5; i++){
        composite.add(new Leaf(i));
    }
    composite.remove(0);
    composite.operation();
    return 0;
}