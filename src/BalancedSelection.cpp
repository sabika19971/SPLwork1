#include "../include/SelectionPolicy.h"
#include <algorithm> // for std::max/min


BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) :
LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore){} // no need for this->

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{
    int bestFacilityIndex = 0;
    int bestFacilityScore = distance(facilitiesOptions[0]);

    for(int i = 1; i < facilitiesOptions.size(); i++) 
    {
        int dist = distance(facilitiesOptions[i]); 
        if(dist < bestFacilityScore)
        {
            bestFacilityScore = dist;
            bestFacilityIndex = i;
        }     
    }
    return facilitiesOptions[bestFacilityIndex];
}

int BalancedSelection::distance(const FacilityType& facilityType) const
{
    int tempEconomyScore = facilityType.getEconomyScore();
    int tempEnvironmentScore = facilityType.getEnvironmentScore();
    int tempLifeQualityScore = facilityType.getLifeQualityScore();
    
    return std::max({tempEconomyScore + EconomyScore, tempEnvironmentScore + EnvironmentScore, tempLifeQualityScore + LifeQualityScore})
    - std::min({tempEconomyScore + EconomyScore, tempEnvironmentScore + EnvironmentScore, tempLifeQualityScore + LifeQualityScore});
}

const string BalancedSelection::toString() const
{
    return "bal";
}

BalancedSelection* BalancedSelection::clone() const
{
    return new BalancedSelection(*this);
}