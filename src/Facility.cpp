#include "../include/Facility.h"


Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price,
                  const int lifeQuality_score, const int economy_score, const int environment_score) :
                  FacilityType(name, category,price, lifeQuality_score,economy_score, environment_score),
                  settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price)
                  {}

Facility :: Facility(const FacilityType& type, const string& settlementName):
                    FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(type.getCost())
                    {}

const string& Facility::getSettlementName() const
{
  return settlementName;
}

const int Facility :: getTimeLeft() const
{
  return timeLeft;
}

FacilityStatus Facility:: step()
{
  timeLeft= timeLeft-1;
  if(timeLeft == 0)
  {
      status= FacilityStatus :: OPERATIONAL;
  }
  return status;
}

void Facility:: setStatus(FacilityStatus status)
{
  (*this).status = status; // same as this->status
}

const FacilityStatus& Facility :: getStatus() const
{
  return status;
}

Facility* Facility::clone() const
{
  return new Facility(*this);
}

const string Facility:: toString() const
{
  std::stringstream ss;
  
    ss << "Facility Information:\n"
    << "Name: " << name << "\n"
    << "Settlement Name: " << settlementName << "\n"
    << "Category: " << this->strGetCategory() << "\n"
    << "Price: " << price << "\n"
    << "Life Quality Score: " << lifeQuality_score << "\n"
    << "Economy Score: " << economy_score << "\n"
    << "Environment Score: " << environment_score << "\n"
    << "Time Left: " << timeLeft;
    return ss.str();
}
                    