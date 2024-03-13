#include "cpu.h"

// add instructions

void CPU::opcodeAddR8R8(Register &r1, Register &r2) {
    uint16_t result = r1.get() + r2.get();
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((r1.get() & 0x0F) + (r2.get() & 0x0F) > 0x0F);
    f.setSubtractFlag(false);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}

void CPU::opcodeAddHLN16(const uint16_t n) {
    uint32_t result = hl.get() + n;
    f.setCarryFlag(result > 0xFFFF);
    f.setHalfCarryFlag((hl.get() & 0x0FFF) + (n & 0x0FFF) > 0x0FFF);
    f.setSubtractFlag(false);
    hl.set(static_cast<uint16_t>(result));
}


void CPU::opcodeAddR16N8(RegisterPair &rp) {
    uint16_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint32_t result = rp.get() + n;
    rp.set(result);
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((rp.get() & 0x0F) + (n & 0x0F) > 0x0F);
    f.setSubtractFlag(false);
}

void CPU::opcodeAddR8N8(Register &r) {
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint16_t result = r.get() + n;
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((r.get() & 0x0F) + (n & 0x0F) > 0x0F);
    f.setSubtractFlag(false);
    r.set(result);
    f.setZeroFlag(r.get() == 0);
}

void CPU::opcodeAddSPE8() {
    int8_t e8 = emulator.memory->read(pc.get());
    pc.increment();
    int32_t result = static_cast<int32_t> (sp.get() + e8);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag((sp.get() & 0x0F) + (e8 & 0x0F) > 0x0F);
    f.setCarryFlag(((sp.get() ^ e8 ^ (result & 0xFFFF)) & 0x100) == 0x100);
    sp.set(result);
}

void CPU::opcodeAddAHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint16_t result = a.get() + value;
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((a.get() & 0x0F) + (value & 0x0F) > 0x0F);
    f.setSubtractFlag(false);
    a.set(result);
    f.setZeroFlag(a.get() == 0);
}

void CPU::opcodeAddHLSP() {
    uint32_t result = hl.get() + sp.get();
    f.setCarryFlag(result > 0xFFFF);
    f.setHalfCarryFlag((hl.get() & 0x0FFF) + (sp.get() & 0x0FFF) > 0x0FFF);
    f.setSubtractFlag(false);
    hl.set(result);
}

// ADC instructions

void CPU::opcodeAdcR8R8(Register &r1, Register &r2) {
    uint8_t carry = f.getCarryFlagValue();
    uint32_t result = r1.get() + r2.get() + carry;
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((r1.get() & 0x0F) + (r2.get() & 0x0F) + carry > 0x0F);
    f.setSubtractFlag(false);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}

void CPU::opcodeAdcR8N8(Register &r) {
    uint8_t carry = f.getCarryFlagValue();
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint32_t result = r.get() + n + carry;
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((r.get() & 0x0F) + (n & 0x0F) + carry > 0x0F);
    f.setSubtractFlag(false);
    r.set(result);
    f.setZeroFlag(r.get() == 0);
}

void CPU::opcodeAdcHL() {
    uint8_t carry = f.getCarryFlagValue();
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint32_t result = a.get() + value + carry;
    f.setCarryFlag(result > 0xFF);
    f.setHalfCarryFlag((a.get() & 0x0F) + (value & 0x0F) + carry > 0x0F);
    f.setSubtractFlag(false);
    a.set(result);
    f.setZeroFlag(a.get() == 0);
}

// SUB instructions

void CPU::opcodeSubR8R8(Register &r1, Register &r2) {
    uint16_t result = r1.get() - r2.get();
    f.setCarryFlag(r1.get() < r2.get());
    f.setHalfCarryFlag((r1.get() & 0x0F) < (r2.get() & 0x0F));
    f.setSubtractFlag(true);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}

void CPU::opcodeSubR8N8(Register &r) {
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint16_t result = r.get() - n;
    f.setCarryFlag(r.get() < n);
    f.setHalfCarryFlag((r.get() & 0x0F) < (n & 0x0F));
    f.setSubtractFlag(true);
    r.set(result);
    f.setZeroFlag(r.get() == 0);
}

void CPU::opcodeSubHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint16_t result = a.get() - value;
    f.setCarryFlag(a.get() < value);
    f.setHalfCarryFlag((a.get() & 0x0F) < (value & 0x0F));
    f.setSubtractFlag(true);
    a.set(result);
    f.setZeroFlag(a.get() == 0);
}

// SBC instructions

void CPU::opcodeSbcR8R8(Register &r1, Register &r2) {
    uint8_t carry = f.getCarryFlagValue();
    uint16_t result = r1.get() - r2.get() - carry;
    f.setCarryFlag(r1.get() < r2.get() + f.getCarryFlag());
    f.setHalfCarryFlag((r1.get() & 0x0F) < (r2.get() & 0x0F) + carry);
    f.setSubtractFlag(true);
    r1.set(result);
    f.setZeroFlag(r1.get() == 0);
}

void CPU::opcodeSbcR8N8(Register &r) {
    uint8_t carry = f.getCarryFlagValue();
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint16_t result = r.get() - n - carry;
    f.setCarryFlag(r.get() < n + f.getCarryFlag());
    f.setHalfCarryFlag((r.get() & 0x0F) < (n & 0x0F) + carry);
    f.setSubtractFlag(true);
    r.set(result);
    f.setZeroFlag(r.get() == 0);
}

void CPU::opcodeSbcHL() {
    uint8_t carry = f.getCarryFlagValue();
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint16_t result = a.get() - value - carry;
    f.setCarryFlag(a.get() < value + carry);
    f.setHalfCarryFlag((a.get() & 0x0F) < (value & 0x0F) + f.getCarryFlag());
    f.setSubtractFlag(true);
    a.set(result);
    f.setZeroFlag(a.get() == 0);
}


// Load instructions:


void CPU::opcodeLoadR8R8(Register &r1, Register &r2) {
    r1.set(r2.get());
}

void CPU::opcodeLoadR8N8(Register &r) {
    // get immediate value
    uint8_t value = emulator.memory->read(pc.get());
    pc.increment();
    r.set(value);
}

void CPU::opcodeLoadR16R8(RegisterPair &rp, Register &r) {
    uint16_t address = rp.get();
    emulator.memory->write(address, r.get());
}

void CPU::opcodeLoadR16N16(RegisterPair &rp) {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    rp.set(address);
}

void CPU::opcodeLoadHLN8() {
    uint8_t value = emulator.memory->read(pc.get());
    pc.increment();
    emulator.memory->write(hl.get(), value);
}

void CPU::opcodeLoadHLR8(Register &r) {
    emulator.memory->write(hl.get(), r.get());
}

void CPU::opcodeLoadR8HL(Register &r) {
    r.set(emulator.memory->read(hl.get()));
}

void CPU::opcodeLoadR16A(RegisterPair &rp) {
    opcodeLoadR16R8(rp, a);
}

void CPU::opcodeLoadN16A() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    emulator.memory->write(address, a.get());
}

void CPU::opcodeLoadAR16(RegisterPair &rp) {
    a.set(emulator.memory->read(rp.get()));
}


void CPU::opcodeLoadAN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    a.set(emulator.memory->read(address));
}

void CPU::LoadHN16A() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= 0xFF00;
    emulator.memory->write(address, a.get());
}

void CPU::LoadHCA() {
    uint8_t offset = c.get();
    uint16_t address = 0xFF00 + offset;
    emulator.memory->write(address, a.get());
}

void CPU::LoadHAN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= 0xFF00;
    a.set(emulator.memory->read(address));
}

void CPU::LoadHAC() {
    uint8_t offset = c.get();
    uint16_t address = 0xFF00 + offset;
    a.set(emulator.memory->read(address));
}

void CPU::LoadHLIA() {
    opcodeLoadHLR8(a);
    hl.increment();
}

void CPU::opcodeLoadHLDA() {
    // load value of register a into memory at address hl
    opcodeLoadHLR8(a);
    hl.decrement();
}

void CPU::opcodeLoadAHLD() {
    opcodeLoadR8HL(a);
    hl.decrement();
}

void CPU::opcodeLoadAHLI() {
    opcodeLoadR8HL(a);
    hl.increment();
}

void CPU::opcodeLoadSPN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    sp.set(address);
}

void CPU::opcodeLoadN16SP() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    emulator.memory->write(address, sp.get() & 0x00FF);
    emulator.memory->write(address + 1, sp.get() >> 8);
}

void CPU::opcodeLoadHLSPN8() {
    // get signed value, not unsigned
    int8_t e8 = emulator.memory->read(pc.get());
    pc.increment();
    int16_t result = sp.get() + e8;
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(((sp.get() ^ e8 ^ (result & 0xFFFF)) & 0x10) == 0x10);
    f.setCarryFlag(((sp.get() ^ e8 ^ (result & 0xFFFF)) & 0x100) == 0x100);
    hl.set(result);
}

void CPU::opcodeLoadSPHL() {
    sp.set(hl.get());
}


void CPU::opcodeIncR8(Register &r) {
    r.increment();
    // set flags
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag((r.get() & 0x0F) == 0);
}

void CPU::opcodeDecR8(Register &r) {
    r.decrement();
    // set flags
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag((r.get() & 0x0F) == 0x0F);
}

void CPU::opcodeIncR16(RegisterPair &rp) {
    rp.increment();
    // no flags set 
}

void CPU::opcodeDecR16(RegisterPair &rp) {
    rp.decrement();
}

void CPU::opcodeIncHL() {
    uint8_t value = emulator.memory->read(hl.get());
    value++;
    emulator.memory->write(hl.get(), value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag((value & 0x0F) == 0);
}

void CPU::opcodeDecHL() {
    uint8_t value = emulator.memory->read(hl.get());
    value--;
    emulator.memory->write(hl.get(), value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag((value & 0x0F) == 0x0F);
}

void CPU::opcodeIncSP() {
    sp.increment();
}

void CPU::opcodeDecSP() {
    sp.decrement();
}

// jump instructions

void CPU::opcodeJpN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    pc.set(address);
}

void CPU::opcodeJpHL() {
    pc.set(hl.get());
}

void CPU::opcodeJpCCN16(const bool condition) {
    if (condition) {
        opcodeJpN16();
    } else {
        pc.increment();
        pc.increment();
    }
}

// only two bytes are read
void CPU::opcodeJrN16() {
    int8_t e8 = emulator.memory->read(pc.get());
    pc.increment();
    int16_t result = pc.get() + e8;
    pc.set(result);
}

void CPU::opcodeJrCCN16(const bool condition) {
    if (condition) {
        opcodeJrN16();
    } else {
        pc.increment();
    }
}

// AND instructions

void CPU::opcodeAndR8R8(Register &r1, Register &r2) {
    r1.set(r1.get() & r2.get());
    f.setZeroFlag(r1.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(true);
    f.setCarryFlag(false);
}

void CPU::opcodeAndR8N8(Register &r) {
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    r.set(r.get() & n);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(true);
    f.setCarryFlag(false);
}

void CPU::opcodeAndHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    a.set(a.get() & value);
    f.setZeroFlag(a.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(true);
    f.setCarryFlag(false);
}

// OR instructions

void CPU::opcodeOrR8R8(Register &r1, Register &r2) {
    r1.set(r1.get() | r2.get());
    f.setZeroFlag(r1.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeOrR8N8(Register &r) {
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    r.set(r.get() | n);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeOrHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    a.set(a.get() | value);
    f.setZeroFlag(a.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

// Compare instructions

void CPU::opcodeCpR8R8(Register &r1, Register &r2) {
    uint8_t result = r1.get() - r2.get();
    f.setZeroFlag(result == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag((r1.get() & 0x0F) < (r2.get() & 0x0F));
    f.setCarryFlag(r1.get() < r2.get());
}

void CPU::opcodeCpR8N8(Register &r) {
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    uint8_t result = r.get() - n;
    f.setZeroFlag(result == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag((r.get() & 0x0F) < (n & 0x0F));
    f.setCarryFlag(r.get() < n);
}

void CPU::opcodeCpHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t result = a.get() - value;
    f.setZeroFlag(result == 0);
    f.setSubtractFlag(true);
    f.setHalfCarryFlag((a.get() & 0x0F) < (value & 0x0F));
    f.setCarryFlag(a.get() < value);
}

// XOR instructions

void CPU::opcodeXorR8R8(Register &r1, Register &r2) {
    r1.set(r1.get() ^ r2.get());
    f.setZeroFlag(r1.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeXorR8N8(Register &r) {
    uint8_t n = emulator.memory->read(pc.get());
    pc.increment();
    r.set(r.get() ^ n);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeXorHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    a.set(a.get() ^ value);
    f.setZeroFlag(a.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}


void CPU::opcodeDI() {
    ime = false;
}

void CPU::opcodeEI() {
    ime = true;
}

// register rotate instructions
void CPU::opcodeRLCA() {
    uint8_t value = a.get();
    f.setCarryFlag(value & 0x80);
    value = (value << 1) | (value >> 7);
    a.set(value);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}

void CPU::opcodeRRCA() {
    uint8_t value = a.get();
    f.setCarryFlag(value & 0x01);
    value = (value >> 1) | (value << 7);
    a.set(value);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}

void CPU::opcodeRLA() {
    uint8_t value = a.get();
    uint8_t carry = f.getCarryFlag();
    f.setCarryFlag(value & 0x80);
    value = (value << 1) | carry;
    a.set(value);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}

void CPU::opcodeRRA() {
    uint8_t value = a.get();
    uint8_t carry = f.getCarryFlag();
    f.setCarryFlag(value & 0x01);
    value = (value >> 1) | (carry << 7);
    a.set(value);
    f.setZeroFlag(false);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
}

void CPU::opcodeDAA() {
    uint8_t value = a.get();
    
    uint16_t adjustment = f.getCarryFlag() ? 0x60 : 0x00;
    if (f.getHalfCarryFlag() || (!f.getSubtractFlag() && (value & 0x0F) > 0x09)) {
        adjustment |= 0x06;
    }

    if (f.getCarryFlag() || (!f.getSubtractFlag() && value > 0x99)) {
        adjustment |= 0x60;
        f.setCarryFlag(true);
    }

    if (f.getSubtractFlag()) {
        value -= adjustment;
    } else {
        value += adjustment;
    }

    if ((adjustment & 0x60) == 0x60) {
        f.setCarryFlag(true);
    }

    f.setZeroFlag(value == 0);
    f.setHalfCarryFlag(false);
    a.set(value);
}

void CPU::opcodeCPL() {
    a.set(~a.get());
    f.setSubtractFlag(true);
    f.setHalfCarryFlag(true);
}

void CPU::opcodeCCF() {
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(!f.getCarryFlag());
}

void CPU::opcodeSCF() {
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(true);
}



// stack instructions
void CPU::opcodePop(RegisterPair &rp) {
    uint8_t low = emulator.memory->read(sp.get());
    sp.increment();
    uint8_t high = emulator.memory->read(sp.get());
    sp.increment();
    rp.set((high << 8) | low);
}

void CPU::opcodePush(RegisterPair &rp) {
    sp.decrement();
    emulator.memory->write(sp.get(), rp.get() >> 8);
    sp.decrement();
    emulator.memory->write(sp.get(), rp.get() & 0x00FF);
}

void CPU::opcodePop(WordRegister &r) {
    uint8_t low = emulator.memory->read(sp.get());
    sp.increment();
    uint8_t high = emulator.memory->read(sp.get());
    sp.increment();
    r.set((high << 8) | low);
}

void CPU::opcodePush(WordRegister &r) {
    sp.decrement();
    emulator.memory->write(sp.get(), r.get() >> 8);
    sp.decrement();
    emulator.memory->write(sp.get(), r.get() & 0x00FF);
}

void CPU::opcodeCallN16() {
    uint16_t address = emulator.memory->read(pc.get());
    pc.increment();
    address |= emulator.memory->read(pc.get()) << 8;
    pc.increment();
    opcodePush(pc);
    pc.set(address);
}

void CPU::opcodeCallCCN16(const bool condition) {
    if (condition) {
        opcodeCallN16();
    } else {
        pc.increment();
        pc.increment();
    }
}

void CPU::opcodeRstN8(const uint8_t n) {
    opcodePush(pc);
    pc.set(n);
}

void CPU::opcodeRet() {
    opcodePop(pc);
}

void CPU::opcodeRetCC(const bool condition) {
    if (condition) {
        opcodeRet();
    }
}

void CPU::opcodeReti() {
    opcodeRet();
    opcodeEI();
}

void CPU::opcodeRlcR8(Register &r) {
    uint8_t msb = r.get() >> 7;
    r.set((r.get() << 1) | msb);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(msb);
}

void CPU::opcodeRlcHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t msb = value >> 7;
    value = (value << 1) | msb;
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(msb);
}

void CPU::opcodeRrcR8(Register &r) {
    uint8_t lsb = r.get() & 0x01;
    r.set((r.get() >> 1) | (lsb << 7));
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeRrcHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t lsb = value & 0x01;
    value = (value >> 1) | (lsb << 7);
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeRlR8(Register &r) {
    uint8_t msb = r.get() >> 7;
    r.set((r.get() << 1) | f.getCarryFlag());
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(msb);
}

void CPU::opcodeRlHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t msb = value >> 7;
    value = (value << 1) | f.getCarryFlag();
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(msb);
}

void CPU::opcodeRrR8(Register &r) {
    uint8_t lsb = r.get() & 0x01;
    r.set((r.get() >> 1) | (f.getCarryFlag() << 7));
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeRrHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t lsb = value & 0x01;
    value = (value >> 1) | (f.getCarryFlag() << 7);
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeSlaR8(Register &r) {
    uint8_t msb = r.get() >> 7;
    r.set(r.get() << 1);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(msb);
}

void CPU::opcodeSlaHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t msb = value >> 7;
    value = value << 1;
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(msb);
}

void CPU::opcodeSraR8(Register &r) {
    uint8_t lsb = r.get() & 0x01;
    uint8_t msb = r.get() >> 7;
    r.set((r.get() >> 1) | (msb << 7));
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeSraHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t lsb = value & 0x01;
    uint8_t msb = value >> 7;
    value = (value >> 1) | (msb << 7);
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeSrlR8(Register &r) {
    uint8_t lsb = r.get() & 0x01;
    r.set(r.get() >> 1);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeSrlHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t lsb = value & 0x01;
    value = value >> 1;
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(lsb);
}

void CPU::opcodeSwapR8(Register &r) {
    uint8_t low = r.get() & 0x0F;
    uint8_t high = r.get() >> 4;
    r.set((low << 4) | high);
    f.setZeroFlag(r.get() == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeSwapHL() {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    uint8_t low = value & 0x0F;
    uint8_t high = value >> 4;
    value = (low << 4) | high;
    emulator.memory->write(address, value);
    f.setZeroFlag(value == 0);
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(false);
    f.setCarryFlag(false);
}

void CPU::opcodeBitU3R8(const uint8_t n, Register &r) {
    f.setZeroFlag(!(r.get() & (1 << n)));
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(true);
}

void CPU::opcodeBitU3HL(const uint8_t n) {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    std::cout << "VALUE: " << std::hex << (int) value << std::endl; 
    f.setZeroFlag(!(value & (1 << n)));
    f.setSubtractFlag(false);
    f.setHalfCarryFlag(true);
}

void CPU::opcodeSetU3R8(const uint8_t n, Register &r) {
    r.set(r.get() | (1 << n));
}

void CPU::opcodeSetU3HL(const uint8_t n) {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    value |= (1 << n);
    emulator.memory->write(address, value);
}

void CPU::opcodeResU3R8(const uint8_t n, Register &r) {
    r.set(r.get() & ~(1 << n));
}

void CPU::opcodeResU3HL(const uint8_t n) {
    uint16_t address = hl.get();
    uint8_t value = emulator.memory->read(address);
    value &= ~(1 << n);
    emulator.memory->write(address, value);
}



void CPU::opcodeCB() {
    uint8_t opcode = emulator.memory->read(pc.get());
    pc.increment();
        if (false) {
        std::cout << "Executing Opcode: " << std::hex << (int)opcode << std::endl;
        // print registers
        std::cout << "Registers: " << std::endl;
        std::cout << " A: " << std::hex << (int)a.get() ;
        std::cout << " B: " << std::hex << (int)b.get() ;
        std::cout << " C: " << std::hex << (int)c.get() ;
        std::cout << " D: " << std::hex << (int)d.get() ;
        std::cout << " E: " << std::hex << (int)e.get() ;
        std::cout << " H: " << std::hex << (int)h.get() ;
        std::cout << " L: " << std::hex << (int)l.get() ;
        std::cout << " BC: " << std::hex << (int)bc.get();
        std::cout << " DE: " << std::hex << (int)de.get();
        std::cout << " HL: " << std::hex << (int)hl.get();
        std::cout << " SP: " << std::hex << (int)sp.get() << std::endl; 
    }
    switch (opcode) {
        case 0x00: // RLC B
            opcodeRlcR8(b);
            break;
        case 0x01: // RLC C
            opcodeRlcR8(c);
            break;
        case 0x02: // RLC D
            opcodeRlcR8(d);
            break;
        case 0x03: // RLC E
            opcodeRlcR8(e);
            break;
        case 0x04: // RLC H
            opcodeRlcR8(h);
            break;
        case 0x05: // RLC L
            opcodeRlcR8(l);
            break;
        case 0x06: // RLC (HL)
            opcodeRlcHL();
            break;
        case 0x07: // RLC A
            opcodeRlcR8(a);
            break;
        case 0x08: // RRC B
            opcodeRrcR8(b);
            break;
        case 0x09: // RRC C
            opcodeRrcR8(c);
            break;
        case 0x0A: // RRC D
            opcodeRrcR8(d);
            break;
        case 0x0B: // RRC E
            opcodeRrcR8(e);
            break;
        case 0x0C: // RRC H
            opcodeRrcR8(h);
            break;
        case 0x0D: // RRC L
            opcodeRrcR8(l);
            break;
        case 0x0E: // RRC (HL)  
            opcodeRrcHL();
            break;
        case 0x0F: // RRC A
            opcodeRrcR8(a);
            break;
        case 0x10: // RL B
            opcodeRlR8(b);
            break;
        case 0x11: // RL C
            opcodeRlR8(c);
            break;
        case 0x12: // RL D
            opcodeRlR8(d);
            break;
        case 0x13: // RL E
            opcodeRlR8(e);
            break;
        case 0x14: // RL H
            opcodeRlR8(h);
            break;
        case 0x15: // RL L
            opcodeRlR8(l);
            break;
        case 0x16: // RL (HL)
            opcodeRlHL();
            break;
        case 0x17: // RL A
            opcodeRlR8(a);
            break;
        case 0x18: // RR B
            opcodeRrR8(b);
            break;
        case 0x19: // RR C
            opcodeRrR8(c);
            break;
        case 0x1A: // RR D
            opcodeRrR8(d);
            break;
        case 0x1B: // RR E
            opcodeRrR8(e);
            break;
        case 0x1C: // RR H
            opcodeRrR8(h);
            break;
        case 0x1D: // RR L
            opcodeRrR8(l);
            break;
        case 0x1E: // RR (HL)
            opcodeRrHL();
            break;
        case 0x1F: // RR A
            opcodeRrR8(a);
            break;
        case 0x20: // SLA B
            opcodeSlaR8(b);
            break;
        case 0x21: // SLA C
            opcodeSlaR8(c);
            break;
        case 0x22: // SLA D
            opcodeSlaR8(d);
            break;
        case 0x23: // SLA E
            opcodeSlaR8(e);
            break;
        case 0x24: // SLA H
            opcodeSlaR8(h);
            break;
        case 0x25: // SLA L
            opcodeSlaR8(l);
            break;
        case 0x26: // SLA (HL)
            opcodeSlaHL();
            break;
        case 0x27: // SLA A
            opcodeSlaR8(a);
            break;
        case 0x28: // SRA B
            opcodeSraR8(b);
            break;
        case 0x29: // SRA C
            opcodeSraR8(c);
            break;
        case 0x2A: // SRA D
            opcodeSraR8(d);
            break;
        case 0x2B: // SRA E
            opcodeSraR8(e);
            break;
        case 0x2C: // SRA H
            opcodeSraR8(h);
            break;
        case 0x2D: // SRA L
            opcodeSraR8(l);
            break;
        case 0x2E: // SRA (HL)
            opcodeSraHL();
            break;
        case 0x2F: // SRA A
            opcodeSraR8(a);
            break;
        case 0x30: // SWAP B
            opcodeSwapR8(b);
            break;
        case 0x31: // SWAP C
            opcodeSwapR8(c);
            break;
        case 0x32: // SWAP D
            opcodeSwapR8(d);
            break;
        case 0x33: // SWAP E
            opcodeSwapR8(e);
            break;
        case 0x34: // SWAP H
            opcodeSwapR8(h);
            break;
        case 0x35: // SWAP L
            opcodeSwapR8(l);
            break;
        case 0x36: // SWAP (HL)
            opcodeSwapHL();
            break;
        case 0x37: // SWAP A
            opcodeSwapR8(a);
            break;
        case 0x38: // SRL B
            opcodeSrlR8(b);
            break;
        case 0x39: // SRL C
            opcodeSrlR8(c);
            break;
        case 0x3A: // SRL D
            opcodeSrlR8(d);
            break;
        case 0x3B: // SRL E
            opcodeSrlR8(e);
            break;
        case 0x3C: // SRL H
            opcodeSrlR8(h);
            break;
        case 0x3D: // SRL L
            opcodeSrlR8(l);
            break;
        case 0x3E: // SRL (HL)
            opcodeSrlHL();
            break;
        case 0x3F: // SRL A
            opcodeSrlR8(a);
            break;
        case 0x40: // BIT 0, B
            opcodeBitU3R8(0, b);
            break;
        case 0x41: // BIT 0, C
            opcodeBitU3R8(0, c);
            break;
        case 0x42: // BIT 0, D
            opcodeBitU3R8(0, d);
            break;
        case 0x43: // BIT 0, E
            opcodeBitU3R8(0, e);
            break;
        case 0x44: // BIT 0, H
            opcodeBitU3R8(0, h);
            break;
        case 0x45: // BIT 0, L
            opcodeBitU3R8(0, l);
            break;
        case 0x46: // BIT 0, (HL)
            opcodeBitU3HL(0);
            break;
        case 0x47: // BIT 0, A
            opcodeBitU3R8(0, a);
            break;
        case 0x48: // BIT 1, B
            opcodeBitU3R8(1, b);
            break;
        case 0x49: // BIT 1, C
            opcodeBitU3R8(1, c);
            break;
        case 0x4A: // BIT 1, D
            opcodeBitU3R8(1, d);
            break;
        case 0x4B: // BIT 1, E
            opcodeBitU3R8(1, e);
            break;
        case 0x4C: // BIT 1, H
            opcodeBitU3R8(1, h);
            break;
        case 0x4D: // BIT 1, L
            opcodeBitU3R8(1, l);
            break;
        case 0x4E: // BIT 1, (HL)
            opcodeBitU3HL(1);
            break;
        case 0x4F: // BIT 1, A
            opcodeBitU3R8(1, a);
            break;
        case 0x50: // BIT 2, B
            opcodeBitU3R8(2, b);
            break;
        case 0x51: // BIT 2, C
            opcodeBitU3R8(2, c);
            break;
        case 0x52: // BIT 2, D
            opcodeBitU3R8(2, d);
            break;
        case 0x53: // BIT 2, E
            opcodeBitU3R8(2, e);
            break;
        case 0x54: // BIT 2, H
            opcodeBitU3R8(2, h);
            break;
        case 0x55: // BIT 2, L
            opcodeBitU3R8(2, l);
            break;
        case 0x56: // BIT 2, (HL)
            opcodeBitU3HL(2);
            break;
        case 0x57: // BIT 2, A
            opcodeBitU3R8(2, a);
            break;
        case 0x58: // BIT 3, B
            opcodeBitU3R8(3, b);
            break;
        case 0x59: // BIT 3, C
            opcodeBitU3R8(3, c);
            break;
        case 0x5A: // BIT 3, D
            opcodeBitU3R8(3, d);
            break;
        case 0x5B: // BIT 3, E
            opcodeBitU3R8(3, e);
            break;
        case 0x5C: // BIT 3, H
            opcodeBitU3R8(3, h);
            break;
        case 0x5D: // BIT 3, L
            opcodeBitU3R8(3, l);
            break;
        case 0x5E: // BIT 3, (HL)
            opcodeBitU3HL(3);
            break;
        case 0x5F: // BIT 3, A
            opcodeBitU3R8(3, a);
            break;
        case 0x60: // BIT 4, B
            opcodeBitU3R8(4, b);
            break;
        case 0x61: // BIT 4, C
            opcodeBitU3R8(4, c);
            break;
        case 0x62: // BIT 4, D
            opcodeBitU3R8(4, d);
            break;
        case 0x63: // BIT 4, E
            opcodeBitU3R8(4, e);
            break;
        case 0x64: // BIT 4, H
            opcodeBitU3R8(4, h);
            break;
        case 0x65: // BIT 4, L
            opcodeBitU3R8(4, l);
            break;
        case 0x66: // BIT 4, (HL)
            opcodeBitU3HL(4);
            break;
        case 0x67: // BIT 4, A
            opcodeBitU3R8(4, a);
            break;
        case 0x68: // BIT 5, B
            opcodeBitU3R8(5, b);
            break;
        case 0x69: // BIT 5, C
            opcodeBitU3R8(5, c);
            break;
        case 0x6A: // BIT 5, D
            opcodeBitU3R8(5, d);
            break;
        case 0x6B: // BIT 5, E
            opcodeBitU3R8(5, e);
            break;
        case 0x6C: // BIT 5, H
            opcodeBitU3R8(5, h);
            break;
        case 0x6D: // BIT 5, L
            opcodeBitU3R8(5, l);
            break;
        case 0x6E: // BIT 5, (HL)
            opcodeBitU3HL(5);
            break;
        case 0x6F: // BIT 5, A
            opcodeBitU3R8(5, a);
            break;
        case 0x70: // BIT 6, B
            opcodeBitU3R8(6, b);
            break;
        case 0x71: // BIT 6, C
            opcodeBitU3R8(6, c);
            break;
        case 0x72: // BIT 6, D
            opcodeBitU3R8(6, d);
            break;
        case 0x73: // BIT 6, E
            opcodeBitU3R8(6, e);
            break;
        case 0x74: // BIT 6, H
            opcodeBitU3R8(6, h);
            break;
        case 0x75: // BIT 6, L
            opcodeBitU3R8(6, l);
            break;
        case 0x76: // BIT 6, (HL)
            opcodeBitU3HL(6);
            break;
        case 0x77: // BIT 6, A
            opcodeBitU3R8(6, a);
            break;
        case 0x78: // BIT 7, B
            opcodeBitU3R8(7, b);
            break;
        case 0x79: // BIT 7, C
            opcodeBitU3R8(7, c);
            break;
        case 0x7A: // BIT 7, D
            opcodeBitU3R8(7, d);
            break;
        case 0x7B: // BIT 7, E
            opcodeBitU3R8(7, e);
            break;
        case 0x7C: // BIT 7, H
            opcodeBitU3R8(7, h);
            break;
        case 0x7D: // BIT 7, L
            opcodeBitU3R8(7, l);
            break;
        case 0x7E: // BIT 7, (HL)
            opcodeBitU3HL(7);
            break;
        case 0x7F: // BIT 7, A
            opcodeBitU3R8(7, a);
            break;
        case 0x80: // RES 0, B
            opcodeResU3R8(0, b);
            break;
        case 0x81: // RES 0, C
            opcodeResU3R8(0, c);
            break;
        case 0x82: // RES 0, D
            opcodeResU3R8(0, d);
            break;
        case 0x83: // RES 0, E
            opcodeResU3R8(0, e);
            break;
        case 0x84: // RES 0, H
            opcodeResU3R8(0, h);
            break;
        case 0x85: // RES 0, L
            opcodeResU3R8(0, l);
            break;
        case 0x86: // RES 0, (HL)
            opcodeResU3HL(0);
            break;
        case 0x87: // RES 0, A
            opcodeResU3R8(0, a);
            break;
        case 0x88: // RES 1, B
            opcodeResU3R8(1, b);
            break;
        case 0x89: // RES 1, C
            opcodeResU3R8(1, c);
            break;
        case 0x8A: // RES 1, D
            opcodeResU3R8(1, d);
            break;
        case 0x8B: // RES 1, E
            opcodeResU3R8(1, e);
            break;
        case 0x8C: // RES 1, H
            opcodeResU3R8(1, h);
            break;
        case 0x8D: // RES 1, L
            opcodeResU3R8(1, l);
            break;
        case 0x8E: // RES 1, (HL)
            opcodeResU3HL(1);
            break;
        case 0x8F: // RES 1, A
            opcodeResU3R8(1, a);
            break;
        case 0x90: // RES 2, B
            opcodeResU3R8(2, b);
            break;
        case 0x91: // RES 2, C
            opcodeResU3R8(2, c);
            break;
        case 0x92: // RES 2, D
            opcodeResU3R8(2, d);
            break;
        case 0x93: // RES 2, E
            opcodeResU3R8(2, e);
            break;
        case 0x94: // RES 2, H
            opcodeResU3R8(2, h);
            break;
        case 0x95: // RES 2, L
            opcodeResU3R8(2, l);
            break;
        case 0x96: // RES 2, (HL)
            opcodeResU3HL(2);
            break;
        case 0x97: // RES 2, A
            opcodeResU3R8(2, a);
            break;
        case 0x98: // RES 3, B
            opcodeResU3R8(3, b);
            break;
        case 0x99: // RES 3, C
            opcodeResU3R8(3, c);
            break;
        case 0x9A: // RES 3, D
            opcodeResU3R8(3, d);
            break;
        case 0x9B: // RES 3, E
            opcodeResU3R8(3, e);
            break;
        case 0x9C: // RES 3, H
            opcodeResU3R8(3, h);
            break;
        case 0x9D: // RES 3, L
            opcodeResU3R8(3, l);
            break;
        case 0x9E: // RES 3, (HL)
            opcodeResU3HL(3);
            break;
        case 0x9F: // RES 3, A
            opcodeResU3R8(3, a);
            break;
        case 0xA0: // RES 4, B
            opcodeResU3R8(4, b);
            break;
        case 0xA1: // RES 4, C
            opcodeResU3R8(4, c);
            break;
        case 0xA2: // RES 4, D
            opcodeResU3R8(4, d);
            break;
        case 0xA3: // RES 4, E
            opcodeResU3R8(4, e);
            break;
        case 0xA4: // RES 4, H
            opcodeResU3R8(4, h);
            break;
        case 0xA5: // RES 4, L
            opcodeResU3R8(4, l);
            break;
        case 0xA6: // RES 4, (HL)
            opcodeResU3HL(4);
            break;
        case 0xA7: // RES 4, A
            opcodeResU3R8(4, a);
            break;
        case 0xA8: // RES 5, B
            opcodeResU3R8(5, b);
            break;
        case 0xA9: // RES 5, C
            opcodeResU3R8(5, c);
            break;
        case 0xAA: // RES 5, D
            opcodeResU3R8(5, d);
            break;
        case 0xAB: // RES 5, E
            opcodeResU3R8(5, e);
            break;
        case 0xAC: // RES 5, H
            opcodeResU3R8(5, h);
            break;
        case 0xAD: // RES 5, L
            opcodeResU3R8(5, l);
            break;
        case 0xAE: // RES 5, (HL)
            opcodeResU3HL(5);
            break;
        case 0xAF: // RES 5, A
            opcodeResU3R8(5, a);
            break;
        case 0xB0: // RES 6, B
            opcodeResU3R8(6, b);
            break;
        case 0xB1: // RES 6, C
            opcodeResU3R8(6, c);
            break;
        case 0xB2: // RES 6, D
            opcodeResU3R8(6, d);
            break;
        case 0xB3: // RES 6, E
            opcodeResU3R8(6, e);
            break;
        case 0xB4: // RES 6, H
            opcodeResU3R8(6, h);
            break;
        case 0xB5: // RES 6, L
            opcodeResU3R8(6, l);
            break;
        case 0xB6: // RES 6, (HL)
            opcodeResU3HL(6);
            break;
        case 0xB7: // RES 6, A
            opcodeResU3R8(6, a);
            break;
        case 0xB8: // RES 7, B
            opcodeResU3R8(7, b);
            break;
        case 0xB9: // RES 7, C
            opcodeResU3R8(7, c);
            break;
        case 0xBA: // RES 7, D
            opcodeResU3R8(7, d);
            break;
        case 0xBB: // RES 7, E
            opcodeResU3R8(7, e);
            break;
        case 0xBC: // RES 7, H
            opcodeResU3R8(7, h);
            break;
        case 0xBD: // RES 7, L
            opcodeResU3R8(7, l);
            break;
        case 0xBE: // RES 7, (HL)
            opcodeResU3HL(7);
            break;
        case 0xBF: // RES 7, A
            opcodeResU3R8(7, a);
            break;
        case 0xC0: // SET 0, B
            opcodeSetU3R8(0, b);
            break;
        case 0xC1: // SET 0, C
            opcodeSetU3R8(0, c);
            break;
        case 0xC2: // SET 0, D
            opcodeSetU3R8(0, d);
            break;
        case 0xC3: // SET 0, E
            opcodeSetU3R8(0, e);
            break;
        case 0xC4: // SET 0, H
            opcodeSetU3R8(0, h);
            break;
        case 0xC5: // SET 0, L
            opcodeSetU3R8(0, l);
            break;
        case 0xC6: // SET 0, (HL)
            opcodeSetU3HL(0);
            break;
        case 0xC7: // SET 0, A
            opcodeSetU3R8(0, a);
            break;
        case 0xC8: // SET 1, B
            opcodeSetU3R8(1, b);
            break;
        case 0xC9: // SET 1, C
            opcodeSetU3R8(1, c);
            break;
        case 0xCA: // SET 1, D
            opcodeSetU3R8(1, d);
            break;
        case 0xCB: // SET 1, E
            opcodeSetU3R8(1, e);
            break;
        case 0xCC: // SET 1, H
            opcodeSetU3R8(1, h);
            break;
        case 0xCD: // SET 1, L
            opcodeSetU3R8(1, l);
            break;
        case 0xCE: // SET 1, (HL)
            opcodeSetU3HL(1);
            break;
        case 0xCF: // SET 1, A
            opcodeSetU3R8(1, a);
            break;
        case 0xD0: // SET 2, B
            opcodeSetU3R8(2, b);
            break;
        case 0xD1: // SET 2, C
            opcodeSetU3R8(2, c);
            break;
        case 0xD2: // SET 2, D
            opcodeSetU3R8(2, d);
            break;
        case 0xD3: // SET 2, E
            opcodeSetU3R8(2, e);
            break;
        case 0xD4: // SET 2, H
            opcodeSetU3R8(2, h);
            break;
        case 0xD5: // SET 2, L
            opcodeSetU3R8(2, l);
            break;
        case 0xD6: // SET 2, (HL)
            opcodeSetU3HL(2);
            break;
        case 0xD7: // SET 2, A
            opcodeSetU3R8(2, a);
            break;
        case 0xD8: // SET 3, B
            opcodeSetU3R8(3, b);
            break;
        case 0xD9: // SET 3, C
            opcodeSetU3R8(3, c);
            break;
        case 0xDA: // SET 3, D
            opcodeSetU3R8(3, d);
            break;
        case 0xDB: // SET 3, E
            opcodeSetU3R8(3, e);
            break;
        case 0xDC: // SET 3, H
            opcodeSetU3R8(3, h);
            break;
        case 0xDD: // SET 3, L
            opcodeSetU3R8(3, l);
            break;
        case 0xDE: // SET 3, (HL)
            opcodeSetU3HL(3);
            break;
        case 0xDF: // SET 3, A
            opcodeSetU3R8(3, a);
            break;
        case 0xE0: // SET 4, B
            opcodeSetU3R8(4, b);
            break;
        case 0xE1: // SET 4, C
            opcodeSetU3R8(4, c);
            break;
        case 0xE2: // SET 4, D
            opcodeSetU3R8(4, d);
            break;
        case 0xE3: // SET 4, E
            opcodeSetU3R8(4, e);
            break;
        case 0xE4: // SET 4, H
            opcodeSetU3R8(4, h);
            break;
        case 0xE5: // SET 4, L
            opcodeSetU3R8(4, l);
            break;
        case 0xE6: // SET 4, (HL)
            opcodeSetU3HL(4);
            break;
        case 0xE7: // SET 4, A
            opcodeSetU3R8(4, a);
            break;
        case 0xE8: // SET 5, B
            opcodeSetU3R8(5, b);
            break;
        case 0xE9: // SET 5, C
            opcodeSetU3R8(5, c);
            break;
        case 0xEA: // SET 5, D
            opcodeSetU3R8(5, d);
            break;
        case 0xEB: // SET 5, E
            opcodeSetU3R8(5, e);
            break;
        case 0xEC: // SET 5, H
            opcodeSetU3R8(5, h);
            break;
        case 0xED: // SET 5, L
            opcodeSetU3R8(5, l);
            break;
        case 0xEE: // SET 5, (HL)
            opcodeSetU3HL(5);
            break;
        case 0xEF: // SET 5, A
            opcodeSetU3R8(5, a);
            break;
        case 0xF0: // SET 6, B
            opcodeSetU3R8(6, b);
            break;
        case 0xF1: // SET 6, C
            opcodeSetU3R8(6, c);
            break;
        case 0xF2: // SET 6, D
            opcodeSetU3R8(6, d);
            break;
        case 0xF3: // SET 6, E
            opcodeSetU3R8(6, e);
            break;
        case 0xF4: // SET 6, H
            opcodeSetU3R8(6, h);
            break;
        case 0xF5: // SET 6, L
            opcodeSetU3R8(6, l);
            break;
        case 0xF6: // SET 6, (HL)
            opcodeSetU3HL(6);
            break;
        case 0xF7: // SET 6, A
            opcodeSetU3R8(6, a);
            break;
        case 0xF8: // SET 7, B
            opcodeSetU3R8(7, b);
            break;
        case 0xF9: // SET 7, C
            opcodeSetU3R8(7, c);
            break;
        case 0xFA: // SET 7, D
            opcodeSetU3R8(7, d);
            break;
        case 0xFB: // SET 7, E
            opcodeSetU3R8(7, e);
            break;
        case 0xFC: // SET 7, H
            opcodeSetU3R8(7, h);
            break;
        case 0xFD: // SET 7, L
            opcodeSetU3R8(7, l);
            break;
        case 0xFE: // SET 7, (HL)
            opcodeSetU3HL(7);
            break;
        case 0xFF: // SET 7, A
            opcodeSetU3R8(7, a);
            break;
        default:
            unimplementedOpcode();
            break;
    }
}
        

void CPU::unimplementedOpcode() {
    std::cerr << "Unimplemented opcode" << std::endl;
    exit(1);
}
