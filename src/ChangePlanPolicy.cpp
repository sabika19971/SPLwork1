#include "../include/Action.h"
#include "../include/Plan.h"
#include "../include/Simulation.h"
#include <climits> // for INT_MAX

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy): 
                                    planId(planId), newPolicy(newPolicy)
                                    {}

void ChangePlanPolicy:: act(Simulation& simulation)
{
    Plan& p = (simulation.getPlan(planId));
    if(p.getPlanId() == INT_MAX|| p.getPolicyType() == newPolicy || !simulation.isValidPolicy(newPolicy)) // assuming the input is valid
    { 
        error("Cannot change selection policy");
        std::cout << "Cannot change selection policy" << std::endl;
    }
    else
    {   
            SelectionPolicy* sm = simulation.getPolicyInstancePointer(newPolicy);
            sm->setParam(p.getlifeQualityScore(),p.getEconomyScore(),p.getEnvironmentScore());
            p.setSelectionPolicy(sm); // DELETES THE OLD POLICY POINTER  
            complete();   
    }
}

ChangePlanPolicy* ChangePlanPolicy:: clone()  const
{
    return new ChangePlanPolicy(*this);
}

const string ChangePlanPolicy ::  toString() const 
{

    std::ostringstream addS;
    addS << "changePolicy " << planId << " "<< newPolicy;
    
    
    if(getStatus() == ActionStatus:: ERROR)
    {
       addS <<" ERROR";
    }
    addS << " COMPLETED"; 
    return addS.str();
    
}




