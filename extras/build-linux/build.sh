#!/bin/sh
mkdir -p dist
docker build -t moderngl-build . -f extras/build-manylinux1/Dockerfile && docker run -v `pwd`/dist:/dist moderngl-build
