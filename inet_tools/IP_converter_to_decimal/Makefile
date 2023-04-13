# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
INCLUDES = -I../build/artifacts
LIBDIR = ../build/lib
LIBS = -lIphlpapi -lws2_32
CP = cp
RM = rm
CC = gcc
TARGET = ip_string_to_dec

ifeq ($(MSYSTEM), MINGW32)
LFLAGS = -L./lib/lib_ethdev/winpcap
else
LFLAGS = -L./lib/lib_ethdev/winpcap/x64
endif

# the build target executable:
ifeq ($(OS),Windows_NT)
all: $(TARGET)
$(TARGET):
	$(CC) -o $(TARGET) $(TARGET).c $(CFLAGS) $(INCLUDES) $(LIBS) $(LFLAGS) -lpcap

else
all: $(TARGET)
$(TARGET):
	$(CC) -o $(TARGET) $(TARGET).c $(CFLAGS) $(INCLUDES) $(LIBS) $(LFLAGS) -lpcap
	
endif

# endif

.PHONY: clean
clean:
	$(RM) -f $(TARGET)

