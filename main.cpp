#undef IL_STD
#define IL_STD

#include <iostream>
#include <sstream>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() {
    IloEnv env;
    IloModel model(env);
    IloNumVarArray x(env);
    int size = 2;
    //variables x0 x1
    for (int i = 0; i < size; i++) {
        stringstream name;
        name << "x(" << i << ")";
        x.add(IloBoolVar(env, 0, 1, name.str().c_str()));
    }
    //constraints
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


    //objective
    // max 2*x0+3*x1
    IloExpr obj(env);
    for (int i = 0; i < size; i++) {
        obj += (i + 2) * x[i];
    }
    model.add(IloMaximize(env, obj));
    IloCplex solver(model); // solver
    solver.setOut(std::cout); // no output
    solver.setParam(IloCplex::Threads, 2); // no multi-threading (less performance)
    solver.solve();
    solver.exportModel("model.lp");
    solver.writeSolution("sol.sl");
    double objective_value = solver.getObjValue();
    IloNumArray value_variables(env);
    solver.getValues(value_variables, x);
    model.end();
    solver.end();
    obj.end();
    std::cout << "Result: " << objective_value << std::endl;
    return 0;
}