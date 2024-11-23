

def startSide():
    print('#ifndef PRECOMPUTED_LOOKUP_TABLES_HPP')
    print('#define PRECOMPUTED_LOOKUP_TABLES_HPP')
    print()
    print('#include "ContainerIncludes.hpp"')
    print('#include "IntegralTypeIncludes.hpp"')
    print()
    print('namespace PresieveLookup {')
    print()

def endSide():
    print()
    print('}')
    print()
    print('#endif')
    print()

def printSievePart(sieves):
    # needs to print some kinda formatting
    pass

def midSide(sieves):
    print('constexpr std::array<std::array<uint8_t>, 16u> presieve_lookup = {\n')

    print('}\n')



def main():
    startSide()

    endSide()


