#include <Highs.h>

#include "abstract_wrapper.h"

class HighsWrapper : public AbstractWrapper {
   public:
    HighsWrapper() { highs.setOptionValue("parallel", "off"); }

    std::string GetVersion() const { return std::string("HiGHS-") + highsVersion(); }

    void Read(const std::string &model_path, FileType ft) { highs.readModel(model_path); }
    Result Solve(double timeout) {
        highs.setOptionValue("time_limit", timeout);
        highs.run();
        double dual;
        highs.getDualObjectiveValue(dual);
        return Result{int(highs.getModelStatus()), highs.getObjectiveValue(), dual};
    }

    ReturnCode GetCode(int status) {
        switch (HighsModelStatus(status)) {
            case HighsModelStatus::kOptimal:
                return ReturnCode::kOptimal;
            case HighsModelStatus::kInfeasible:
                return ReturnCode::kInfeasible;
            case HighsModelStatus::kUnboundedOrInfeasible:
                return ReturnCode::kInfOrUnb;
            case HighsModelStatus::kUnbounded:
                return ReturnCode::kUnbounded;
            case HighsModelStatus::kTimeLimit:
            case HighsModelStatus::kIterationLimit:
                return ReturnCode::kTimeout;
            default:
                return ReturnCode::kUnknown;
        }
    }

    ~HighsWrapper() {}

   private:
    Highs highs;
};
