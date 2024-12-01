#include "../include/Action.h"
#include "../include/Simulation.h"

PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog :: act(Simulation &simulation)
{
    simulation.printActionLog();
    complete();
}

PrintActionsLog* PrintActionsLog:: clone() const 
{
    return new PrintActionsLog(*this);
}

const string PrintActionsLog :: toString() const 
{
        return "Action Print Log";
}
