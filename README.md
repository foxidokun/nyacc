nuacc is `nya`-fied C-like lang compiler for formal lang course. Yes, we are cooked 

### Supported functionality
- functions
- control flow (if, for, while) with C-like syntax
- types: u8..u64, i8..i64, str, void (u = unsigned, iXX means intXX_t from C, str is kinda const char *)
- compatability with C ABI => possibility of calling from both sides
- stdlib with I/O and string functions
- math (+-*/, unary minus with automatic casts to bigger types)
- logic operators (&&, ||, !, >, >=, <, <=)
- and maybe more, i forgot...

### Compiling from source
0. Probably docker is simplier, so just use it
1. You need llvm libs, flex and bison
2. Clone repo
3. Run cmake & build
```bash
cd nyacc && mkdir build && cd build
cmake ..
make -j16
cd ..
```
4. Run via Wrapper or True

### Using docker
```
docker build . -t nyacc_compiler
docker run -it --mount src="$(pwd)",target=/pwd_dir,type=bind nyacc_compiler:latest
```
Now, compile any example with wrapper or manual compilation

### Wrapper usage
```bash
./wrapper.sh [BUILD DIR] [INPUT FILE] [OUTPUT FILE]
```
Where build dir is cmake build dir
For example, to test readme example from repo directory, run
```bash
./wrapper.sh build examples/readme_example.nya ./example
./example
```

### Manual usage
1. Translate into IR with `nyacc <input file> <output ir file>`
2. Then compile with `clang++ <out ir file> libnyacclib.a (from cmake build dir)`

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

  str outw = concat(concat(hello, name), " from Cutie Development Team :3");

  for (i32 i = 0; !(i >= 10); i = i - -1) {
    println_s(format_line(i + 1, outw));
  }

  return 0;
}

```

where top definitions is from nyacc's stdlib (it has way more functions, u can see [or add yours] in stdlib/)