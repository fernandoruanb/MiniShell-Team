#include <string>
#include <iostream>

using namespace std;


//Calculator
int	is_sign(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

void	make_count(string input)
{
	int	i;
	int	a, b;

	if (input == "exit")
		return ;
	i = 0;
	while (i < input.length() && !is_sign(input[i]))
		i++;
	a = stoi(input.substr(0, i));
	b = stoi(input.substr(i + 1));
	switch (input[i])
	{
		case '+':
			cout << a + b << endl;
			break;
		case '-':
			cout << a - b << endl;
			break;
		case '*':
			cout << a * b << endl;
			break;
		case '/':
			if (b == 0)
			{
				cout << "\033[33mDivision to 0 is forbiden.\033[0m" << endl;
				break;
			}
			cout << a / b << endl;
			break;
	}
}

int	main(void)
{
	string	temp;

	cout << "\033[33mWelcome to the calculator!\033[0m" << endl;
	while (temp != "exit")
	{
		cout << "\033[33mEnter the calculation: \033[0m";
		cin >> temp;
		make_count(temp);
	}
	return (0);
}

// int	main(void)
// {
// 	string	name;
// 	string	answer;

// 	cout << "Type your name" << endl;
// 	cin >> name;
// 	cout << "Hi " + name + "!" << endl;
// 	cout << "Long time no see uh..." << endl;
// 	cout << "...how you doing?" << endl;
// 	cin >> answer;
// 	if (answer == "fine" || answer == "good")
// 		cout << "Good to know" << endl;
// 	else
// 		cout << "No one cares" << endl;
// 	return (0);
// }
