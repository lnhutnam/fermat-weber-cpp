#include "../include/model.h"
#include "../include/example.h"
#include <iostream>

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        std::cout << "[Error] - Invalid number of parameters" << std::endl;
        std::cout << "[Usage] - ./executable instance_type model_type" << std::endl;
        return -1;
    }

    ProblemInstance problemInstance;

    int instanceNumber = atoi(argv[1]);
    switch (instanceNumber) {
        case 1:
            problemInstance = createProblemOne();
            break;
        case 2:
            problemInstance = createProblemTwo();
            break;
        case 3:
            problemInstance = createProblemThree();
            break;
        default:
            std::cout << "[Error] - Invalid instance number" << std::endl;
            return -1;
    }
    
    try {
        // Create an optimization environment
        GRBEnv env = GRBEnv(true);
        env.set("LogFile", "fermat-weber.log");
        env.start();

        int modelType = atoi(argv[2]);
        GRBModel model = (modelType == 1)
            ? createOriginalModel(env, problemInstance.coordinates, problemInstance.edges)
            : createMaculanModel(env, problemInstance.coordinates.size(), problemInstance.coordinates);

        // Write the model to a file for inspection
        model.write("optimization_model.lp");

        // Solve the optimization problem
        model.optimize();

        // Print optimization results
        int totalPoints = problemInstance.coordinates.size();
        std::cout << "Optimization Results:" << std::endl;
        std::cout << "Facility Locations:" << std::endl;
        for (int i = 0; i < totalPoints - 2; i++) {
            for (int j = 0; j < 2; j++) {  
                std::string varName = "x_{" + std::to_string(totalPoints + i + 1) + ',' + std::to_string(j + 1) + '}';
                std::cout << "  " << varName << ": " 
                          << model.getVarByName(varName).get(GRB_DoubleAttr_X) << std::endl;        
            }
        }

        std::cout << "\nAssignment Variables:" << std::endl;
        GRBVar* vars = model.getVars();
        for (int i = 0; i < model.get(GRB_IntAttr_NumVars); i++) {
            if (vars[i].get(GRB_StringAttr_VarName).at(0) == 'y' && vars[i].get(GRB_DoubleAttr_X) > 0) {
                std::cout << "  " << vars[i].get(GRB_StringAttr_VarName) << ": " 
                          << vars[i].get(GRB_DoubleAttr_X) << std::endl;
            }
        }

    } catch (GRBException e) {
        std::cout << "Optimization Error:" << std::endl;
        std::cout << "  Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "  Error Message: " << e.getMessage() << std::endl;
    } catch (...) {
        std::cout << "Unexpected error during optimization" << std::endl;
    }

    return 0;
}
