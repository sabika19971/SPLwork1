#include "../include/Plan.h";

const int Plan :: getlifeQualityScore() const{
    return life_quality_score;
}

const int Plan :: getEconomyScore() const{
    return economy_score;
}

const int Plan :: getEnvironmentScore() const {
    return environment_score;
}

void Plan :: setSelectionPolicy(SelectionPolicy* selectionPolicy){
    this -> selectionPolicy = selectionPolicy;
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
}
/*
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
*/