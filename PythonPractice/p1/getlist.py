def getlist(original_list):
	created_list = []
	o_length = len(original_list)
	while o_length != 0:
		for get in range(o_length // 2 + (o_length & 1)):
			created_list.append(original_list[get])
			del original_list[get]
		o_length //= 2
	return created_list
if __name__ == '__main__':
	print(getlist([1,2,3,4,5,6]))
