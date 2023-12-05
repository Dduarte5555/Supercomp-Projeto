#!/bin/bash
##SBATCH -n 2
##SBATCH --time=00:10:00
##SBATCH --partition=normal

mpirun -n 2 ./MPICompilado

