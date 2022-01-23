#ifndef Simulator
#define Simulator

#include <iostream>
#include <string>                                                                                                                          
#include <fstream>                                                              
#include <sstream> 
#include <vector> 

class Connection 
{
    public:
    double voltage{};
    double current{};

};

class Component
{
    public:
    Component(Connection& p, Connection& n, std::string const name): 
                                    positive{p}, negative{n}, Name{name}{}
    std::string get_name() const;
    virtual double get_voltage() const;
    virtual double get_current() const = 0;
    virtual void simulate(double timestep, bool should_print) = 0;
    virtual ~Component() = default;

    protected: 
    Connection& positive;
    Connection& negative;
    std::string const Name; 

};


class Resistor : public Component
{
    public: 
    Resistor(Connection & p, Connection & n, std::string const name, double Resistance) : Component(p,n,name), resistance{Resistance} { };
    double get_resistance() const; 
    double get_current() const override;
    void simulate(double timestep, bool should_print) override;

    private:
    double resistance{}; 
};

class Battery : public Component
{
    public: 
    Battery(Connection & p, Connection & n, std::string const name, double Voltage) : Component(p,n,name), voltage{Voltage} { };
    double get_current() const override;
    void simulate(double timestep,bool should_print) override;
    double get_voltage() const override; 

    private:
    double voltage{};

};

class Capacitor : public Component
{
    public: 
    Capacitor(Connection & p, Connection & n, std::string const name, double Capacitance) : Component(p,n,name), capacitance{Capacitance} { };
    double get_charge();
    double get_current() const override;
    void simulate(double timestep, bool should_print) override;

    
    private:
    double capacitance{};
    double charge{}; 

};

class Circuit
{
    public:
        Circuit(){}
        ~Circuit();
        void add_resistor(Connection& p, Connection& n, std ::string const name,double resistance);
        void add_battery(Connection& p, Connection& n, std ::string const name, double voltage);
        void add_capacitor(Connection& p, Connection& n, std ::string const name, double capacitance);
        void simulate(int iterations, int prints, double timestep);
    private:
        std::vector<Component*> circuit;
};

#endif
