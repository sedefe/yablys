#include "abstract_wrapper.h"
#include "esolver/io/controller.h"
#include "esolver/solvers/milp/milp.h"

class ReshalaWrapper : public AbstractWrapper {
   public:
    ReshalaWrapper() {}

    void Read(const std::string &model_path) {
        model = MilpModel();
        IOController::ifpath = model_path;
        IOController::LoadFromFile(model);
    }
    Result Solve() {
        MilpSolver solver(model);
        auto result = solver.Solve();

        return Result{int(result.result.status), result.result.y};
    }

    ~ReshalaWrapper() {}

   private:
    MilpModel model;
};
