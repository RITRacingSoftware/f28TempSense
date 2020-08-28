#! /bin/bash

docker rm f28ts
docker run --name f28ts -v $PWD:/at90 f28ts 'make'