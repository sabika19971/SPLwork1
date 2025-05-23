#include "../include/Action.h"
#include "../include/Plan.h"
#include "../include/Simulation.h"
#include "../include/Facility.h"
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
            int tempLifeQualityScore = 0, tempEconomyScore = 0, tempEnvironmentScore = 0; 
            for (Facility* facil : p.getUnderConstructionFacilities())
            {
                tempLifeQualityScore += facil -> getLifeQualityScore();
                tempEconomyScore += facil -> getEconomyScore();
                tempEnvironmentScore += facil -> getEnvironmentScore();
            }
            sm->setParam(p.getlifeQualityScore() + tempLifeQualityScore, p.getEconomyScore() + tempEconomyScore, p.getEnvironmentScore() + tempEnvironmentScore);
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
    else
    {
        addS << " COMPLETED";
    } 
    return addS.str();
    
}




