# neuroPictures

Учебный проект: нейронная сеть на C++ для распознавания рукописных цифр, написанная с нуля (без ML-фреймворков). Сеть учится на датасете MNIST, а отдельное приложение на Qt и OpenCV позволяет рисовать цифру мышью.

## Что внутри

| Папка | Содержимое |
|-------|------------|
| `nn/` | Сама сеть: матрицы и вспомогательные функции (`utility.cpp`), полносвязный слой (`perceptron.cpp`), сеть, обучение, сохранение и загрузка весов (`network.cpp`) |
| `UI/` | `learner.cpp` для обучения на MNIST; `interface.cpp`, `editor.cpp` окно для рисования цифр (Qt + OpenCV) |
| `GPU_stuff/` | Эксперименты с умножением матриц на CUDA |
| `tests/` | Тесты матриц на [doctest](https://github.com/doctest/doctest) |
| `include/`, `lib/`, `opencv/` | Сторонние библиотеки (CUDA, OpenCV и их зависимости), лежат прямо в репозитории |

## Сборка и запуск

Нужен компилятор с поддержкой C++17 и CMake 3.24+.

Обучение (читает с stdin пути к файлам MNIST в формате idx: изображения и метки):

```bash
mkdir build && cd build
cmake ..
cmake --build . --target learner
./learner
```

Веса периодически сохраняются в `network.txt`.

Тесты:

```bash
g++ -std=c++17 tests/tests.cpp -o tests_run && ./tests_run
```

## Авторы

TheLostDesu, verapasichenko, idar66913, iagribanov.
