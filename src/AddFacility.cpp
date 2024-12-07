#include "../include/Action.h"
#include "../include/Facility.h"
#include "../include/Simulation.h"

AddFacility :: AddFacility(const string& facilityName, const FacilityCategory facilityCategory, const int price,
                                         const int lifeQualityScore, const int economyScore, const int environmentScore) :
                                         facilityName(facilityName), facilityCategory(facilityCategory),
                                         price(price),lifeQualityScore(lifeQualityScore), economyScore(economyScore), 
                                         environmentScore(environmentScore)
                                         {}


// void AddFacility ::act(Simulation& simulation)
// {
//     FacilityType nF(facilityName,facilityCategory, price, lifeQualityScore,economyScore,environmentScore);
//     if(!simulation.addFacility(nF))
//     {  
//         error("Facility already exists"); 
//     } 
//     else
//     {
//         complete();
//     }  
// }



void AddFacility ::act(Simulation& simulation)
{
   // -------- validatoin of input ----------//
     if(simulation.isFacilityExsist(facilityName)){
        // -------- perform the action -----------//
        FacilityType nF(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore);
        if(simulation.addFacility(nF)){
            complete();
             std::cout<<this->toString()<<std::endl;
        }
        else{
             error("Facility already exists"); 
             std::cout<<this->toString()<<std::endl;
        }
        
         
     }
     else{
        error("Facility already exists"); 
        std::cout<<this->toString()<<std::endl;   
        std::cout<<"Facility already exists"<<std::endl;   
     }    
}


AddFacility* AddFacility :: clone() const 
{
    return new AddFacility(*this);
}

// const string AddFacility:: toString() const 
// {
//     if( getStatus() == ActionStatus :: ERROR)
//     {
//         return getErrorMsg();
//     }
//     std::ostringstream addF;
//     addF << "AddFacility : with Facility name:"+ facilityName + " Facility Category: ";
//     if(facilityCategory == FacilityCategory::ECONOMY)
//     {
//         addF<< "ECONOMY ";
//     }
//     else if (facilityCategory == FacilityCategory::ENVIRONMENT)
//     {
//         addF<<"ENVIRONMENT ";
//     }
//     else
//     {
//         addF<< "LIFE_QUALITY ";
//     }     
//     addF << "Price | L | ECO | ENV " << price << "|" <<lifeQualityScore << "|"<<economyScore << "|" << environmentScore << " COMPLETE";
//     return addF.str();
// }

const string AddFacility:: toString() const 
{
    std::ostringstream addF;
    addF << "facility " << facilityName;
   
    if(facilityCategory == FacilityCategory::LIFE_QUALITY)
    {
        addF<< "0 ";
    }
    else if (facilityCategory == FacilityCategory::ECONOMY)
    {
        addF<<"1 ";
    }
    else
    {
        addF<< "2 ";
    } 
    addF << price <<" " << lifeQualityScore << " " << economyScore << " " <<environmentScore;
     if( getStatus() == ActionStatus :: ERROR)
    {
        addF <<" ERROR";
    }    
    else
    {
        addF <<" COMPLETED";
    }
    return addF.str();
}



