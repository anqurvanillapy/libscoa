#include "match.h"
Matcher::Matcher(std::list<scoa_msg_t &> &msg_arr)
{
    msg_arr = msg_arr;
    current_branch_flow = &match_flow;
}

Matcher &Matcher::match(const string &str)
{
    current_branch_flow->push_back(MatchFlowNode(
        MATCHING,
        [=](uint32_t index, std::array<boost::any> &msg) -> bool {
            if (match_index >= msg.size())
                return false;
            auto msg_str_ptr = msg[index];
            if (
                msg_str.type() == typeid(string) && (boost::any_cast<shared_ptr<string>>(msg_str_ptr)->compare(str) == 0))
                return true;
            return false;
        }));
    return *this;
}

template <typename Element>
Matcher &Matcher::catch_element(Element *ele)
{
    current_branch_flow->push_back(MatchFlowNode(
        CATCH_ELEMENT,
        [=](uint32_t index, std::array<boost::any> &msg) -> bool {
            if (match_index >= msg.size())
                return false;
            auto result = msg[index];
            if (result.type() != typeid(Element))
                return false;
            *ele = boost::any_cast<Element>(msg[index]);
            return true;
        }));
    return *this;
}

Matcher &Matcher::callfunc(std::function<void()> &lambda)
{
    current_branch_flow->push_back(MatchFlowNode(
        CALLFUNC,
        [=](uint32_t index, std::array<boost::any> &msg) -> bool {
            if (match_index >= msg.size())
                return false;
            auto result = msg[index];
            if (result.type() != typeid(Element))
                return false;
            *ele = boost::any_cast<Element>(msg[index]);
            return true;
        }));
    return *this;
}

Matcher &Matcher::then()
{

    //save current_branch_flow
    cond_flow_vec.push_back(current_branch_flow);
    //if current_branch_flow is empty, need to push an empty condition node
    if (current_branch_flow->empty())
        current_branch_flow->push_back(MatchFlowNode(CONDNODE, nullptr));
    //save current MatchFlow node
    cond_node_vec.push_back(&current_branch_flow->back());
    add_branch();
    return *this;

}

Matcher &Matcher::maybe()
{
    auto last_cond_node = cond_node_vec.back();
    current_branch_flow = &(last_cond_node->next);
    add_branch();
    return *this;
}

Matcher &Matcher::end_then()
{
    current_branch_flow = cond_flow_vec.pop_back();
    cond_node_vec.pop_back();
    return *this;
}

bool Matcher::end()
{
}

void add_branch()
{
    //switch to last MatchFlow node
    current_branch_flow = &(current_branch_flow->back().next);
    //add a condition node
    current_branch_flow.push_back(MatchFlowNode(CONDNODE, nullptr));
    //switch to condition node
    current_branch_flow = &(current_branch_flow->back().next);
}

recv()
    .match("ok")
    .catch_ele(&url)
    .then()
        .match("GET")
        .catch_ele(&request)
        .callfunc([]() { /* do something */ })
    .maybe()
        .then()
            .match("POST")
            .catch_ele(&request)
        .maybe()
            .match("PUT")
            .callfunc([]() { /* do something */ })
        .cond_end()
    .maybe()
        .match("DELETE")
        .callfunc([]() { /* do something */ })
    .end()
