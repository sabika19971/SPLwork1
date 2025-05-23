#include "../include/SelectionPolicy.h"



EconomySelection::EconomySelection(): lastSelectedIndex(-1)
{
}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    while(facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY)
    {
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string EconomySelection::toString() const
{
    return "eco";
}

EconomySelection* EconomySelection::clone() const
{
    return new EconomySelection(*this);
}

void EconomySelection:: setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore)
{
}

void EconomySelection:: addParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore)
{
}
