#ifndef __LIBSCOA_ACTOR_MATCH_H
#define __LIBSCOA_ACTOR_MATCH_H
#include <vector>
#include <utility>
#include <string>

class Matcher
{
  public:
    Matcher(const std::vector<scoa_msg_t&> &);

    Matcher& match(std::string str);
    template <typename Element> Matcher& get_ele(Element ele);
    template <typename Func> Matcher& callfunc(Func& lambda);
    Matcher& then();
    Matcher& or();
    Matcher& cond_end();
    void end();

  private:
    bool branch_match_successed;
    bool finished;
    std::vector<BaseAST>  AST_vec;
    std::vector<uint32_t> prematch_pos;
    // store <match_index, branch_match_successed and prematch_pos>
    std::vector<std::tuple<uint32_t, bool, std::vector<int>> cond_vec;
    uint32_t         cond_index; 
    uint32_t         match_index;
    uint32_t         ast_index;    
};

class BaseAST
{
public:
    virtual ~BastAST(){}
    virtual void run(Matcher&) = 0;

};

class MatchAST : BaseAST
{
public:
    MatchAST(const std::string& str):str(str) {}
    void run(Matcher&) override;
private:
    std::string str;
};

class GeteleAST<typename Element> : BaseAST
{
public:
    GeteleAST(Element ele) : ele(ele) {}
    void run(Matcher&) override;
private:
    Element ele;
};

class CondAST : BaseAST
{
public:
    CondAST(std::unique_ptr<std::vector<BaseAST>> cond) : cond(cond) {}
    void run(Matcher&) override;
private:
    std::unique_ptr<std::vector<BaseAST>> cond;
};

class CallFuncAST<typename Func>
{
public:
    CallFuncAST(Func& lambda): lambda(lambda) {}
    void run(Matcher&) override;
private:
    Func& lambda;
}

#endif // __LIBSCOA_ACTOR_MATCH_H

    recv()
        .match("ok")
        .get_ele(&url) -> then(&url)
        .then()
            .match("GET")
            .get_ele(&request)
            .callfunc([]() { /* do something */ })
        .or()
            .then()
                .match("POST")
                .get_ele(&request)
            .or()
                .match("PUT")
                .callfunc([]() { /* do something */ })
            .cond_end()
        .or()
            .match("DELETE")
            .callfunc([]() { /* do something */ })
        .end()

