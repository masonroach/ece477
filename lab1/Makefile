# Mason Roach
# Patrick Roy
#
# ============================ Instructions ============================= 
# make
#	Running [make] or [make all] will compile an executable for the
#	current lab directory
#
# make debug
#	Running [make debug] will compile similarly to [make all] except
#	additional warnings and compiler flags will be used
#
# make clean
#	Running [make clean] will remove unessecary files, such as object
#	files, and executables
#

# =================== CHANGE THIS SECTION BETWEEN LABS ===================   
LABNAME = lab1
OBJS = $(LABNAME).o
# ========================================================================

TARGET = $(LABNAME)
LIBS = 

CFLAGS = -Wall

.PHONY : all clean debug

all: $(TARGET)

debug : CFLAGS += -Wextra
debug : all

$(TARGET): $(OBJS)
	$(CC)  -o $(TARGET) $(CFLAGS) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
