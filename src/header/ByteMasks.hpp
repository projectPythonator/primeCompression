#ifndef BYTE_MASKS_HPP
#define BYTE_MASKS_HPP

// need to include file with rb5 primorial????

// TODO fix namespace name.
// TODO fix name for byte_mask_lookup there has to be a better one
// TODO change type of byte_mask_lookup to array type maybe
namespace ByteInfo {
    constexpr std::size_t bits_per_mask = 8u;

    enum Bitmasks : uint8_t {
        bitmask_0 = 0xfeU; // 1111 1110
        bitmask_1 = 0xfdU; // 1111 1101
        bitmask_2 = 0xfbU; // 1111 1011
        bitmask_3 = 0xf7U; // 1111 0111
        bitmask_4 = 0xefU; // 1110 1111
        bitmask_5 = 0xdfU; // 1101 1111
        bitmask_6 = 0xbfU; // 1011 1111
        bitmask_7 = 0x7fU; // 0111 1111
    };

    constexpr uint8_t byte_mask_lookup[RB5_PRIMORIAL][bits_per_mask] = {
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {254, 253, 251, 247, 239, 223, 191, 127},
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {253, 223, 239, 254, 127, 247, 251, 191},
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {251, 239, 254, 191, 253, 127, 247, 223},
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {247, 254, 191, 223, 251, 253, 127, 239}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {239, 127, 253, 251, 223, 191, 254, 247},
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {223, 247, 127, 253, 191, 254, 239, 251},
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {191, 251, 247, 127, 254, 239, 223, 253},
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {127, 191, 223, 239, 247, 251, 253, 254}
    };
}

#endif
