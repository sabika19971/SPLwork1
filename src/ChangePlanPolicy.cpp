#include "../include/Action.h"


ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy): 
                                    planId(planId), newPolicy(newPolicy)
                                    {}

void ChangePlanPolicy:: act(Simulation& simulation)
{
    Plan& p = (simulation.getPlan(planId));
    if(p.getPlanId() == -1|| p.getPolicyType() == newPolicy) // assuming the input is valid
    { 
        error("Cannot change selection policy");
    }
    else{    
        SelectionPolicy* sm = simulation.getPolicyInstancePointer(newPolicy);
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
    return "we have change the policy to " + newPolicy;
}



