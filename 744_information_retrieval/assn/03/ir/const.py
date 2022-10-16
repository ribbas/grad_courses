DOC_PROC = 10_000
CHUNK_SIZE = 1_000_000

BYTE_FMT_CHAR = "I"
BYTE_FMT_SIZE = 4

QUERY_DOC_ID = 0

# arbitrary - 75,000 for keywords and 90,000 for questions
PARALLEL_THRESH = 90_000


class IDX:

    # shared indices
    TID = 0

    class DICT:

        # dictionary indices
        OF = 1  # offset
        WID = 2  # width
        DF = 3  # document frequency

    class INVF:

        # inverted file indices
        DID = 1  # document ID
        TF = 2  # term count
        STR = 3  # term string


JHED = "sahmed80"
