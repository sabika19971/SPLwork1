#include "../include/Plan.h"

Plan :: Plan(const int planId, const Settlement& settlement, SelectionPolicy* selectionPolicy, const vector<FacilityType>& facilityOptions):
                plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus :: AVALIABLE),facilities(), underConstruction(), facilityOptions(facilityOptions), 
                life_quality_score(0), economy_score(0), environment_score(0),construction_limit(static_cast<int>(settlement.getType()) + 1), // ADDED 1
                policyType(selectionPolicy -> toString())
{}

// SECOND COPY CONSTRUCTOR
Plan::Plan(const Plan& other, Settlement* sett) : plan_id(other.plan_id),  settlement(*sett),selectionPolicy((other.selectionPolicy) -> clone()), status(other.status),
                                facilities(),underConstruction(),facilityOptions(other.facilityOptions), // gives him the same "catalog" 
                                life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score),
                                construction_limit(other.construction_limit), policyType(other.policyType)
                                
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

// first copy constructor
Plan::Plan(const Plan& other) : plan_id(other.plan_id),  settlement(other.settlement),selectionPolicy((other.selectionPolicy) -> clone()), status(other.status),
                                facilities(),underConstruction(),facilityOptions(other.facilityOptions), // gives him the same "catalog" 
                                life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score),
                                construction_limit(other.construction_limit), policyType(other.policyType)
                                
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

    delete selectionPolicy; 
}

// MOVE first COPY CONSTRUCTOR
Plan::Plan(Plan&& other): plan_id(other.plan_id),  settlement(other.settlement),selectionPolicy((other.selectionPolicy) -> clone()), status(other.status),
                        facilities(),underConstruction(),facilityOptions(other.facilityOptions), // gives him the same "catalog" 
                        life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score),
                        construction_limit(other.construction_limit), policyType(other.policyType)
                                
{
    facilities = std::move(other.facilities);

    underConstruction = std::move(other.underConstruction);
}

string Plan::getSettlementName() const
{
    return settlement.getName();
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
    // do not earase prints-  is not debug print - this is the output for the action according to instructions.
    std:: cout<< plan_id << std::endl;
    if((this -> selectionPolicy)->toString() == "bal")
    {
        std::cout << "previousPolicy: Balance" <<std::endl;
    }
    else if((this -> selectionPolicy)->toString() == "nve")
    {
        std::cout << "previousPolicy: Naive" <<std::endl;
    }
    else if((this -> selectionPolicy)->toString()=="eco")
    {
        std::cout << "previousPolicy: Economy" <<std::endl;
    }
    else
    {
        std::cout << "previousPolicy: Enviroment" <<std::endl;
    }
    // delete the previous selection policy.
    delete (this -> selectionPolicy); 
    
    // set the curr selection policy
    (this -> selectionPolicy) = selectionPolicy;
     if(selectionPolicy->toString() == "bal")
    {
        std::cout << "newPolicy: Balance" <<std::endl;
    }
    else if(selectionPolicy->toString() == "nve")
    {
        std::cout << "newPolicy: Naive" <<std::endl;
    }
    else if(selectionPolicy->toString()=="eco")
    {
        std::cout << "newPolicy: Economy" <<std::endl;
    }
    else
    {
        std::cout << "newPolicy: Enviroment" <<std::endl;
    }
}

void Plan :: step()
{
    if (status == PlanStatus ::AVALIABLE)
    {
        while(underConstruction.size() < construction_limit )
        {
            const FacilityType& facil =  selectionPolicy -> selectFacility(facilityOptions);
            Facility* f = new Facility(facil, settlement.getName());
            addFacility(f); 
        }
        status  = PlanStatus :: BUSY; 
    }
   
    for (size_t i = 0; i < underConstruction.size(); )  // Notice we don't increment i manually here
    {
        if (underConstruction[i] -> step() == FacilityStatus::OPERATIONAL)
        {
            facilities.push_back(underConstruction[i]);
            life_quality_score += underConstruction[i] -> getLifeQualityScore();
            economy_score += underConstruction[i] -> getEconomyScore();
            environment_score += underConstruction[i] -> getEnvironmentScore();
            underConstruction.erase(underConstruction.begin() + i);
            selectionPolicy->setParam(life_quality_score,economy_score,environment_score); // update the policy pram according to the plan pram.
            
            // Don't increment i since we want to check the next element which moved into the current position
        }
        else
        {
            i++;  // Increment i only when we don't erase
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
    oss << "Plan ID< " << plan_id << ">"<<"\n";

    // ---------- print settelment name and type + selection policy ----- //
    oss  << "SettlementName <"<< settlement.getName() << ">"<<"\n";    
    
    
    // ---------- print plan status ----------- //
    switch (status)
    {
        case PlanStatus :: AVALIABLE:
        {
            oss << "PlanStatus: " << "AVALIABLE" << ">"<<"\n"; 
            break;
        }
        case PlanStatus :: BUSY : 
        {
            oss << "PlanStatus< " << "BUSY" << ">"<<"\n"; 
            break;
        }  
    }

    // --------- selectionPolicy --------- //
    oss << "SelectionPolicy: " << selectionPolicy -> toString()<<"\n"; 
    
    // -------- print life,economy,enviroment _ score ----------- //
    oss << "LifeQualityScore< " << life_quality_score << ">"<<"\n";
    oss << "EconomyScore<" << economy_score << ">"<<"\n";
    oss << "EnvironmentScore<" << environment_score << ">"<<"\n";

    // --------- print facilities on OPERATION --------- //
    oss << "-------------------------------------------------------\n";
    oss << "Opertional Facilities:\n";
    
    for (const auto* facility : facilities) 
    {
        if (facility) 
        {
            oss << "FacilityName< " << facility->getName() << ">"<<"\n";
            oss << "FacilityStatus<" << facility->strGetStatus() << ">"<<"\n";
        }
    }
    
    // --------- print facilities UNDERCONSTRUCTION --------- //
     oss << "------------------------------------------------------\n";
    oss << "Facilities UNDERCONSTRUCTION:\n";
    for (const auto* facility : underConstruction) 
    {
        if (facility) 
        {
           oss << "FacilityName< " << facility->getName() << ">"<<"\n";
           oss << "FacilityStatus<" << facility->strGetStatus() << ">"<<"\n";
        }
    }
    
    return oss.str();  
}



const string Plan::getPolicyType() const
{ 
   return policyType;
}
    
