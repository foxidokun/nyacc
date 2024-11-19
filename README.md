nuacc is `nya`-fied C-like lang compiler for formal lang course. Yes, we are cooked 

**Under development right now**

### Current usage (will be simplified)
1. Build, you need llvm-18 and libfmt
2. Translate into IR with `nyacc <input file> <output ir file>`
3. Then compile with `clang++ <out ir file> libnyacclib.a -lfmt`

### Current possibilities
```
str in_s();
void println_s(str x);
str concat(str a, str b);
str format_i(str fmt, i64 v);

str format_line(i32 idx, str line) {
  str predicate = format_i("Idx {}: ", idx);
  return concat(predicate, line);
}

i64 main() {
  str hello = "Hello";
  hello = concat(hello, " ");
  str name = in_s();

  str outw = concat(concat(hello, name), "!");

  for (i32 i = 0; !(i >= 10); i = i + 1) {
    println_s(format_line(i + 1, outw));
  }

  return 0;
}

```

where top definitions is from nyacc's stdlib (it has way more functions)