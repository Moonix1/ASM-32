#include "Gen.h"

#include "Log.h"
#include "Instructions.h"

namespace ASM32 {

    OBJGen::OBJGen(std::vector<std::shared_ptr<Expr>> exprs, std::string outputName)
        : m_Exprs(exprs), m_File(std::ofstream(outputName, std::ios::binary)) {
        COFFHeader coffHeader = {
            .mtype = 0x8664,
            .sections = 1,
            .tds = 0,
            .pst = 0x40,
            .numofs = 0,
            .opths = 0xE0,
            .charas = 0x0102
        };

        m_File.write(reinterpret_cast<char*>(&coffHeader), sizeof(coffHeader));
        
        GenerateProgram();
    }

    OBJGen::~OBJGen() {
        m_File.close();
    }

    void OBJGen::GenerateProgram() {
        std::unordered_map<std::string, u8> moveInstructionsReg = {
            { "rax", MOV_RAX },
            { "rbx", MOV_RBX },
            { "rcx", MOV_RCX },
            { "rdx", MOV_RDX },
            { "rsp", MOV_RSP },
            { "rbp", MOV_RBP },
            { "rsi", MOV_RSI },
            { "rdi", MOV_RDI },
            { "r8",  MOV_R8 },
            { "r9",  MOV_R9 },
            { "r10", MOV_R10 },
            { "r11", MOV_R11 },
            { "r12", MOV_R12 },
            { "r13", MOV_R13 },
            { "r14", MOV_R14 },
            { "r15", MOV_R15 },
        };
        
        while (m_Pos < m_Exprs.size()) {
            if (auto sectionExpr = std::dynamic_pointer_cast<SectionExpr>(m_Exprs[m_Pos])) {
                SectionHeader sHeader = {};
                memcpy(sHeader.name, sectionExpr->m_Section.c_str(), strlen(sectionExpr->m_Section.c_str()));
                sHeader.vsize = 0;
                sHeader.vaddr = 0;
                sHeader.rdatas = 0;
                sHeader.prdata = 0;
                sHeader.preloca = 0;
                sHeader.linen = 0;
                sHeader.charas = 0x60000020;

                m_File.write(reinterpret_cast<char*>(&sHeader), sizeof(sHeader));

                size_t sectionStartOffset = m_File.tellp();

                size_t alignmentPadding = (0x200 - (sectionStartOffset % 0x200)) % 0x200;
                if (alignmentPadding > 0) {
                    std::vector<u8> padding(alignmentPadding, 0);
                    m_File.write(reinterpret_cast<char*>(&padding[0]), padding.size());
                }

                m_Pos += 1;
                while (m_Pos < m_Exprs.size()) {
                    if (auto moveExpr = std::dynamic_pointer_cast<MoveExpr>(m_Exprs[m_Pos])) {
                        std::shared_ptr<RegisterExpr> regExpr = std::dynamic_pointer_cast<RegisterExpr>(moveExpr->m_LHS);
                        std::shared_ptr<NumberExpr> numExpr = std::dynamic_pointer_cast<NumberExpr>(moveExpr->m_RHS);

                        m_File.write(reinterpret_cast<char*>(&moveInstructionsReg[regExpr->m_Value]), 1);
                        GenerateNumber64(numExpr->m_Value);
                    } else if (auto haltExpr = std::dynamic_pointer_cast<HaltExpr>(m_Exprs[m_Pos])) {
                        u8 halt = 0xF4;
                        m_File.write(reinterpret_cast<char*>(&halt), 1);
                    } else break;

                    m_Pos += 1;
                }

                size_t sectionEndOffset = m_File.tellp();

                sHeader.rdatas = static_cast<u32>(sectionEndOffset - sectionStartOffset);
                sHeader.vsize = sHeader.rdatas;
                sHeader.prdata = static_cast<u32>(sectionStartOffset);

                sHeader.vaddr = m_VAddr;

                m_File.seekp(sectionStartOffset - sizeof(SectionHeader), std::ios::beg);
                m_File.write(reinterpret_cast<char*>(&sHeader), sizeof(sHeader));

                m_File.seekp(sectionEndOffset, std::ios::beg);

                m_VAddr += sHeader.vsize;
            } else {
                ERROR("objgen: invalid expr!");
                exit(1);
            }
        }
    }

    void OBJGen::GenerateNumber64(u64 val) {
        u8 buffer[8];
        for (int i = 0 ; i < 8 ; i++) {
            buffer[i] = static_cast<u8>(val & 0xFF);
            val >>= 8;
        }

        m_File.write(reinterpret_cast<char*>(buffer), sizeof(buffer));
    }

}