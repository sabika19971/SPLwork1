#include "../include/Action.h"

AddFacility :: AddFacility(const string& facilityName, const FacilityCategory facilityCategory, const int price,
                                         const int lifeQualityScore, const int economyScore, const int environmentScore):facilityName(facilityName), facilityCategory(facilityCategory),
                                         price(price),lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore)
                                         {

                                         }


void AddFacility ::act(Simulation& simulation){
         FacilityType* nF = new FacilityType(facilityName,facilityCategory, price, lifeQualityScore,economyScore,environmentScore);
    if(!simulation.addFacility(*nF)){  
          error("Facility already exists");
     
    } 
    
}

AddFacility* AddFacility :: clone() const {
    return new AddFacility(*this);
}
const string AddFacility:: toString() const {
    if( getStatus() == ActionStatus :: ERROR){
        return getErrorMsg();
    }
    std::ostringstream addF;
   addF << "AddFacility : with Facility name:"+ facilityName + " Facility Type: ";

    
    switch(facilityCategory)
    {
        case FacilityCategory:: ECONOMY : addF << "ECONOMY";
        case FacilityCategory:: ENVIRONMENT : addF << "ENVIRONMENT";
        case FacilityCategory:: LIFE_QUALITY : addF << "LIFE_QUALITY";
        
        
    }
    addF << "Price | L | ECO | ENV" << price << "|" <<lifeQualityScore << "|"<<economyScore << "|" << environmentScore << "COMPLETE";
   
    
    return addF.str();
        }



