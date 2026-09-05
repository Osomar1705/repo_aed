<div align="center">

# 📚 CS2023 — Data Structures Library

**A compact C++ snippet library for linked structures, with a test target for each one.**
*Librería compacta de snippets en C++ para estructuras enlazadas, con un test por cada una.*

![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Make](https://img.shields.io/badge/Make-427819?style=flat-square&logo=gnu&logoColor=white)

</div>

---

## 🌟 What's inside

Reference implementations written to be read, not just to compile — each file is self-contained and paired with a test.

| Snippet | Topic |
| --- | --- |
| `00_template.cpp` | Starting scaffold for exercises |
| `01_vector.cpp` | Dynamic array: growth, indexing, invalidation |
| `02_lista_simple.cpp` | Singly linked list |
| `03_lista_doble.cpp` | Doubly linked list |
| `04_lista_circular.cpp` | Circular list |
| `05_patrones_lista.cpp` | Recurring list patterns (traversal, insertion, deletion, reversal) |
| `06_io_listas.cpp` | Reading and printing lists |

`tests/test_01.cpp` … `test_05.cpp` exercise the corresponding snippets.

---

## 🚀 Build & run

```bash
cd cs2023-lib
make            # build every target
make test       # run the test suite
make clean
```

---

## 🇪🇸 En español

Librería de referencia para el curso **CS2023 – Algoritmos y Estructuras de Datos**. Cada snippet es autocontenido y está escrito para *leerse*, no solo para compilar: vector dinámico, lista simple, doble y circular, patrones recurrentes de recorrido/inserción/borrado, y entrada-salida de listas.

Cada snippet tiene su test correspondiente en `tests/`. Todo se compila con `make` desde `cs2023-lib/`.

---

<div align="center">

Built by [**Osmar Vilchez Aguirre**](https://github.com/Osomar1705) · UTEC 🇵🇪

</div>
