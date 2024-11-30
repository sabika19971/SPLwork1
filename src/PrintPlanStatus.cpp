#include "../include/Action.h"

 PrintPlanStatus:: PrintPlanStatus(int planId) : planId(planId){

 }

void  PrintPlanStatus ::act (Simulation& simulation) {
    Plan p (simulation.getPlan(planId));
        if(p.getPlanId() == -1){
                error("Plan doesn't exist");
        }
        else{
            p.toString();
        }
}


        PrintPlanStatus* PrintPlanStatus:: clone() const {
            return new PrintPlanStatus(*this); 
        }
        const string PrintPlanStatus:: toString() const {
          return "I have printed Plan: " + planId;
        }







