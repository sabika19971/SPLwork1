#include "../include/Auxiliary.h"
/*
This is a 'static' method that receives a string(line) and returns a vector of the string's arguments.

For example:
parseArguments("settlement KfarSPL 0") will return vector with ["settlement", "KfarSPL", "0"]

To execute this method, use Auxiliary::parseArguments(line)
*/
std::vector<std::string> Auxiliary::parseArguments(const std::string& line) {
    std::vector<std::string> arguments;
    std::istringstream stream(line);
    std::string argument;

    while (stream >> argument) {
        arguments.push_back(argument);
    }

    return arguments;
}

/*
void Auxiliary::execute(Simulation& simulation, const vector<string>& parsedInput)
{
    BaseAction* action;
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
    //addAction(action); 
    action -> act(simulation);
}
*/