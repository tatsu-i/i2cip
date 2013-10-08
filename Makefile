CC            = gcc
CFLAGS        = -g #-O4 -Wall -I/usr/local/include
DEST          = /usr/local/bin
INCLUDES      = -I/usr/local/include -L/usr/local/lib -lwiringPi
LDFLAGS       = #-L/usr/local/lib
LIBS          = -lm
OBJS          = main.o
PROGRAM       = printi2c
PYPROGRAM     = pi2cip

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS)
	                $(CC) $(OBJS) $(INCLUDES) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

clean:;         rm -f *.o *~ $(PROGRAM)

install:        $(PROGRAM)
	                install -s $(PROGRAM) $(DEST)
	                chmod 4755 $(DEST)/$(PROGRAM)
	                cp $(PYPROGRAM) $(DEST)/
	                chmod 755 $(DEST)/$(PYPROGRAM)

