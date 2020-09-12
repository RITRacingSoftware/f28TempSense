#! /bin/bash

docker rm f28ts
docker run --name f28ts -v $PWD:/f28ts f28ts 'make'
