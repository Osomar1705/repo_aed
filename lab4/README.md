# lab4 — BBST, recursión y backtracking

Plantillas para consultar en el examen. Basadas en mi código del curso CS2023 (BST de semana6, AVL de semana9) y en el mismo estilo (`data_type`, `TreeNode`, snake_case). Cada archivo de `snippets/` compila **solo**.

## ¿Qué archivo abro?

| Me piden… | Archivo |
|---|---|
| Árbol binario de búsqueda simple (insertar/buscar/borrar/recorridos) | `00_bst.cpp` |
| **BBST** = BST balanceado (AVL, altura O(log n) garantizada) | `01_avl.cpp` |
| Recursión clásica (factorial, fib, potencia rápida, gcd, hanoi, bsearch) | `02_recursion.cpp` |
| Backtracking (subconjuntos, permutaciones, combinaciones, paréntesis, N-reinas) | `03_backtracking.cpp` |

## BST vs AVL (¿cuál uso?)

| | BST (`00`) | AVL / BBST (`01`) |
|---|---|---|
| Buscar / insertar / borrar | O(altura) | **O(log n)** garantizado |
| Peor caso (datos ordenados) | **O(n)** (degenera a lista) | O(log n) (se rebalancea) |
| Código | corto | más largo (rotaciones) |
| Cuándo | datos aleatorios / lo piden explícito | cuando importa el peor caso |

**AVL en 4 casos** (si `|FB|=2`): LL → rotar derecha · RR → rotar izquierda · LR → izq en el hijo + derecha · RL → der en el hijo + izquierda. `FB(v) = h(izq) - h(der)`, con `h(nulo) = -1`.

## Backtracking — el esquema es siempre el mismo

```
ELEGIR una opción  →  EXPLORAR (recursión)  →  DESHACER (volver atrás)
```
La **poda** (cortar ramas inválidas antes de seguir) es lo que lo hace más rápido que fuerza bruta.

| Patrón | Cuántas soluciones |
|---|---|
| Subconjuntos | 2^n |
| Permutaciones | n! |
| Combinaciones C(n,k) | C(n,k) |
| Paréntesis válidos | Catalan(n) |
| N-reinas | (conocido: n=4→2, n=8→92) |

## Errores típicos

1. **Recursión sin caso base** → desbordas la pila. Define el caso base antes de llamar.
2. **Fibonacci sin memo** → O(2^n), se cuelga. Usa el `memo`.
3. **BST: olvidar los 3 casos al borrar** (0, 1, 2 hijos); con 2 hijos usa el sucesor.
4. **AVL: no reasignar la raíz** que devuelve `insert`/`erase` (`root = insert(root, x)`).
5. **AVL: no actualizar `parent`** tras rotar/insertar.
6. **Backtracking: olvidar el DESHACER** (`pop_back`, `usado=false`) → ensucias el estado de otras ramas.
7. **Permutaciones/combinaciones: no podar** (`usado`, `inicio`) → repeticiones o explosión.

---
`make all` compila los tests · `make test` los corre · `make clean` limpia.
Flags: `-std=c++17 -Wall -Wextra -g -fsanitize=address,undefined`.
