#ifndef CLASS_H
#define CLASS_H

#include<string>

class StudentGrade{
  private:
    std::string name;
    int score;
    char CalculateGradeLetter() const;
    

  public:
    StudentGrade();
    StudentGrade(std::string StudentName,int initial_score);
    int getScore() const;
    std::string getName() const;
    void setScore(int newScore);
    
}
;
#endif 
