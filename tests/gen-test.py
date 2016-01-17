#! /usr/bin/python3

# Generate test cases for every instruction using every kind of operands
# a file named mov-rt contains the following instruction:
# mov %eax, %t0

binary_instructions = ["mov"]
operands_types = ["r", "i", "m", "t"]
operands_for_type = {
        "r" : "%eax", # register
        "i" : "$0", # immediate
        "m" : "0x0(%eax)", # memory access
        "t" : "%t0", # temporary
        }

def valid_types(lhs, rhs):
    if rhs == "i":
        return False
    return True

for instr in binary_instructions:
    for lhs in operands_types:
        for rhs in operands_types:
            if not(valid_types(lhs, rhs)):
                continue

            filename = "{0}-{1}{2}.s".format(instr, lhs, rhs)
            file = open(filename, "w")
            file.write("  .text\n") # Section name
            file.write("{0} {1}, {2}".format(instr, operands_for_type[lhs],
                                                    operands_for_type[rhs]))
