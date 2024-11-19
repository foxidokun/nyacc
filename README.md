nuacc is `nya`-fied C-like lang compiler for formal lang course. Yes, we are cooked 

**Under delopment right now**

Curreent usage: `nyacc <input file> <output ir file>`

Current possibilities: 
```
f64 entry(i64 shift);

i64 sum(i64 x, i64 y) {
  return x + y;
}

f64 entry(i64 shift) {
  f64 b = 6;
  i32 x = 4;
  i64 a = x + b;
  f64 res = a + 9.5;
  i64 temp = 2;
  res = res + sum(2, temp);
  return res + shift;
}
```