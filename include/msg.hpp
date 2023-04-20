#include "rsa.hpp"

class Message {
    std::string m;
    int* c;

    RSA rsa;
    key public_key = rsa.get_keys().first;
    key private_key = rsa.get_keys().second;

public:

    std::pair<key, key> get_keys() { return std::make_pair(public_key, private_key); }


    Message& operator=(std::string str)
    {
        m = str;
        return *this;
    }

    friend std::istream& operator>>(std::istream& input, Message& msg) {
        std::getline(input, msg.m);
        return input;
    }

    friend std::ostream& operator<<(std::ostream& out, Message& msg)
    {
        out << msg.m;
        return out;
    }

    void encrypt() {
        int* c = new int[m.size()];
        for(auto i = 0; i < m.size(); i++) {
            c[i] = rsa.encrypt((int)(m[i]), public_key);
            m[i] = c[i];
        }
        this->c = c;
    }

    void decrypt(bool show = false) {
        for(auto i = 0; i < m.size(); i++) {
            m[i] = (char)(rsa.decrypt(c[i], private_key));
            if(show)
                std::cout << m[i];
        }
        delete[] c;
    }

    void set_message(std::string message) {
        m = message;
    }

    void show() {
        std::cout << m << std::endl;
    }

    
};

