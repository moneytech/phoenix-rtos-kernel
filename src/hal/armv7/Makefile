#
# Makefile for Phoenix-RTOS kernel (ARMv7 HAL)
#
# Copyright 2016-2017 Phoenix Systems
#


ifneq (, $(findstring stm32, $(TARGET)))
	ASMS = _init-stm32.S
	SRCS = stm32.c console-stm32.c interrupts-stm32.c timer-stm32.c pmap-stm32.c
else ifneq (, $(findstring imxrt, $(TARGET)))
	ASMS = _init-imxrt.S
	SRCS = interrupts-imxrt.c timer-imxrt.c pmap-imxrt.c
	ifneq (, $(findstring 1170, $(TARGET)))
		SRCS += imxrt1170.c console-imxrt1170.c
	else
		SRCS += imxrt.c console-imxrt.c
	endif
endif


ASMS +=
SRCS += spinlock.c cpu.c hal.c exceptions.c syspage.c


OBJS = $(ASMS:.S=.o) $(SRCS:.c=.o)


all: check $(ARCH)


check:
	@(if test -z "$(ARCH)"; then\
		echo "Error: Only main Makefile can be used for compilation!";\
		exit 1;\
	fi;)


.c.o:
	@(printf " CC  %-24s  " "$<"; $(CC) -c $(CFLAGS) $<)

	@(file="$@"; \
	datasz=0;\
	textsz=0;\
	rodatasz=0;\
	for i in `$(OBJDUMP) -t $$file | grep -e " O " | grep -v ".rodata" | awk '{ print $$4 }'`; do \
		datasz=`echo $$(($$datasz + 0x$$i))`;\
	done; \
	for i in `$(OBJDUMP) -t $$file | grep -e " O " | grep ".rodata" | awk '{ print $$5 }'`; do \
                rodatasz=`echo $$(($$rodatasz + 0x$$i))`;\
        done; \
	for i in `$(OBJDUMP) -t $$file | grep -e " F " | awk '{ print $$5 }'`; do \
		textsz=`echo $$(($$textsz + 0x$$i))`;\
	done;\
	printf "data=%-5d  text=%-5d  rodata=%-5d\n" $$datasz $$textsz $$rodatasz)


.S.o:
	@(printf " ASM %-24s  " "$<"; $(CC) -c $(CFLAGS) $<)

	@(file="$@"; \
	datasz=0;\
	textsz=0;\
	for i in `$(OBJDUMP) -t $$file | grep -e " O " | awk '{ print $$5 }'`; do \
		datasz=`echo $$(($$datasz + 0x$$i))`;\
	done; \
	for i in `$(OBJDUMP) -t $$file | grep -e " F " | awk '{ print $$5 }'`; do \
		textsz=`echo $$(($$textsz + 0x$$i))`;\
	done;\
	printf "data=%-5d  text=%-5d\n" $$datasz $$textsz)


-include .depend


$(ARCH): $(OBJS)
	@$(AR) $(ARFLAGS) $(ARCH) $(OBJS) 2>/dev/null


depend: check
	@$(MKDEP) $(MKDEPFLAGS) $(SRCS) >.depend


clean: check
	@rm -f core *.o $(ARCH)
