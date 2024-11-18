#pragma once

#include <string>

class Expression {
  public:
    virtual std::string format() const = 0;
    virtual ~Expression() = default;
};