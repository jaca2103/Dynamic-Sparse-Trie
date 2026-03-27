# Dynamic Sparse Trie

A specialized data structure designed for storing values indexed by sparse keys from a large universe $N$. This project implements a hierarchical tree (Trie-like) as an alternative to hash tables, offering more predictable performance in pessimistic scenarios.

## Overview / Opis projektu

### English
This C implementation uses a dynamic tree structure to manage sparse keys. Unlike standard tries, it stores values directly in nodes to optimize space. Navigation through the tree is determined by a two-parameter modular arithmetic system ($n$ for the root and $k$ for subsequent levels).

### Polski
Implementacja w języku C wykorzystująca dynamiczną strukturę drzewiastą do zarządzania rzadkimi kluczami. W przeciwieństwie do standardowych drzew Trie, wartości są przechowywane bezpośrednio w węzłach. Nawigacja w drzewie odbywa się na podstawie arytmetyki modularnej zdefiniowanej przez parametry $n$ (dla korzenia) oraz $k$ (dla kolejnych poziomów).

## Features / Cechy implementacji

* **Memory Efficiency:** Children arrays are allocated lazily (only when a collision occurs) to save RAM.
* **Path Calculation:** Uses `key % n` for the first level and `(x / n) % k` for deeper levels to resolve paths.
* **"Search-Left" Deletion:** When an internal node is deleted, the algorithm automatically finds the leftmost leaf to replace the deleted key, maintaining structural integrity.
* **Dynamic Scaling:** The tree grows only as much as needed by the number of collisions.

## Usage / Obsługa programu

The program reads from standard input (`stdin`). The first line should contain configuration parameters:
`count min max n k`

### Supported Commands:
| Command | Action | Description |
| :--- | :--- | :--- |
| **I <key>** | Insert | Adds a key to the structure. |
| **L <key>** | Look-up | Checks if a key exists. |
| **D <key>** | Delete | Removes a key using the left-leaf strategy. |
| **P** | Print | Prints all keys currently in the tree (pre-order). |
