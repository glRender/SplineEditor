#!/bin/sh
find src/ -iname *.h -o -iname *.cpp | xargs clang-format-6.0 -i
