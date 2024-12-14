# Standard Cluster Tool

## Installation

### Prerequisites

Ensure you have the following installed on your system:
- [Git](https://git-scm.com/)
- A compatible C++ compiler (e.g., GCC or Clang)
- make (build tool)

### Steps

1. Clone the Repository

Clone the repository to your local machine:
git clone https://github.com/srschofield/standard-cluster-tool.git
cd standard-cluster-tool
Build the Project
Compile the source code using the provided Makefile:
make
This will generate the required binaries in the project directory.
Install the Tool
To make the binary accessible system-wide, run:
make install
This will copy the binary to /usr/local/bin.
Run the Tool
If installed, you can run the tool system-wide using:
sct
Alternatively, if not installed, run it directly from the project directory:
./sct