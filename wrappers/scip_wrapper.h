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

    void Read(const std::string &model_path) { SCIPreadProb(scip, model_path.c_str(), NULL); }
    Result Solve() {
        SCIPsolve(scip);

        return Result{SCIPgetStatus(scip), SCIPgetPrimalbound(scip)};
    }

    ~ScipWrapper() { SCIPfree(&scip); }

   private:
    SCIP *scip;
};
