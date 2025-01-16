#include "struktury.h"
#include "poczekalnia.h"
#include "gamemanager.h"
#include "playermanager.h"

#define MAX_EVENTS 10

#define MAXBUF 255
using namespace std;

Poczekalnia pocz;
GameManager gra;
PlayerManager player;
PointsCount pts;

void setnonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void do_use_fd(int ufd){
    char buff[MAXBUF]; // dodaj ochrone przed przepelnieniem bufora na wszelki wypadek
    cout << "id:"<< ufd << endl;
    int size = 0;
    try{
        size = read(ufd,buff,MAXBUF); //dodać exita i shutdowana przy błędzie
        if(size == 0){
            throw(1);
        } else if(size>=MAXBUF){
            cout << "Niemożliwa ilosc znakow, rozłączam" << endl;
            throw(1);
        }

    } catch(int l){
        cout << "gracz sie rozlaczyl" << endl;
        if(player.podajPozycjeGracza(ufd)=='g'){
            gra.refactor(ufd,pocz.zwrocPokoj(ufd));
        }
        player.usunGracza(ufd);
        return;
    }
    if(size>=3){
        string command = string(buff,size);
        size = command.string::find(';');
        if(size == -1) return;
        command = command.string::substr(0,size);
        //dodać testowanie gdzie znajduje się gracz, i osyłanie go do danej klasy
        switch(player.podajPozycjeGracza(ufd)){ //switch dla czytelnosci
        case 'r': //sygnały związane z poczekalnia, przeniesc do klasy poczekalnia
            pocz.actionManager(ufd,command);
            break;
        case 'g': //komendy dla gry
            //if w grze
            gra.actionManager(ufd,command,pocz.zwrocPokoj(ufd));
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    struct epoll_event ev, events[MAX_EVENTS];
    int fd, conn_sock, nfds, epollfd;

    fd = socket(PF_INET,SOCK_STREAM,0);
    sockaddr_in addr{AF_INET,htons(9999),{htonl(INADDR_ANY) }};
    const int one = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));
    socklen_t addrlen = sizeof(addr);
    bind(fd,(sockaddr*)&addr,sizeof(addr));
    listen(fd,1);

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("epoll_ctl: fd");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == fd) { //połączenie, dodaje gracza

                conn_sock = accept(fd,
                                   (struct sockaddr *) &addr, &addrlen);
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                setnonblocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                              &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
                player.przygotujGracza(conn_sock);
                cout << "dołączył gracz o id: " << conn_sock <<endl;
            } else {
                do_use_fd(events[n].data.fd);
            }
        }
    }

    shutdown(fd,SHUT_RDWR);
    close(fd);
    return 0;
}
