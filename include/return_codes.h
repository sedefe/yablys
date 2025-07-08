#pragma once

enum class ReturnCode {
    kUnknown = -1,
    kOptimal = 0,
    kInfeasible = 1,
    kUnbounded = 2,
    kInfOrUnb = 3,
    kTimeout = 4,
};
