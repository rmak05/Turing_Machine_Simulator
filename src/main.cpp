#include <iostream>
#include <SFML/Graphics.hpp>
#include "turing_machine.hpp"
#include "simulator.hpp"

int main(){
    try{
        simulator sim;
        while(sim.simulate_turing_machine()){}
    }
    catch(const std::exception& _e){
        std::cout << _e.what() << std::endl;
    }
    catch(...){
        std::cout << "Unknown exception" << std::endl;
    }

    return 0;
}