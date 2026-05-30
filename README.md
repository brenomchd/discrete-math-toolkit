# Discrete Math Toolkit

Academic repository containing number theory and cryptography algorithms implemented in C.

## About

This repository contains practical implementations developed for the Discrete Mathematics course, focusing on classical algorithms from Number Theory and Cryptography.

The projects explore mathematical foundations widely used in Computer Science, including modular arithmetic, prime number generation, Diophantine equations, the Chinese Remainder Theorem, and RSA cryptography.

Main topics explored in this repository:

- Number Theory
- Modular Arithmetic
- Prime Numbers
- Euclidean Algorithms
- Chinese Remainder Theorem
- RSA Cryptography
- Mathematical Algorithms
- Computational Mathematics

The codebase was developed using:

- C
- Number Theory
- Cryptography
- Modular Arithmetic
- Mathematical Computing

---

## Repository Structure

```text
.
├── number-theory-src/
│   ├── main.c
│   ├── number-theory.c
│   └── number-theory.h
├── cryptography-src/
│   ├── main.c
│   ├── cryptography.c
│   ├── cryptography.h
│   └── run.sh
└── README.md
```

---

## Number Theory

Implementation of classical Number Theory algorithms.

Implemented algorithms:

- Sieve of Eratosthenes
- Greatest Divisor
- Greatest Common Divisor (GCD)
- Prime Factorization Tree
- Euclidean Algorithm
- Extended Euclidean Algorithm
- Modular Linear Equations
- Chinese Remainder Theorem

Concepts explored:

- Divisibility
- Prime Numbers
- Congruences
- Modular Arithmetic
- Diophantine Equations

---

## Cryptography

Implementation of RSA-related cryptographic algorithms.

Implemented algorithms:

- RSA Public Key Recovery
- RSA Private Key Recovery
- RSA Encryption
- RSA Decryption

Concepts explored:

- Public-Key Cryptography
- RSA Algorithm
- Modular Exponentiation
- Euler's Totient Function
- Modular Inverses

---

## Requirements

- GCC
- Linux or Unix-like environment

---

## Build

### Number Theory

```bash
gcc number-theory-src/number-theory.c number-theory-src/main.c -o number-theory
```

### Cryptography

```bash
gcc cryptography-src/cryptography.c cryptography-src/main.c -o cryptography
```

---

## Run

### Number Theory

```bash
./number-theory
```

### Cryptography

```bash
./cryptography
```

---

## Notes

This repository focuses on educational implementations of mathematical algorithms that form the foundation of modern Computer Science, cryptography, and algorithm design.

The goal is to provide practical understanding of Number Theory concepts and their application in cryptographic systems.

---

## Author

Breno Machado Barros
