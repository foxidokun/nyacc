nuacc is `nya`-fied C-like lang compiler for formal lang course. Yes, we are cooked 

**Under delopment right now**

Curreent usage: `nyacc <input file> <output ir file>`

Current possibilities: 
```
f64 entry(i64 shift);

void out(str val);

void fun() {
  return;
}

i64 sum(f64 x, f64 y) {
  return x + y;
}

f64 entry(i64 shift) {
  str xxx = "xxx";
  f64 b = 6;
  i32 x = 4;
  i64 a = x + b;
  f64 res = a + 9.5;
  i64 temp = 2;
  res = res + sum(2, temp);
  out(xxx);
  out("AYAYA");
  return res + shift;
}
```

where `out` is from c++ file
```
extern "C" void out(const char* str) {
  fmt::println("OUT: {}", str);
}
```