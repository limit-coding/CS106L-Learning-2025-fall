/*
 * Part 3 参考代码 —— 不要直接包含此文件，只是复制到 user.h / user.cpp 用
 */

// ========== 在 user.h 的 class User 里、operator<< 声明下面加这两行： ==========
//
//   User& operator+=(User& rhs);
//   bool operator<(const User& rhs) const;
//

// ========== 在 user.cpp 里、拷贝赋值 operator= 实现后面加下面两段： ==========

User& User::operator+=(User& rhs)
{
  add_friend(rhs.get_name());   // 把对方的名字加进自己的好友列表
  rhs.add_friend(_name);        // 把自己的名字加进对方的好友列表
  return *this;
}

bool User::operator<(const User& rhs) const
{
  return _name < rhs._name;
}
