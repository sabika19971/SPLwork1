#include "../include/SelectionPolicy.h"


SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(0) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    while(facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ENVIRONMENT)
    {
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string SustainabilitySelection::toString() const
{
    return "env";
}

SustainabilitySelection* SustainabilitySelection::clone() const
{
    return new SustainabilitySelection(*this);
}

void SustainabilitySelection:: setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore)
{
    
}