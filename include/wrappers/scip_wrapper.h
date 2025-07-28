#include <scip/scip.h>
#include <scip/scipdefplugins.h>

#include "abstract_wrapper.h"

class ScipWrapper : public AbstractWrapper {
   public:
    ScipWrapper() {
        scip = NULL;
        SCIPcreate(&scip);
        SCIPincludeDefaultPlugins(scip);
    }

    std::string GetVersion() const {
        return std::string("SCIP-") + std::to_string(SCIP_VERSION_MAJOR) + '.' +
               std::to_string(SCIP_VERSION_MINOR) + '.' + std::to_string(SCIP_VERSION_PATCH);
    }

    void Read(const std::string &model_path, FileType ft) {
        SCIPreadProb(scip, model_path.c_str(), NULL);
    }
    Result Solve(double timeout) {
        SCIPsetRealParam(scip, "limits/time", timeout);
        SCIPsolve(scip);

        return Result{SCIPgetStatus(scip), SCIPgetPrimalbound(scip), SCIPgetDualbound(scip)};
    }

    ReturnCode GetCode(int status) {
        switch (status) {
            case SCIP_STATUS_OPTIMAL:
                return ReturnCode::kOptimal;
            case SCIP_STATUS_INFEASIBLE:
                return ReturnCode::kInfeasible;
            case SCIP_STATUS_UNBOUNDED:
                return ReturnCode::kUnbounded;
            case SCIP_STATUS_INFORUNBD:
                return ReturnCode::kInfOrUnb;
            default:
                return ReturnCode::kUnknown;
        }
    }

    ~ScipWrapper() { SCIPfree(&scip); }

   private:
    SCIP *scip;
};
