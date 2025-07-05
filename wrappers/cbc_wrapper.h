#include <cbc/Cbc_C_Interface.h>

#include "abstract_wrapper.h"

class CbcWrapper : public AbstractWrapper {
   public:
    CbcWrapper() {}

    std::string GetVersion() const { return std::string("CBC-") + Cbc_getVersion(); }

    void Read(const std::string &model_path) {
        model = Cbc_newModel();
        Cbc_readLp(model, model_path.c_str());
    }
    Result Solve() {
        Cbc_solve(model);

        return Result{Cbc_status(model), Cbc_getObjValue(model)};
    }

    ~CbcWrapper() { Cbc_deleteModel(model); }

   private:
    Cbc_Model *model;
};
