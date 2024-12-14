# Standard Cluster Tool - v1.6 (14 December 2024)

**Authors:** Oliver Warschkow, Steven R. Schofield, University College London

## Usage
```
sct <template> [<options> ...] <cluster-descriptor>
```

### Templates
- **Si**  
  Si(001) surface template generated using  
  VASP GGA_DFT (Warschkow et al. Surf.Sci. 2007).

- **Si2024**  
  Si(001) surface template generated using  
  CASTEP v19, PBE, USP, (8x4x1) MP, 800 eV, 20 layers (Schofield 2024).

- **Ge2024**  
  Ge(001) surface template generated using  
  CASTEP v19, PBE, USP, (8x4x1) MP, 800 eV, 20 layers (Schofield 2024).

- **DSi**  
  Si(001) surface template generated using  
  DMol3 PBE/DZP (Tracey et al. JCP 2012).

### Options
- **`-p2x1`**  
  Selects a p(2x1) flat-dimer pattern.  
  *Default dimer-buckling pattern.*

- **`-c4x2`**  
  Selects a c(4x2) buckled dimer pattern.

- **`-c4x2inv`**  
  Selects a c(4x2) buckled dimer pattern with opposite orientation to the `-c4x2` option.

- **`-p2x2`**  
  Selects a p(2x2) buckled dimer pattern.

- **`-p2x2inv`**  
  Selects a p(2x2) buckled dimer pattern with opposite orientation to the `-p2x2` option.

- **`-xyz`**  
  Prints cluster in XYZ file format.  
  *Default output format.*

- **`-gaussian`**  
  Prints cluster as a Gaussian input structure with `opt=ModRedunant` constraint flags.

- **`-ascending`**  
  Prints structure ordered by atomic layer starting with the deepest layer.  
  *Default ordering of atoms.*

- **`-descending`**  
  Prints structure ordered by atomic layer surface (dimer) layer.

- **`-hfirst`**  
  Reorders atoms so that the terminating hydrogen atoms come before any of the cluster atoms.  
  *Default output order.*

- **`-hlast`**  
  Reorders atoms so that the terminating hydrogen atoms come after the cluster atoms.

---

## Example Usage

### Single-Dimer Cluster
```
sct Si2024 -gaussian "4'" > my_cluster.gjf
```
Creates a single-dimer, single-row Si9H12 cluster in Gaussian input format.  
**Note:** The third argument is written as `<four><prime>`, where "four" refers to the number of silicon layers below the dimer, and "prime" indicates that this is not a "wide" cluster.

### Two-Dimer Cluster
```
sct Si2024 -gaussian "4'4'" > my_cluster.gjf
```
Creates a two-dimer cluster Si15H16.

### Four-Dimer-in-Two-Rows Cluster
```
sct Si2024 -gaussian "4'4'|4'4'" > my_cluster.gjf
```
Creates a four-dimer-in-two-rows cluster Si35H32.  
**Note:** Each "four" has a prime, and rows are separated by a vertical bar.

### Cluster with Varying Depth
```
sct Si2024 -gaussian "2'4'2'" > my_cluster.gjf
```
Creates a cluster with varying depth, combining numbers for different depths.


## Installation

### Prerequisites

Ensure you have the following installed on your system:
- [Git](https://git-scm.com/)
- A compatible C++ compiler (e.g., GCC or Clang)
- make (build tool)

### Steps

1. **Clone the Repository**  
Clone the repository to your local machine:  
```bash
git clone https://github.com/srschofield/standard-cluster-tool.git
cd standard-cluster-tool
```

2. **Build the Project**  
Compile the source code using the provided Makefile:
```bash
make
```
This will generate the required binaries in the project directory.

3. **Install the Tool**  
To make the binary accessible system-wide, run:
```bash
make install
```
This will copy the binary to /usr/local/bin.

4. **Run the Tool**  
If installed into your path, you can run the tool system-wide using:
```bash
sct
```
Alternatively, if not installed, run it directly from the project directory:
```bash
./sct
```

