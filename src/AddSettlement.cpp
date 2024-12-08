#include "../include/Action.h"
#include "../include/Settlement.h"
#include "../include/Simulation.h"
AddSettlement::AddSettlement(const string& settlementName,SettlementType settlementType):
                            settlementName(settlementName), settlementType(settlementType)
                            {}

void AddSettlement::act(Simulation& simulation) 
{ 
    // -------- validatoin of input ----------// 
    if(!(simulation.isSettlementExists(settlementName)))
    {
        // --------- preforming the act ---------- //
        Settlement* nS = new Settlement(settlementName,settlementType);
        bool isAdded (simulation.addSettlement(nS));
        if(isAdded)
        {
            complete();     
        }
        else
        {
            std::cout<<"Settlement already exist"<<std::endl;
            error("Settlement already exist");    
        }
    }
    else
    {
        std::cout<<"Settlement already exist"<<std::endl;
        error("Settlement already exist");
    }
}


AddSettlement* AddSettlement:: clone() const
{
    return new AddSettlement(*this); 

}

const string AddSettlement :: toString() const
{
    std::ostringstream addS;
    addS << "settlement " + settlementName + " ";
    
    switch(settlementType)
    {
        case SettlementType:: CITY :
            addS << "1";
            break;
        case SettlementType:: METROPOLIS : 
            addS <<"2";
            break;
        case SettlementType:: VILLAGE : 
            addS << "0";
            break;
        
    }
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