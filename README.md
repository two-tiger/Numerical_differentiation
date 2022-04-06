# Numerical_differentiation
## Content

```
Numerical_differentiation
├─ .gitignore
├─ CMakeLists.txt
├─ README.md
├─ include
│  ├─ function.h
│  ├─ mycomplex.h
│  ├─ myvector.h
│  └─ vectorfunction.h
├─ src
│  ├─ function.c
│  ├─ mycomplex.c
│  ├─ myvector.c
│  └─ vectorfunction.c
└─ test
   ├─ CMakeLists.txt
   ├─ testcomplex.c
   ├─ testcomplexgrad.c
   ├─ testcomplexjacobi.c
   ├─ testfunction.c
   ├─ testhessian.c
   ├─ testomp.c
   └─ testvectorfunction.c

```
## Quick Start

```bash
git clone https://github.com/two-tiger/Numerical_differentiation.git
cd ./Numerical_differentiation
mkdir build
cd build
cmake ..
cmake --build
ctest
```

## Reference

Yunus M. Agamawi and Anil V. Rao. 2020. CGPOPS: A C++ Software for Solving Multiple-Phase Optimal Control Problems Using Adaptive Gaussian Quadrature Collocation and Sparse Nonlinear Programming.ACM Trans. Math. Softw. 46, 3, Article 25 (July 2020), 38 pages

[Paper link](https://doi.org/10.1145/3390463)

This project implements the algorithm in part <4.4 Computation Derivatives of NLP Functions> of the reference.

## TODO

- [X] Prepare
    - [X] Vector
    - [X] Matrix
    - [X] NdsclaFunction
    - [X] VectorFunction
    - [X] Complex
    - [ ] Bicomplex
    - [X] Dual <- Here
    - [ ] Hyper-Dual
- [X] Central Finite Difference
    - [X] CentralGrad
    - [X] CentralJacobi
    - [X] CentralHessian
- [X] Bicomplex-Step
    - [X] ComplexGrad
    - [X] ComplexJacobi
    - [ ] ComplexHessian
- [ ] Hyper-Dual
    - [X] DualGrad <- Here
    - [ ] DualJacobi
    - [ ] DualHessian