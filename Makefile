#*
#* _COPYRIGHT_
#*
#* File Name: Makefile
#* System Environment: GNU/Linux
#* Created Time: 2013-01-14
#* Author: Johan
#* E-mail: Johaness@qq.com
#* Description: 
#*
#*

CC = gcc
AR = ar

LDFLAGS = `pkg-config --cflags --libs gstreamer-0.10 glib-2.0 gthread-2.0`
INC_PATH = -I/usr/local/include/upnp
LIB_PATH = -L/usr/local/lib
PARAMETER = ${INC_PATH} ${LIB_PATH} -lupnp -lthreadutil -lixml

SRC = ${PWD}/Src

OBJS = Util.o FileHandle.o Actions.o Device.o Debug.o Core.o

#PROGS = Media
PROGS = Main

LIBRADIO = lib${PROGS}.a

all: 	${OBJS} ${LIBRADIO} ${PROGS}
	mv *.o ./tmp/

Util.o:
	${CC} -c ${SRC}/Util.c ${INC_PATH}

FileHandle.o:
	${CC} -c ${SRC}/FileHandle.c ${INC_PATH}

Actions.o:
	${CC} -c ${SRC}/Actions.c ${INC_PATH} ${LDFLAGS}

Device.o:
	${CC} -c ${SRC}/Device.c ${INC_PATH}

Debug.o:
	${CC} ${LDFLAGS} -c ${SRC}/Debug.c

Core.o:
	${CC} ${LDFLAGS} -c ${SRC}/Core.c

Main:
	${CC} ${SRC}/Main.c ${OBJS} -o ${PROGS} ${PARAMETER} ${LDFLAGS}

${LIBRADIO}:
	${AR} rs ${PWD}/Lib/${LIBRADIO} ${OBJS}

.PHONY : clean

clean:
	rm -f ${PROGS} ${OBJS} ${LIBRADIO}
	rm -fr ./Lib/*
	rm -f ./tmp/*
