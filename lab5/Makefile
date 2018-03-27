# Mason Roach
# Patrick Roy
#
# ============================ Instructions ============================= 
# make
#	Running [make] or [make all] will compile an executable for the
#	current lab directory
#	Note: when using the avrdude, run [sudo make]
#
# make clean
#	Running [make clean] will remove unessecary files, such as object
#	files, and executables
#

# =================== CHANGE THIS SECTION BETWEEN LABS ===================   
LABNAME = lab5atmega
OBJS = $(LABNAME).o
# ========================================================================

CC = avr-gcc
OBJCOPY = avr-objcopy
PROGRAMMER = avrispmkII

TARGET = $(LABNAME)
LIBS = 

CFLAGS = -Wall -mmcu=atmega88p -O3

.PHONY : all clean debug

all: 
	make clean
	gcc -o lab5pc -Wall lab5pc.c
	make $(TARGET)

debug : CFLAGS += -Wextra
debug : all

$(TARGET): $(OBJS)
	$(CC)  -o $(TARGET) $(CFLAGS) $(OBJS) $(LIBS)
	$(OBJCOPY) -R .eeprom -O ihex $(TARGET) $(TARGET).hex
	avrdude -p m88p -c $(PROGRAMMER) -P usb -V -e -F -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).hex lab5pc
