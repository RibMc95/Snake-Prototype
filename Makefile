# Makefile for Snake Game
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = snake_game
SOURCES = main.cpp

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LIBS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run target
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run