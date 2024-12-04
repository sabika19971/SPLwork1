#include "../include/Action.h"
#include "../include/Simulation.h"

#include "../include/SelectionPolicy.h"


// NO NEED FOR THIS -> ACCORDING TO CHATGPT
AddPlan::AddPlan(const string& settlementName, const string& selectionPolicy) : settlementName(settlementName), 
                                                                                selectionPolicy(selectionPolicy) {}

void AddPlan::act(Simulation& simulation)
{
     // -------- validatoin of input ----------//
     if(simulation.isValidPolicy(selectionPolicy)&& simulation.isSettlementExists(settlementName)){
        // -------- perform the action -----------//
        SelectionPolicy* policy = simulation.getPolicyInstancePointer(selectionPolicy);
        simulation.addPlan(simulation.getSettlement(settlementName), policy);
        complete();
      
     }
     else{
        error("Cannot create this plan"); 
       
        std::cout<<"Cannot create this plan"<<std::endl;   
     }    

}

const string AddPlan::toString() const
{
    string stat;
    if(this -> getStatus() == ActionStatus::COMPLETED){
         return "AddPlan : " + settlementName + " " + selectionPolicy + " - COMPLETED  " ; 
    }
    return getErrorMsg();
   
}


AddPlan* AddPlan::clone() const
{
    return new AddPlan(*this); 
}

// // WE ADDED
// SelectionPolicy* AddPlan::getPolicyInstancePointer(const string& threeLetters)
// {
//     if(threeLetters == "nve")
//     {
//         return new NaiveSelection();
//     }
//     else if (threeLetters == "eco")
//     {
//         return new EconomySelection();
//     }
//     else if (threeLetters == "env")
//     {
//         return new SustainabilitySelection();
//     }
//     else if (threeLetters == "bal")
//     { 
//         return new BalancedSelection(0,0,0);
//     }
//     else
//     {
//         return nullptr;
//     }
// }