int find(string worlds[], string line)
{
	int count = 0;
	int len = line.length();
	int start = 0;
	int end = 0;
	bool find = false;
	for (int i = 0; i < len; i++) {
		if (find) {
			if (!isalpha(line[i])) {
				end = i;
				find = 0;
				worlds[count++] = line.substr(start, end - start);
			}
		}
		else if (isalpha(line[i])) {
			start = i;
			find = true;
		}
	}
	if (find) {
		end = len - 1;
		find = 0;
		worlds[count++] = line.substr(start, end - start + 1);
	}
	return count;
}