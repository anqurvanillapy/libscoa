#ifndef __LIBSCOA_ACTOR_MATCH_H
#define __LIBSCOA_ACTOR_MATCH_H
#include <vector>

class Matcher
{
  public:
    Matcher(const vector<scoa_msg_t&> &);

    Matcher& match(string str);
    template <typename Element> Matcher& get_ele(Element ele);
    template <typename Func> Matcher& callfunc(Func& lambda);
    Matcher& then();
    Matcher& or();
    void end();

  private:
    bool on_branch_match_success;
    bool finished;
    std::vector<int> prematch_pos;
    std::vector<int> cond_vec;
    int              cond_index;
};

#endif // __LIBSCOA_ACTOR_MATCH_H

    recv()
        .match("ok")
        .get_ele(&url)
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
        .end()

