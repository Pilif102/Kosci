#include "struktury.h"
#include "poczekalnia.h"
#include "gamemanager.h"
#include "playermanager.h"

#define MAX_EVENTS 10

#define MAXBUF 255
using namespace std;

Poczekalnia pocz;

void setnonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void do_use_fd(int ufd){
    char buff[MAXBUF];
    cout << ufd << endl;
    int size = read(ufd,buff,MAXBUF); //dodać exita i shutdowana przy błędzie
    //dodać testowanie gdzie znajduje się gracz, i osyłanie go do danej klasy
    switch(buff[0]){ //switch dla czytelnosci
    case 'r': //sygnały związane z poczekalnia, przeniesc do klasy poczekalnia
        //if(gracz not in poczekalnia)
        switch(buff[1]){
        case 'n':
            pocz.nowyPokoj(ufd);
            break;
        case 'r':
            pocz.podajPokoje(ufd);
            break;
        case 'j':
            //unikaj nie-numerow (teraz nie implementuje) i pustych wartosci
            string s = buff;
            s.erase(0,2);
            int wyb = stoi(s);
            pocz.wyborPokoju(ufd,wyb);
            break;
        }
        break;
    case 'g': //komendy dla gry
        //if w grze
        switch(buff[2]){
        case 's':
            //zglos gotowosc
            break;
        case 'r':
            //przerzuc kosci
            break;
        case 'c':
            //zablokowac kosc o danym id
            break;
        case 'p':
            //wybierz rubryke punktacji (id)
            break;
        // case 'z':
        //     //zmienione zasady (może, może nie)
        //     break;
        case 'q':
            //wyjdz z gry
            break;
        }

    case 'q':
        shutdown(ufd,SHUT_RDWR);
        close(ufd);
        break;
    default:
        write(ufd,"br",2);
    }
    if(buff[0]=='q'){
        return;
    }
    write(ufd,"\n",1);
}

int main()
{
    pocz.pokoje[0].liczbaGraczy=2;

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
            if (events[n].data.fd == fd) {

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
            } else {
                do_use_fd(events[n].data.fd);
            }
        }
    }

    shutdown(fd,SHUT_RDWR);
    close(fd);
    return 0;

}
