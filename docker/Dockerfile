FROM ubuntu:20.04

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install build-essential zsh git curl libncurses5-dev libtinfo5 gcc-arm-none-eabi u-boot-tools

COPY zshenv /root/.zshenv
COPY zshrc /root/.zshrc

ENTRYPOINT ["zsh"]
