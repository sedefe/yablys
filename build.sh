#!/bin/bash

set -e

usage() {
  echo "Usage: $0 [OPTION]..."
  echo "       -C : use CBC"
  echo "       -S : use SCIP"
  echo "       -H : use HiGHS"
  echo "       -O : use COPT"
  exit 0
}


while getopts "CSHOR" option; do
  case $option in
  C)
    cTGT_DEF=-DUSE_CBC=ON
    ;;
  S)
    sTGT_DEF=-DUSE_SCIP=ON
    ;;
  H)
    hTGT_DEF=-DUSE_HIGHS=ON
    ;;
  O)
    oTGT_DEF=-DUSE_COPT=ON
    ;;
  *)
    usage
    ;;
  esac
done


do_make() {
  cmake -DCMAKE_BUILD_TYPE=RELEASE \
        -DCMAKE_VERBOSE_MAKEFILE=ON \
        -B build \
        "$@" \
        -S .
  cmake --build build
}

if [ "$#" -ne 1 ]; then
  usage
  exit 1
fi

do_make $TARGET_DEF $cTGT_DEF $sTGT_DEF $hTGT_DEF $oTGT_DEF
