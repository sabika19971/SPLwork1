#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Action.h"
#include "Auxiliary.h"
using std::string;
using std::vector;


class Simulation {
    public:
/**
        * @brief inisialize the simulation from the data of the confing file.
        * @param paramName string& configFilePath 
        * @return Description of the return value or void if none.
    */Simulation(const string& configFilePath); 
        
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */ void start();
       
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */void addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy);
        
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */void addAction(BaseAction* action);
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */bool addSettlement(Settlement* settlement);    
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */bool addFacility(FacilityType facility);     
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */ bool isSettlementExists(const string& settlementName);  

/**
        * @brief return a settelment that was added to the simulation (in vectior settelments).
        * @param settlementName - get the settelment name to be found. 
        * @return if found return the settelment reference. else throw exception.
    */  Settlement& getSettlement(const string& settlementName);  
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */ Plan& getPlan(const int planID);  

/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */void step();
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */ void close();       

/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */void open();  
        

// ------------ WE ADDED-------------------
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */SelectionPolicy* getPolicyInstancePointer(const string& threeLetters);
/**
        * @brief Brief description of the function.
        * @param paramName Description of the parameter(s).
        * @return Description of the return value or void if none.
    */ const void printActionLog();

    bool isValidPolicy (const string& policyName);
   bool isFacilityExsist(const string& facilityName);
        
// ----------- Rule of 3 ---------------------
        Simulation(const Simulation& other);
        ~Simulation();
        Simulation& operator=(const Simulation& other);
        
// -------------- Addition for Rule of 5 ---------------------
        Simulation(Simulation&& other); // in the end
        Simulation& operator=(Simulation&& other); // in the end


    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions; // the catalog of facilities that can be bield 
        Settlement defaultSettlement;
        Plan defaultPlan;
         


};
