#!/bin/sh
cmake -S /hangbag -B /hangbag/build
make -C /hangbag/build $1
