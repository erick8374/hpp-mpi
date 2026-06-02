# Paralelização Friendly Numbers com MPI

## Instruções para executar

### Compilação
```
$ mpicc friendly_mpi.c -o friendly_mpi
```

### Execução
```

$ mpirun -np 2 ./friendly_mpi 1 800000

$ mpirun -np 4 ./friendly_mpi 1 800000

$ mpirun -np 8 ./friendly_mpi 1 800000

$ mpirun -np 16 ./friendly_mpi 1 800000

$ mpirun -np 32 ./friendly_mpi 1 800000

```

