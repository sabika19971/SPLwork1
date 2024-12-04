#include "../include/Action.h"

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::PENDING) {} // MAYBE WILL NEED TO CHANGE DEFAULT VALUES

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::complete()
{
    
    status = ActionStatus::COMPLETED;
    
}

void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    this -> errorMsg = errorMsg; 
}

const string& BaseAction::getErrorMsg() const
{
    return errorMsg;
}