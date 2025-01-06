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

create_doxygen_docs () {
  doxygen Doxyfile
}
clean_doxygen_docs () {
  rm -rf ./docs
}

case "$1" in
  build_testlib)
    build_test_library
    ;;
  test_gd)
    execute_gd_test
    ;;
  doxygen)
    clean_doxygen_docs
    create_doxygen_docs
    ;;
  prep_for_publish)
    clean_module
    clean_test_library
    clean_doxygen_docs
    create_doxygen_docs
    ;;
  *)
    echo "Invalid command."
    ;;
esac