#! /usr/bin/python3

# Generate test cases for every instruction using every kind of operands
# a file named mov-rt contains the following instruction:
# mov %eax, %t0

binary_instructions = ["mov", "add", "imul", "lea", "sal", "sar", "sub"]
need_suffix = ["mov", "add", "sub"]
operands_types = ["r", "i", "m", "t"]
operands_for_type = {
        "r" : "%eax", # register
        "i" : "$0", # immediate
        "m" : "0x0(%eax)", # memory access
        "t" : "%t0", # temporary
        }

def valid_types(instr, lhs, rhs):
    if rhs == "i":
        return False
    if rhs == "m" and lhs == "m":
        return False
    if instr == "lea" and (lhs != "m" or rhs != "r"):
        return False
    if instr == "imul" and rhs == "m":
        return False
    if instr == "sal" and (lhs != "i" or (rhs != "r" or rhs != "m")):
        return False
    if instr == "sar" and (lhs != "i" or (rhs != "r" or rhs != "m")):
        return False

    return True

def add_instr_suffix(instr, lhs, rhs):
    if (rhs == "m" or rhs == "t") and instr in need_suffix:
        return instr + "l"
    return instr

for instr in binary_instructions:
    for lhs in operands_types:
        for rhs in operands_types:
            if not(valid_types(instr, lhs, rhs)):
                continue

            suff_instr = add_instr_suffix(instr, lhs, rhs)
            filename = "{0}-{1}{2}.s".format(suff_instr, lhs, rhs)
            file = open(filename, "w")
            file.write("  .text\n") # Section name
            file.write("{0} {1}, {2}".format(suff_instr, operands_for_type[lhs],
                                                    operands_for_type[rhs]))
