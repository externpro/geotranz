####
# Compiler declarations
####

#Sun SPARCworks
#cc = cc
#CC = CC
#posic = -G -K pic
#COMPILER_BOOLS = -DCOMPILER_HAS_NO_BOOLEAN
#COMPILER_ISSUES = $(COMPILER_BOOLS) $(COMPILER_CASTS)

#Gnu
cc = gcc
CC = g++
posic = -shared -fPIC
COMPILER_ISSUES = $(COMPILER_CASTS)

####
# Support declarations
####

DEBUG = -g

CFLAGS = $(DEBUG)
CCFLAGS = $(CFLAGS) $(COMPILER_ISSUES)

####
# Directories
####

DTCCDIR = ../../dt_cc
ENGINEDIR = ../../engine
SRCDIR = ../../geotrans2/src
JNIDIR = ../../geotrans2/java_gui/geotrans/jni
JAVADIR = /usr/local/j2sdk1_3_1#Note: Change this for your system

####
# Libraries
####

LIBDTCC = $(DTCCDIR)/unix/libdtcc.a
LIBENGINE = $(ENGINEDIR)/unix/libengine.a
LIBGEOTRANS = libgeotrans.so.1
LIBJNI = libjnigeotrans.so

#LIBS = $(XPCLASSLIBS) $(MOTIFLIBS) $(XLIBS) -lm

####
# Sources
####

DTCCSRCS = \
        threads.c \
        albers.c \
        azeq.c \
        bng.c \
        bonne.c \
        cassini.c \
        cyleqa.c \
        datum.c \
        eckert4.c \
        eckert6.c \
        ellipse.c \
        eqdcyl.c \
        gars.c \
        geocent.c \
        geoid.c \
        georef.c \
        gnomonic.c \
        grinten.c \
        lambert_1.c \
        lambert_2.c \
        loccart.c \
        mercator.c \
        mgrs.c \
        miller.c \
        mollweid.c \
        neys.c \
        nzmg.c \
        omerc.c \
        orthogr.c \
        polarst.c \
        polycon.c \
        sinusoid.c \
        stereogr.c \
        trcyleqa.c \
        tranmerc.c \
        ups.c \
        usng.c \
        utm.c

SRCS = \
        strtoval.c \
        fiomeths.c \
        source.c \
        cstrndup.c

JNISRCS = \
        JNIStrtoval.c \
        JNIFiomeths.c \
        JNISource.c \
        ThrowException.c \
        JNIEngine.c

####
# Includes
####

DTCCINCS = \
        -I$(DTCCDIR)/threads \
        -I$(DTCCDIR)/albers \
        -I$(DTCCDIR)/azeq \
        -I$(DTCCDIR)/bonne \
        -I$(DTCCDIR)/bng \
        -I$(DTCCDIR)/cassini \
        -I$(DTCCDIR)/cyleqa \
        -I$(DTCCDIR)/datum \
        -I$(DTCCDIR)/eckert4 \
        -I$(DTCCDIR)/eckert6 \
        -I$(DTCCDIR)/ellipse \
        -I$(DTCCDIR)/eqdcyl \
        -I$(DTCCDIR)/gars \
        -I$(DTCCDIR)/geocent \
        -I$(DTCCDIR)/geoid \
        -I$(DTCCDIR)/georef \
        -I$(DTCCDIR)/gnomonic \
        -I$(DTCCDIR)/grinten \
        -I$(DTCCDIR)/lambert_1 \
        -I$(DTCCDIR)/lambert_2 \
        -I$(DTCCDIR)/loccart \
        -I$(DTCCDIR)/mercator \
        -I$(DTCCDIR)/mgrs \
        -I$(DTCCDIR)/miller \
        -I$(DTCCDIR)/mollweid \
        -I$(DTCCDIR)/neys \
        -I$(DTCCDIR)/nzmg \
        -I$(DTCCDIR)/omerc \
        -I$(DTCCDIR)/orthogr \
        -I$(DTCCDIR)/polarst \
        -I$(DTCCDIR)/polycon \
        -I$(DTCCDIR)/sinusoid \
        -I$(DTCCDIR)/stereogr \
        -I$(DTCCDIR)/trcyleqa \
        -I$(DTCCDIR)/tranmerc \
        -I$(DTCCDIR)/ups \
        -I$(DTCCDIR)/usng \
        -I$(DTCCDIR)/utm


INCLUDES = \
        -I$(ENGINEDIR)/src \
        -I$(SRCDIR)

JNIINCS = \
        -I$(JNIDIR)

JAVAINCS = \
        -I$(JAVADIR)/include \
        -I$(JAVADIR)/include/solaris

####
# Targets
####

#GEOTRANS shared object library
# make libgeotrans.so.1
$(LIBGEOTRANS):   $(DTCCSRCS) $(DTCCSRCS:.c=.o) engine.o
	$(cc) -dy -o $(LIBGEOTRANS) $(posic) $(DTCCSRCS:.c=.o)  engine.o -lm
#	$(cc) -dy -o $(LIBGEOTRANS) $(posic) -h $(LIBGEOTRANS) $(DTCCSRCS:.c=.o)  engine.o -lm


#JNI shared object library
# make libjnigeotrans.so
$(LIBJNI): posic_sources $(JNISRCS) $(JNISRCS:.c=.o)
	$(cc) -dy -o $(LIBJNI) $(posic) -h $(LIBJNI) $(LIBGEOTRANS) $(JNISRCS:.c=.o) $(SRCS:.c=.o) -lm

####
# Supporting Rules
####

#DT&CC Modules - for GEOTRANS shared object library
# To build the DT&CC Modules, type the following:
# cd ../../dt_cc/unix
# make libdtcc.a
$(DTCCSRCS):
	ln -s $(DTCCDIR)/$(@:.c=)/$@ .

$(DTCCSRCS:.c=.o):$(@:.o=.c)
	$(cc) -c $(CFLAGS) $(posic) $(INCLUDES) $(DTCCINCS) $(@:.o=.c)

#GEOTRANS Engine - for GEOTRANS shared object library
# To build the GEOTRANS Engine, type the following:
# cd ../../engine/unix
# make libengine.a
engine.c:
	ln -s $(ENGINEDIR)/src/engine.c engine.c

engine.o:engine.c
	$(cc) -c $(CFLAGS) $(posic) $(INCLUDES) $(DTCCINCS) $(@:.o=.c)

#Misc GEOTRANS application sources
$(SRCS):
	ln -s $(SRCDIR)/$@ .

posic_sources:
	make "P=$(posic)" $(SRCS) $(SRCS:.c=.o)

force_rebuild:

$(SRCS:.c=.o):$(@:.o=.c) force_rebuild
	$(cc) -c $(CFLAGS) $(P) $(INCLUDES) $(@:.o=.c)

#JNI sources - for Java version
$(JNISRCS):
	ln -s $(JNIDIR)/$@ .

$(JNISRCS:.c=.o):$(@:.o=.c)
	$(cc) -c $(CFLAGS) $(posic) $(INCLUDES) $(JNIINCS) $(JAVAINCS) $(@:.o=.c)

clean:
	$(RM) *.c *.cpp *.o $(BINARY)
