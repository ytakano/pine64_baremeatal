TOOL_PREFIX=aarch64-linux-gnu
CC=${TOOL_PREFIX}-gcc
OBJCOPY=${TOOL_PREFIX}-objcopy
CFLAGS = \
	-fpic -Wall -fno-common -fno-builtin -ffreestanding -nostdinc	\
	-fno-strict-aliasing -fno-stack-protector -fno-toplevel-reorder	\
	-Wstrict-prototypes -Wno-format-nonliteral -Wno-format-security -nostdlib
#CFLAGS = \
#	-marm -fpic -Wall -fno-common -fno-builtin -ffreestanding -nostdinc	\
#	-fno-strict-aliasing -mno-thumb-interwork -fno-stack-protector -fno-toplevel-reorder	\
#	-Wstrict-prototypes -Wno-format-nonliteral -Wno-format-security -nostdlib

SRC = main.c

TARGET = serial
SD_CARD_PATH = /dev/sdb

all: ${TARGET}.sunxi
${TARGET}.sunxi	: ${SRC}
	${CC} ${CFLAGS} ${SRC} -o ${TARGET}.elf -T ${TARGET}.lds -Wl,-N
	${OBJCOPY} -O binary ${TARGET}.elf ${TARGET}.bin
	mksunxiboot ${TARGET}.bin ${TARGET}.sunxi

write	:${TARGET}.sunxi
	sudo dd if=${TARGET}.sunxi of=${SD_CARD_PATH} bs=1024 seek=8
	sudo sync; sudo sync; sudo sync;

transfer:
	sunxi-fel -l
	sunxi-fel -v spl ${TARGET}.sunxi

clean	:
	rm -f ${TARGET}.elf ${TARGET}.bin ${TARGET}.sunxi


