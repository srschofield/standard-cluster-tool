# Compiler and flags
CXX = g++
CXXFLAGS = -O2

# Target binary and source files
TARGET = sct
SRCS = Atom.cpp AtomList.cpp DSiliconTemplate.cpp Parser.cpp Position.cpp SiliconTemplate.cpp Template.cpp sct.cpp Silicon2024Template.cpp Germanium2024Template.cpp
OBJS = $(SRCS:.cpp=.o)

# Install directory
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Install the binary
install: $(TARGET)
	install -d $(BINDIR)
	install $(TARGET) $(BINDIR)

# Uninstall the binary
uninstall:
	rm -f $(BINDIR)/$(TARGET)

# Phony targets
.PHONY: all clean install uninstall

