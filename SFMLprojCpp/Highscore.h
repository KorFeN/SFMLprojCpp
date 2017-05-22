#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

using namespace std;

class Highscore
{
public:
	Highscore(int score, string name)
	{
		this->score = score;
		this->name = name;
	};
	Highscore() 
	{
		this->score = -1;
		this->name = "UNKNOWN";
	};
	~Highscore() {};

	int getScore() const { return this->score; };
	string getName() const { return this->name; };
	void setScore(int score) { this->score = score; };
	void setName(string name) { this->name = name; };

	Highscore& operator=(Highscore& otherObj) noexcept
	{
		if (this != &otherObj)
		{
			this->name = otherObj.name;
			this->score = otherObj.score;
		}
		return *this;
	}

private:
	int score;
	string name;
};


#endif // !HIGHSCORE_H
