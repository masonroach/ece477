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

.PHONY : all clean debug

all:
	make -f Makefile -C atmega88
	make -f Makefile -C atmega324

clean:
	make clean -C atmega88
	make clean -C atmega324
