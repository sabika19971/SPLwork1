#include "../include/Action.h"
#include "../include/Simulation.h"



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
    std::ostringstream addS;
    addS << "backup ";

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