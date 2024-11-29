#include "../include/Simulation.h"
#include <fstream>
#include <iostream>


Simulation::Simulation(const string& configFilePath)
{
    planCounter = 0;
    std::ifstream file(configFilePath);
    string line;
 
    while (std::getline(file,line))
    {
        vector<string> arguments = Auxiliary::parseArguments(line); // Parsing a specific line
        if (arguments[0] == "settlement")
        {
            settlements.push_back(new Settlement(arguments[1], static_cast<SettlementType>(std::stoi(arguments[2]))));
        }
        else if (arguments[0] == "facility")
        {
            facilitiesOptions.push_back(FacilityType(arguments[1], static_cast<FacilityCategory>(std::stoi(arguments[2])),
                                        std::stoi(arguments[3]), std::stoi(arguments[4]), std::stoi(arguments[5]),
                                        std::stoi(arguments[6])));
        }
        else if (arguments[0] == "plan")
        {
            Settlement* temp; // DONT DELETE, temporary pointer for existing settlement, used by the Plan constructor
            for (Settlement* sett : settlements)
            {
                if (sett -> getName() == arguments [1])
                {
                    temp = sett;
                }
            }
            plans.push_back(Plan(planCounter, *temp, getPolicyInstancePointer(arguments[2]) , facilitiesOptions));
            planCounter++;
        }
    }
}


void Simulation::addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy)
{
    plans.push_back(Plan(planCounter, settlement, selectionPolicy, facilitiesOptions));
    planCounter++;
}

void Simulation::addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement* settlement)
{
    if (isSettlementExists(settlement -> getName()))
    {
        return false;
    }
    settlements.push_back(settlement);
    return true;
}

bool Simulation::addFacility(FacilityType facility)
{
    for (FacilityType facil : facilitiesOptions)
    {
        if (facil.getName() == facility.getName())
        {
            return false;
        }
    }
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isSettlementExists(const string& settlementName)
{
    for (Settlement* sett : settlements)
    {
        if (sett -> getName() == settlementName) // settlementName already exists
        {
            return true;
        }
    }
    return false;
}

Settlement& Simulation::getSettlement(const string& settlementName)
{
    for (Settlement* sett : settlements)
    {
        if (sett -> getName() == settlementName) 
        {
            return *sett;
        }
    }
    // NEED TO THROW ERROR / RETURN A DEFAULT INSTANCE OF A SETTLEMENT
}

Plan& Simulation::getPlan(const int planID)
{
    if(planID >= plans.size())
    {
        // NEED TO THROW ERROR / RETURN A DEFAULT INSTANCE OF A PLAN
    }
    return plans[planID]; // works because of the way the constructor works, planCounter starts from 0
}

void Simulation::start()
{
    std::cout << "The simulation has started" << std::endl;
    open(); 
    string userInput;
    BaseAction* action;
    while (isRunning)
    {
        std::cin >> userInput; // User Input
        vector<string> parsedInput = Auxiliary::parseArguments(userInput);
        if (parsedInput[0] == "step")
        {
            action = new SimulateStep(std::stoi(parsedInput[1]));
        }
        else if (parsedInput[0] == "plan")
        {
            action = new AddPlan(parsedInput[1], parsedInput[2]);
        }
        else if (parsedInput[0] == "settlement")
        {
            action = new AddSettlement(parsedInput[1], static_cast<SettlementType>(std::stoi(parsedInput[2])));
        }
        else if (parsedInput[0] == "facility")
        {
            action = new AddFacility(parsedInput[1], static_cast<FacilityCategory>(std::stoi(parsedInput[2])), 
                                    std::stoi(parsedInput[3]), std::stoi(parsedInput[4]), std::stoi(parsedInput[5]),
                                    std::stoi(parsedInput[6]));
        }
        else if (parsedInput[0] == "planStatus")
        {
            action = new PrintPlanStatus(std::stoi(parsedInput[1]));
        }
        else if (parsedInput[0] == "changePolicy")
        {
            action = new ChangePlanPolicy(std::stoi(parsedInput[1]), parsedInput[2]);
        }
        else if (parsedInput[0] == "log")
        {
            action = new PrintActionsLog();
        }
        else if (parsedInput[0] == "close")
        {
            action = new Close();
        }
        else if (parsedInput[0] == "backup")
        {
            action = new BackupSimulation();
        }
        else if (parsedInput[0] == "restore")
        {
            action = new RestoreSimulation();
        }

        action -> act(*this);
        delete action;
    }
}

void Simulation::step()
{
    for (Plan plan : plans)
    {
        plan.step();
    }
}

void Simulation::open()
{
    isRunning = true;
}

void Simulation::close()
{
    isRunning = false; // Stops the run of start()
    for (Plan plan : plans) // Printing results
    {
        std::cout << plan.toString() << std::endl;
    }
    // NEED TO DELETE IRRELEVENT MEMORY TO AVOID MEMORY LEAKS, THIS FUNCTION ENDS THE PROGRAM
}


// WE ADDED
SelectionPolicy* Simulation::getPolicyInstancePointer(string& threeLetters)
{
    if(threeLetters == "nve")
    {
        return new NaiveSelection();
    }
    else if (threeLetters == "eco")
    {
        return new EconomySelection();
    }
    else if (threeLetters == "env")
    {
        return new SustainabilitySelection();
    }
    else // Balanced "bal"
    {
        return new BalancedSelection(0,0,0);
    }
}