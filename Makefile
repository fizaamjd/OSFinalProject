CC = cc
CFLAGS ?= -O2 -Wall -Wextra
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0)
APPS := my_os calculator calender clock filemanager notepad minsweeper tictactoe
HELPERS := allocate-memory access-hard-drive utilize-cores
.PHONY: all check clean
all: $(APPS) $(HELPERS)
my_os: Main.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
calculator: Calculator.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
calender: Calender.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
clock: Time.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
filemanager: FileManager.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
notepad: Notepad.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
minsweeper: MinSweeper.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
tictactoe: TicTacToe.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -o $@ $(GTK_LIBS)
allocate-memory: AllocateMemory.c
	$(CC) $(CFLAGS) $< -o $@
access-hard-drive: AccessHardDrive.c
	$(CC) $(CFLAGS) $< -o $@
utilize-cores: UtilizeCores.c
	$(CC) $(CFLAGS) $< -o $@
check: all
	printf "2\n" | ./allocate-memory | grep -q "2"
	printf "2\n" | ./access-hard-drive | grep -q "2"
	printf "2\n" | ./utilize-cores | grep -q "2"
clean:
	rm -f $(APPS) $(HELPERS)
