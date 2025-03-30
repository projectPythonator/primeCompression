#include "header/InputToData.hpp"

namespace {
    constexpr std::uint8_t unsigned_zero = '0';
    constexpr std::uint8_t unsigned_new_line = '\n';
    constexpr std::uint8_t unsigned_line_break = unsigned_new_line - unsigned_zero;

    std::size_t setIndexLocations(
            const std::span<const std::uint8_t> buf, 
            const std::span<std::size_t> indices) {
        std::size_t step = std::distance(buf.begin(), std::find(buf.begin(), buf.end(), unsigned_new_line));
        std::size_t i = 0;
        for (std::size_t b = step; b < buf.size(); b += (step+1)) {
            if (buf[b] != unsigned_line_break)
                step++;
            indices[i++] = step;
        }
        return i;
    }
}

namespace ProjectIO {

    std::size_t BytesToData::readRBX() {
        return readBlockOfBytes(byteData.getSpan());
    }

    std::size_t BytesToData::readText() {
        byteData.resetSpan();
        sizeData.resetSpan();
        byteData.setSpan(0u, getNextTextBlock(byteData.getSpan()));
        sizeData.setSpan(0u, setIndexLocations(byteData.getSpan(), sizeData.getSpan()));
        return sizeData.getAmount();
    }

    std::size_t BinaryToData::readBinary() {
        return readBlockOfBinary(binaryData.getSpan());
    }
}
