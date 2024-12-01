#include "../include/Action.h"

AddSettlement::AddSettlement(const string& settlementName,SettlementType settlementType):
                            settlementName(settlementName), settlementType(settlementType)
                            {}

void AddSettlement::act(Simulation& simulation) 
{ 
    Settlement* nS = new Settlement(settlementName,settlementType);
    if(simulation.getSettlement(settlementName).getType() != settlementType || !simulation.isSettlementExists(settlementName)) // enum compared by value according to chat 
    { 
          error("Settlement already exist or you have entered a non valide Settlement type.");   
    } 
    else
    {
        simulation.addSettlement(nS);
        complete();
    }
} 

AddSettlement* AddSettlement:: clone() const
{
    return new AddSettlement(*this); 

}

const string AddSettlement :: toString() const
{
    if(getStatus() == ActionStatus:: ERROR)
    {
        return getErrorMsg();
    }
    
    std::ostringstream addS;
    addS << "AddSettlement : " + settlementName + " ";

    switch(settlementType)
    {
        case SettlementType:: CITY : addS << "CITY";
        case SettlementType:: METROPOLIS : addS <<"METROPOLIS";
        case SettlementType:: VILLAGE : addS << "VILLAGE";
        
    }
    addS << " COMPLETED"; 
    return addS.str();
}