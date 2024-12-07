#include "../include/SelectionPolicy.h"


NaiveSelection::NaiveSelection(): lastSelectedIndex(0) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) 
{
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const
{
    return "nve";
}

NaiveSelection* NaiveSelection::clone() const
{
    return new NaiveSelection(*this);
}

void NaiveSelection:: setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore)
{
    
}