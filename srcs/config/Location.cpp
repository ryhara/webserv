#include "Location.hpp"

Location::Location(/* args */) : location("/"), get_method(true), post_method(false), delete_method(false), autoindex(false), alias(""), index(""), upload_path("")
{
}

Location::~Location()
{
}

Location::Location(std::string location) : get_method(true), post_method(false), delete_method(false), autoindex(false)
{
	this->location = location;
}
size_t		Location::addInfo(std::vector<std::vector<std::string> > &parseLines, size_t startIndex)
{
	this->cgi_extension.clear();
	this->redir_path.clear();
	std::vector<std::string> parseLine;
	while (startIndex < parseLines.size())
	{
		if (parseLines[startIndex][0] == "}")
			return startIndex;
		parseLine = parseLines[startIndex];
		if (parseLine[0] == "alias")
		{
			if (parseLine.size() != 3)
			{
				std::cout << "Location: invalid config : alias less or more arguments" << std::endl;
				exit (1);
			}
			if (parseLine[2] != ";")
			{
				std::cout << "Location: invalid config : alias not end with ';'" << std::endl;
				exit (1);
			}
			this->alias = parseLine[1];
		}
		else if (parseLine[0] == "index")
		{
			if (parseLine.size() != 3)
			{
				std::cout << "Location: invalid config : index less or more arguments" << std::endl;
				exit (1);
			}
			if (parseLine[2] != ";")
			{
				std::cout << "Location: invalid config : index not end with ';'" << std::endl;
				exit (1);
			}
			this->index = parseLine[1];
		}
		else if (parseLine[0] == "autoindex")
		{
			if (parseLine.size() != 3)
			{
				std::cout << "Location: invalid config : autoindex less or more arguments" << std::endl;
				exit (1);
			}
			if (parseLine[2] != ";")
			{
				std::cout << "Location: invalid config : autoindex not end with ';'" << std::endl;
				exit (1);
			}
			if (parseLine[1] == "on")
				this->autoindex = true;
			else if (parseLine[1] == "off")
				this->autoindex = false;
			else
			{
				std::cout << "Location: invalid config : autoindex on, off 以外の入力" << std::endl;
				exit (1);
			}
		}
		else if (parseLine[0] == "upload_path")
		{
			if (parseLine.size() != 3)
			{
				std::cout << "Location: invalid config : upload_path less or more arguments" << std::endl;
				exit (1);
			}
			if (parseLine[2] != ";")
			{
				std::cout << "Location: invalid config : upload_path not end with ';'" << std::endl;
				exit (1);
			}
			this->upload_path = parseLine[1];
		}
		else if (parseLine[0] == "cgi_extension")
		{
			if (parseLine.size() < 3)
			{
				std::cout << "Location: invalid config : cgi_path less arguments" << std::endl;
				exit (1);
			}
			if (parseLine.back() != ";")
			{
				std::cout << "Location: invalid config : cgi_path not end with ';'" << std::endl;
				exit (1);
			}
			for (size_t i = 1; i < parseLine.size() - 1; i++)
				this->cgi_extension.push_back(parseLine[i]);
		}
		else if (parseLine[0] == "redir_path")
		{
			if (parseLine.size() < 3)
			{
				std::cout << "Location: invalid config : redir_path less arguments" << std::endl;
				exit (1);
			}
			if (parseLine.back() != ";")
			{
				std::cout << "Location: invalid config : redir_path not end with ';'" << std::endl;
				exit (1);
			}
			for (size_t i = 1; i < parseLine.size() - 1; i++)
				this->redir_path.push_back(parseLine[i]);
		}
		else if (parseLine[0] == "method")
		{
			if (parseLine.size() < 3)
			{
				std::cout << "Location: invalid config : method less arguments" << std::endl;
				exit (1);
			}
			if (parseLine.back() != ";")
			{
				std::cout << "Location: invalid config : method not end with ';'" << std::endl;
				exit (1);
			}
			for (size_t i = 1; i < parseLine.size() - 1; i++)
			{
				if (parseLine[i] == "GET")
					this->get_method = true;
				else if (parseLine[i] == "POST")
					this->post_method = true;
				else if (parseLine[i] == "DELETE")
					this->delete_method = true;
				else
				{
					std::cout << "Location: invalid config : method GET, POST, DELETE 以外の入力" << std::endl;
					exit (1);
				}
			}
		}
		else
		{
			std::cout << parseLine[0] << std::endl;
			std::cout << "Location: invalid config : 不適切な要素" << std::endl;
			exit (1);
		}
		startIndex++;
	}
	std::cout << "Location: invalid config : location not end with '}'" << std::endl;
	exit (1);
}

std::string Location::get_path() const
{
	return this->location;
}

void Location::getLocation() const
{
	std::cout << "-----------location: " << this->location << "--------------" << std::endl;
	std::cout << "alias: " << this->alias << std::endl;
	std::cout << "index: " << this->index << std::endl;
	std::cout << "autoindex: " << this->autoindex << std::endl;
	std::cout << "upload_path: " << this->upload_path << std::endl;
	std::cout << "cgi_path: ";
	for (size_t i = 0; i < this->cgi_extension.size(); i++)
		std::cout << this->cgi_extension[i] << " ";
	std::cout << std::endl;
	std::cout << "redir_path: ";
	for (size_t i = 0; i < this->redir_path.size(); i++)
		std::cout << this->redir_path[i] << " ";
	std::cout << std::endl;
	std::cout << "get_method: " << this->get_method << std::endl;
	std::cout << "post_method: " << this->post_method << std::endl;
	std::cout << "delete_method: " << this->delete_method << std::endl << std::endl;
}