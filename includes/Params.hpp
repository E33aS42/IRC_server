#ifndef PARAMS_HPP
# define PARAMS_HPP

# include "All.hpp"

class Params
{

    public:

        Params();
        ~Params();

        // void            set_param(std::string name, std::string value);
        // std::string     get_param(std::string name);
        void               set_port(std::string port);
        void               set_password(std::string pass);
        std::string        get_port();
        std::string        get_password();

    private:
        // std::map<std::string,std::string> params;
        std::string        port;
        std::string        pass;



};

#endif /* ********************************************************** PARAMS_H */
