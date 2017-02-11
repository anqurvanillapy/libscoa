#include "match.h"
Matcher::Matcher(const vector<scoa_msg_t &> & msgs_)
{
    msgs = msgs_;
    // on_branch_match_success initialize state should be true, because it match nothing
    branch_match_success = true;
    finished = false;
    cond_index = 0;
    match_index = 0; 
    ast_index = 0
}

Matcher& Matcher::match(string str)
{



}
template <typename Element>
Matcher& Matcher::get_ele(Element ele)
{   
}   
template <typename Func>
Matcher& Matcher::callfunc(Func &lambda)
{

}
Matcher& Matcher::then()
{
    cond_vec.push_back(std::make_tuple(match_index, branch_match_successed, new vector<uint32_t>(prematch_pos)));
    return *this;
}
Matcher& Matcher::or()
{
    auto state = cond_vec.back();
    std::tie(match_index, branch_match_successed and prematch_pos) = state;
    return *this;
}
bool Matcher::end()
{

}

private:
bool branch_match_success;
bool finished;
const std::vector<scoa_msg_t &> msgs;
std::vector<int> prematch_pos;
std::vector<int> cond_vec;
int cond_index;
uint32_t         match_index;       
