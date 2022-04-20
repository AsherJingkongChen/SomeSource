def getlist(original_list):
	created_list = []
	bound = len(original_list) // 2 + (len(original_list) & 1)
	while len(original_list) != 0:
		for offset in range(bound):
			created_list.append(original_list[offset])
			del original_list[offset]
		bound = len(original_list) // 2 + (len(original_list) & 1)
	return created_list
if __name__ == '__main__':
	print(getlist( [1,2,3,4,5,6] ))
