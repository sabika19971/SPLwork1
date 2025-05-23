#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
using std::vector;
using std::string;


enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy* selectionPolicy, const vector<FacilityType> &facilityOptions);
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy* selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*>& getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
        const int getPlanId() const;
        const string getPolicyType() const;
        
        // WE ADDED
        string getSettlementName() const;
        Plan(const Plan& other, Settlement* sett);
        const vector<Facility*>& getUnderConstructionFacilities();

        // Rule of 3
        Plan(const Plan& other);
        ~Plan();
        Plan& operator=(const Plan& other) = delete; // DONT NEED TO IMPLEMENT
        
        // Addition for Rule of 5
        Plan(Plan&& other); 
        Plan& operator=(Plan&& other) = delete; // DONT NEED TO IMPLEMENT

    private:
        int plan_id;
        const Settlement& settlement;
        SelectionPolicy* selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType>& facilityOptions;
        int life_quality_score, economy_score, environment_score;

        // WE ADDED
        size_t construction_limit;
        string policyType;

};