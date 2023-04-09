#include <iostream>
#include <stack>
#include <map>
using namespace std;

// базовый класс операции
class Operation {
public:
    virtual ~Operation() {}
    virtual void execute(stack<double>& st) = 0;
};

// конкретные операции
class AddOperation : public Operation {
public:
    void execute(stack<double>& st) override {
        double b = st.top(); st.pop();
        double a = st.top(); st.pop();
        st.push(a + b);
    }
};

class SubOperation : public Operation {
public:
    void execute(std::stack<double>& st) override {
        double b = st.top(); st.pop();
        double a = st.top(); st.pop();
        st.push(a - b);
    }
};

class MulOperation : public Operation {
public:
    void execute(stack<double>& st) override {
        double b = st.top(); st.pop();
        double a = st.top(); st.pop();
        st.push(a * b);
    }
};

class DivOperation : public Operation {
public:
    void execute(stack<double>& st) override {
        double b = st.top(); st.pop();
        double a = st.top(); st.pop();
        st.push(a / b);
    }
};

// фабрика операций
class OperationFactory {
public:
    virtual ~OperationFactory() {}
    virtual Operation* createOperation() = 0;
};

// конкретные фабрики операций
class AddOperationFactory : public OperationFactory {
public:
    Operation* createOperation() override {
        return new AddOperation();
    }
};

class SubOperationFactory : public OperationFactory {
public:
    Operation* createOperation() override {
        return new SubOperation();
    }
};

class MulOperationFactory : public OperationFactory {
public:
    Operation* createOperation() override {
        return new MulOperation();
    }
};

class DivOperationFactory : public OperationFactory {
public:
    Operation* createOperation() override {
        return new DivOperation();
    }
};

// калькулятор
class Calculator {
public:
    Calculator() {
        operations_['+'] = new AddOperationFactory();
        operations_['-'] = new SubOperationFactory();
        operations_['*'] = new MulOperationFactory();
        operations_['/'] = new DivOperationFactory();
    }

    ~Calculator() {
        for (auto op : operations_) {
            delete op.second;
        }
    }

    void push(double value) {
        st_.push(value);
    }

    void pop() {
        st_.pop();
    }

    void execute(char operation) {
        if (operations_.find(operation) != operations_.end()) {  // операция поддерживается
            OperationFactory* factory = operations_[operation];
            Operation* op = factory->createOperation();
            op->execute(st_);
            delete op;
        }
    }

    void print() {
        cout << st_.top() << endl;
    }

private:
    stack<double> st_;

    map<char, OperationFactory*> operations_;
};
int main() {
    Calculator calc;

    calc.push(10);
    calc.push(15);
    calc.execute('+');

    calc.print();

    calc.push(7);
    calc.execute('-');

    calc.print();

    calc.push(3);
    calc.execute('*');

    calc.print();

    calc.push(5);
    calc.execute('/');

    calc.print();

    return 0;
}
