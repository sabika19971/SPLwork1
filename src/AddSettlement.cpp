#include "../include/Action.h"
#include "../include/Settlement.h"
#include "../include/Simulation.h"
AddSettlement::AddSettlement(const string& settlementName,SettlementType settlementType):
                            settlementName(settlementName), settlementType(settlementType)
                            {}

void AddSettlement::act(Simulation& simulation) 
{ 
    // -------- validatoin of input ----------// 
    if(!(simulation.isSettlementExists(settlementName))){
        // --------- preforming the act ---------- //
            Settlement* nS = new Settlement(settlementName,settlementType);
            bool isAdded (simulation.addSettlement(nS));
            if(isAdded){
                complete();
                
            }
            else{
                std::cout<<"Settlement already exist"<<std::endl;
                error("Settlement already exist");
               
            }
    }
    else{
         std::cout<<"Settlement already exist"<<std::endl;
         error("Settlement already exist");
        
    }

    
}

// void AddSettlement::act(Simulation& simulation) 
// { 
//     try{
//          Settlement* nS = new Settlement(settlementName,settlementType);
//          simulation.addSettlement(nS);
//     }
//     catch(const std::runtime_error& e){
//         std::cout<<"im in catch"<<std::endl;
//           error("Settlement already exist");
//           std::cout<<"Settlement already exist"<<std::endl;
//     }
           
    
// }


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