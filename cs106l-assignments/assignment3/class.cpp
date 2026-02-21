#include"class.h"
#include<iostream>

StudentGrade::StudentGrade():name("Unknown"),score(0){};
StudentGrade::StudentGrade(std::string StudentName,int initial_score):
  name(StudentName),score(initial_score){};
char StudentGrade::CalculateGradeLetter() const{
  if(score>=90) return 'A';
  else if(score>=80) return 'B';
  else if(score>=70) return 'C';
  else return 'F';
}
int StudentGrade::getScore() const{
  std::cout<<"Your score is "<<score<<std::endl;
  
  return score;
}
std::string StudentGrade:: getName() const{
  std::cout<<"Your name is "<<name<<std::endl;
  return name;
}
void StudentGrade::setScore(int newScore){
  if(newScore>=0 && newScore<=100) score=newScore;
}