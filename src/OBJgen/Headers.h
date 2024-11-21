#pragma once

#include "Defines.h"

#ifdef _WIN64 || _WIN32

struct COFFHeader {
    u16 mtype;                      // Machine type
    u16 sections;                   // Number of sections
    u32 tds;                        // TimeDateStamp
    u32 pst;                        // Pointer to symbol table (should not be 0 if there's no symbol table)
    u32 numofs;                     // Number of symbols (can be 0 if no symbols)
    u16 opths;                      // Size of optional header
    u16 charas;                     // Characteristics (Executable)
};

struct SectionHeader {
    u8  name[8];                     // 8 bytes (section name, padded)
    u32 vsize;                      // 4 bytes (virtual size of the section);
    u32 vaddr;                      // 4 bytes (virtual address of the section)
    u32 rdatas;                     // 4 bytes (size of the section in the file)
    u32 prdata;                     // 4 bytes (offset to raw data in file)
    u32 preloca;                    // 4 bytes (pointer to relocations, 0 if none)
    u32 linen;                      // 4 bytes (pointer to line numbers, 0 if none)
    u32 charas;                     // 4 bytes (flags for section attributes)
};

struct Symbol {
    const char *name;
    u64 value;	                    // Address or offset
    u16 section;	                // Section
    u8  type;                       // Type of symbol
    u8  storagec;                   // Storage Class
};

#endif