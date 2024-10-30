# Use Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set noninteractive mode
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && apt-get install -y \
    curl        \
    wget        \
    xz-utils    \
    gcc         \
    g++         \
    make        \
    make        \
    git         \
    python3     \
    && rm -rf /var/lib/apt/lists/* 

# Define environment variables
ENV TOOLCHAIN_URL=https://releases.linaro.org/components/toolchain/binaries/7.4-2019.02/aarch64-linux-gnu/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz \
    TOOLCHAIN_DIR=/opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu

# Download and extract the toolchain
RUN curl -SL ${TOOLCHAIN_URL} | tar -xJC /opt

# Add the toolchain binaries to the PATH
ENV PATH=${TOOLCHAIN_DIR}/bin:$PATH

ENV CMAKE_URL=https://cmake.org/files/v3.23/cmake-3.23.0-linux-x86_64.tar.gz
RUN curl -SL ${CMAKE_URL} | tar -xzC /usr/local && ln -s /usr/local/cmake-3.23.0-linux-x86_64/bin/cmake /usr/local/bin/cmake
ENV PATH=/usr/local/cmake-3.23.0-linux-x86_64/bin:$PATH

# Set working directory
WORKDIR /workspace

# Command to run when the container starts
CMD ["bash"]