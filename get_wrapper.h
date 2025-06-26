#define CbcWrapper 1
#define HighsWrapper 2
#define ScipWrapper 3
#define CoptWrapper 4

#if SOLVER_CLASS == CbcWrapper
#undef CbcWrapper
#include "wrappers/cbc_wrapper.h"
#endif
#if SOLVER_CLASS == HighsWrapper
#undef HighsWrapper
#include "wrappers/highs_wrapper.h"
#endif
#if SOLVER_CLASS == ScipWrapper
#undef ScipWrapper
#include "wrappers/scip_wrapper.h"
#endif
#if SOLVER_CLASS == CoptWrapper
#undef CoptWrapper
#include "wrappers/copt_wrapper.h"
#endif
