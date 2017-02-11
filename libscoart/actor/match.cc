#include "match.h"
Matcher::Matcher(const vector<scoa_msg_t &> & msgs_)
{
    msgs = msgs_;
    branch_match_success = false;
    finished = false;
    cond_index = 0;
}

Matcher& Matcher::match(string str)
{
    if (prematch_pos.empty)
    {
        
    }
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

}
Matcher& Matcher:: or ()
{

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