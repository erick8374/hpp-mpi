# Paralelização Friendly Numbers com MPI

## Instruções para executar

### Compilação
```
$ mpicc mpi_friendly_numbers.c -o mpi_friendly_numbers
```

### Execução
```

$ mpirun -np 2 ./mpi_friendly_numbers 1 800000 --hostfile hosts.txt

$ mpirun -np 4 ./mpi_friendly_numbers 1 800000 --hostfile hosts.txt

$ mpirun -np 8 ./mpi_friendly_numbers 1 800000 --hostfile hosts.txt

$ mpirun -np 16 ./mpi_friendly_numbers 1 800000 --hostfile hosts.txt

$ mpirun -np 32 ./mpi_friendly_numbers 1 800000 --hostfile hosts.txt

```

