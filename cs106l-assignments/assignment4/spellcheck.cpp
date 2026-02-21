#include "spellcheck.h"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
  //find_all()能找到所有单词的位置,并且用迭代器记录下来
  auto iters=find_all(source.begin(), source.end(),[](unsigned char ch){
    return std::isspace(ch);
  });
  //记载一个存储tokens的set
  std::set<Token> tokens;
  //transform()函数，五个参数，分别是第一组迭代器（begin()与end()-1），第二组迭代器（begin()+1，end()）,准备算完导入的容器，操作逻辑（用lambda）
  //iters.begin(),prev(iters.end()),next(iters.begin()),inserter,lambda
  //把transform的Token传到这个set里面
  std::transform(iters.begin(),std::prev(iters.end()),std::next(iters.begin()),std::inserter(tokens,tokens.end()),[&source](auto start,auto last){
    return Token(source,start,last);
  });
  //删除这些空单词
  std::erase_if(tokens,[](const Token& t){
    return t.content.empty();
  });
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  //先定义一个rv好写
  namespace rv=std::ranges::views;
  //这里的view是个range，经过了filter，transform,filter的range，后面通过调用begin(),end()开始计算
  auto view=source 
  //使用显式捕获是更有意义的
  //第一个filter，用于把不属于dictionary里面单词提取出来
    | rv::filter([&dictionary](const Token& t){
        return !dictionary.contains(t.content);
    }) 
  //第二个transform，不同于前面的，这个是range库里的transform，用于把符合条件的加工进view，这里就是把类里的Token和对应的suggestion返回出来
    | rv::transform([&dictionary](const Token& t){
        auto sug_view=dictionary | rv::filter([&t](const std::string& word){
          return levenshtein(t.content,word)==1;
        });
        std::set<std::string>suggestion(sug_view.begin(),sug_view.end());
        return Misspelling{t,suggestion};
    }) 
  //第三个filter，用于把suggestion里空的删了
    | rv::filter([](const Misspelling& m){
        return !m.suggestions.empty();
    });
  //最后执行就好了
  return std::set<Misspelling>(view.begin(),view.end());
};

/* Helper methods */

#include "utils.cpp"