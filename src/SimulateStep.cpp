#include "../include/Action.h"
#include "../include/Simulation.h"

SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps){

    
} // no need for this -> according to chatGPT

void SimulateStep::act(Simulation& simulation)
{
    for (int i = 1; i <= numOfSteps; i++)
    {
        simulation.step();
    }
    complete();
}

const string SimulateStep::toString() const
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
    return "SimulateStep : " + std::to_string(numOfSteps) + " - " + stat; 
}

SimulateStep* SimulateStep::clone() const
{
    return new SimulateStep(*this);
}