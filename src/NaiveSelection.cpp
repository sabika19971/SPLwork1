#include "../include/SelectionPolicy.h"

NaiveSelection::NaiveSelection(): lastSelectedIndex(0) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) 
{
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const
{
    return "NaiveSelection";
}

NaiveSelection* NaiveSelection::clone() const
{
    return new NaiveSelection(*this);
}