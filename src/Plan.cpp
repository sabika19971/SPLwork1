#include "../include/Plan.h";

Plan :: Plan(const int planId, const Settlement& settlement, SelectionPolicy* selectionPolicy, const vector<FacilityType>& facilityOptions):
                plan_id(plan_id), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), 
                status(PlanStatus :: AVALIABLE), construction_limit(static_cast<int>(settlement.getType())) 
{
policyType = selectionPolicy ->toString(); // why we could not do that in the inisializer ? 

}

const int Plan :: getlifeQualityScore() const{
    return life_quality_score;
}

const int Plan :: getEconomyScore() const{
    return economy_score;
}

const int Plan :: getEnvironmentScore() const {
    return environment_score;
}
const int Plan :: getPlanId() const{
            return plan_id;

        }

void Plan :: setSelectionPolicy(SelectionPolicy* selectionPolicy){
    delete selectionPolicy; 
    this -> selectionPolicy = selectionPolicy;
    policyType = selectionPolicy->toString();
}

void Plan :: step(){
    if (status == PlanStatus ::AVALIABLE){
    int typeValue( static_cast<int>(settlement.getType()) );
       while(underConstruction.size()<construction_limit ){
          const FacilityType& facil =  selectionPolicy->selectFacility(facilityOptions);
          Facility* f = new Facility(facil, settlement.getName());
          underConstruction.push_back(f);
          typeValue = typeValue -1;
       }

    }
    for (size_t i(0); i < underConstruction.size(); ++i) {
        if(underConstruction[i]->step()== FacilityStatus :: OPERATIONAL){
            facilities.push_back(underConstruction[i]);
            underConstruction.erase(underConstruction.begin()+i);
        }

    }
    if(underConstruction.size() == construction_limit) {
        status = PlanStatus :: BUSY;
    }
    else{
        status = PlanStatus :: AVALIABLE;
    }
     

}

void Plan :: printStatus(){
            switch(status){
                case PlanStatus :: AVALIABLE:{
                std:: cout << "SettlementName< " + settlement.getName() + " >\n";
                std:: cout << "PlanSatus: AVALIABLE";
                }
                case PlanStatus :: BUSY : {
                    std:: cout << "SettlementName< " + settlement.getName() + " >\n";
                    std:: cout << "PlanSatus: BUSY";
                } 
            }
}

        const vector<Facility*>& Plan :: getFacilities() const{
            return facilities;
        }

        void Plan :: addFacility(Facility* facility){
            // no need to implement; 
        }
        const string Plan :: toString() const{
          std::ostringstream oss;
                // ---------- print ID -------//

                oss << "Plan ID: " << plan_id << "\n";
                // ---------- print settelment name and type + selection policy ----- //

                oss << "SettlementName: " << settlement.toString() << "\n";
                oss << "Selection Policy: " << selectionPolicy->toString() << "\n";
                
                // ---------- print plan status ----------- //

                switch (status)
                {
                case PlanStatus :: AVALIABLE:{
                    oss << "Status: " << "AVALIABLE" << "\n"; 
                    break;
                
                 case PlanStatus :: BUSY : {
                       oss << "Status: " << "BUSY" << "\n"; 
                      break;
                 }
                  
                }
                // --------- selectionPolicy --------- //
                    oss << "SelectionPolicy: " << selectionPolicy->toString();
               
                // -------- print life,economy,enviroment _ score ----------- //
                oss << "Life Quality Score: " << life_quality_score << "\n";
                oss << "Economy Score: " << economy_score << "\n";
                oss << "Environment Score: " << environment_score << "\n";
                // --------- print facilities on OPERATION --------- //
                oss << "Facilities:\n";
                for (const auto* facility : facilities) {
                    if (facility) {
                        oss << "  - " << facility->toString() << "\n";
                    }
                }
                // --------- print facilities UNDERCONSTRUCTION --------- //
                oss << "Facilities UNDERCONSTRUCTION:\n";
                for (const auto* facility : underConstruction) {
                    if (facility) {
                        oss << "  - " << facility->toString() << "\n";
                    }
                }
                return oss.str();
                    
         
        }

       