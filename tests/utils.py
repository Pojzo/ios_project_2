def convert_to_bytes(array: list[list[str]]) -> list[list[bytes]]:
    return [[x.encode() for x in vector] for vector in array]


