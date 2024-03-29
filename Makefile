CXX = gcc
CFLAGS = -Wall -Werror -pedantic -fpic -g
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

#Library-related macros
LIBCORENAME = board
LIBTARGET :=lib$(LIBCORENAME:=.so)
LIBSOURCE = $(LIBCORENAME)
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

#Application-related macros
EXESOURCE = main
TARGET = $(EXESOURCE:=.exe)
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

#Running the program
run: $(TARGET)
	@echo "\n Running the executable" $(TARGET)
	sh exportLD.sh $(TARGET)
	@echo ""

all: $(TARGET) 

#Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET)
	@echo "\nGenerating the executable " $@ "from " $<
	$(CXX) $(EXESOURCEOFILE) -l$(LIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm

#Generating the library binary code
$(LIBTARGET): $(LIBSOURCEOFILE)
	@echo "\nGenerating the library binary code .so from object files (.o) " $@
	$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)

#Generating an object file from a C file having the same name
.c.o:
	@echo "\nGenerating object file (.o)" $@ " from c source file (.c)" $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

#Cleaning the content of the current directory
clean:
	@echo "\nCleaning temporary files"
	rm -rf *.o *~ *.so *.exe