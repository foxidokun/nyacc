nuacc is `nya`-fied C-like lang compiler for formal lang course. Yes, we are cooked 

**Under delopment right now**

Curreent usage: `nyacc <input file> <output ir file>`

Current possibilities: 
```
i64 sum() {
  return 2 + 3;
}

f64 entry() {
  f64 b = 6;
  i32 x = 4;
  i64 a = x + b;
  f64 res = a + 9.5;
  res = res + 11.4;
  return res;
}
```