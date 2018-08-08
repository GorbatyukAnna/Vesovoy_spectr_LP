// Vesovoy_spectr_LP.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <array>
#include<chrono>
#include<thread>


using std::ifstream;
using std::ofstream;
using std::cout;
using std::string;
using std::vector;



vector<int> string_to_vector(string str)
{
	vector<int> vec;


	for (int i = 0; i < str.length(); i++)
	{
		
		if (str[i] == '0') vec.push_back(0);
		if (str[i] == '1') vec.push_back(1);
	}


	return vec;
}
void read_from_file(string file_name, vector<vector<int>>& vec)
{
	ifstream file(file_name);
	string str;
	vector<int> tmp;
	if (!file.is_open())
	{
		cout << "Enable to open file." << std::endl;
	}
	else
	{
		while (getline(file, str))
		{
			tmp = string_to_vector(str);
			vec.push_back(tmp);
		}

	}
	file.close();
}
vector<int> sum(vector<int> v1, vector<int> v2)
{
	vector<int> res;
	if (v1.size() != v2.size())
	{
		cout << " Vectors have different sizes";
		abort();
	}
	for (int i = 0; i < v1.size(); i++)
	{
		if ((v1[i] == 0 && v2[i] == 0) || (v1[i] == 1 && v2[i] == 1)) res.push_back(0);
		else res.push_back(1);
	}
	return res;
}
bool vec_has_no_elements(vector < vector<int>>& vec, int& k)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].size() != 0)
		{
			k = i;
			return false;
		}
	}
	return true;
}
bool vec_has_no_elements(vector < vector<int>>* vec, int size, int& k)
{
	for (int i = 0; i < size; i++)
	{
		if (vec[i].size() != 0)
		{
			k = i;
			return false;
		}
	}
	return true;
}
void get_iterations(vector < vector<int>>& vec,vector < vector<int>>& vec2, vector < vector<int>>* helper, int size, int k)
{
	vector<int> tmp;
	for (int i = k; i < size; i++)
	{
		for (int j = 0; j < helper[i].size(); j++)
		{
			tmp = sum(vec2[i], helper[i][j]);
			vec.push_back(tmp);

			for (int p = i + 1; p < size; p++)
			{
				helper[p].push_back(tmp);
			}

		}
		helper[i].erase(helper[i].begin(), helper[i].end());
	}
}
void sum_of_few_vec(vector<vector<int>>& vec, int size, int number)
{
	if (size < number) { cout << "Error. Enable vector size < number of elements for sum. "; return; }
	vector<vector<int>> * helper = new vector<vector<int>>[size];
	vector<int> tmp;
	vector<vector<int>> vec2;
	vec2 = vec;
	for (int i = 0; i < vec[0].size(); i++)
	{
		tmp.push_back(0);
	}
	vec.push_back(tmp);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j< size; j++)
		{
			tmp = sum(vec2[i], vec[j]);
			vec.push_back(tmp);
			for (int k = j + 1; k < size; k++)
			{
				helper[k].push_back(tmp);
			}
		}
	}
	int p;
	if (vec_has_no_elements(helper, size, p) == false)
	{
		get_iterations(vec,vec2, helper, size, p);
	}

	delete[] helper;
}
int vector_weight(vector<int> vec)
{
	int res = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == 1) res += 1;
	}
	return res;
}

void get_weight(vector<vector<int>> & vec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	ofstream file("Text_out.txt");
	vector<int> tmp;
	int tmp2;
	if (!file.is_open())
	{
		cout << "Enable to open file for writing." << std::endl;
	}
	else
	{
		while (!vec.empty())
		{
			tmp = vec.front();
			tmp2 = vector_weight(tmp);
			for (int i = 0; i < tmp.size(); i++)
			{
				file << tmp[i];
			}

			file << "	" << tmp2 << "\n";
			vec.erase(vec.begin());
		}
	}
	file.close();

}
int main()
{

	cout << "Please, enter a file name: ";
	string file;
	std::cin >> file;
	int size;
	vector<vector<int>> vec;
	read_from_file(file, vec);
	size = vec.size();
	sum_of_few_vec(vec, size, 2);
	std::thread th(get_weight, vec);
	//get_weight(vec);

	th.join();
	system("pause");
	return 0;
}

