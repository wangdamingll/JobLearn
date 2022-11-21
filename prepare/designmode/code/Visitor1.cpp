#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;
#include <vector>

class Element;
class CPU;
class VideoCard;
class MainBoard;

class Visitor {
public:
    Visitor(std::string name) {
        visitorName = name;
    }
    virtual void visitCPU( CPU* cpu ) {};
    virtual void visitVideoCard( VideoCard* videoCard ) {};
    virtual void visitMainBoard( MainBoard* mainBoard ) {};

    std::string getName() {
        return this->visitorName;
    };
private:
    std::string visitorName;
};

class Element {
public:
    Element( std::string name ) {
        eleName = name;
    }
    virtual void accept( Visitor* visitor ) {};

    virtual std::string getName() {
        return this->eleName;
    }
private:
    std::string eleName;
};

class CPU : public Element {
public:
    CPU(std::string name) : Element(name) {}

    void accept(Visitor* visitor) {
        visitor->visitCPU(this);
    }
};

class VideoCard : public Element {
public:
    VideoCard(std::string name) : Element(name) {}

    void accept(Visitor* visitor) {
        visitor->visitVideoCard(this);
    }
};

class MainBoard : public Element {
public:
    MainBoard(std::string name) : Element(name) {}

    void accept(Visitor* visitor) {
        visitor->visitMainBoard(this);
    }
};

class CircuitDetector : public Visitor {
public:
    CircuitDetector(std::string name) : Visitor(name) {}

    // checking cpu
    void visitCPU( CPU* cpu ) {
        std::cout << Visitor::getName() << " is checking CPU's circuits.(" << cpu->getName()<<")" << std::endl;
    }

    // checking videoCard
    void visitVideoCard( VideoCard* videoCard ) {
        std::cout << Visitor::getName() << " is checking VideoCard's circuits.(" << videoCard->getName()<<")" << std::endl;
    }

    // checking mainboard
    void visitMainBoard( MainBoard* mainboard ) {
        std::cout << Visitor::getName() << " is checking MainBoard's circuits.(" << mainboard->getName() <<")" << std::endl;
    }

};

class FunctionDetector : public Visitor {
public:
    FunctionDetector(std::string name) : Visitor(name) {}
    virtual void visitCPU( CPU* cpu ) {
        std::cout << Visitor::getName() << " is check CPU's function.(" << cpu->getName() << ")"<< std::endl;
    }

    // checking videoCard
    void visitVideoCard( VideoCard* videoCard ) {
        std::cout << Visitor::getName() << " is checking VideoCard's function.(" << videoCard->getName()<< ")" << std::endl;
    }

    // checking mainboard
    void visitMainBoard( MainBoard* mainboard ) {
        std::cout << Visitor::getName() << " is checking MainBoard's function.(" << mainboard->getName() << ")"<< std::endl;
    }
};


class Computer {
public:
    Computer(CPU* cpu, VideoCard* videocard, MainBoard* mainboard) {
        elementList.push_back(cpu);
        elementList.push_back(videocard);
        elementList.push_back(mainboard);
    };
    void Accept(Visitor* visitor) {
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
    myComputer->Accept(Dan);
    std::cout << "\nStep 2: Tom is checking computer's functions." << std::endl;
    myComputer->Accept(Tom);

    return 0;
}