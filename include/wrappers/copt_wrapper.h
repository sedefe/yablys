#include <coptcpp.h>
#include <coptcpp_pch.h>
#include <envr.h>

#include "abstract_wrapper.h"

class CoptWrapper : public AbstractWrapper {
   public:
    CoptWrapper() : model(env.CreateModel("xxx")) { model.SetIntParam(COPT_INTPARAM_THREADS, 1); }

    std::string GetVersion() const {
        return std::string("COPT-") + std::to_string(COPT_VERSION_MAJOR) + '.' +
               std::to_string(COPT_VERSION_MINOR) + '.' + std::to_string(COPT_VERSION_TECHNICAL);
    }

    void Read(const std::string &model_path, FileType ft) { model.Read(model_path.c_str()); }
    Result Solve() {
        model.Solve();

        return Result{model.GetIntAttr(COPT_INTATTR_MIPSTATUS),
                      model.GetDblAttr(COPT_DBLATTR_BESTOBJ)};
    }

    ReturnCode GetCode(int status) {
        switch (status) {
            case COPT_MIPSTATUS_OPTIMAL:
                return ReturnCode::kOptimal;
            case COPT_LPSTATUS_INFEASIBLE:
                return ReturnCode::kInfeasible;
            case COPT_MIPSTATUS_UNBOUNDED:
                return ReturnCode::kUnbounded;
            case COPT_MIPSTATUS_INF_OR_UNB:
                return ReturnCode::kInfOrUnb;
            default:
                return ReturnCode::kUnknown;
        }
    }

    ~CoptWrapper() {}

   private:
    Envr env;
    Model model;
};
