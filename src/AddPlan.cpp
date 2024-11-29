#include "../include/Action.h"


// NO NEED FOR THIS -> ACCORDING TO CHATGPT
AddPlan::AddPlan(const string& settlementName, const string& selectionPolicy) : settlementName(settlementName), 
                                                                                selectionPolicy(selectionPolicy) {}

void AddPlan::act(Simulation& simulation)
{
    SelectionPolicy* policy = getPolicyInstancePointer(selectionPolicy); // DONT DELETE THIS, USED BY THE simulation.addPlan
    if (policy == nullptr || !simulation.isSettlementExists(settlementName))
    {
        error("Cannot create this plan");
    }
    else
    {
        simulation.addPlan(simulation.getSettlement(settlementName), policy);
    }
}

const string AddPlan::toString() const
{
    string stat;
    switch(getStatus())
    {
        case ActionStatus::COMPLETED : stat = "COMPLETED";
        case ActionStatus::ERROR : stat = "ERROR";
        default: stat = "PENDING";
    }
    return "AddPlan : " + settlementName + selectionPolicy + " - " + stat; 
}

AddPlan* AddPlan::clone() const
{
    return new AddPlan(*this);
}

// WE ADDED
SelectionPolicy* AddPlan::getPolicyInstancePointer(const string& threeLetters)
{
    if(threeLetters == "nve")
    {
        return new NaiveSelection();
    }
    else if (threeLetters == "eco")
    {
        return new EconomySelection();
    }
    else if (threeLetters == "env")
    {
        return new SustainabilitySelection();
    }
    else if (threeLetters == "bal")
    { 
        return new BalancedSelection(0,0,0);
    }
    else
    {
        return nullptr;
    }
}