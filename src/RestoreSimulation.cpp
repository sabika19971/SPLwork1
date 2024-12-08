#include "../include/Action.h"
#include "../include/Simulation.h"


RestoreSimulation::RestoreSimulation(){}

void RestoreSimulation::act(Simulation& simulation)
{
    if (backup != nullptr)
    {
        std::cout << "im in the not null" << std:: endl;
        simulation = *backup; 
        complete();
    }
    else
    {
        std::cout <<"No backup available" << std::endl;
        error("No backup available");

    }
}

RestoreSimulation* RestoreSimulation::clone() const
{
    return new RestoreSimulation(*this);
}

const string RestoreSimulation::toString() const
{
    std::ostringstream addS;
    addS << "restore ";

    if(getStatus() == ActionStatus:: ERROR)
    {
       addS <<" ERROR";
    }
    else
    {
       addS << " COMPLETED";
    }
    
    return addS.str();
}