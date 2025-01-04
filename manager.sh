#!/bin/bash

build_module () {
    scons
}

clean_module() {
    cd src
    rm -f *.os
}

build_test_library () {
    cd testlib
    make testlib.so
    cd ..
    cp testlib/testlib.so demo/bin/testlib.so
}

clean_test_library() {
    rm -f demo/bin/testlib.so
}

execute_gd_test () {
    cd demo
    godot --no-window --headless --script test.gd
}

case "$1" in
  build_testlib)
    build_test_library
    ;;
  test_gd)
    execute_gd_test
    ;;
  *)
    echo "Invalid command."
    ;;
esac
