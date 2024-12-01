# Please implement your Makefile rules and targets below.
all: clean link
#link: compile
#		g++ -o bin/main bin/main.o bin/Auxiliary.o

link: 
		g++ -g -Wall -Weffc++ -std=c++11 -Iinclude \
		src/Auxiliary.cpp \
		src/Settlement.cpp src/FacilityType.cpp src/Facility.cpp \
		src/BalancedSelection.cpp src/EconomySelection.cpp src/NaiveSelection.cpp src/SustainabilitySelection.cpp \
		src/Plan.cpp src/Simulation.cpp \
		src/BaseAction.cpp src/AddFacility.cpp src/AddPlan.cpp src/AddSettlement.cpp \
		src/BackupSimulation.cpp src/ChangePlanPolicy.cpp src/Close.cpp  \
		src/PrintActionLog.cpp src/PrintPlanStatus.cpp src/RestoreSimulation.cpp src/SimulateStep.cpp  \
		src/main.cpp -o my_program
		

#compile: src/main.cpp src/Auxiliary.cpp include
#		g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp 
#		g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Auxiliary.o src/Auxiliary.cpp

clean: 
		rm -rf bin/*
		
# Customize this file to define how to build your project.