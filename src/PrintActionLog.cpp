#include "../include/Action.h"



void ChangePlanPolicy :: act(Simulation &simulation){
    simulation.printActionLog();
}


        PrintActionsLog* PrintActionsLog:: clone() const {
            return new PrintActionsLog(*this);
        }
        const string PrintActionsLog :: toString() const {
                return "Action Print Log";
        }
