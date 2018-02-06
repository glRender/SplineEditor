#pragma once

#include <string>

template <typename T>
struct Result
{
    const T value;
    const std::string description;
};
