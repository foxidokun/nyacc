#include "fmt/format.h"
#include <expressions/common.h>

class SumExpression: public Expression {
  public:
    SumExpression(int lhs, int rhs): lhs_(lhs), rhs_(rhs) {}

    std::string format() const override {
      return fmt::format("{} + {}", lhs_, rhs_);
    }

  private:
    int lhs_;
    int rhs_;
};