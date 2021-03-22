smatch sm;
string str = "hello_2019";
regex_match(str, sm, regex("([a-zA-Z]+)_([0-9]+)"));
sm.position();
sm.length();
for (auto x : sm)
	cout << x << endl;
