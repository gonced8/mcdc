CC = gcc
CFLAGS = -I$(LDIR) -Wall -ansi -pedantic -O3

.PHONY: all run clean

SDIR = src
ODIR = obj
LDIR = lib

LIBS = -lpthread

MCDC_OBJ = mcdc binary bubblesort function print solve threads

MOBJ = $(patsubst %,$(ODIR)/%.o,$(MCDC_OBJ))

# Executables

all: mcdc

mcdc : $(MOBJ)
	$(CC) -o $@ $^ $(LIBS)

$(ODIR):
	mkdir -p $@

# Objects

SRC = mcdc
LIB = mcdc function threads
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = binary
LIB = binary
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = bubblesort
LIB = bubblesort
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = function
LIB = function
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = print
LIB = print binary
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = solve
LIB = solve binary bubblesort print
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = threads
LIB = threads solve
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

run: mcdc
	time ./mcdc

clean:
	rm -rf mcdc $(ODIR)
