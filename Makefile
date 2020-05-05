TARGET=apk
CPPFLAGS=-c

SRC=src
OBJ=obj
SRCFILES=$(wildcard $(SRC)/*.cpp)
OBJFILES=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCFILES))
HDRFILES=$(wildcard $(SRC)/*.h)

all: $(TARGET)

$(TARGET): $(OBJFILES) $(HDRFILES)
	g++ $(CPPFLAGS) -o $@ $(OBJFILES)

$(OBJ)/%.o: $(SRC)/%.cpp $(HDRFILES)
	g++ $(CPPFLAGS) $< -o $@ -I$(SRC)