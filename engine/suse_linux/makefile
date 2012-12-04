####
# Compiler declarations
####

#Sun SPARCworks
#cc = cc
#CC = CC
#Gnu
cc = gcc
CC = g++

####
# Support declarations
####

DEBUG = -g

CFLAGS = $(DEBUG)

####
# Directories
####

ENGINEDIR = ../src
DTCCDIR = ../../dt_cc

####
# Libraries
####

LIB =  libengine.a

####
# Sources
####

SRCS = 	engine.c 

####
# Includes
####

INCLUDES = \
	-I$(ENGINEDIR) \
	-I$(DTCCDIR)/albers \
	-I$(DTCCDIR)/azeq \
	-I$(DTCCDIR)/bng \
	-I$(DTCCDIR)/bonne \
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

####
# Suffix rules
####

.SUFFIXES: .c .o

.c.o:
	$(cc) -c $(CFLAGS) $(INCLUDES) $<

####
# Targets
####

all: $(LIB)

$(SRCS):
	ln -s $(ENGINEDIR)/$@ .

$(LIB):	 $(SRCS:.c=.o)
	ar -rv $(LIB) $(SRCS:.c=.o)

clean:	
	$(RM) *.c *.o *.a
