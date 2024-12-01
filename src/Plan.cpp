#include "../include/Plan.h"

Plan :: Plan(const int planId, const Settlement& settlement, SelectionPolicy* selectionPolicy, const vector<FacilityType>& facilityOptions):
                plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus :: AVALIABLE),facilities(), underConstruction(), facilityOptions(facilityOptions), 
                life_quality_score(0), economy_score(0), environment_score(0),construction_limit(static_cast<int>(settlement.getType())),
                policyType(selectionPolicy -> toString())
{}

// COPY CONSTRUCTOR
Plan::Plan(const Plan& other) : plan_id(other.plan_id),  settlement(other.settlement),selectionPolicy((other.selectionPolicy) -> clone()), status(other.status),
                               facilities(),underConstruction(),facilityOptions(other.facilityOptions), 
                                life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score),
                                 construction_limit(other.construction_limit), policyType(other.policyType)
                                // gives him the same "catalog"
{
    for (Facility* f : other.facilities)
    {
        (this -> facilities).push_back(f -> clone());
    }

    for (Facility* f : other.underConstruction)
    {
        (this -> underConstruction).push_back(f -> clone());
    }
}

// DESTRUCTOR
Plan::~Plan()
{
    for (Facility* f : facilities)
    {
        delete f;
    }

    for (Facility* f : underConstruction)
    {
        delete f;
    } 

    facilities.clear();

    underConstruction.clear();
}

const int Plan :: getlifeQualityScore() const
{
    return life_quality_score;
}

const int Plan :: getEconomyScore() const
{
    return economy_score;
}

const int Plan :: getEnvironmentScore() const
{
    return environment_score;
}

const int Plan :: getPlanId() const
{
    return plan_id;
}

void Plan :: setSelectionPolicy(SelectionPolicy* selectionPolicy)
{
    delete selectionPolicy; 
    (this -> selectionPolicy) = selectionPolicy;
    policyType = selectionPolicy -> toString();
}

void Plan :: step()
{
    if (status == PlanStatus ::AVALIABLE)
    {
        int typeValue( static_cast<int>(settlement.getType()) );
        while(underConstruction.size() < construction_limit )
        {
            const FacilityType& facil =  selectionPolicy -> selectFacility(facilityOptions);
            Facility* f = new Facility(facil, settlement.getName());
            addFacility(f); // CODE MOVED TO addFacility()
            typeValue = typeValue -1;
        }
    }

    for (size_t i(0); i < underConstruction.size(); ++i)
    {
        if(underConstruction[i]->step()== FacilityStatus :: OPERATIONAL)
        {
            facilities.push_back(underConstruction[i]);
            underConstruction.erase(underConstruction.begin()+i);
        }
    }

    if(underConstruction.size() == construction_limit) 
    {
        status = PlanStatus :: BUSY;
    }
    else
    {
        status = PlanStatus :: AVALIABLE;  
    }   
}

void Plan :: printStatus()
{
    switch(status)
    {
        case PlanStatus :: AVALIABLE:
        {
            std:: cout << "SettlementName< " + settlement.getName() + " >\n";
            std:: cout << "PlanSatus: AVALIABLE";
        }
        case PlanStatus :: BUSY : 
        {
            std:: cout << "SettlementName< " + settlement.getName() + " >\n";
            std:: cout << "PlanSatus: BUSY";
        } 
    }
}

const vector<Facility*>& Plan :: getFacilities() const
{
    return facilities;
}

void Plan :: addFacility(Facility* facility)
{
    underConstruction.push_back(facility);
}

const string Plan :: toString() const
{
    std::ostringstream oss;
    // ---------- print ID -------//
    oss << "Plan ID: " << plan_id << "\n";

    // ---------- print settelment name and type + selection policy ----- //
    oss << "SettlementName: " << settlement.toString() << "\n";
    oss << "Selection Policy: " << selectionPolicy->toString() << "\n";
    
    // ---------- print plan status ----------- //
    switch (status)
    {
        case PlanStatus :: AVALIABLE:
        {
            oss << "Status: " << "AVALIABLE" << "\n"; 
            break;
        }
        case PlanStatus :: BUSY : 
        {
            oss << "Status: " << "BUSY" << "\n"; 
            break;
        }  
    }

    // --------- selectionPolicy --------- //
    oss << "SelectionPolicy: " << selectionPolicy->toString();
    
    // -------- print life,economy,enviroment _ score ----------- //
    oss << "Life Quality Score: " << life_quality_score << "\n";
    oss << "Economy Score: " << economy_score << "\n";
    oss << "Environment Score: " << environment_score << "\n";

    // --------- print facilities on OPERATION --------- //
    oss << "Facilities:\n";
    for (const auto* facility : facilities) 
    {
        if (facility) 
        {
            oss << "  - " << facility->toString() << "\n";
        }
    }

    // --------- print facilities UNDERCONSTRUCTION --------- //
    oss << "Facilities UNDERCONSTRUCTION:\n";
    for (const auto* facility : underConstruction) 
    {
        if (facility) 
        {
            oss << "  - " << facility->toString() << "\n";
        }
    }
    return oss.str();  
}



const string Plan::getPolicyType() const
{ 
    return "";
}
    
