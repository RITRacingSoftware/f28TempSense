FROM ubuntu:19.10
WORKDIR /f28ts

# Move everything in the f28 folder to the docker container file system
COPY . /f28ts

# Install required tools
RUN apt-get update
RUN apt-get install -y gcc-avr binutils-avr avr-libc make