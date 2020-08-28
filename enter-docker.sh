#! /bin/bash

docker rm f28ts
docker run -it -v $PWD:/f28ts f28ts