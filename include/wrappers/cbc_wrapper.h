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
    Result Solve() {
        Cbc_solve(model);

        return Result{Cbc_status(model), Cbc_getObjValue(model)};
    }

    ~CbcWrapper() {
        if (model != nullptr) {
            Cbc_deleteModel(model);
        }
    }

   private:
    Cbc_Model *model;
};
