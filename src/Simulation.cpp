#include "../include/Simulation.h"
#include <fstream>
#include <iostream>
using std::string;
using std::vector;

Simulation::Simulation(const string& configFilePath) : planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions() 
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

    std::cout<<" setelments are :"<<std::endl;
    for (Settlement* s : settlements)
    {
        std::cout<<s ->toString()<<std::endl;
    }

    std::cout<<" facilities options are :"<<std::endl;
    for (int i(0); i<facilitiesOptions.size(); i++)
    {
        std::cout << "facility name:"+ facilitiesOptions[i].getName()<<std::endl;
        std::cout << "facility cost:"<< facilitiesOptions[i].getCost() <<std::endl;
        std::cout << "facility economy_score:"<< facilitiesOptions[i].getEconomyScore() <<std::endl;
        std::cout << "facility enviroment_score:"<< facilitiesOptions[i].getEnvironmentScore() <<std::endl;
        std::cout << "facility quality life score:"<<facilitiesOptions[i].getLifeQualityScore() <<std::endl;
        std:: cout <<"facility category: " << facilitiesOptions[i].strGetCategory()<<std::endl;
        std::cout << "-----------------------------------------------------------------" <<std::endl; 
    }

    std::cout<<" plans are :"<<std::endl;
    for(int(i);i<plans.size();i++)
    {
        std::cout<<plans[i].toString()<<std::endl;
        
    }  
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
    plans.emplace_back(planCounter, settlement, selectionPolicy, facilitiesOptions);
    planCounter++;
    std::cout << "plans are " << std::endl;
    for(int i(0);i<plans.size();i++)
    {
        std::cout<<plans[i].toString()<<std::endl;
        std::cout <<"---------------------------" << std::endl;
    }
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
    std::cout<<" setelments are :"<<std::endl;
    for (Settlement* s : settlements)
    {
        std::cout<<s ->toString()<<std::endl;
    }
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
    std::cout<<" facilities options are :"<<std::endl;
    for (int i(0); i<facilitiesOptions.size(); i++)
    {
    std::cout << "facility name:"+ facilitiesOptions[i].getName()<<std::endl;
    std::cout << "facility cost:"<< facilitiesOptions[i].getCost() <<std::endl;
    std::cout << "facility economy_score:"<< facilitiesOptions[i].getEconomyScore() <<std::endl;
    std::cout << "facility enviroment_score:"<< facilitiesOptions[i].getEnvironmentScore() <<std::endl;
    std::cout << "facility quality life score:"<<facilitiesOptions[i].getLifeQualityScore() <<std::endl;
    std:: cout <<"facility category: " << facilitiesOptions[i].strGetCategory()<<std::endl;
    std::cout << "-----------------------------------------------------------------" <<std::endl; 
    }
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
        if (sett->getName() == settlementName) 
        {
            return *sett;
        }
    }
    throw std::runtime_error("Settlement not found: " + settlementName);
}

Plan& Simulation::getPlan(const int planID)
{
    if(planID >= plans.size() || planID < 0)
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
    bool preform = false;
    BaseAction* action = nullptr;
    while (isRunning)
    {
        std::getline (std::cin,userInput);
        vector<std::string> parsedInput = Auxiliary::parseArguments(userInput);
      
        if (parsedInput[0] == "step") 
        {
            preform = true;
            action = new SimulateStep(std::stoi(parsedInput[1]));
        }
        else if (parsedInput[0] == "plan" )
        {
               preform = true;
               action = new AddPlan(parsedInput[1], parsedInput[2]);    
        }
        else if (parsedInput[0] == "settlement")
        { 
                 preform = true;
                 action = new AddSettlement(parsedInput[1], static_cast<SettlementType>(std::stoi(parsedInput[2])));  
        }
        else if (parsedInput[0] == "facility")
        {
            preform = true;
          
            action = new AddFacility(parsedInput[1], static_cast<FacilityCategory>(std::stoi(parsedInput[2])), 
                                    std::stoi(parsedInput[3]), std::stoi(parsedInput[4]), std::stoi(parsedInput[5]),
                                    std::stoi(parsedInput[6]));
        }
        else if (parsedInput[0] == "planStatus") //not working  need to debug 
        {
            action = new PrintPlanStatus(std::stoi(parsedInput[1]));
            preform = true;
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
            preform=true;
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
        
        if(preform)
        {
            action -> act(*this);
            addAction(action);
            action = nullptr;
            preform = false;   
        }  
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
    for (Plan& plan : plans)
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

bool Simulation::isValidPolicy (const string& policyName){
    if(policyName=="nve" || policyName == "bal" || policyName=="eco"|| policyName=="env"){
        return true;
    }
    return false;
}

bool Simulation :: isFacilityExsist(const string& facilityName){
    for(int i(0);i< facilitiesOptions.size(); i++){
        if(facilitiesOptions[i].getName() ==facilityName ){
            return false;
        }
        return true;
    }
}
