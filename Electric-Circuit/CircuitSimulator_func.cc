#include <iostream>
#include "labb4_header.h"
#include <math.h>
#include <iomanip>
#include <string>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;


string Component::get_name() const
{
    return Name;
}

double Battery::get_voltage() const // kanske kan tas bort
{
    return voltage; 
}

double Component::get_voltage() const
{
    return positive.voltage - negative.voltage; 
}

double Resistor::get_current() const
{
    double voltage{get_voltage()};
    double current{voltage/resistance};
    return current;
}

double Battery::get_current() const
{
    return 0;
}

double Capacitor::get_current() const
{
    double voltage{get_voltage()};
    double current{capacitance*(voltage-charge)};
    return current;
}

double Capacitor::get_charge() // här struntar vi i timestep då den enbart ska vara med i simulate
{
    double charge_temp{capacitance*(fabs(positive.voltage-negative.voltage)-charge)};
    return charge_temp;
}

void Capacitor::simulate(double timestep, bool should_print)
{
    double charge_to_add{get_charge()*timestep}; 
    charge += charge_to_add;

    if (positive.voltage - negative.voltage > 0)    
    {
        positive.voltage -= charge_to_add;
        negative.voltage += charge_to_add;
    }
    else if (positive.voltage - negative.voltage < 0) 
    {
        positive.voltage += charge_to_add;
        negative.voltage -= charge_to_add;
    }
    

    double voltage{get_voltage()};
    double current{get_current()};
    
    if (should_print)
    {
        cout << setfill(' ');
        cout << setw(5) << right << fixed << setprecision(2) << voltage
        << setw(6) << fixed << setprecision(2) << current << "  ";
    }
}

void Resistor::simulate(double timestep, bool should_print)
{
    double voltage_diff{get_voltage()};
    double current{get_current()};

    positive.voltage =  positive.voltage - (((voltage_diff))/resistance * timestep ); 
    negative.voltage = negative.voltage + (((voltage_diff))/resistance * timestep );
    
    voltage_diff = get_voltage();
    current = get_current();

    if (should_print)
    {
        cout << setfill(' ');
        cout << setw(5) << right << fixed << setprecision(2) << voltage_diff
        << setw(6) << fixed << setprecision(2) << current << "  ";
    }
}

void Battery::simulate(double timestep, bool should_print)
{
    positive.voltage = voltage; 
    negative.voltage = 0;
    if (should_print)
    {
        cout << setfill(' ');
        cout << setw(5) << right << fixed << setprecision(2) << get_voltage() 
        << setw(6) << fixed << setprecision(2) << get_current() << "  ";
    }
}

Circuit :: ~Circuit()
{
    for (Component* component:circuit)
    {
        delete component; 
    }
}

void Circuit::add_resistor(Connection& p, Connection& n, string const name,double resistance)
{
    circuit.push_back(new Resistor(p, n, name, resistance));
}

void Circuit::add_battery(Connection& p, Connection& n, string const name, double voltage)
{
    circuit.push_back(new Battery(p, n, name, voltage));
}

void Circuit::add_capacitor(Connection& p, Connection& n, string const name, double capacitance)
{
    circuit.push_back(new Capacitor(p, n, name, capacitance));
}

void Circuit::simulate( int iterations, int prints, double timestep)
{
    int print_intervals{iterations/prints};
    bool print{false};

    for (Component* component:circuit)
    {
        cout << setfill(' ') << setw(11) << right << component-> get_name()<< "  ";
    }
    cout << endl;
    for (Component* component:circuit)
    {
        cout << setw(5) << right << "Volt" << setw(6) << right << "Curr" << "  ";
    }

    for (int i=1; i<=iterations; i++)
    {
        if (i % print_intervals == 0)
        {
            print = true;
            cout << endl;
        }
        for (Component* component:circuit)
        {
            component->simulate(timestep, print);
        }
        print = false;
    }
    cout << endl;
}
