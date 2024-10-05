build:
	gcc *.c utilities/*.c -o nc.exe

clean:
	cmd /C del nc.exe
