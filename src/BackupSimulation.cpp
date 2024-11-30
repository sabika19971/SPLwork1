#include "../include/Action.h"


BackupSimulation::BackupSimulation(){}

void BackupSimulation::act(Simulation& simulation)
{
    if (backup == nullptr)
    {
        backup = new Simulation(simulation); // NEED TO IMPLEMENT THE LOGIC IN THE COPY CONSTRUCTOR OF Simulation.cpp
    }
    else
    {
        *backup = simulation; // NEED TO IMPLEMENT THE LOGIC IN THE OPERATION= METHOD OF Simulation.cpp
    }
    complete();
}

BackupSimulation* BackupSimulation::clone() const
{
    return new BackupSimulation(*this);
}

const string BackupSimulation::toString() const
{
    string stat;
    switch(getStatus())
    {
        case ActionStatus::COMPLETED : stat = "COMPLETED";
        case ActionStatus::ERROR : stat = "ERROR";
        default: stat = "PENDING";
    }
    return "BackupSimulation : " + stat; 
}