
#include "../include/Settlement.h";

Settlement:: Settlement(const string &name, SettlementType type)
    {

    }
const string& Settlement::getName() const{
        return name;
      }
        SettlementType Settlement:: getType() const{
            return type;
        }
        const string Settlement:: toString() const{
            switch(getType())
            {
            case SettlementType ::VILLAGE : return "the name is:" + name+ "VILLAGE" ;       
            case SettlementType ::METROPOLIS : return "the name is:" + name+ "METROPOLIS" ;
            case SettlementType ::CITY : return "the name is:" + name+ "CITY" ;
            }
           
        }





