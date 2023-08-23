CC = gcc -Wall -Werror -Wextra
TARGET = s21_grep

$(TARGET): s21_grep.o
	$(CC) s21_grep.o -o $(TARGET)

s21_grep.o: 
	$(CC) -c s21_grep.c -o s21_grep.o

clean:
	rm $(TARGET) *.o


