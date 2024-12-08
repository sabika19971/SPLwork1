#pragma once
#include <vector>
#include "Facility.h"
#include <iostream>
using std::vector;
using std::string;

class SelectionPolicy {
    public:
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) = 0;
        virtual const string toString() const = 0;
        virtual SelectionPolicy* clone() const = 0;
        virtual ~SelectionPolicy() = default;
        virtual void setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) = 0;
        virtual void addParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) = 0;
    
        //----------- setters ---------------// 
        
};

class NaiveSelection: public SelectionPolicy {
    public:
        NaiveSelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        NaiveSelection *clone() const override;
        ~NaiveSelection() override = default;
        void setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
        void addParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
    private:
        int lastSelectedIndex;
};

class BalancedSelection: public SelectionPolicy {
    public:
        BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        BalancedSelection *clone() const override;
        ~BalancedSelection() override = default;
        void setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
        void addParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
        

    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;

        // WE ADDED
        int distance(const FacilityType&) const;
};

class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        EconomySelection *clone() const override;
        ~EconomySelection() override = default;
        void setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
        void addParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
        
    private:
        int lastSelectedIndex;

};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        SustainabilitySelection *clone() const override;
        ~SustainabilitySelection() override = default;
        void setParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
        void addParam (const int UlifeScore, const int UEconomyScore, const int UEnvScore) override;
    private:
        int lastSelectedIndex;
};