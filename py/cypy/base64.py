def base64(bs):
    if not isinstance(bs, (bytes, bytearray)):
        raise TypeError
    code = ''.join([bin(b)[2:].zfill(8) for b in bs])
