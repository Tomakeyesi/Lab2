# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = 
TARGET = gronsfeld_cipher
SOURCES = main.cpp modAlphaCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Создание исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Компиляция объектных файлов
%.o: %.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Отладка
debug: CXXFLAGS += -g
debug: clean $(TARGET)

# Проверка утечек памяти
valgrind: debug
	valgrind --leak-check=full ./$(TARGET)

# Сборка с оптимизацией
release: CXXFLAGS += -O3
release: clean $(TARGET)

# Тестирование
test: $(TARGET)
	@echo "Запуск тестов..."
	@./$(TARGET)

.PHONY: all clean run debug valgrind release test
