# cs2023-lib — Listas (examen Codeforces)

Copia-pega bajo presión. Cada archivo de `snippets/` compila **solo**, sin depender de los demás. C++17, punteros crudos.

## 1. ¿Qué archivo abro?

| Me piden… | Archivo |
|---|---|
| Arranque rápido (includes, main, typedefs) | `00_template.cpp` |
| Arreglo dinámico propio (como vector) | `01_vector.cpp` |
| Lista enlazada simple completa / `struct Nodo` suelto | `02_lista_simple.cpp` |
| Lista doble, borrar por puntero en O(1), recorrer al revés | `03_lista_doble.cpp` |
| Round-robin, turnos, buffer circular | `04_lista_circular.cpp` |
| **Truco sobre `Nodo` (reverse, ciclo, merge, k-ésimo…)** | `05_patrones_lista.cpp` |
| Leer/imprimir/convertir listas | `06_io_listas.cpp` |

## 2. Arreglo/Vector vs Lista simple vs Lista doble

| Operación | Arreglo/Vector | Lista simple | Lista doble |
|---|---|---|---|
| Acceso por índice `[k]` | **O(1)** | O(k) | O(k) |
| Insertar/eliminar al inicio | O(n) | **O(1)** | **O(1)** |
| Insertar/eliminar al final | O(1) amort. | O(1) con `tail` (insert); pop O(n) | **O(1)** |
| Insertar en medio con puntero | O(n) | O(1) (después de) | **O(1)** |
| Eliminar dado el puntero | O(n) | O(n) (necesita el previo) | **O(1)** real |
| Memoria extra por elemento | 0 (+capacidad ociosa) | 1 puntero | 2 punteros |

## 3. TAGs de `05_patrones_lista.cpp` (Ctrl+F)

| TAG | Qué hace |
|---|---|
| `[REVERSE-IT]` | Invertir la lista, iterativo (el de siempre). |
| `[REVERSE-REC]` | Invertir la lista, recursivo. |
| `[REVERSE-MN]` | Invertir solo el segmento `m..n` (1-indexado). |
| `[MERGE]` | Fusionar dos listas ya ordenadas. |
| `[DEDUP]` | Quitar duplicados de lista ordenada. |
| `[MEDIO]` | Nodo medio con fast/slow. |
| `[CICLO]` | ¿Hay ciclo? (Floyd). |
| `[CICLO-INI]` | Nodo donde empieza el ciclo. |
| `[KTH-FIN]` | Borrar el k-ésimo desde el final, una pasada. |
| `[ROTAR]` | Rotar k posiciones a la derecha. |
| `[PARTIR]` | Particionar por x, orden estable. |
| `[MSORT]` | Merge sort sobre la lista, O(n log n). |

## 4. Errores típicos con listas

1. **Perder el head**: reasignas `head` sin guardar el nodo viejo → se pierde toda la lista. Guarda `nx = p->next` antes de tocar punteros.
2. **No usar dummy head**: borrar/insertar en la cabeza se vuelve un caso especial feo. Un `Nodo dummy; dummy.next = head;` lo unifica.
3. **No actualizar `tail`**: tras push/pop/reverse el `tail` queda apuntando a basura. Actualízalo siempre que cambie el último nodo.
4. **Borrar sin reconectar**: haces `delete cur` pero `prev->next` aún apunta al nodo muerto → use-after-free. Reconecta primero, borra después.
5. **Leer `->next` de `nullptr`**: en fast/slow y recorridos, la condición es `while (fast && fast->next)`, nunca al revés.
6. **Off-by-one en `at(k)`**: 0-indexado, avanza exactamente `k` veces; valida `0 <= k < n` antes.
7. **Bucle infinito en circular**: recorre contando `n` pasos, no esperes `nullptr` (nunca llega). Al `clear`, rompe el círculo antes de liberar.
8. **Fuga al hacer `clear`**: reasignar `head = nullptr` no libera nodos. Recorre y `delete` uno por uno.

---
`make all` compila los tests · `make test` los corre · `make clean` limpia.
Flags: `-std=c++17 -Wall -Wextra -g -fsanitize=address,undefined`.
