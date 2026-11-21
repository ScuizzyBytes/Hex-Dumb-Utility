# ⚡ HEX_DUMP // C++20 Binary Stream Inspector

![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

> **Raw bytes don't lie.** A zero-dependency, low-level C++20 CLI utility engineered to dissect binary files at the byte level with surgical precision.

---

## 🎯 The Vision

`hex_dump` strips away file abstractions and exposes the raw hexadecimal and ASCII structure of any binary or text file directly in your terminal. Built from scratch in modern **C++20** with strict compiler flags (`-Wall -Wextra -Wpedantic -Wshadow -Wconversion`), it prioritizes deterministic memory safety, clean stream I/O, and instantaneous execution.

---

## ⚙️ Architecture & Data Flow

The engine operates on a fixed-size 16-byte sliding buffer (`std::vector<uint8_t>`), reading raw binary chunks via `std::ifstream` and tracking exact byte counts through `file.gcount()` to eliminate buffer over-reads on partial trailing lines.

```text
+-------------------+      std::ios::binary      +-----------------------+
|   Target Binary   | -------------------------> |   std::ifstream       |
+-------------------+                            +-----------------------+
                                                            |
                                                 file.read() (16 bytes)
                                                            v
+-------------------+      std::isprint()        +-----------------------+
|   ASCII Column    | <------------------------- | std::vector<uint8_t>  |
+-------------------+                            +-----------------------+
                                                            |
                                                 std::hex / std::setw(2)
                                                            v
                                                 +-----------------------+
                                                 |  Offset + Hex Grid    |
                                                 +-----------------------+
