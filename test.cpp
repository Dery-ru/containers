#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Log
{
private:
	int _day ;
	int _hours ;
	int _minutes ;
	int _id ;
	char _status ;
public:
	Log();
	Log(int day ,int hours ,int minutes ,int id ,char status);
	~Log();

	// Log operator+(const Log &b) const;
	int &getDay() const {return (this->_day);};
	int &getHours() const {return (this->_hours);};
	int &getMinutes() const {return (this->_minutes);};
	int &getId() const {return (this->_id);};
	int &getStatus() const {return (this->_status);};
	
	

};

Log::Log()
{
	int day  = 0;
	int hours = 0;
	int minutes = 0;
	int id = 0;
	char status = 0;
}

Log::Log(int day ,int hours ,int minutes ,int id ,char status):_day(day), _hours(hours), _minutes(minutes), _id(id), _status(status) {}

Log::~Log()
{
}


std::string my_substr(const std::string &s, int st, int fn)
{
	std::string temp;
	for(; st < fn - 1; ++st)
	{
		temp.push_back(s[st]);
	}
	return(temp);
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<int> elems;
	std::vector<std::string> ret;

	elems.push_back(0);
	for(int i = 1; i < s.length(); ++i)
	{
		if (s[i] == ',')
		{
			elems.push_back(i + 1);
		}
	}
	elems.push_back(s.length());

	// for(int i = 0; i< elems.size(); ++i)
	// 	std::cout << "[" << elems[i] << "]\t" ;

	for(int i = 1; i < elems.size();++i)
	{
		ret.push_back(my_substr(s,elems[i - 1], elems[i]));
	}

	return(ret);
}

int super_mega_counter(vector<Log> & logs)
{
	map<int> count_id = 0;
	for(int i = 1; i < logs.size(); ++i)
	{
		if (count_id(logs[i - 1].getId())

	}
}

int main()
{
	int count_log = 0;
	cin >> count_log;
	if (count_log < 2 || count_log > 200000)
	{
		std::cout << "count_log ERROR: count_log = " << count_log;
		retutn(1);
	}
	vector<Log> logs;
	for(int i = 0; count_log > i; ++i)
	{
		string rec; 
		cin >> rec;
		vector<std::string> log = split(rec, ' ');
		int day = atoi(log[0].c_str());
		int hours = atoi(log[1].c_str());
		int minutes = atoi(log[2].c_str());
		int id = atoi(log[3].c_str());
		char status = log[4][0];
		logs.push_back(Log(day, hours, minute, id, status));
	}
	vector<int> result;
	result.push_back(super_mega_counter(logs))
	return 0;
}
