#pragma once

struct ValType {
  enum class Kind {
    Int,
    UInt,
    Float
  };

  Kind kind;
  int bitwidth;
};