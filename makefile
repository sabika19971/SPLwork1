# Please implement your Makefile rules and targets below.
all: clean compile link

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/Auxiliary.cpp -o bin/Auxiliary.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/Settlement.cpp -o bin/Settlement.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/FacilityType.cpp -o bin/FacilityType.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/Facility.cpp -o bin/Facility.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/BalancedSelection.cpp -o bin/BalancedSelection.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/EconomySelection.cpp -o bin/EconomySelection.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/NaiveSelection.cpp -o bin/NaiveSelection.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/SustainabilitySelection.cpp -o bin/SustainabilitySelection.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/Plan.cpp -o bin/Plan.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/BaseAction.cpp -o bin/BaseAction.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/AddFacility.cpp -o bin/AddFacility.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/AddPlan.cpp -o bin/AddPlan.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/AddSettlement.cpp -o bin/AddSettlement.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/BackupSimulation.cpp -o bin/BackupSimulation.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/ChangePlanPolicy.cpp -o bin/ChangePlanPolicy.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/Close.cpp -o bin/Close.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/PrintActionLog.cpp -o bin/PrintActionLog.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/PrintPlanStatus.cpp -o bin/PrintPlanStatus.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/RestoreSimulation.cpp -o bin/RestoreSimulation.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/SimulateStep.cpp -o bin/SimulateStep.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/Simulation.cpp -o bin/Simulation.o
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c src/main.cpp -o bin/main.o

link:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude bin/Auxiliary.o bin/Settlement.o bin/FacilityType.o bin/Facility.o \
	bin/BalancedSelection.o bin/EconomySelection.o bin/NaiveSelection.o bin/SustainabilitySelection.o bin/Plan.o \
	bin/BaseAction.o bin/AddFacility.o bin/AddPlan.o bin/AddSettlement.o bin/BackupSimulation.o bin/ChangePlanPolicy.o \
	bin/Close.o bin/PrintActionLog.o bin/PrintPlanStatus.o bin/RestoreSimulation.o bin/SimulateStep.o bin/Simulation.o \
	bin/main.o -o bin/simulation

clean:
	rm -f bin/*.o bin/simulation	
