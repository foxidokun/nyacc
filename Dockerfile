FROM alpine:latest
RUN apk --no-cache add clang cmake make fish flex flex-dev bison musl-dev llvm18 llvm18-dev llvm18-static llvm18-gtest llvm18-libs llvm18-linker-tools llvm18-test-utils llvm18-test-utils-pyc git
COPY . /code
RUN cd /code && rm -rf build && mkdir build && cd build && cmake .. && make -j16

WORKDIR /code
CMD /usr/bin/fish