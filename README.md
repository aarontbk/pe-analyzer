# PE File Analyzer

A C++ tool for analyzing Portable Executable (PE) files, providing detailed information about their structure and contents.

## Features

- Parses and displays DOS header information
- Shows NT headers with machine type and characteristics
- Displays optional header details including entry point and image base
- Lists all data directories with their RVAs and sizes
- Shows section table with detailed information about each section
- Displays import and export tables
- Supports both 32-bit (PE32) and 64-bit (PE32+) PE files

## Output Format

The tool provides a structured output of the PE file's contents. Here's an example of the output format:

```
=== DOS Header ===
Magic number        : MZ
e_lfanew (PE offset): 78

=== NT Headers ===
Signature           : PE
Machine             : 8664 (AMD64)
Number of Sections  : 11
TimeDateStamp       : 68235b04 (2025-05-13 14:45:24 UTC)
SizeOfOptionalHeader: f0
Characteristics     : 22   (Executable, 64-bit)

=== Optional Header (PE32+) ===
Magic               : 20b (PE32+)
Entry Point         : 1443c0
Image Base          : 140000000
Section Alignment   : 1000
File Alignment      : 200
Subsystem           : 2    (Windows GUI)
DLL Characteristics : c160 (High Entropy VA, Dynamic Base, NX compatible, Control Flow Guard, Terminal Server aware)
Size of Image       : 2ff000
Size of Headers     : 400

=== Data Directories ===
[00] Export Table               : RVA: 24be64   Size: 87
[01] Import Table               : RVA: 24beec   Size: 64
[02] Resource Table             : RVA: 28b000   Size: 70640
...

=== Section Table ===
[0] .text
    RVA       : 1000
    RawOffset : 400
    VirtualSize : 2166c7
    RawSize     : 216800
    Flags       : 60000020 (Code, Execute, Read)
...

=== Import Table ===
Imported DLLs:
[0] chrome_elf.dll
    - GetInstallDetailsPayload
    - Ordinal: 24904
    ...

=== Export Table ===
- GetHandleVerifier
- GetPakFileHashes
- IsSandboxedProcess
```

## Building

```bash
make
```

## Usage

```bash
./bin/pe-analyzer <path-to-pe-file>
```

## Output Sections

1. **DOS Header**: Contains the MZ signature and PE file offset
2. **NT Headers**: Shows file signature, machine type, and characteristics
3. **Optional Header**: Displays PE32+ specific information
4. **Data Directories**: Lists all data directories with their RVAs and sizes
5. **Section Table**: Shows detailed information about each section
6. **Import Table**: Lists all imported DLLs and their functions
7. **Export Table**: Shows exported functions (if any)

## Notes

- All hex values are displayed without the "0x" prefix
- Section indices are shown in decimal format
- Imported functions can be shown by name or ordinal
- Section flags include descriptions of their characteristics 