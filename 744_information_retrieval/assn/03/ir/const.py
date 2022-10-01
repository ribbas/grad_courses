DOC_PROC = 10_000
CHUNK_SIZE = 1_000_000

BYTE_FMT_CHAR = "I"
BYTE_FMT_SIZE = 4

QUERY_DOC_ID = -1


class IDX:

    # shared indices
    TID = 0

    class DICT:

        # dictionary indices
        OF = 1
        LEN = 2
        DF = 3
        TF = 4

    class INVF:

        # inverted file indices
        DID = 1
        TC = 2
        STR = 3
