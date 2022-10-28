#include <iostream>
#include <vector>
#include <string>
class Pasport
{
	private:

		std::string first_name;
		std::string last_name;
		std::string middle_name;

	public:
		Pasport(const std::string &_first_name, const std::string &_last_name, const std::string &_middle_name) : first_name(_first_name), last_name(_last_name), middle_name(_middle_name) {};
		~Pasport(){};
		const std::string &getFN(){return (this->first_name);}
		const std::string &getLN(){return (this->last_name);}
		const std::string &getMN(){return (this->middle_name);}

		void setFN(const std::string &_fn){this->first_name = _fn;}
		void setLN(const std::string &_ln){this->last_name = _ln;}
		void setMN(const std::string &_mn){this->middle_name = _mn;}

		friend std::ostream& operator<< (std::ostream &out, const Pasport &pasport)
		{
			out << "Pasport: " << pasport.first_name << "\n\t " << pasport.last_name << "\n\t " << pasport.middle_name << "\n";
			return out;
		}
};

class DataBase: protected Pasport
{
	private:
		std::vector<Pasport *> base;
	public:
		DataBase(){}
		~DataBase(){
			std::map<Pasport *>::iterator it_begin = this->base.begin();
			std::map<Pasport *>::iterator it_end = this->base.end();
			while (it_begin != it_end)
			{
				delete it_begin->second;
				++it_begin;
			}
			this->base.clear();
		}
		void SpellBook::learnSpell(Pasport *ps_ptr)
		{
			if (ps_ptr)
				base.insert(std::pair<std::string, Pasport *>(spell_ptr->getName(), spell_ptr->clone()));
		}

		void SpellBook::forgetSpell(std::string const &spell_name)
		{
			std::map<std::string, ASpell *>::iterator it = arr_spell.find(spell_name);
			if (it != arr_spell.end())
				delete it->second;
			arr_spell.erase(spell_name);
		}

		ASpell* SpellBook::createSpell(std::string const &spell_name)
		{
			std::map<std::string, ASpell *>::iterator it = arr_spell.find(spell_name);
			if (it != arr_spell.end())
				return arr_spell[spell_name];
			return NULL;
		}

};
int main(int argc, char const *argv[])
{
	Pasport ps("lol", "kek", "chebureck");
	std::cout << ps;

	return 0;
}
