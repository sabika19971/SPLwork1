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

//#include "Action.h" // New
/*
class BaseAction;
class SimulateStep;
class SelectionPolicy;
class AddPlan;
class AddSettlement;
class AddFacility;
class PrintPlanStatus;
class ChangePlanPolicy;
class PrintActionsLog;
class Close;
class BackupSimulation;
class RestoreSimulation;
*/

class Simulation {
    public:
        Simulation(const string &configFilePath);
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement &getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();

        // WE ADDED
        SelectionPolicy* getPolicyInstancePointer(const string& threeLetters);
        const void printActionLog();

        // WE ADDED
        
        // Rule of 3
        Simulation(const Simulation& other);
        ~Simulation();
        Simulation& operator=(const Simulation& other);
        
        // Addition for Rule of 5
        Simulation(Simulation&& other); // in the end
        Simulation& operator=(Simulation&& other); // in the end


    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
        //Plan* defaultPlan; ISNT USED


};
