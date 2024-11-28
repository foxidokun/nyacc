BUILD_PATH=$1
COMPILER="$1/nyacc"
STDLIB="$1/libnyacclib.a"

$COMPILER $2 /tmp/nyacc_out.ll && clang++ /tmp/nyacc_out.ll $STDLIB -o $3