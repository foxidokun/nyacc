#include <cstdint>
#include <cstring>
#include <fmt/base.h>
#include <fmt/format.h>
#include <iostream>
#include <string>

using str = const char*;

// PRIVATE

static str strdup(const std::string& val) {
  auto storage = new char[val.size() + 1];
  memcpy(storage, val.c_str(), val.size() + 1);
  return storage;
}

template<typename T>
static void _print(T val) {
  fmt::print("{}", val);
}

template<typename T>
static void _println(T val) {
  fmt::println("{}", val);
}

template<typename T>
static T _in() {
  fmt::print("Input: ");
  T val;
  std::cin >> val;
  return val;
}

template<>
str _in<str>() {
  fmt::print("Input: ");
  std::string val;
  std::getline(std::cin, val);
  return strdup(val);
}

template<typename T>
str _format(str format, T val) {
  return strdup(fmt::format(fmt::runtime(format), val));
}

// PUBLIC

#define CREATE_PRINT_WRAPPER(extern_name, print_inner, type) \
extern "C" void extern_name (type val) { \
  print_inner(val); \
}

CREATE_PRINT_WRAPPER(print_s, _print, str)
CREATE_PRINT_WRAPPER(print_d, _print, double)
CREATE_PRINT_WRAPPER(print_i, _print, int64_t)
CREATE_PRINT_WRAPPER(print_u, _print, uint64_t)

CREATE_PRINT_WRAPPER(println_s, _println, str)
CREATE_PRINT_WRAPPER(println_d, _println, double)
CREATE_PRINT_WRAPPER(println_i, _println, int64_t)
CREATE_PRINT_WRAPPER(println_u, _println, uint64_t)

#define CREATE_IN_WRAPPER(extern_name, rettype) \
extern "C" rettype extern_name () { \
  return _in<rettype> (); \
}

CREATE_IN_WRAPPER(in_s, str)
CREATE_IN_WRAPPER(in_d, double)
CREATE_IN_WRAPPER(in_i, int64_t)
CREATE_IN_WRAPPER(in_u, uint64_t)

#define CREATE_FORMAT_WRAPPER(extern_name, type) \
extern "C" void extern_name (str format, type val) { \
  _format<type> (format, val); \
}

CREATE_FORMAT_WRAPPER(format_s, str);
CREATE_FORMAT_WRAPPER(format_d, double);
CREATE_FORMAT_WRAPPER(format_i, int64_t);
CREATE_FORMAT_WRAPPER(format_u, uint64_t);

extern "C" str concat(str a, str b) {
  return strdup(fmt::format("{}{}", a, b));
}

extern "C" void strfree(str val) {
  delete val;
}