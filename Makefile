TARGET = autoclicker.exe

SOURCES = main.c

CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0` -framework ApplicationServices -framework Carbon

CC = gcc

BREW = /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
GTK_INSTALL = brew install gtk+3

all: $(TARGET)

check_brew:
	@if ! command -v brew &> /dev/null; then \
		echo "Homebrew n'est pas installé. Installation de Homebrew..."; \
		$(BREW); \
	else \
		echo "Homebrew est déjà installé."; \
	fi

check_gtk:
	@if ! pkg-config --exists gtk+-3.0; then \
		echo "GTK+3 n'est pas installé. Installation de GTK+3..."; \
		$(GTK_INSTALL); \
	else \
		echo "GTK+3 est déjà installé."; \
	fi

$(TARGET): check_brew check_gtk $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
