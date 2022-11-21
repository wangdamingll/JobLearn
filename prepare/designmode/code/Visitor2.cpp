#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*--------Template--------*/
template <typename... Types>
class Visitor_;
template <typename T, typename... Types>
class Visitor_<T,Types...> : Visitor_<Types...>{
public:
    using Visitor_<Types...>::Visit;//避免覆盖父类的同名方法
    virtual void Visit(T&) = 0;
};
template <typename T>
class Visitor_<T>{
public:
    virtual void Visit(T&) = 0;
};


class Element;
class CPU;
class VideoCard;
class MainBoard;
class Element;

using VisitorBase=Visitor_<CPU,VideoCard,MainBoard> ;

/*------------------*/

class Visitor : public VisitorBase {
public:
    Visitor(std::string&& name) {
        visitorName = std::forward<string>(name);
    }

    std::string getName() {
        return this->visitorName;
    };
private:
    std::string visitorName;
};


class Element {
public:
    Element( std::string&& name ) {
        eleName = std::forward<string>(name);
    }
    virtual void accept( Visitor& visitor ) {};

    virtual std::string getName() {
        return this->eleName;
    }
private:
    std::string eleName;
};

/*----------- Elements -------------*/

class CPU : public Element {
public:
    CPU(std::string name) : Element(std::move(name)) {}

    void accept(Visitor& visitor) override {
        visitor.Visit(*this);
    }
};

class VideoCard : public Element {
public:
    VideoCard(std::string name) : Element(std::move(name)) {}

    void accept(Visitor& visitor) override {
        visitor.Visit(*this);
    }
};

class MainBoard : public Element {
public:
    MainBoard(std::string name) : Element(std::move(name)) {}

    void accept(Visitor& visitor) override {
        visitor.Visit(*this);
    }
};

/*----------- ConcreteVisitor -------------*/

class CircuitDetector : public Visitor{
public:
    CircuitDetector(std::string name) : Visitor(std::move(name)) {}

    // checking cpu
    void Visit(CPU& cpu ) override {
        std::cout << Visitor::getName() << " is checking CPU's circuits.(" << cpu.getName()<<")" << std::endl;
    }

    // checking videoCard
    void Visit( VideoCard& videoCard ) override {
        std::cout << Visitor::getName() << " is checking VideoCard's circuits.(" << videoCard.getName()<<")" << std::endl;
    }

    // checking mainboard
    void Visit( MainBoard& mainboard ) override {
        std::cout << Visitor::getName() << " is checking MainBoard's circuits.(" << mainboard.getName() <<")" << std::endl;
    }

};

class FunctionDetector : public Visitor {
public:
    FunctionDetector(std::string name) : Visitor(std::move(name)) {}
    void Visit( CPU& cpu )  override {
        std::cout << Visitor::getName() << " is check CPU's function.(" << cpu.getName() << ")"<< std::endl;
    }

    // checking videoCard
    void Visit( VideoCard& videoCard ) override  {
        std::cout << Visitor::getName() << " is checking VideoCard's function.(" << videoCard.getName()<< ")" << std::endl;
    }

    // checking mainboard
    void Visit( MainBoard& mainboard ) override {
        std::cout << Visitor::getName() << " is checking MainBoard's function.(" << mainboard.getName() << ")"<< std::endl;
    }
};

/*------------------------*/
class Computer {
public:
    Computer(CPU* cpu, VideoCard* videocard, MainBoard* mainboard) {
        elementList.push_back(cpu);
        elementList.push_back(videocard);
        elementList.push_back(mainboard);
    };
    void Accept(Visitor& visitor) {
        for( std::vector<Element*>::iterator i = elementList.begin(); i != elementList.end(); i++ )
        {
            (*i)->accept(visitor);
        }
    };
private:
    std::vector<Element*> elementList;
};


int main(){
    CPU* cpu = new CPU("Intel CPU");
    VideoCard* videocard = new VideoCard("XXX video card");
    MainBoard* mainboard = new MainBoard("HUAWEI mainboard");
    Computer* myComputer = new Computer(cpu, videocard, mainboard);

    CircuitDetector* Dan = new CircuitDetector("CircuitDetector Dan");
    FunctionDetector* Tom = new FunctionDetector("FunctionDetector Tom");

    std::cout << "\nStep 1: Dan is checking computer's circuits." << std::endl;
    myComputer->Accept(*Dan);
    std::cout << "\nStep 2: Tom is checking computer's functions." << std::endl;
    myComputer->Accept(*Tom);

    return 0;
}