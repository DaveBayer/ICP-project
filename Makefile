TARGET=apk
CPPFLAGS=-std=c++17

SRC=src
OBJ=obj
SRCFILES:=$(wildcard $(SRC)/*.cpp)
OBJFILES:=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCFILES))
HDRFILES:=$(wildcard $(SRC)/*.h)

all: $(TARGET)


#$(TARGET): $(SRCFILES) $(HDRFILES)
#	g++ $(CPPFLAGS) -o $@ $(SRCFILES) $(HDRFILES)
$(TARGET): $(OBJFILES) $(HDRFILES)
	g++ $(CPPFLAGS) -o $@ $(OBJFILES) -I$(SRC)

$(OBJ)/%.o: $(SRC)/%.cpp $(HDRFILES)
	g++ $(CPPFLAGS) $< -c -o $@ -I$(SRC)

clean:
	rm -r $(OBJ)
	mkdir $(OBJ)