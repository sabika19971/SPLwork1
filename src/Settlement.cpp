#include "../include/Settlement.h"


Settlement:: Settlement(const string& name, SettlementType type): name(name), type(type){}

const string& Settlement::getName() const
{
    return name;
}

SettlementType Settlement:: getType() const
{
    return type;
}

const string Settlement::toString() const {
    // Map SettlementType enum to string
    string typeString;
    switch (type) {
        case SettlementType::VILLAGE:
            typeString = "Village";
            break;
        case SettlementType::CITY:
            typeString = "City";
            break;
        case SettlementType::METROPOLIS:
            typeString = "Metropolis";
            break;
        default:
            typeString = "Unknown";
    }

    // Return a descriptive string
    return "Settlement Name: " + name + ", Type: " + typeString;
}


Settlement* Settlement::clone() const
{
    return new Settlement(*this);
}





