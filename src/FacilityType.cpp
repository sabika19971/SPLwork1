#include "../include/Facility.h"
 FacilityType::FacilityType(const string& name, const FacilityCategory category, const int price, 
                                    const int lifeQuality_score, const int economy_score,
                                             const int environment_score):
 name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), 
 economy_score(economy_score),environment_score(environment_score)
 {

 }

  const string& FacilityType:: getName() const{
    return name;
  }

   int FacilityType:: getCost() const{
    return price;
   }
   int FacilityType:: getLifeQualityScore() const{
    return lifeQuality_score;
   }
int FacilityType :: getEnvironmentScore() const{
    return environment_score;
}
 int FacilityType:: getEconomyScore() const{
    return economy_score;
 }
 FacilityCategory FacilityType:: getCategory() const{
    return category;
 }

/* PROBABLY NOT NEEDED
//WE ADDED
string FacilityType::getCategoryString() const
{
   switch(category)
   {
      case FacilityCategory::LIFE_QUALITY: return "LIFE_QUALITY";
      case FacilityCategory::ECONOMY: return "ECONOMY";
      case FacilityCategory::ENVIRONMENT: return "ENVIRONMENT";
      default: return "error"; //shouldnt happen
   }
}
*/






