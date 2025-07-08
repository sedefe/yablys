#pragma once

#include <filesystem>
#include <string>

enum class FileType { kLp, kMps, kUnknown };

FileType extension2FileType(const std::filesystem::path& ext) {
    if (ext == ".lp") {
        return FileType::kLp;
    }
    if (ext == ".mps") {
        return FileType::kMps;
    }
    return FileType::kUnknown;
}
