#include <string>
#include <iostream>

using namespace std;

int	main(void)
{
	string	name;
	string	answer;

	cout << "Type your name" << endl;
	cin >> name;
	cout << "Hi " + name + "!" << endl;
	cout << "Long time no see uh..." << endl;
	cout << "...how you doing?" << endl;
	cin >> answer;
	if (answer == "fine" || answer == "good")
		cout << "Good to know" << endl;
	else
		cout << "No one cares" << endl;
	return (0);
}
