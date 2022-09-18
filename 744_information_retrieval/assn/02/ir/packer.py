from struct import pack, unpack


BYTE_FMT_CHAR = "i"
BYTE_FMT_SIZE = 4


class Packer:
    @staticmethod
    def encode(data: list[int]) -> bytes:

        return pack(BYTE_FMT_CHAR * len(data), *data)

    @staticmethod
    def decode(data: bytes) -> tuple[int, ...]:

        return unpack(BYTE_FMT_CHAR * (len(data) // BYTE_FMT_SIZE), data)
