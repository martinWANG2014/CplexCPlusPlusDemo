// must define the IL_STD marco for current standard c++ version rather than older one. 
#undef IL_STD
#define IL_STD

#include <iostream>
#include <sstream>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() {
    // cplex environment, declare only once time, release it at the end of program.
    IloEnv env;
    // cplex model
    IloModel model(env);
    // decision variables
    IloNumVarArray x(env);
    int size = 2;
    // variables x0 x1
    for (int i = 0; i < size; i++) {
        stringstream name;
        name << "x(" << i << ")";
        x.add(IloBoolVar(env, 0, 1, name.str().c_str()));
    }
    // constraints
    // x0 + x1 <= 1
    IloExpr constraint1(env);
    constraint1 += x[0];
    constraint1 += x[1];
    model.add(constraint1 <= 1);

    // x0 - x1 >= 1
    IloExpr constraint2(env);
    constraint2 += x[0];
    constraint2 += -x[1];
    model.add(constraint2 >= 0);

    // function objective
    // max 2*x0+3*x1
    IloExpr obj(env);
    for (int i = 0; i < size; i++) {
        obj += (i + 2) * x[i];
    }
    model.add(IloMaximize(env, obj));

    //define a solver for the constructed model.
    IloCplex solver(model);

    // set the output as stdout
    solver.setOut(std::cout);

    // use one single thread.
    solver.setParam(IloCplex::Threads, 1);

    // now , solve the model
    solver.solve();

    // export the model.
    solver.exportModel("model.lp");

    // export the solution.
    solver.writeSolution("sol.sl");

    // get the function objective value.
    double objective_value = solver.getObjValue();

    //get the decision variables values.
    IloNumArray value_variables(env);
    solver.getValues(value_variables, x);

    //release all the allocated resources
    model.end();
    solver.end();
    obj.end();

    std::cout << "Result: " << objective_value << std::endl;
    return 0;
}
