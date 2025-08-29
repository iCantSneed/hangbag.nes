#!/bin/sh
sed "s|%HANGBAG_ROM%|$(gzip -c $1 | base64 -w0)|" $2 > $3
