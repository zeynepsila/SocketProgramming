#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>  //Linux için
#include <arpa/inet.h>   //Linux için
//#include <Winsock2.h>  //windows için
//#include <winsock.h>   //windows için


int main(void)
{
    //TCP SOCKETİ OLUŞTURMA ISLEMI
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); //AP_INET = IPv4, SOCK_STREAM = TCP

    if(socket_desc < 0){
        printf("Hata : Socket olusturulamadi!\n");
        return EXIT_FAILURE;
    }

    printf("Socket basariyla olusturuldu!\n");

    //SERVER ADRESINI OLUSTURMA ISLEMI
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //SOCKETI ADRESE BAGLAMA ISLEMI
    int bind_result;
    bind_result = bind(socket_desc, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if(bind_result < 0){
        printf("HATA: BIND ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("PORT NUMARASI: %d\n", ntohs(server_addr.sin_port));
    printf("BIND ISLEMI BASARILI!\n");

    //GELECEK OLAN ISTEGI DINLEME ISTEGI
    int listen_status = listen(socket_desc, 1); //socket adı ve kaç kullanıcının baglanmasını istediğimiz sayı

    if(listen <0 ){
        printf("HATA: DINLEME ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("DINLEME ISLEMI BASLADI!\n");

    //ISTEMCI ADRESINI İLKLEME ISLEMI
    struct sockaddr_in client_addr;
    socklen_t client_socklen = sizeof(client_addr);

    int client_sock_desc;
    client_sock_desc = accept(socket_desc, (struct sockaddr*) &client_addr, &client_socklen);

    if(client_sock_desc < 0 ){
        printf("HATA: ISTEK KABUL ETME BASARISIZ OLDU!\n");
    }

    printf("ISTEK BASARIYLA KABUL EDILDI!\n");

    //ISTEMCIDEN GELEN MESAJ ICIN BELLEKTEN YER AYIR
    char client_message[1024];
    memset(client_message, '\0', sizeof(client_message)); //belirlenen degisken içine belirlenen sayida karakter basmaya yarar
    
    //ISTEMCIDEN GELEN MESAJI AL
    int receive_result;
    receive_result = recv(client_sock_desc, client_message, sizeof(client_message), 0); // istemcinin socketi yazılır

    if(receive_result <0 ){
        printf("HATA: MESAJ ALMA ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

        printf("HATA: MESAJ ALMA ISLEMI BASARILI! MESAJ: %s\n", client_message);

        char server_message[] = "Merhaba. İsteğiniz sunucu tarafından alindi";

        //HAZIRLANAN MESAJI GÖNDERME ISLEMI
        int send_result;
        send_result = send(client_sock_desc, server_message, strlen(server_message), 0); //sunucunun hazırladığı mesajı client socketine gönderiyoruz 

        if(send_result <0 ){
        printf("HATA: MESAJ GONDERME ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("MESAJ GONDERME ISLEMI BASARILI!\n");

    close(client_sock_desc);
    close(socket_desc);

    return EXIT_SUCCESS;
}
