# Define the name of the output binary
TARGET = simulation

# Define the source, include, and build directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Find all source files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Define the object files to be created in the build directory
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I$(INC_DIR) -Wall -g

# Default target: build the executable
all: $(TARGET)

# Build the executable by linking all object files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up all generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Please implement your Makefile rules and targets below.
#all: clean link
#link: compile
#		g++ -o bin/main bin/main.o bin/Auxiliary.o

#link: 
#		g++ -g -Wall -Weffc++ -std=c++11 -Iinclude \
		src/Auxiliary.cpp \
		src/Settlement.cpp src/FacilityType.cpp src/Facility.cpp \
		src/BalancedSelection.cpp src/EconomySelection.cpp src/NaiveSelection.cpp src/SustainabilitySelection.cpp \
		src/Plan.cpp \
		src/BaseAction.cpp src/AddFacility.cpp src/AddPlan.cpp src/AddSettlement.cpp \
		src/BackupSimulation.cpp src/ChangePlanPolicy.cpp src/Close.cpp  \
		src/PrintActionLog.cpp src/PrintPlanStatus.cpp src/RestoreSimulation.cpp src/SimulateStep.cpp  \
		src/Simulation.cpp  src/main.cpp  -o my_program
		

#compile: src/main.cpp src/Auxiliary.cpp include
#		g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp 
#		g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Auxiliary.o src/Auxiliary.cpp

#clean: 
#		rm -rf bin/*
		
# Customize this file to define how to build your project.