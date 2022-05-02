# Makefile for liblog.a 
# $Header: Makefile$
#
# Project:	
# Module:	
# Programmer:	John C. Noble
# Organization:	JHU/APL
# Host System:	SunOS 4.0.1
# Date Created: 03-01-93
# Modifications:
#	$Log$
# 
# 

# Library to make (eg: libeg.a)
LIBRARY = libsock.a 
# Program for testing LIBRARY (eg: egtest)
# Directory name where this code resides
PROJECT_ROOT	= ../../..
BIN		= $(PROJECT_ROOT)/bin
LIB		= $(PROJECT_ROOT)/lib
INCLUDE		= $(PROJECT_ROOT)/include
PROGRAM = try

DEBUG	= DEBUG
VERSION	= BSD
CFLAGS	= -g -D$(DEBUG) -D$(VERSION) -I$(INCLUDE)
CC	= cc $(CFLAGS)
AR	= ar cr

README	= Readme
MAKEFILE = Makefile

# Source files for LIBRARY routines (don't include the test PROGRAM.c)
SRC	= setup_server.c \
		setup_client.c

# Object modules for LIBRARY (don't include the test PROGRAM.o)
OBJ	= setup_server.o \
		setup_client.o

# Other LIBS needed to compile the test PROGRAM (eg: /usr/local/lib/libother.a)
LIBS	= 
# How they are invoked on the compile line (eg: -lspecial)
LLIBS	= 

SRCS	= $(SRC)

.c.o:
	$(CC) -c $<

it: $(LIBRARY) 

all: local_side1 local_side2 remote_side1 remote_side2 tags

#
# some test programs
#
test_server: test_server.o $(LIBRARY)
	$(CC) $(CFLAGS) test_server.o $(LIBRARY) -o test_server -lsocket -lnsl

test_client: test_client.o $(LIBRARY)
	$(CC) $(CFLAGS) test_client.o $(LIBRARY) -o test_client -lsocket -lnsl

local_side1: $(LIBRARY) local_side1.o
	$(CC) $(CFLAGS) local_side1.o $(LIBRARY) -o local_side1

local_side2: $(LIBRARY) local_side2.o
	$(CC) $(CFLAGS) local_side2.o $(LIBRARY) -o local_side2

remote_side1: $(LIBRARY) remote_side1.o
	$(CC) $(CFLAGS) remote_side1.o $(LIBRARY) -o remote_side1

remote_side2: $(LIBRARY) remote_side2.o
	$(CC) $(CFLAGS) remote_side2.o $(LIBRARY) -o remote_side2

install: $(LIB)/$(LIBRARY)
$(LIB)/$(LIBRARY): $(LIBRARY)
	cp $(LIBRARY) $(LIB)
	ranlib $(LIB)/$(LIBRARY)

$(PROGRAM): $(OBJ) $(LIBS) $(LIBRARY) $(PROGRAM).o
	$(CC) $(PROGRAM).o $(LIBRARY) -o $(PROGRAM)

$(LIBRARY): $(OBJ)
	$(AR) $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)

$(OBJ): $(HDR) $(MAKEFILE)

$(SRCS):
	co $@

tags: $(HDR) $(SRCS)
	ctags $(HDR) $(SRCS)

clean cleanup:
	rm -f $(PROGRAM).o $(OBJ) core a.out mon.out gmon.out 

bare: clean
	rm -f $(LISTING) $(PROFILE) $(XREF)

depend: $(SRCS)
	rm -f dependlist;
	for i in $(SRC); do $(CC) -M -I$(INCLUDE) $$i >> dependlist; done
	sed -e '1,/^# DO NOT DELETE/!d' Makefile > /tmp/mm.tmp
	cat dependlist >> /tmp/mm.tmp
	mv /tmp/mm.tmp Makefile
	rm -f dependlist

# DO NOT DELETE THIS LINE - make depend uses it
setup_server.o: setup_server.c /usr/include/unistd.h \
 /usr/gcc/10/lib/gcc/x86_64-pc-solaris2.11/10.2.0/include-fixed/sys/feature_tests.h \
 /usr/include/sys/ccompile.h /usr/include/sys/note.h \
 /usr/include/sys/isa_defs.h /usr/include/sys/types.h \
 /usr/include/sys/machtypes.h /usr/include/ia32/sys/machtypes.h \
 /usr/include/sys/int_types.h /usr/include/sys/select.h \
 /usr/include/sys/time_impl.h /usr/include/sys/time.h /usr/include/time.h \
 /usr/include/iso/time_iso.h /usr/include/sys/timespec_util.h \
 /usr/include/sys/types32.h /usr/include/sys/unistd.h \
 /usr/include/strings.h /usr/include/string.h \
 /usr/include/iso/string_iso.h ../../../include/socket_utils.h \
 /usr/include/errno.h /usr/include/sys/errno.h \
 /usr/gcc/10/lib/gcc/x86_64-pc-solaris2.11/10.2.0/include-fixed/stdio.h \
 /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h \
 /usr/include/stdio_tag.h /usr/include/stdio_impl.h \
 /usr/include/iso/stdio_c99.h /usr/include/sys/file.h \
 /usr/include/sys/t_lock.h /usr/include/sys/machlock.h \
 /usr/include/sys/param.h /usr/include/sys/mutex.h \
 /usr/include/sys/rwlock.h /usr/include/sys/semaphore.h \
 /usr/include/sys/condvar.h /usr/include/sys/socket.h \
 /usr/include/sys/uio.h /usr/include/sys/uio_impl.h \
 /usr/include/sys/socket_impl.h /usr/include/sys/un.h \
 /usr/include/net/if_dl.h /usr/include/sys/netconfig.h \
 /usr/include/netinet/in.h /usr/include/sys/stream.h \
 /usr/include/sys/poll.h /usr/include/sys/cred.h \
 /usr/include/sys/refstr.h /usr/include/sys/model.h \
 /usr/include/sys/byteorder.h /usr/include/sys/sock_flow_sla.h \
 /usr/include/netdb.h /usr/include/paths.h /usr/include/sys/paths.h
setup_client.o: setup_client.c /usr/include/unistd.h \
 /usr/gcc/10/lib/gcc/x86_64-pc-solaris2.11/10.2.0/include-fixed/sys/feature_tests.h \
 /usr/include/sys/ccompile.h /usr/include/sys/note.h \
 /usr/include/sys/isa_defs.h /usr/include/sys/types.h \
 /usr/include/sys/machtypes.h /usr/include/ia32/sys/machtypes.h \
 /usr/include/sys/int_types.h /usr/include/sys/select.h \
 /usr/include/sys/time_impl.h /usr/include/sys/time.h /usr/include/time.h \
 /usr/include/iso/time_iso.h /usr/include/sys/timespec_util.h \
 /usr/include/sys/types32.h /usr/include/sys/unistd.h \
 /usr/include/strings.h /usr/include/string.h \
 /usr/include/iso/string_iso.h ../../../include/socket_utils.h \
 /usr/include/errno.h /usr/include/sys/errno.h \
 /usr/gcc/10/lib/gcc/x86_64-pc-solaris2.11/10.2.0/include-fixed/stdio.h \
 /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h \
 /usr/include/stdio_tag.h /usr/include/stdio_impl.h \
 /usr/include/iso/stdio_c99.h /usr/include/sys/file.h \
 /usr/include/sys/t_lock.h /usr/include/sys/machlock.h \
 /usr/include/sys/param.h /usr/include/sys/mutex.h \
 /usr/include/sys/rwlock.h /usr/include/sys/semaphore.h \
 /usr/include/sys/condvar.h /usr/include/sys/socket.h \
 /usr/include/sys/uio.h /usr/include/sys/uio_impl.h \
 /usr/include/sys/socket_impl.h /usr/include/sys/un.h \
 /usr/include/net/if_dl.h /usr/include/sys/netconfig.h \
 /usr/include/netinet/in.h /usr/include/sys/stream.h \
 /usr/include/sys/poll.h /usr/include/sys/cred.h \
 /usr/include/sys/refstr.h /usr/include/sys/model.h \
 /usr/include/sys/byteorder.h /usr/include/sys/sock_flow_sla.h \
 /usr/include/netdb.h /usr/include/paths.h /usr/include/sys/paths.h
