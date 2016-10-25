#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;


int main()
{
	map <string, string> txtmsg;
	list<string> msgs;
	txtmsg["CU"] = "see you";
	txtmsg[":-)"] = "I'm happy";
	txtmsg[":-("] = "I'm unhappy";
	txtmsg[";-)"] = "wink";
	txtmsg[":=P"] = "stick out my tongue";
	txtmsg["(~.~)"] = "sleepy";
	txtmsg["TA"] = "totally awesome";
	txtmsg["CCC"] = "Canadian Computing Competition";
	txtmsg["CUZ"] = "because";
	txtmsg["TY"] = "thank-you";
	txtmsg["YW"] = "you're welcome";
	txtmsg["TTYL"] = "talk to you later";
	string word;
	while (word !="TTYL" )
	{
		cin >> word;
		msgs.push_back(word);
	}
	string end;
	for (list<string>::const_iterator iter = msgs.begin(), end = msgs.end(); iter != end; ++iter) {
		if (txtmsg.count(*iter))
			cout << txtmsg[*iter] << endl;
		else
			std::cout << *iter << endl;
	}
	return 0;

}