def calculate_checksum(data, k = 16):
	checksum = 0
	
	for i in range(0, len(data), k // 8):
		checksum += int.from_bytes(data[i : i + k // 8], byteorder = 'big', signed = False)
		checksum &= (1 << k) - 1

	return (1 << k) - checksum - 1


def is_checksum_correct(data, checksum, k = 16):
	assert checksum < (1 << k)
	
	for i in range(0, len(data), k // 8):
		checksum += int.from_bytes(data[i : i + k // 8], byteorder = 'big', signed = False)
		checksum &= (1 << k) - 1
	
	return checksum == (1 << k) - 1


sample1 = bytes([0x00, 0x11, 0x57, 0x09])
broken1 = bytes([0x00, 0x10, 0x57, 0x09])
assert is_checksum_correct(sample1, calculate_checksum(sample1))
assert not is_checksum_correct(broken1, calculate_checksum(sample1))

sample2 = bytes([0xff, 0x1a, 0x5c, 0xbd])
broken2 = bytes([0xff, 0x1b, 0x5d, 0xbd])
assert is_checksum_correct(sample2, calculate_checksum(sample2))
assert not is_checksum_correct(broken2, calculate_checksum(sample2))

