#include "../include/Action.h"
#include "../include/Simulation.h"

Close::Close(){}

void Close::act(Simulation& simulation)
{
    simulation.close(); // also loop through all the plans in the simulation and calling their toString
    complete();
    // simulation variable will be deleted in main.cpp because its on the stack  
}

Close* Close::clone() const
{
    return new Close(*this);
}

const string Close::toString() const
{
    string stat;
    switch(getStatus())
    {
        case ActionStatus::COMPLETED : stat = "COMPLETED";
        case ActionStatus::ERROR : stat = "ERROR" + getErrorMsg();
        default: stat = "PENDING";
    }
    return "Close : " + stat;
}
