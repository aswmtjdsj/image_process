CC=g++
CFLAGS=-g -Wall -std=c++0x
LIB=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_nonfree -lopencv_legacy
SRC=handle_avatar.cpp

main: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB) 

clean:
	-rm main


