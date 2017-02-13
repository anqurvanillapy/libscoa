#ifndef __LIBSCOA_ACTOR_MATCH_H
#define __LIBSCOA_ACTOR_MATCH_H
#include <list>
#include <utility>
#include <string>
#include <array>
#include <type_traits>
#include <functional>
#include "../libscoa.h"

enum func_type
{
    MATCHING,
    CATCH_ELEMENT,
    CALLFUNC,
    CONDNODE
};

class MatchFlowNode
{
  public:
    MatchFlowNode(
        func_type t, 
        const std::function<bool(uint32_t, std::function<bool(uint32_t, std::array<boost::any> &> func)
        :t(t), func(func) {}

    MatchFlowNode(
        func_type t, 
        std::function<bool(uint32_t, std::function<bool(uint32_t, std::array<boost::any> &> func)
        :t(t), func(func) {}    

    func_type t;
    std::function<bool(uint32_t, std::list<MatchFlowNode>&)> func;
    std::list<MatchFlowNode> next;
};

class Matcher
{
  public:
    Matcher(const std::array<scoa_msg_t &> &);

    Matcher &match(std::string str);
    template <typename Element>
    Matcher &catch_element(Element *ele);
    Matcher &callfunc(std::function<void()> &lambda);
    Matcher &then();
    Matcher &maybe();
    Matcher &end_then();
    void end();

  private:
    bool branch_match_succeed;
    bool finished;
    std::array<scoa_msg_t &> msg_arr;

    std::list<MatchFlowNode> *current_branch_flow;
    std::list<MatchFlowNode> match_flow;

    // cond_vec store <match_index, branch_match_succeed and prematch_pos>
    std::vector<std::list<MatchFlowNode> *> cond_flow_vec;
    std::vector<MatchFlowNode*> cond_node_vec;


    uint32_t cond_index;
    uint32_t match_index;
    uint32_t branch_index;
};

// class BaseAST
// {
// public:
//     virtual ~BastAST(){}
//     virtual void run(Matcher&) = 0;

// };

// class MatchAST : BaseAST
// {
// public:
//     MatchAST(const std::string& str):str(str) {}
//     void run(Matcher&) override;
// private:
//     std::string str;
// };

// template <typename Element>
// class GeteleAST : BaseAST
// {
// public:
//     GeteleAST(Element ele) : ele(ele) {}
//     void run(Matcher&) override;
// private:
//     Element ele;
// };

// class CondAST : BaseAST
// {
// public:
//     CondAST(std::unique_ptr<std::vector<BaseAST>> cond) : cond(cond) {}
//     void run(Matcher&) override;
// private:
//     std::unique_ptr<std::vector<BaseAST>> cond;
// };

// template <typename Func>
// class CallFuncAST
// {
// public:
//     CallFuncAST(Func& lambda): lambda(lambda) {}
//     void run(Matcher&) override;
// private:
//     Func& lambda;
// }

#endif // __LIBSCOA_ACTOR_MATCH_H

recv()
        .match("ok")
        .get_ele(&url)
        ->then(&url)
        .then()
        .match("GET")
        .get_ele(&request)
        .callfunc([]() { /* do something */ })
        .or
    ()
        .then()
        .match("POST")
        .get_ele(&request)
        .or
    ()
        .match("PUT")
        .callfunc([]() { /* do something */ })
        .cond_end()
        .or
    ()
        .match("DELETE")
        .callfunc([]() { /* do something */ })
        .end()
