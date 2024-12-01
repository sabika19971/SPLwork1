#include "../include/Simulation.h"
#include <fstream>
#include <iostream>
using std::string;
using std::vector;

Simulation::Simulation(const string& configFilePath) : planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions() 
{
   
  
    
    planCounter = 1;
    std:: cout <<"constractor5"<<std::endl;
    std::ifstream file(configFilePath);
    std:: cout <<"constractor3asd"<<std::endl;
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
    Settlement* defaultS = new Settlement("000",SettlementType ::CITY); // default settlement instance
       std:: cout <<"constractor1"<<std::endl;
    Plan defaultPlan = Plan(-1,*defaultS,new NaiveSelection(), facilitiesOptions); // default plan instance
       std:: cout <<"constractor2"<<std::endl;
    settlements.insert(settlements.begin(),defaultS);
       std:: cout <<"constractor3"<<std::endl;
    plans.insert(plans.begin(),defaultPlan); // need to work on 
    std:: cout <<"constractor4"<<std::endl;
}

// COPY CONSTRUCTOR
Simulation::Simulation(const Simulation& other) : isRunning(other.isRunning), planCounter(other.planCounter),
                                                actionsLog(), plans(), settlements(), facilitiesOptions() 
{
    // actionLog - vector<BaseAction*> actionsLog - DEEP
    for (BaseAction* b : other.actionsLog) 
    {
        (this -> actionsLog).push_back(b -> clone());
    }
    
    // settlements - vector<Settlement*> settlements - DEEP
    for (Settlement* s : other.settlements)
    {
        (this -> settlements).push_back(s -> clone());
    }

    // plans - vector<Plan> plans - DEEP
    for (Plan p : other.plans)
    {
        (this -> plans).push_back(Plan(p)); // USES Plan copy constructor
    }

    // facilitiesOptions - vector<FacilityType> facilitiesOptions - DEEP
    for (FacilityType f : other.facilitiesOptions)
    {
        (this -> facilitiesOptions).push_back(FacilityType(f)); // USES FacilityType  default copy constructor 
    }
}

// OPERATOR= 
Simulation& Simulation::operator=(const Simulation& other) // OTHER = RUNNING SIMULATION
{
    if (this != &other)
    {
        (this -> isRunning) = other.isRunning;
        (this -> planCounter) = other.planCounter;
    
        // DELETE POINTERS
        for (BaseAction* b : (this -> actionsLog)) 
        {
            delete b;
        }

        for (Settlement* s : (this -> settlements))
        {
            delete s;
        }

        // DELETE VECTOR NODES
        (this -> actionsLog).clear();

        (this -> settlements).clear();
        
        (this -> plans).clear();

        (this -> facilitiesOptions).clear();

        // DEEP COPY other VECTORS
        // actionLog - vector<BaseAction*> actionsLog - DEEP
        for (BaseAction* b : other.actionsLog) 
        {
            (this -> actionsLog).push_back(b -> clone());
        }
        
        // settlements - vector<Settlement*> settlements - DEEP
        for (Settlement* s : other.settlements)
        {
            (this -> settlements).push_back(s -> clone());
        }

        // plans - vector<Plan> plans - DEEP
        for (Plan p : other.plans)
        {
            (this -> plans).push_back(Plan(p)); // USES Plan copy constructor
        }

        // facilitiesOptions - vector<FacilityType> facilitiesOptions - DEEP
        for (FacilityType f : other.facilitiesOptions)
        {
            (this -> facilitiesOptions).push_back(FacilityType(f)); // USES FacilityType default copy constructor
        }
    }
    return *this;
}

// DESTRUCTOR
Simulation::~Simulation()
{
    for (BaseAction* b : actionsLog)
    {
        delete b;
    }

    for (Settlement* s : settlements)
    {
        delete s;
    }

    // DELETE VECTOR NODES
    actionsLog.clear();

    settlements.clear();
    
    plans.clear();

    facilitiesOptions.clear();
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
    return *settlements[0]; // default instance
}

Plan& Simulation::getPlan(const int planID)
{
    if(planID >= plans.size())
    {
        return plans[0]; // default instance
    }
    return plans[planID]; 
}

void Simulation::start()
{
    std::cout << "The simulation has started" << std::endl;
    open(); // make is running to TRUE
    string userInput;
    BaseAction* action = nullptr;
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
        addAction(action); 
        
       
        
       //Auxiliary::execute(*this, parsedInput);
    }
}

const void Simulation:: printActionLog(){
    if(actionsLog.empty())
    {
        std::cout<<"no actions to print";
    }
    int i(1);
    for (BaseAction* action : actionsLog)
    {
        std::cout<< i << ")"<< action -> toString() <<"\n";
        i++;
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
}


// WE ADDED
SelectionPolicy* Simulation::getPolicyInstancePointer(const string& threeLetters)
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
