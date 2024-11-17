# Custom Assembler and Stack-Based Virtual Machine

This repository demonstrates a complete stack-based virtual machine (VM) and an assembler to compile human-readable assembly-like code into binary instructions executable on the VM.

---

## Features

### Stack-Based Virtual Machine (VM)

- **Execution Environment**:
  - Stack-based architecture for computation.
  - Supports basic arithmetic and control instructions.
- **Instruction Set**:
  - Arithmetic: `Add`, `Sub`, `Multiply`, `Divide`
  - Control: `Halt`
- **Memory**:
  - 1 million addressable memory locations.
  - Stack pointer (`sp`) and program counter (`pc`) for execution tracking.
- **Error Handling**:
  - Stack underflow/overflow detection.
  - Out-of-bounds program counter handling.
  - Unrecognized instruction error.

### Assembler

- Converts high-level assembly-like code into binary machine instructions.
- Supports a basic instruction set for testing and execution on the VM.

### Lexer

- Tokenizes input assembly code into meaningful units for the assembler.
- Handles:
  - Special characters.
  - Whitespace removal.
  - Grouping symbols and operators.