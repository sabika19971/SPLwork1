#include "../include/SelectionPolicy.h"


EconomySelection::EconomySelection(): lastSelectedIndex(0) {}

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
