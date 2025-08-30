FROM alpine:edge
ARG CC65_PATH=/opt/cc65
ENV CC65_PATH=${CC65_PATH}

ADD https://github.com/cc65/cc65.git /opt/cc65

RUN apk add --no-cache cmake gcc make musl-dev
RUN make -C ${CC65_PATH} -j && apk del gcc musl-dev

COPY build.sh /build.sh

ENTRYPOINT ["/bin/sh", "/build.sh"]
