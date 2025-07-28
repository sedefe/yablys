#include <cbc/Cbc_C_Interface.h>

#include "abstract_wrapper.h"

class CbcWrapper : public AbstractWrapper {
   public:
    CbcWrapper() { model = nullptr; }

    std::string GetVersion() const { return std::string("CBC-") + Cbc_getVersion(); }

    void Read(const std::string &model_path, FileType ft) {
        model = Cbc_newModel();
        switch (ft) {
            case FileType::kLp:
                Cbc_readLp(model, model_path.c_str());
                break;
            case FileType::kMps:
                Cbc_readMps(model, model_path.c_str());
                break;
            default:  // todo: handle
                break;
        }
    }
    Result Solve(double timeout) {
        Cbc_setMaximumSeconds(model, timeout);
        Cbc_solve(model);

        return Result{Cbc_secondaryStatus(model), Cbc_getObjValue(model), Cbc_getBestPossibleObjValue(model)};
    }

    ReturnCode GetCode(int status) {
        switch (status) {
            case -1:
                return ReturnCode::kUnknown;
            case 0:
                return ReturnCode::kOptimal;
            case 1:
                return ReturnCode::kInfeasible;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                return ReturnCode::kTimeout;
            case 7:
                return ReturnCode::kUnbounded;
            case 8:
                return ReturnCode::kTimeout;
            default:
                return ReturnCode::kUnknown;
        }
    }

    ~CbcWrapper() {
        if (model != nullptr) {
            Cbc_deleteModel(model);
        }
    }

   private:
    Cbc_Model *model;
};
