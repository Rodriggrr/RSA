#include "include/msg.hpp"

int main()
{
    Message m;

    //Mostrar chaves;
    std::cout << "Suas chaves são:\nPública:\nn: " ;
    std::cout << m.get_keys().first.b <<"\ne: " << m.get_keys().first.a;
    std::cout << "\n\nPrivada:\nn: ";
    std::cout << m.get_keys().second.b <<"\nd: " << m.get_keys().second.a << '\n';
    //

    std::cout << "\nDigite sua mensagem: \n";
    std::cin >> m;
    m.encrypt();
    std::cout << "\nMensagem Encriptada: " << m;
    std::cout << "\nDecriptando... (isso pode demorar um pouco.)\n";
    m.decrypt();
    std::cout << "Mensagem Decriptada: " << m << "\n";

    return 0;
}