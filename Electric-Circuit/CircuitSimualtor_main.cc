#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "CircuitSimulator.h"
using namespace std;

int main(int argc, char** argv)
{   
    int total_iter{};
    int total_prints{};
    double time_step{};
    double battery_voltage{};

    try
    {
        total_iter = std::stoi(argv[1]);
        total_prints = std::stoi(argv[2]);
        time_step = std::stod(argv[3]);
        battery_voltage = std::stod(argv[4]);
    }
    
    
    catch(std::invalid_argument& b)
    {
        cerr << "Invalid argument in "<< b.what()  << endl;
        return 1;
    }

    catch(std::exception& e)
    {
        cout << "Missing input with error message: " << endl;
        cerr << e.what() << endl;
        return 1;
    }
   

    Connection P,N,L,R;
    bool print{false};

    Circuit krets{};
    krets.add_battery(P, N, "BAT1", battery_voltage);
    krets.add_resistor(P, L,  "R1", 150);
    krets.add_resistor(P, R, "R2", 50);
    krets.add_capacitor(R, L, "C3", 1);
    krets.add_resistor(L, N, "R4", 300);
    krets.add_capacitor(R, N, "C5", 0.75);
    krets.simulate(total_iter, total_prints, time_step);

    return 0;
}
