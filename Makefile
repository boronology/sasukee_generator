CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -Wextra
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc
OBJ=sasukee

all:main.cpp
	if [ ! -f sasukee.png ]; \
	then wget http://dic.nicovideo.jp/oekaki/211471.png -O sasukee.png; \
	fi
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o ${OBJ} main.cpp

image:
	wget http://dic.nicovideo.jp/oekaki/211471.png -O sasukee.png

clean:
	rm sasukee sasukee.png
