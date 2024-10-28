all: threads processes

threads: threads.c
	gcc threads.c -lpthread -o threads

processes: processes.c
	gcc processes.c -o processes
