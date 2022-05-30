#include <iostream>
#include <map>

// Context上下文包含对解释器来说是全局的信息
class Context
{
public:
    void set( const std::string& var, const bool value)
    {
        vars.insert( std::pair<std::string, bool>( var, value ) );
    }

    bool get( const std::string& exp )
    {
        return vars[ exp ];
    }
    // ...

private:
    std::map<std::string, bool> vars;
    // ...
};

// Abstract Expression 声明了抽象语法树中所有节点共有的抽象解释操作
class AbstractExpression {
public:
    virtual ~AbstractExpression() {}
    
    virtual bool interpret( Context* const )
    {
        return false;
    }
    // ...
};

// TerminalExpression实现了与语法中的终端符号相关的解释操作（句子中的每个终端符号都需要一个实例）
class TerminalExpression : public AbstractExpression {
public:
    TerminalExpression( const std::string& val ) : value( val ) {}
    
    ~TerminalExpression() {}
    
    bool interpret( Context* const context )
    {
        return context->get( value );
    }
    // ...
    
private:
    std::string value;
    // ...
};

// NonterminalExpression为语法中的非终端符实现解释操作（语法中的每个规则都需要一个这样的类）
class NonterminalExpression : public AbstractExpression {
public:
    NonterminalExpression( AbstractExpression *left, AbstractExpression *right ) : 
        lop( left ), rop( right ) {}
    
    ~NonterminalExpression(){
        delete lop;
        delete rop;
    }
    
    bool interpret( Context *const context ){
        return lop->interpret( context ) && rop->interpret( context );
    }
    // ...
    
private:
    AbstractExpression *lop;
    AbstractExpression *rop;
    // ...
};

int main(){
    // An example of very simple expression tree
    // that corresponds to expression (A AND B)
    AbstractExpression *A = new TerminalExpression("A");
    AbstractExpression *B = new TerminalExpression("B");
    AbstractExpression *exp = new NonterminalExpression( A, B );
    
    Context context;
    context.set( "A", true );
    context.set( "B", false );
    
    std::cout << context.get( "A" ) << " AND " << context.get( "B" );
    std::cout << " = " << exp->interpret( &context ) << std::endl;
    
    delete exp;
    return 0;
}
