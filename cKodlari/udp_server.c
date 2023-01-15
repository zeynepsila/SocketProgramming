#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>  //Linux için
#include <arpa/inet.h>   //Linux için
//#include <Winsock2.h>  //windows için
//#include <winsock.h>   //windows için

int main(void){

    //UDP SOCKETİ OLUŞTURMA ISLEMI
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //IPPROTO_UDP: UDP PROTOKOLU

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

    //UDP'DE LISTEN KULLANMIYORUZ
    //ISTEMCI ADRESI OLUSTURMA ISLEMI
    struct socksddr_in client_addr;
    socklen_t client_socklen = sizeof(client_addr);

    //ISTEMCIDEN ALINACAK MESAJ ICIN HAFIZADAN YER AYIRMA ISLEMI
    char client_message[10024];
    memset(client_message, '\0', sizeof(client_message));

    //ISTEMCIDEN GELEN MESAJI AL
    int receive_result = recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*) &client_addr, &client_socklen);

    if(receive_result < 0){
        printf("HATA: MESAJ ALMA ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }

    printf("MESAJ ALMA ISLEMI BASARILI!Mesaj: %s \n", client_message);

    //CEVAP VERME MESAJINI OLUSTUR
    char server_message[] = "Merhaba. Mesajınız bize ulastı.";

    int send_result = sendto(socket_desc, server_message, strlen(server_message), 0, (struct sockaddr*) &client_addr, client_socklen);

    if(send_result < 0){
        printf("HATA: MESAJ GONDERME ISLEMI BASARISIZ!\n");
        return EXIT_FAILURE;
    }
 
    printf("MESAJ GONDERME ISLEMI BASARILI!!\n");


    return EXIT_SUCCESS;
}