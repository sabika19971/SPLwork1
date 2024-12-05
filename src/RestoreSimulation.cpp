#include "../include/Action.h"
#include "../include/Simulation.h"


RestoreSimulation::RestoreSimulation(){}

void RestoreSimulation::act(Simulation& simulation)
{
    if (backup != nullptr)
    {
        simulation = *backup; 
        complete();
    }
    else
    {
        error("No backup available");
    }
}

RestoreSimulation* RestoreSimulation::clone() const
{
    return new RestoreSimulation(*this);
}

const string RestoreSimulation::toString() const
{
    string stat;
    switch(getStatus())
    {
        case ActionStatus::COMPLETED :
            stat = "COMPLETED";
            break;
        case ActionStatus::ERROR : 
            stat = "ERROR";
            break;
        default: stat = "PENDING";
            break;
    }
    return "RestoreSimulation : " + stat; 
}