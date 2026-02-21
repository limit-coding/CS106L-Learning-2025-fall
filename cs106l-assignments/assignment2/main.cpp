/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include<random>

std::string kYourName = "David Smith"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::ifstream ifs(filename);
  
  std::string line;
  std::set<std::string> s;
  while(std::getline(ifs,line)){
    s.insert(line);
  }
  ifs.close();
  return s;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */

std::string find_name(std::string name){
  char first=name[0];
  int it=name.find(' ');
  char last=name[it+1];
  return {first,last};
}

std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> find_res;
  auto str1=find_name(name);
  for(const std::string& str:students){
    if(find_name(str)==str1){
      find_res.push(&str);
    }
  }
  return find_res;

}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  //很高级的随机数
  if(matches.empty()) return "NO MATCHES FOUND.";

  // 1. 定义随机数引擎（类似于发牌员）
  std::random_device rd;  // 获取硬件随机数种子
  std::mt19937 gen(rd()); // 使用梅森旋转算法引擎

  // 2. 定义分布范围（类似于规定点数范围）
  std::uniform_int_distribution<> dis(0, matches.size() - 1);

  // 3. 生成随机数
  int target_index = dis(gen);
  for(int i=0;i<target_index;++i){
    matches.pop();
  }
  std::string result=*matches.front();
  return result;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
