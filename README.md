[![Actions Status](https://github.com/Greezzee/VerificationTask3/workflows/Ubuntu/badge.svg)](https://github.com/Greezzee/VerificationTask3/actions)
[![codecov](https://codecov.io/github/Greezzee/VerificationTask3/graph/badge.svg?token=7UI41WMA0R)](https://codecov.io/github/Greezzee/VerificationTask3)
### Verification Task 3
Используемые утилиты:

CI: Github Actions (Конфиг-файл .github/workflows/ubuntu.uml)

Инструмент для unit тестов: googletest
Инструмент для сбора покрытия: gcov
Визуализация покрытия: codecov (покрытие по ветвлениям в коде - генерируется в CI), 
    lcov (покрытие по строчкам и функциям, html в папке lcov_html - генерируется вручную для демонстрации полного покрытия по разным метрикам)
Инструмент статического анализа: cppcheck
Инструмент динамического анализа: ASAN (provided by gcc)

### Локальная Сборка

make test - запуск только unit-тестов
make coverage - запуск unit-тестов со сбором покрытия
make cppcheck - запуск со статическим анализатором
make test_asan - запуск с ASAN

### Author
Зорин Евгений Михайлович (МФТИ, М01-303б)