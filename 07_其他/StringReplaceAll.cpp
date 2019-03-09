void replace_all(string& str, const string& old_value, const string& new_value)
{
	int len = old_value.length();
	while (true) {
		string::size_type   pos(0);
		if ((pos = str.find(old_value)) != string::npos) {
			str.replace(pos, len, new_value);
		}
		else {
			break;
		}
	}
}