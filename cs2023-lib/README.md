# cs2023-lib

Listas y hash tables para copiar y pegar bajo presión. C++17, punteros crudos.
Cada archivo de `snippets/` compila solo; la única excepción es
`08_patrones_hash.cpp`, que incluye al `07_hash_table.cpp`.

Sigue la nomenclatura del curso (Sem3 Listas y Sem5 Hash tables, prof. V. Racsó Galván).

Convenciones que hay que recordar:
- Lista simple: `LinkedNode<T>` / `LinkedList<T>`, campo `data`, con `head` y `tail`.
- `insert(node, v)` inserta **después** de `node`; `erase(node)` borra el nodo **siguiente** a `node` (¡ojo con esta convención!). También hay `insert(k,v)` / `erase(k)` 0-indexed.
- Problemas tipo CF/LeetCode: `struct ListNode { int val; ListNode* next; }`.

## 1. ¿Qué archivo abro?

| Me piden… | Archivo |
|---|---|
| Arranque rápido (includes, main, fast I/O) | `00_template.cpp` |
| Arreglo dinámico propio (`Vector<T>`, sz/cap/data) | `01_vector.cpp` |
| Lista enlazada simple completa / `ListNode` suelto | `02_lista_simple.cpp` |
| Lista doble, borrar por puntero en O(1), recorrer al revés | `03_lista_doble.cpp` |
| Round-robin, turnos, buffer circular | `04_lista_circular.cpp` |
| Trucos sobre `ListNode` (reverse, ciclo, merge, k-ésimo) | `05_patrones_lista.cpp` |
| Leer/imprimir/convertir listas | `06_io_listas.cpp` |
| Hash table con chaining (`my_map<K,V>`) | `07_hash_table.cpp` |
| Trucos con hash table (frecuencias, two-sum, subarreglos) | `08_patrones_hash.cpp` |

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

## 4. TAGs de hash table (Ctrl+F)

La estructura, en `07_hash_table.cpp`:

| TAG | Qué hace |
|---|---|
| `[FIND-POS]` | Posición de la llave dentro de su cajón (base de todo lo demás). |
| `[OP-BRACKET]` | `M[k]`: lee, escribe, e inserta si no existe. |
| `[HAS-KEY]` | ¿Existe? Sin insertar. |
| `[ERASE]` | Borrar en O(1) (swap con el último + pop_back). |
| `[HASH-INT]` | Hash polinomial sobre los dígitos. |
| `[HASH-STR]` | Hash polinomial sobre los caracteres. |
| `[PRINT]` | Ver qué hay en cada cajón (depurar). |

Los problemas, en `08_patrones_hash.cpp`:

| TAG | Qué hace |
|---|---|
| `[FREQ]` | Contar ocurrencias y responder consultas en O(1). |
| `[DISTINTOS]` | Cuántos valores distintos (la tabla como set). |
| `[PERMUT]` | ¿Un arreglo es reordenación del otro? |
| `[TWO-SUM]` | ¿Hay dos elementos que sumen S? |
| `[MAS-REPE]` | El más repetido, desempate por orden de aparición. |
| `[SUBARR-SUMA]` | Cuántos subarreglos suman exactamente S. |

Elegir `m`: unos `2*n` cajones. Cajones de más no cuestan casi nada; de menos,
las listas crecen y el O(1) se vuelve O(n).

En un contest de verdad va `unordered_map` con `reserve(2*n)`, o `map` si hacen
falta las llaves en orden. `my_map` es para el curso y para entender qué hay
adentro.

## 5. Errores típicos con hash tables

1. **`operator[]` sin actualizar la posición tras insertar**: devuelve el elemento equivocado. Inserta al final y deja el índice apuntando ahí.
2. **`_hash` sin `const`** llamado desde un método `const` como `has_key`: ni compila.
3. **Negativos**: `while (key > 0)` no entra y todos caen al cajón 0. Suma un `OFFSET` **al guardar y al consultar**, nunca en un solo lado.
4. **Usar `M[x]` para consultar**: inserta la llave con valor 0 y el mapa crece solo. Para preguntar, `has_key(x)` (o `count(x)` en la STL).
5. **`m` chico**: todo cae en pocos cajones y el O(1) se vuelve O(n).
6. **Desbordar el int en el hash**: falta el `1ll *` antes de la multiplicación.
7. **Esperar orden**: la hash table no tiene orden. Si lo necesitas, guarda el orden de aparición aparte o usa `map`.

## 6. Errores típicos con listas

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
