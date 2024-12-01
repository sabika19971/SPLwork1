#include "../include/Action.h"


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
        case ActionStatus::COMPLETED : stat = "COMPLETED";
        case ActionStatus::ERROR : stat = "ERROR";
        default: stat = "PENDING";
    }
    return "RestoreSimulation : " + stat; 
}