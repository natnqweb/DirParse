#pragma once
#include "dirparser.h"
#include <filesystem>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <io.h>
#include <fstream>
#include <string>
#include "thread_pool.h"
class Dirparser  {

public:
	
	using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

	Dirparser() {
		//  check how many threads do we have
		num_threads = std::thread::hardware_concurrency();
		
	}
	~Dirparser() {

	}
	struct stat  info {};
	bool check_if_path_exists(std::string path) {
		int erno = -1;
		auto ErrorMsg = [&](std::string path)
		{
			_get_errno(&erno);

			
		};
		erno = -1;
		if (stat(path.c_str(), &info) != 0)
			ErrorMsg(path);
		if (_access(path.c_str(), 0) != 0)
			ErrorMsg(path);
		if (std::filesystem::exists(path) == 0)
			ErrorMsg(path);
		if (erno < 0)
			return true;
		else
		{

			return false;
		}
	}
	void set_path(std::string path) {
		if (std::filesystem::exists(path))
		_path = path;
	}
	std::string get_path() {
		return _path;
	}
	long long get_num_of_empty_files() {
		return empty_files;
	}
	long long get_num_of_lines_in_file(std::string filename) {

		std::string line;   // To read each line from code
		int count = 0;    // Variable to keep count of each line

		std::ifstream mFile(filename);

		if (mFile.is_open())
		{
			while (mFile.peek() != EOF)
			{
				std::getline(mFile, line);
				count++;
			}
			mFile.close();

		}
		else {
			empty_files++;
			return 0;
		}
		return count;
	}
	// checks non recursive search only one directory no subdirs
	void parse_all_single_dir() {
		// pool constructor 
		thread_pool pool(num_threads);
		// variable for saving number of lines
		long long total_number_of_lines = 0;
		// push task as lambda
		pool.push_task([&] {
		for (const auto& entry : std::filesystem::directory_iterator(_path)) {

			std::cout << entry.path().string() << std::endl;

		}
			});
		// push task as lambda
		pool.push_task([&] {
		for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		number_of_lines_in_dir += get_num_of_lines_in_file(entry.path().string());
		}
			});
		// when tasks done get print results
		pool.wait_for_tasks();
		std::cout << "begin path : " << _path << std::endl;
		std::cout << "number of lines inside files : " << number_of_lines_in_dir << std::endl;
		std::cout << "number of items without lines : " << get_num_of_empty_files() << std::endl;


	}
	long print_size_of_dirs() {
		long i = 0;
		for (const auto& dirEntry : recursive_directory_iterator(_path))
			i++;


		return i;
	}
	void parse_all_recursive() 
	{
		thread_pool pool(num_threads);
		long i = 0;
		// output all directories to console 
		pool.push_task([&] {
			for (const auto& dirEntry : recursive_directory_iterator(_path)) {
			std::cout << dirEntry << std::endl;
			i++;
		}	
			});
		// check how many lines we have as separate task becouse we want smooth output on console, if not in separate it would block console output
		pool.push_task([&] {
			for (const auto& dirEntry : recursive_directory_iterator(_path))
			number_of_lines_in_dir += get_num_of_lines_in_file(dirEntry.path().string());
			});
		// when tasks are done  print results
		pool.wait_for_tasks();
		
			std::cout << "begin path : "<< _path << std::endl;
			std::cout << "number of lines inside files : " << number_of_lines_in_dir << std::endl;
			std::cout <<"number of items without lines : " << get_num_of_empty_files() << std::endl;
			std::cout <<"recursive interations : " << i << std::endl;
		



				
		}
		
		
	
	
	
private:
	unsigned int num_threads = 0;
	std::string _path = "";
	long long empty_files = 0;
	long long number_of_lines_in_dir=0;



};


